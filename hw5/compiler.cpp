#include "compiler.h"

#include <memory>
#include <utility>

Compiler::Compiler() : symbol_table(), semantic_checks(symbol_table), code_gen(semantic_checks) {

}


Compiler &Compiler::instance() {
    static Compiler compiler;
    return compiler;
}

void Compiler::ParseProgram(int lineno) {
    if (!semantic_checks.IsMainDefined()) {
        errorMainMissing();
        exit(0);
    }

    symbol_table.PopScope();
}

void Compiler::ParseFuncs(int lineno) {
    // nop
}

STypePtr Compiler::ParseFuncHead(int lineno, const STypePtr& ret_type, const STypePtr& id, const STypePtr& formals) {
    auto dynamic_cast_id = dynamic_pointer_cast<STypeString>(id);
    auto dynamic_cast_ret_type = dynamic_pointer_cast<STypeCType>(ret_type);
    auto dynamic_cast_formals = dynamic_pointer_cast<STypeArgList>(formals);

    if (symbol_table.IsSymbolDefined(dynamic_cast_id->token)) {
        errorDef(lineno, dynamic_cast_id->token);
        exit(0);
    }

    auto function_symbol = make_shared<STypeFunctionSymbol>(dynamic_cast_id->token, dynamic_cast_ret_type->general_type,
                                                            dynamic_cast_formals->arg_list);
    symbol_table.AddFunction(function_symbol);
    symbol_table.PushFunctionScope(FUNCTION_SCOPE, dynamic_cast_ret_type->general_type, function_symbol);
    for (const auto& param:function_symbol->parameters) {
        auto param_symbol = make_shared<STypeSymbol>(param);
        if (semantic_checks.IsSymbolDefined(param_symbol->name)) {
            errorDef(lineno, param_symbol->name);
            exit(0);
        }

        symbol_table.AddParam(param_symbol);
    }
    return function_symbol;
}

void Compiler::ParseFuncDecl(int lineno) {
}

STypePtr Compiler::ParseRetType(int lineno, STypePtr type) {
    return type;
}

STypeCTypePtr Compiler::ParseRetType(int lineno) {
    auto type_pointer = make_shared<STypeCType>(VOID_TYPE);
    return type_pointer;
}

STypeArgListPtr Compiler::ParseFormals(int lineno) {
    auto formals_pointer = make_shared<STypeArgList>();
    return formals_pointer;
}

STypeArgListPtr Compiler::ParseFormals(int lineno, const STypePtr& formals) {
    auto dynamic_cast_formals = dynamic_pointer_cast<STypeArgList>(formals);

    auto formals_pointer = make_shared<STypeArgList>();
    for (auto symbol_iter = dynamic_cast_formals->arg_list.rbegin();
         symbol_iter != dynamic_cast_formals->arg_list.rend(); symbol_iter++) {

        formals_pointer->arg_list.push_back(*symbol_iter);
    }
    return formals_pointer;
}

STypeArgListPtr Compiler::ParseFormalsList(int lineno, const STypePtr& formal) {
    auto dynamic_cast_formal = dynamic_pointer_cast<STypeSymbol>(formal);

    auto arg_list_pointer = make_shared<STypeArgList>();
    arg_list_pointer->arg_list.push_back(*dynamic_cast_formal);
    return arg_list_pointer;
}

STypeArgListPtr Compiler::ParseFormalsList(int lineno, const STypePtr& formal, const STypePtr& formals_list) {
    auto dynamic_cast_formals_list = dynamic_pointer_cast<STypeArgList>(formals_list);
    auto dynamic_cast_formal = dynamic_pointer_cast<STypeSymbol>(formal);

    dynamic_cast_formals_list->arg_list.push_back(*dynamic_cast_formal);
    return dynamic_cast_formals_list;
}

STypeSymbolPtr Compiler::ParseFormalDecl(int lineno, const STypePtr& type, const STypePtr& id) {
    auto dynamic_cast_type = dynamic_pointer_cast<STypeCType>(type);
    auto dynamic_cast_id = dynamic_pointer_cast<STypeString>(id);

    auto symbol_pointer = make_shared<STypeSymbol>(dynamic_cast_id->token, symbol_table.scope_stack.top()->offset,
                                                   dynamic_cast_type->general_type);
    return symbol_pointer;
}

STypeStatementPtr Compiler::ParseStatements(int lineno, STypePtr &statement) {
    // TODO all statements
    return STypeStatementPtr();
}

