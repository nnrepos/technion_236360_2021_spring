#include "code_gen.h"

#include <utility>

CodeGen::CodeGen(SemanticChecks &semantic_ref) : register_count(0), code_buffer(), semantic_ref(semantic_ref) {
    EmitGlobalFunctions();
}

register_name CodeGen::GenRegister() {
    register_name ret;
    return (ret + "%r" + to_string(register_count++));
}

void CodeGen::EmitGlobalFunctions() {
    // printf
    code_buffer.emitGlobal("declare i32 @printf(i8*, ...)");

    // exit
    code_buffer.emitGlobal("declare void @exit(i32)");

    // print
    code_buffer.emitGlobal(R"(@.str_specifier = constant [4 x i8] c"%s\0A\00")");
    code_buffer.emitGlobal("define void @print(i8*) {");
    code_buffer.emitGlobal("    %spec_ptr = getelementptr [4 x i8], [4 x i8]* @.str_specifier, i32 0, i32 0");
    code_buffer.emitGlobal("    call i32 (i8*, ...) @printf(i8* %spec_ptr, i8* %0)");
    code_buffer.emitGlobal("    ret void");
    code_buffer.emitGlobal("}");

    // printi
    code_buffer.emitGlobal(R"(@.int_specifier = constant [4 x i8] c"%d\0A\00")");
    code_buffer.emitGlobal("define void @printi(i32) {");
    code_buffer.emitGlobal("    %spec_ptr = getelementptr [4 x i8], [4 x i8]* @.int_specifier, i32 0, i32 0");
    code_buffer.emitGlobal("    call i32 (i8*, ...) @printf(i8* %spec_ptr, i32 %0)");
    code_buffer.emitGlobal("    ret void");
    code_buffer.emitGlobal("}");

    // zero
    code_buffer.emitGlobal(R"(@err_zero = constant [23 x i8] c"Error division by zero\00")");

}

STypeRegisterPtr CodeGen::EmitBinop(const STypePtr &exp1, string binop, const STypePtr &exp2) {
    auto dynamic_cast_reg_exp1 = dynamic_pointer_cast<STypeRegister>(exp1);
    auto dynamic_cast_num_exp1 = dynamic_pointer_cast<STypeNumber>(exp1);
    auto dynamic_cast_reg_exp2 = dynamic_pointer_cast<STypeRegister>(exp2);
    auto dynamic_cast_num_exp2 = dynamic_pointer_cast<STypeNumber>(exp2);

    auto reg_result = make_shared<STypeRegister>(GenRegister(), INT_TYPE);

    if (binop == "/") {
        EmitCheckDivZero(exp2);
    }

    string binop_str = reg_result->reg_name + " = ";
    switch (binop[0]) {
        case '+':
            binop_str += "add ";
            break;
        case '-':
            binop_str += "sub ";
            break;
        case '*':
            binop_str += "smul ";
            break;
        case '/':
            binop_str += "sdiv ";
            break;
    }

    // all types are i32
    binop_str += "i32 ";

    // TODO: test dynamic_cast_string later
    if (dynamic_cast_reg_exp1) {
        binop_str += dynamic_cast_reg_exp1->reg_name;
    } else {
        binop_str += to_string(dynamic_cast_num_exp1->token);
    }

    binop_str += ", ";

    if (dynamic_cast_reg_exp2) {
        binop_str += dynamic_cast_reg_exp2->reg_name;
    } else {
        binop_str += to_string(dynamic_cast_num_exp2->token);
    }

    code_buffer.emit(binop_str);

    if (semantic_ref.CheckAndGetBinOpType(exp1->general_type, exp2->general_type) == BYTE_TYPE) {
        // byte < 256
        auto reg_old_result = reg_result->reg_name;
        reg_result->reg_name = GenRegister();
        code_buffer.emit(reg_result->reg_name + " = and i32 " + reg_old_result + ", 255");
    }

    return reg_result;
}

void CodeGen::EmitCheckDivZero(const STypePtr &exp) {
    auto dynamic_cast_reg_exp = dynamic_pointer_cast<STypeRegister>(exp);
    auto dynamic_cast_num_exp = dynamic_pointer_cast<STypeNumber>(exp);

    auto is_zero = GenRegister();
    auto err_str = GenRegister();

    if (dynamic_cast_reg_exp) {
        code_buffer.emit(is_zero + " = icmp eq i32 " + dynamic_cast_reg_exp->reg_name + ", 0");
    } else {
        code_buffer.emit(is_zero + " = icmp eq i32 " + to_string(dynamic_cast_num_exp->token) + ", 0");
    }

    auto bp_zero_and_non = code_buffer.emit("br i1 " + is_zero + ", label @, label @");
    auto label_err_zero = code_buffer.genLabel("_err_zero");
    vector<pair<int, BranchLabelIndex>> bp_zero_vec;
    bp_zero_vec.emplace_back(bp_zero_and_non, FIRST);
    code_buffer.bpatch(bp_zero_vec, label_err_zero);

    code_buffer.emit(err_str + " = getelementptr [23 x i8], [23 x i8]* @err_zero, i32 0, i32 0");
    code_buffer.emit("call void (i8*) @print(i8* " + err_str + ")");
    code_buffer.emit("call void (i32) @exit(i32 0)");
    code_buffer.emit("unreachable");

    auto label_non_zero = code_buffer.genLabel("_non_zero");
    vector<pair<int, BranchLabelIndex>> bp_non_vec;
    bp_non_vec.emplace_back(bp_zero_and_non, SECOND);
    code_buffer.bpatch(bp_non_vec, label_non_zero);
}

