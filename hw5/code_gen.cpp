#include "code_gen.h"

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

STypeRegisterPtr CodeGen::EmitBinop(const STypePtr& exp1, string binop, const STypePtr& exp2) {
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

void CodeGen::EmitCheckDivZero(const STypePtr& exp) {
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

STypeRegisterPtr CodeGen::EmitCall(const STypeFunctionSymbolPtr& func, const STypeExpListPtr& exp_list) {
    auto reg_result = make_shared<STypeRegister>(GenRegister(), func->ret_type);
    string out_str;

    if(func->ret_type != VOID_TYPE)
    {
        out_str += reg_result->reg_name + " = ";
    }

    switch(func->ret_type){
        case VOID_TYPE:
            out_str += "void ";
            break;
        case STRING_TYPE:
            out_str += "i8* ";
            break;
        default:
            out_str += "i32 ";
            break;
    }

    out_str += "@" + func->name + "(";
    for (size_t i=0; i<exp_list->exp_list.size(); ++i){
        if (i>0){
            out_str += ", ";
        }
        out_str += GetExpString(exp_list->exp_list[i]);
    }
    out_str += ")";

    code_buffer.emit(out_str);
    return reg_result;
}

STypeRegisterPtr CodeGen::EmitCall(const STypeFunctionSymbolPtr& func) {
    auto reg_result = make_shared<STypeRegister>(GenRegister(), func->ret_type);
    string out_str;

    if(func->ret_type != VOID_TYPE)
    {
        out_str += reg_result->reg_name + " = ";
    }

    switch(func->ret_type){
        case VOID_TYPE:
            out_str += "void ";
            break;
        case STRING_TYPE:
            out_str += "i8* ";
            break;
        default:
            out_str += "i32 ";
            break;
    }

    out_str += "@" + func->name + "()";

    code_buffer.emit(out_str);
    return reg_result;
}

string CodeGen::GetExpString(STypePtr exp) {
    auto dynamic_cast_num_exp = dynamic_pointer_cast<STypeNumber>(exp);
    auto dynamic_cast_reg_exp = dynamic_pointer_cast<STypeRegister>(exp);
    auto dynamic_cast_str_exp = dynamic_pointer_cast<STypeString>(exp);
    auto dynamic_cast_sym_exp = dynamic_pointer_cast<STypeSymbol>(exp);


    if (dynamic_cast_num_exp){
        // todo
        cout << "GOT NUM\n";
        return to_string(dynamic_cast_num_exp->token);
    }else if (dynamic_cast_reg_exp){
        cout << "GOT REG\n";
        return dynamic_cast_reg_exp->reg_name;
    } else if (dynamic_cast_str_exp){
        cout << "GOT STR\n";
        return dynamic_cast_str_exp->token;
    } else if (dynamic_cast_sym_exp){
        cout << "GOT SYM\n";
        return OffsetToRegister(dynamic_cast_sym_exp->offset);
    } else{
        assert(false);
    }
}

string CodeGen::OffsetToRegister(int offset) {
    // TODO: handle args and local vars
    string ret = "%";
    return (ret+to_string(offset));
}