STypeStatementPtr Compiler::ParseStatementOfStatements(int lineno, STypePtr &statements) {
    return STypeStatementPtr();
}

STypeStatementPtr Compiler::ParseStatementType(int lineno, const STypePtr& type, const STypePtr& id) {
    auto dynamic_cast_type = dynamic_pointer_cast<STypeCType>(type);
    auto dynamic_cast_id = dynamic_pointer_cast<STypeString>(id);

    if (semantic_checks.IsSymbolDefined(dynamic_cast_id->token)) {
        errorDef(lineno, dynamic_cast_id->token);
        exit(0);
    }

    const auto symbol = make_shared<STypeSymbol>(dynamic_cast_id->token, 0, dynamic_cast_type->general_type);
    symbol_table.AddVariable(symbol);

    return code_gen.EmitStatementType(dynamic_cast_id->token);
}

STypeStatementPtr Compiler::ParseStatementTypeAssign(int lineno, const STypePtr& type, const STypePtr& id, const STypePtr& exp) {
    auto dynamic_cast_type = dynamic_pointer_cast<STypeCType>(type);
    auto dynamic_cast_id = dynamic_pointer_cast<STypeString>(id);

    if (semantic_checks.IsFunctionType(exp->general_type)) {
        auto cast_function = dynamic_pointer_cast<STypeFunctionSymbol>(exp);
        errorUndef(lineno, cast_function->name);
        exit(0);
    }

    if (!semantic_checks.IsLegalAssignTypes(dynamic_cast_type->general_type, exp->general_type)) {
        errorMismatch(lineno);
        exit(0);
    }
    if (semantic_checks.IsSymbolDefined(dynamic_cast_id->token)) {
        errorDef(lineno, dynamic_cast_id->token);
        exit(0);
    }

    const auto symbol = make_shared<STypeSymbol>(dynamic_cast_id->token, 0, dynamic_cast_type->general_type);
    symbol_table.AddVariable(symbol);


    return code_gen.EmitStatementAssign(dynamic_cast_id->token, exp);
}

STypeStatementPtr Compiler::ParseStatementAssign(int lineno, const STypePtr& id, const STypePtr& exp) {
    auto dynamic_cast_id = dynamic_pointer_cast<STypeString>(id);

    if (!semantic_checks.IsSymbolDefined(dynamic_cast_id->token)) {
        errorUndef(lineno, dynamic_cast_id->token);
        exit(0);
    }

    auto symbol_from_id = symbol_table.GetDefinedSymbol(dynamic_cast_id->token);

    if (semantic_checks.IsFunctionType(exp->general_type)) {
        auto cast_function = dynamic_pointer_cast<STypeFunctionSymbol>(exp);
        errorUndef(lineno, cast_function->name);
        exit(0);
    }

    if (semantic_checks.IsFunctionType(symbol_from_id->general_type)) {
        auto cast_function = dynamic_pointer_cast<STypeFunctionSymbol>(symbol_from_id);
        errorUndef(lineno, cast_function->name);
        exit(0);
    }

    if (!semantic_checks.IsLegalAssignTypes(symbol_from_id->general_type, exp->general_type)) {
        errorMismatch(lineno);
        exit(0);
    }

    return code_gen.EmitStatementAssign(dynamic_cast_id->token, exp);
}

STypeStatementPtr Compiler::ParseStatementCall(int lineno) {
    return code_gen.EmitStatementCall();
}

STypeStatementPtr Compiler::ParseStatementReturn(int lineno) {
    if (!semantic_checks.IsLegalReturnType(VOID_TYPE)) {
        errorMismatch(lineno);
        exit(0);
    }

    return code_gen.EmitStatementReturn();
}

STypeStatementPtr Compiler::ParseStatementReturnExp(int lineno, const STypePtr& exp) {
    if (semantic_checks.IsFunctionType(exp->general_type)) {
        auto cast_function = dynamic_pointer_cast<STypeFunctionSymbol>(exp);
        errorUndef(lineno, cast_function->name);
        exit(0);
    }

    if ((!semantic_checks.IsLegalReturnType(exp->general_type)) || (semantic_checks.IsVoidType(exp->general_type))) {
        errorMismatch(lineno);
        exit(0);
    }

    return code_gen.EmitStatementReturnExp(exp);
}

STypeStatementPtr Compiler::ParseStatementIf(int lineno) {
    return code_gen.EmitStatementIf();
}

STypeStatementPtr Compiler::ParseStatementIfElse(int lineno) {
    return code_gen.EmitStatementIfElse();
}