STypeRegisterPtr CodeGen::EmitCall(const STypeFunctionSymbolPtr &func, const STypeExpListPtr &exp_list) {
    auto reg_result = make_shared<STypeRegister>(GenRegister(), func->ret_type);
    string out_str;

    if (func->ret_type != VOID_TYPE) {
        out_str += reg_result->reg_name + " = ";
    }

    string llvm_type = GetLLVMType(func->ret_type);
    out_str += llvm_type + " @" + func->name + "(";

    for (size_t i = 0; i < exp_list->exp_list.size(); ++i) {
        if (i > 0) {
            out_str += ", ";
        }
        out_str += GetNonBoolExpString(exp_list->exp_list[i]);
    }
    out_str += ")";

    code_buffer.emit(out_str);
    return reg_result;
}

STypeRegisterPtr CodeGen::EmitCall(const STypeFunctionSymbolPtr &func) {
    auto reg_result = make_shared<STypeRegister>(GenRegister(), func->ret_type);
    string out_str;

    if (func->ret_type != VOID_TYPE) {
        out_str += reg_result->reg_name + " = ";
    }

    string llvm_type = GetLLVMType(func->ret_type);

    out_str += llvm_type + " @" + func->name + "()";

    code_buffer.emit(out_str);
    return reg_result;
}

string CodeGen::GetLLVMType(const Type &type) const {
    string llvm_type;
    switch (type) {
        case VOID_TYPE:
            llvm_type = "void";
            break;
        case STRING_TYPE:
            llvm_type = "i8*";
            break;
        default:
            llvm_type = "i32";
            break;
    }
    return llvm_type;
}

string CodeGen::GetNonBoolExpString(const STypePtr& exp) {
    auto dynamic_cast_num_exp = dynamic_pointer_cast<STypeNumber>(exp);
    auto dynamic_cast_reg_exp = dynamic_pointer_cast<STypeRegister>(exp);
    auto dynamic_cast_str_exp = dynamic_pointer_cast<STypeString>(exp);
    auto dynamic_cast_sym_exp = dynamic_pointer_cast<STypeSymbol>(exp);


    if (dynamic_cast_num_exp) {
        // todo
        cout << "GOT NUM\n";
        return to_string(dynamic_cast_num_exp->token);
    } else if (dynamic_cast_reg_exp) {
        cout << "GOT REG\n";
        return dynamic_cast_reg_exp->reg_name;
    } else if (dynamic_cast_str_exp) {
        cout << "GOT STR\n";
        return dynamic_cast_str_exp->token;
    } else if (dynamic_cast_sym_exp) {
        cout << "GOT SYM\n";
        return OffsetToRegister(dynamic_cast_sym_exp->offset);
    } else {
        assert(false);
    }
}

string CodeGen::OffsetToRegister(int offset) {
    // TODO: handle args and local vars
    string ret = "%";
    return (ret + to_string(offset));
}

void CodeGen::EmitProgram() {
    cout << "code starts here:\n";
    code_buffer.printGlobalBuffer();
    code_buffer.printCodeBuffer();
}

STypeBoolExpPtr CodeGen::EmitRelOp(const STypePtr& exp1, STypePtr &relop, const STypePtr& exp2) {
    auto exp1_value = GetNonBoolExpString(exp1);
    auto exp2_value = GetNonBoolExpString(exp2);

    auto reg_icmp = GenRegister();
    string icmp_string(reg_icmp + " = icmp ");

    auto dynamic_cast_relop = dynamic_pointer_cast<STypeString>(relop);
    auto relop_str = dynamic_cast_relop->token;

    if (relop_str == "<") {
        icmp_string += "slt";
    } else if (relop_str == ">") {
        icmp_string += "sgt";
    } else if (relop_str == "<=") {
        icmp_string += "sle";
    } else if (relop_str == ">=") {
        icmp_string += "sge";
    } else if (relop_str == "==") {
        icmp_string += "eq";
    } else if (relop_str == "!=") {
        icmp_string += "ne";
    } else {
        assert(false);
    }

    icmp_string += " i32 " + exp1_value + ", " + exp2_value;
    code_buffer.emit(icmp_string);
    auto branch_addr = code_buffer.emit("br i1 " + reg_icmp + ", label @, label @");

    auto true_list = CodeBuffer::makelist({branch_addr, FIRST});
    auto false_list = CodeBuffer::makelist({branch_addr, SECOND});

    return make_shared<STypeBoolExp>(true_list,false_list);
}