STypeStatementPtr Compiler::ParseStatementWhile(int lineno) {
    return code_gen.EmitStatementWhile();
}

STypeStatementPtr Compiler::ParseStatementSwitch(int lineno) {
    return code_gen.EmitStatementSwitch();
}

STypeStatementPtr Compiler::ParseStatementBreak(int lineno) {
    if (!semantic_checks.IsLegalBreak()) {
        errorUnexpectedBreak(lineno);
        exit(0);
    }

    return code_gen.EmitStatementBreak();
}

STypeStatementPtr Compiler::ParseStatementContinue(int lineno) {
    if (!semantic_checks.IsLegalContinue()) {
        errorUnexpectedContinue(lineno);
        exit(0);
    }

    return code_gen.EmitStatementContinue();
}

STypePtr Compiler::ParseCall(int lineno, const STypePtr& id, const STypePtr& exp_list) {
    auto dynamic_cast_id = dynamic_pointer_cast<STypeString>(id);

    if (!semantic_checks.IsSymbolDefined(dynamic_cast_id->token)) {
        errorUndefFunc(lineno, dynamic_cast_id->token);
        exit(0);
    }

    auto symbol_from_id = symbol_table.GetDefinedSymbol(dynamic_cast_id->token);

    if (!semantic_checks.IsFunctionType(symbol_from_id->general_type)) {
        errorUndefFunc(lineno, dynamic_cast_id->token);
        exit(0);
    }

    auto dynamic_cast_func = dynamic_pointer_cast<STypeFunctionSymbol>(symbol_from_id);
    auto dynamic_cast_exp_list = dynamic_pointer_cast<STypeExpList>(exp_list);

    auto reversed_exp_list = make_shared<STypeExpList>();
    for (auto exp_iter = dynamic_cast_exp_list->exp_list.rbegin();
         exp_iter != dynamic_cast_exp_list->exp_list.rend(); exp_iter++) {

        reversed_exp_list->exp_list.push_back(*exp_iter);
    }

    if (!semantic_checks.IsLegalCallTypes(dynamic_cast_func, reversed_exp_list)) {
        vector<string> expected_args;
        for (const auto& symbol:dynamic_cast_func->parameters) {
            expected_args.push_back(TypeToString(symbol.general_type));
        }
        errorPrototypeMismatch(lineno, dynamic_cast_id->token, expected_args);
        exit(0);
    }

    return code_gen.EmitCall(dynamic_cast_func, dynamic_cast_exp_list);
}

STypePtr Compiler::ParseCall(int lineno, const STypePtr& id) {
    auto dynamic_cast_id = dynamic_pointer_cast<STypeString>(id);

    if (!semantic_checks.IsSymbolDefined(dynamic_cast_id->token)) {
        errorUndefFunc(lineno, dynamic_cast_id->token);
        exit(0);
    }

    auto symbol_from_id = symbol_table.GetDefinedSymbol(dynamic_cast_id->token);

    if (!semantic_checks.IsFunctionType(symbol_from_id->general_type)) {
        errorUndefFunc(lineno, dynamic_cast_id->token);
        exit(0);
    }

    auto dynamic_cast_func = dynamic_pointer_cast<STypeFunctionSymbol>(symbol_from_id);
    auto empty_exp_list = make_shared<STypeExpList>();

    if (!semantic_checks.IsLegalCallTypes(dynamic_cast_func, empty_exp_list)) {
        vector<string> expected_args;
        for (const auto& symbol:dynamic_cast_func->parameters) {
            expected_args.push_back(TypeToString(symbol.general_type));
        }
        errorPrototypeMismatch(lineno, dynamic_cast_id->token, expected_args);
        exit(0);
    }

    return code_gen.EmitCall(dynamic_cast_func);
}

STypePtr Compiler::ParseExplist(int lineno, const STypePtr& exp) {
    auto exp_list_pointer = make_shared<STypeExpList>();
    exp_list_pointer->exp_list.push_back(exp);
    return exp_list_pointer;
}

STypePtr Compiler::ParseExplist(int lineno, const STypePtr& exp, const STypePtr& exp_list) {
    auto dynamic_cast_exp_list = dynamic_pointer_cast<STypeExpList>(exp_list);

    dynamic_cast_exp_list->exp_list.push_back(exp);
    return dynamic_cast_exp_list;
}

STypeCTypePtr Compiler::ParseInt(int lineno) {
    return std::make_shared<STypeCType>(INT_TYPE);
}