STypeStatementPtr CodeGen::EmitStatementType(string id) {
    auto symbol = semantic_ref.table_ref.GetDefinedSymbol(id);
    auto statement = make_shared<STypeStatement>(branch_list());

    // create default value and store in stack
    // r = 0+0
    auto reg_default_value = GenRegister();
    code_buffer.emit(reg_default_value + " = add i32 0, 0");

    EmitStoreVar(symbol->offset, reg_default_value);

    return statement;
}

STypeStatementPtr CodeGen::EmitStatementAssign(string id, const STypePtr& exp) {
    auto symbol = semantic_ref.table_ref.GetDefinedSymbol(id);
    auto statement = make_shared<STypeStatement>(branch_list());
    auto reg_result = GenRegister();

    if (exp->general_type == BOOL_TYPE){
        auto dynamic_cast_bool_exp = dynamic_pointer_cast<STypeBoolExp>(exp);

        // create phi junction
        auto true_label = code_buffer.genLabel("_assign_true");
        auto bp_true = code_buffer.emit("br label @");
        auto false_label = code_buffer.genLabel("_assign_false");
        auto bp_false = code_buffer.emit("br label @");
        auto assign_label = code_buffer.genLabel("_assign_final");

        auto assign_true_list = CodeBuffer::makelist(branch_pair(bp_true, FIRST));
        auto assign_false_list = CodeBuffer::makelist(branch_pair (bp_false, FIRST));

        code_buffer.bpatch(dynamic_cast_bool_exp->true_list, true_label);
        code_buffer.bpatch(dynamic_cast_bool_exp->false_list, false_label);
        code_buffer.bpatch(assign_true_list, assign_label);
        code_buffer.bpatch(assign_false_list, assign_label);

        code_buffer.emit(reg_result + " = phi i32 [1, %" + true_label + "], [0, %" + false_label + "]");

    } else{
        auto exp_str = GetNonBoolExpString(exp);
        code_buffer.emit(reg_result + " = add i32 " + exp_str + ", 0");
    }

    // store and return
    EmitStoreVar(symbol->offset, reg_result);

    return statement;
}

STypePtr CodeGen::EmitFuncHead() {
    // TODO
    // emit define
    string emit_string("define ");

    // allocate stack
    stack_register = GenRegister();
    code_buffer.emit(stack_register + " = alloca i32, i32 " + to_string(STACK_SIZE));

    return STypePtr();
}

void CodeGen::EmitStoreVar(int offset, const register_name& reg_to_store) {
    assert(!stack_register.empty());
    auto reg_pointer_to_stack = GenRegister();

    if (offset >= 0) {
        // get address on stack
        code_buffer.emit(reg_pointer_to_stack + " = getelementptr i32, i32* " + stack_register +
                         ", i32 " + to_string(offset));

        // store in stack
        code_buffer.emit("store i32 " + reg_to_store + ", i32* " + reg_pointer_to_stack);
    }
}

STypeStatementPtr CodeGen::EmitStatementAssign(STypePtr id, STypePtr exp) {
    return STypeStatementPtr();
}

STypeStatementPtr CodeGen::EmitStatementCall() {
    return STypeStatementPtr();
}

STypeStatementPtr CodeGen::EmitStatementReturn() {
    return STypeStatementPtr();
}

STypeStatementPtr CodeGen::EmitStatementReturnExp(STypePtr exp) {
    return STypeStatementPtr();
}

STypeStatementPtr CodeGen::EmitStatementIf() {
    return STypeStatementPtr();
}

STypeStatementPtr CodeGen::EmitStatementIfElse() {
    return STypeStatementPtr();
}

STypeStatementPtr CodeGen::EmitStatementWhile() {
    return STypeStatementPtr();
}

STypeStatementPtr CodeGen::EmitStatementBreak() {
    return STypeStatementPtr();
}

STypeStatementPtr CodeGen::EmitStatementContinue() {
    return STypeStatementPtr();
}

STypeStatementPtr CodeGen::EmitStatementSwitch() {
    return STypeStatementPtr();
}

STypePtr CodeGen::EmitFuncDecl() {
    return STypePtr();
}

STypeBoolExpPtr CodeGen::EmitTrue() {
    return STypeBoolExpPtr();
}

STypeBoolExpPtr CodeGen::EmitFalse() {
    return STypeBoolExpPtr();
}

STypeBoolExpPtr CodeGen::EmitNot(STypePtr bool_exp) {
    return STypeBoolExpPtr();
}

STypeBoolExpPtr CodeGen::EmitAnd(STypePtr bool_exp1, STypePtr bool_exp2) {
    return STypeBoolExpPtr();
}

STypeBoolExpPtr CodeGen::EmitOr(STypePtr bool_exp1, STypePtr bool_exp2) {
    return STypeBoolExpPtr();
}

STypeRegisterPtr CodeGen::EmitCast(STypePtr type, STypePtr exp) {
    return STypeRegisterPtr();
}

void CodeGen::EmitCaseList() {

}

void CodeGen::EmitCaseDefault() {

}

void CodeGen::EmitCaseDecl() {

}