STypeCTypePtr Compiler::ParseByte(int lineno) {
    return std::make_shared<STypeCType>(BYTE_TYPE);
}

STypeCTypePtr Compiler::ParseBool(int lineno) {
    return std::make_shared<STypeCType>(BOOL_TYPE);
}

STypePtr Compiler::ParseParentheses(int lineno, STypePtr exp) {
    return exp;
}

STypeRegisterPtr Compiler::ParseBinop(int lineno, const STypePtr& exp1, STypePtr &binop, const STypePtr& exp2) {
    if (semantic_checks.IsFunctionType(exp1->general_type)) {
        auto cast_function = dynamic_pointer_cast<STypeFunctionSymbol>(exp1);
        errorUndef(lineno, cast_function->name);
        exit(0);
    }

    if (semantic_checks.IsFunctionType(exp2->general_type)) {
        auto cast_function = dynamic_pointer_cast<STypeFunctionSymbol>(exp2);
        errorUndef(lineno, cast_function->name);
        exit(0);
    }

    if (semantic_checks.CheckAndGetBinOpType(exp1->general_type, exp2->general_type) == ERROR_TYPE) {
        errorMismatch(lineno);
        exit(0);
    }

    // return register type
    auto dynamic_cast_binop = dynamic_pointer_cast<STypeString>(binop);
    return code_gen.EmitBinop(exp1, dynamic_cast_binop->token, exp2);
}

STypePtr Compiler::ParseID(int lineno, const STypePtr& id) {
    auto dynamic_cast_string = dynamic_pointer_cast<STypeString>(id);

    if (!symbol_table.IsSymbolDefined(dynamic_cast_string->token)) {
        errorUndef(lineno, dynamic_cast_string->token);
        exit(0);
    }

    auto id_pointer = symbol_table.GetDefinedSymbol(dynamic_cast_string->token);
    return id_pointer;
}

STypePtr Compiler::ParseCallExp(int lineno, STypePtr call_exp) {
    return call_exp;
}

STypeNumberPtr Compiler::ParseNum(int lineno, const STypePtr& num) {
    auto dynamic_cast_num = dynamic_pointer_cast<STypeNumber>(num);

    return dynamic_cast_num;
}

STypePtr Compiler::ParseNumB(int lineno, STypePtr num) {
    auto dynamic_cast_num = dynamic_pointer_cast<STypeNumber>(num);

    if (!semantic_checks.IsByteOverflow(dynamic_cast_num->token)) {
        errorByteTooLarge(lineno, to_string(dynamic_cast_num->token));
        exit(0);
    }
    num->general_type = BYTE_TYPE;
    return num;
}

STypeStringPtr Compiler::ParseString(int lineno, const STypePtr& stype_string) {
    auto dynamic_cast_string = dynamic_pointer_cast<STypeString>(stype_string);

    return dynamic_cast_string;
}

STypeBoolExpPtr Compiler::ParseTrue(int lineno) {
    // TODO: all these
    return STypeBoolExpPtr();
}

STypeBoolExpPtr Compiler::ParseFalse(int lineno) {
    return STypeBoolExpPtr();
}

STypeBoolExpPtr Compiler::ParseNot(int lineno, STypePtr bool_exp) {
    // exp can be a bool literal or an id
    if (semantic_checks.IsFunctionType(bool_exp->general_type)) {
        auto cast_function = dynamic_pointer_cast<STypeFunctionSymbol>(bool_exp);
        errorUndef(lineno, cast_function->name);
        exit(0);
    }

    if (!semantic_checks.IsBoolType(bool_exp->general_type)) {
        errorMismatch(lineno);
        exit(0);
    }

    return STypeBoolExpPtr();
}

STypeBoolExpPtr Compiler::ParseAnd(int lineno, STypePtr bool_exp1, const STypePtr& bool_exp2) {
    if (semantic_checks.IsFunctionType(bool_exp1->general_type)) {
        auto cast_function = dynamic_pointer_cast<STypeFunctionSymbol>(bool_exp1);
        errorUndef(lineno, cast_function->name);
        exit(0);
    }

    if (semantic_checks.IsFunctionType(bool_exp2->general_type)) {
        auto cast_function = dynamic_pointer_cast<STypeFunctionSymbol>(bool_exp2);
        errorUndef(lineno, cast_function->name);
        exit(0);
    }

    if (!semantic_checks.IsBoolType(bool_exp1->general_type)) {
        errorMismatch(lineno);
        exit(0);
    }

    if (!semantic_checks.IsBoolType(bool_exp2->general_type)) {
        errorMismatch(lineno);
        exit(0);
    }

    return STypeBoolExpPtr();
}

STypeBoolExpPtr Compiler::ParseOr(int lineno, STypePtr bool_exp1, const STypePtr& bool_exp2) {
    if (semantic_checks.IsFunctionType(bool_exp1->general_type)) {
        auto cast_function = dynamic_pointer_cast<STypeFunctionSymbol>(bool_exp1);
        errorUndef(lineno, cast_function->name);
        exit(0);
    }

    if (semantic_checks.IsFunctionType(bool_exp2->general_type)) {
        auto cast_function = dynamic_pointer_cast<STypeFunctionSymbol>(bool_exp2);
        errorUndef(lineno, cast_function->name);
        exit(0);
    }

    if (!semantic_checks.IsBoolType(bool_exp1->general_type)) {
        errorMismatch(lineno);
        exit(0);
    }

    if (!semantic_checks.IsBoolType(bool_exp2->general_type)) {
        errorMismatch(lineno);
        exit(0);
    }

    return STypeBoolExpPtr();
}

STypeBoolExpPtr Compiler::ParseRelOp(int lineno, const STypePtr &exp1, STypePtr &relop, const STypePtr &exp2) {
    if (semantic_checks.IsFunctionType(exp1->general_type)) {
        auto cast_function = dynamic_pointer_cast<STypeFunctionSymbol>(exp1);
        errorUndef(lineno, cast_function->name);
        exit(0);
    }

    if (semantic_checks.IsFunctionType(exp2->general_type)) {
        auto cast_function = dynamic_pointer_cast<STypeFunctionSymbol>(exp2);
        errorUndef(lineno, cast_function->name);
        exit(0);
    }

    if (!semantic_checks.IsLegalRelopTypes(exp1->general_type, exp2->general_type)) {
        errorMismatch(lineno);
        exit(0);
    }

    return code_gen.EmitRelOp(exp1, relop, exp2);
}

STypePtr Compiler::ParseCast(int lineno, const STypePtr& type, STypePtr exp) {
    auto dynamic_cast_type = dynamic_pointer_cast<STypeCType>(type);

    if (semantic_checks.IsFunctionType(exp->general_type)) {
        auto cast_function = dynamic_pointer_cast<STypeFunctionSymbol>(exp);
        errorUndef(lineno, cast_function->name);
        exit(0);
    }


    if (!semantic_checks.IsLegalCast(dynamic_cast_type->general_type, exp->general_type)) {
        errorMismatch(lineno);
        exit(0);
    }

    exp->general_type = dynamic_cast_type->general_type;
    return exp;
}

void Compiler::ParseCaseList(int lineno) {

}

void Compiler::ParseCaseDefault(int lineno) {

}

void Compiler::ParseCaseDecl(int lineno) {

}

void Compiler::ParsePushStatementScope(int lineno) {
    symbol_table.PushScope(STATEMENT_SCOPE);
}

void Compiler::ParsePushWhileScope(int lineno) {
    symbol_table.PushScope(WHILE_SCOPE);
}

void Compiler::ParsePushSwitchScope(int lineno) {
    symbol_table.PushScope(SWITCH_SCOPE);
}

void Compiler::ParsePopScope(int lineno) {
    symbol_table.PopScope();
}

void Compiler::ParseCheckSwitchExp(int lineno, const STypePtr& num_exp) {
    if (semantic_checks.IsFunctionType(num_exp->general_type)) {
        auto cast_function = dynamic_pointer_cast<STypeFunctionSymbol>(num_exp);
        errorUndef(lineno, cast_function->name);
        exit(0);
    }

    if (!semantic_checks.IsLegalAssignTypes(INT_TYPE, num_exp->general_type)) {
        errorMismatch(lineno);
        exit(0);
    }
}

void Compiler::ParseCheckBool(int lineno, const STypePtr& bool_exp) {
    if (semantic_checks.IsFunctionType(bool_exp->general_type)) {
        auto cast_function = dynamic_pointer_cast<STypeFunctionSymbol>(bool_exp);
        errorUndef(lineno, cast_function->name);
        exit(0);
    }

    if (!semantic_checks.IsBoolType(bool_exp->general_type)) {
        errorMismatch(lineno);
        exit(0);
    }
}

STypeStatementPtr Compiler::ParseStatements(int lineno, STypePtr &statements, STypePtr &statement) {
    // TODO
    return STypeStatementPtr();
}
