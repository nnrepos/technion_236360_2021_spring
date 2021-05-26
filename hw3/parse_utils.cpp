#include "parse_utils.h"

#include <memory>

ParseUtils::ParseUtils() : symbol_table(), semantic_checks(symbol_table) {

}


ParseUtils &ParseUtils::instance() {
    static ParseUtils parse_utils;
    return parse_utils;
}

void ParseUtils::ParseProgram(int lineno) {
    if (!semantic_checks.IsMainDefined()) {
        errorMainMissing();
        exit(0);
    }
}

void ParseUtils::ParseFuncs(int lineno) {
    // nop
}

STypePtr ParseUtils::ParseFuncHead(int lineno, STypePtr ret_type, STypePtr id, STypePtr formals) {
    auto dynamic_cast_id = dynamic_pointer_cast<STypeString>(id);
    auto dynamic_cast_ret_type = dynamic_pointer_cast<STypeCType>(ret_type);
    auto dynamic_cast_formals = dynamic_pointer_cast<STypeArgList>(formals);

    if (symbol_table.IsSymbolDefined(dynamic_cast_id->token)) {
        errorDef(lineno, dynamic_cast_id->token);
        exit(0);
    }

    symbol_table.PushFunctionScope(FUNCTION_SCOPE, ret_type->general_type);
    auto function_symbol = make_shared<STypeFunctionSymbol>(dynamic_cast_id->token, dynamic_cast_ret_type->type, 0,
                                                            dynamic_cast_formals->arg_list);
    return function_symbol;
}

void ParseUtils::ParseFuncDecl(int lineno, STypePtr function_head) {
    auto dynamic_cast_function = dynamic_pointer_cast<STypeFunctionSymbol>(function_head);
    symbol_table.AddFunction(dynamic_cast_function);
}

STypePtr ParseUtils::ParseRetType(int lineno, STypePtr type) {
    return type;
}

STypeCTypePtr ParseUtils::ParseRetType(int lineno) {
    auto type_pointer = make_shared<STypeCType>(VOID_TYPE);
    return type_pointer;
}

STypeArgListPtr ParseUtils::ParseFormals(int lineno) {
    auto formals_pointer = make_shared<STypeArgList>();
    return formals_pointer;
}

STypeArgListPtr ParseUtils::ParseFormals(int lineno, STypePtr formals) {
    auto dynamic_cast_formals = dynamic_pointer_cast<STypeArgList>(formals);

    auto formals_pointer = make_shared<STypeArgList>();
    for (auto symbol:dynamic_cast_formals->arg_list) {
        formals_pointer->arg_list.push_back(symbol);
    }
    return formals_pointer;
}

STypeArgListPtr ParseUtils::ParseFormalsList(int lineno, STypePtr formal) {
    auto dynamic_cast_formal = dynamic_pointer_cast<STypeSymbol>(formal);

    auto arg_list_pointer = make_shared<STypeArgList>();
    arg_list_pointer->arg_list.push_back(*dynamic_cast_formal);
    return arg_list_pointer;
}

STypeArgListPtr ParseUtils::ParseFormalsList(int lineno, STypePtr formal, STypePtr formals_list) {
    auto dynamic_cast_formals_list = dynamic_pointer_cast<STypeArgList>(formals_list);
    auto dynamic_cast_formal = dynamic_pointer_cast<STypeSymbol>(formal);

    dynamic_cast_formals_list->arg_list.push_back(*dynamic_cast_formal);
    return dynamic_cast_formals_list;
}

STypeSymbolPtr ParseUtils::ParseFormalDecl(int lineno, STypePtr type, STypePtr id) {
    auto dynamic_cast_type = dynamic_pointer_cast<STypeCType>(type);
    auto dynamic_cast_id = dynamic_pointer_cast<STypeString>(id);

    auto symbol_pointer = make_shared<STypeSymbol>(dynamic_cast_id->token, symbol_table.scope_stack.top()->offset,
                                                   dynamic_cast_type->type);
    return symbol_pointer;
}

void ParseUtils::ParseStatements(int lineno) {

}

void ParseUtils::ParseStatements(int lineno, STypePtr x) {

}

void ParseUtils::ParseStatementOfStatements(int lineno) {

}

void ParseUtils::ParseStatementType(int lineno, STypePtr type, STypePtr id) {
    auto dynamic_cast_type = dynamic_pointer_cast<STypeCType>(type);
    auto dynamic_cast_id = dynamic_pointer_cast<STypeString>(id);

    if (semantic_checks.IsSymbolDefined(dynamic_cast_id->token)) {
        errorDef(lineno, dynamic_cast_id->token);
        exit(0);
    }
    const auto symbol = make_shared<STypeSymbol>(dynamic_cast_id->token, 0, dynamic_cast_type->type);
    symbol_table.AddVariable(symbol);
}

void ParseUtils::ParseStatementTypeAssign(int lineno, STypePtr type, STypePtr id, STypePtr exp) {
    auto dynamic_cast_type = dynamic_pointer_cast<STypeCType>(type);
    auto dynamic_cast_id = dynamic_pointer_cast<STypeString>(id);

    if (!semantic_checks.IsLegalAssignTypes(dynamic_cast_type->type, exp->general_type)) {
        errorMismatch(lineno);
        exit(0);
    }
    if (semantic_checks.IsSymbolDefined(dynamic_cast_id->token)) {
        errorDef(lineno, dynamic_cast_id->token);
        exit(0);
    }
    const auto symbol = make_shared<STypeSymbol>(dynamic_cast_id->token, 0, dynamic_cast_type->type);
    symbol_table.AddVariable(symbol);
}

void ParseUtils::ParseStatementAssign(int lineno, STypePtr id, STypePtr exp) {
    auto dynamic_cast_id = dynamic_pointer_cast<STypeString>(id);

    if (!semantic_checks.IsSymbolDefined(dynamic_cast_id->token)) {
        errorUndef(lineno, dynamic_cast_id->token);
        exit(0);
    }

    auto symbol_from_id = symbol_table.GetDefinedSymbol(dynamic_cast_id->token);

    if (!semantic_checks.IsLegalAssignTypes(symbol_from_id->general_type, exp->general_type)) {
        errorMismatch(lineno);
        exit(0);
    }
}

void ParseUtils::ParseStatementCall(int lineno) {

}

void ParseUtils::ParseStatementReturn(int lineno) {
    if (!semantic_checks.IsLegalReturnType(VOID_TYPE)){
        errorMismatch(lineno);
        exit(0);
    }
}

void ParseUtils::ParseStatementReturnExp(int lineno, STypePtr exp) {
    if (!semantic_checks.IsLegalReturnType(exp->general_type)){
        errorMismatch(lineno);
        exit(0);
    }
}

void ParseUtils::ParseStatementIf(int lineno, STypePtr exp) {
    if (!semantic_checks.IsBoolType(exp->general_type)){
        errorMismatch(lineno);
        exit(0);
    }
}

void ParseUtils::ParseStatementIfElse(int lineno, STypePtr exp) {
    if (!semantic_checks.IsBoolType(exp->general_type)){
        errorMismatch(lineno);
        exit(0);
    }
}

void ParseUtils::ParseStatementWhile(int lineno, STypePtr exp) {
    if (!semantic_checks.IsBoolType(exp->general_type)){
        errorMismatch(lineno);
        exit(0);
    }
}

void ParseUtils::ParseStatementSwitch(int lineno, STypePtr exp) {
    if (!semantic_checks.IsLegalAssignTypes(INT_TYPE,exp->general_type)){
        errorMismatch(lineno);
        exit(0);
    }
}

void ParseUtils::ParseStatementBreak(int lineno) {
    if (!semantic_checks.IsLegalBreakContinue()){
        errorUnexpectedBreak(lineno);
        exit(0);
    }
}

void ParseUtils::ParseStatementContinue(int lineno) {
    if (!semantic_checks.IsLegalBreakContinue()){
        errorUnexpectedContinue(lineno);
        exit(0);
    }
}

STypePtr ParseUtils::ParseCall(int lineno, STypePtr id, STypePtr exp_list) {
    auto dynamic_cast_id = dynamic_pointer_cast<STypeString>(id);

    if (!semantic_checks.IsSymbolDefined(dynamic_cast_id->token)) {
        errorUndefFunc(lineno, dynamic_cast_id->token);
        exit(0);
    }

    auto symbol_from_id = symbol_table.GetDefinedSymbol(dynamic_cast_id->token);

    if (!semantic_checks.IsFunctionType(symbol_from_id->general_type)){
        errorUndefFunc(lineno, dynamic_cast_id->token);
        exit(0);
    }

    auto dynamic_cast_func = dynamic_pointer_cast<STypeFunctionSymbol>(symbol_from_id);
    auto dynamic_cast_exp_list = dynamic_pointer_cast<STypeExpList>(exp_list);

    if (!semantic_checks.IsLegalCallTypes(dynamic_cast_func,dynamic_cast_exp_list)){
        vector<string> expected_args;
        for(auto symbol:dynamic_cast_func->parameters){
            expected_args.push_back(TypeToString(symbol.general_type));
        }
        errorPrototypeMismatch(lineno, dynamic_cast_id->token, expected_args);
        exit(0);
    }

    auto ret_type_pointer = make_shared<STypeBase>(dynamic_cast_func->ret_type);
    return ret_type_pointer;
}

STypePtr ParseUtils::ParseCall(int lineno, STypePtr id) {
    auto dynamic_cast_id = dynamic_pointer_cast<STypeString>(id);

    if (!semantic_checks.IsSymbolDefined(dynamic_cast_id->token)) {
        errorUndefFunc(lineno, dynamic_cast_id->token);
        exit(0);
    }

    auto symbol_from_id = symbol_table.GetDefinedSymbol(dynamic_cast_id->token);

    if (!semantic_checks.IsFunctionType(symbol_from_id->general_type)){
        errorUndefFunc(lineno, dynamic_cast_id->token);
        exit(0);
    }

    auto dynamic_cast_func = dynamic_pointer_cast<STypeFunctionSymbol>(symbol_from_id);
    auto empty_exp_list = STypeExpListPtr();

    if (!semantic_checks.IsLegalCallTypes(dynamic_cast_func,empty_exp_list)){
        vector<string> expected_args;
        for(auto symbol:dynamic_cast_func->parameters){
            expected_args.push_back(TypeToString(symbol.general_type));
        }
        errorPrototypeMismatch(lineno, dynamic_cast_id->token, expected_args);
        exit(0);
    }

    auto ret_type_pointer = make_shared<STypeBase>(dynamic_cast_func->ret_type);
    return ret_type_pointer;
}

STypePtr ParseUtils::ParseExplist(int lineno, STypePtr exp) {
    auto exp_list_pointer = make_shared<STypeExpList>();
    exp_list_pointer->exp_list.push_back(*exp);
    return exp_list_pointer;
}

STypePtr ParseUtils::ParseExplist(int lineno, STypePtr exp, STypePtr exp_list) {
    auto dynamic_cast_exp_list = dynamic_pointer_cast<STypeExpList>(exp_list);

    dynamic_cast_exp_list->exp_list.push_back(*exp);
    return dynamic_cast_exp_list;
}

STypeCTypePtr ParseUtils::ParseInt(int lineno) {
    return std::make_shared<STypeCType>(INT_TYPE);
}

STypeCTypePtr ParseUtils::ParseByte(int lineno) {
    return std::make_shared<STypeCType>(BYTE_TYPE);
}

STypeCTypePtr ParseUtils::ParseBool(int lineno) {
    return std::make_shared<STypeCType>(BOOL_TYPE);
}

STypePtr ParseUtils::ParseParentheses(int lineno, STypePtr exp) {
    return exp;
}

STypePtr ParseUtils::ParseBinop(int lineno, STypePtr exp1, STypePtr exp2) {
    if (semantic_checks.CheckAndGetBinOpType(exp1->general_type, exp2->general_type) == OTHER_TYPE){
        errorMismatch(lineno);
        exit(0);
    }
    return exp1;
}

STypeStringPtr ParseUtils::ParseID(int lineno, STypePtr id) {
    auto string_pointer = dynamic_pointer_cast<STypeString>(id);
    return string_pointer;
}

STypePtr ParseUtils::ParseCallExp(int lineno, STypePtr call_exp) {
    return call_exp;
}

STypeNumberPtr ParseUtils::ParseNum(int lineno, STypePtr num) {
    auto dynamic_cast_num = dynamic_pointer_cast<STypeNumber>(num);

    return dynamic_cast_num;
}

STypePtr ParseUtils::ParseNumB(int lineno, STypePtr num) {
    auto dynamic_cast_num = dynamic_pointer_cast<STypeNumber>(num);

    if (!semantic_checks.IsByteOverflow(dynamic_cast_num->token)) {
        errorByteTooLarge(lineno, to_string(dynamic_cast_num->token));
        exit(0);
    }
    num->general_type = BYTE_TYPE;
    return num;
}

STypePtr ParseUtils::ParseString(int lineno, STypePtr strrrrrraaa) {
    return STypePtr();
}

STypeBoolPtr ParseUtils::ParseTrue(int lineno) {
    auto bool_pointer = make_shared<STypeBool>(true);
    return bool_pointer;
}

STypeBoolPtr ParseUtils::ParseFalse(int lineno) {
    auto bool_pointer = make_shared<STypeBool>(false);
    return bool_pointer;
}

STypeBoolPtr ParseUtils::ParseNot(int lineno, STypePtr bool_exp) {
    auto dynamic_cast_bool_exp = dynamic_pointer_cast<STypeBool>(bool_exp);

    if (!semantic_checks.IsBoolType(dynamic_cast_bool_exp->general_type)){
        errorMismatch(lineno);
        exit(0);
    }

    dynamic_cast_bool_exp->token = !dynamic_cast_bool_exp->token;
    return dynamic_cast_bool_exp;
}

STypeBoolPtr ParseUtils::ParseAnd(int lineno, STypePtr bool_exp1, STypePtr bool_exp2) {
    auto dynamic_cast_bool_exp1 = dynamic_pointer_cast<STypeBool>(bool_exp1);
    auto dynamic_cast_bool_exp2 = dynamic_pointer_cast<STypeBool>(bool_exp2);

    if (!semantic_checks.IsBoolType(dynamic_cast_bool_exp1->general_type)){
        errorMismatch(lineno);
        exit(0);
    }

    if (!semantic_checks.IsBoolType(dynamic_cast_bool_exp2->general_type)){
        errorMismatch(lineno);
        exit(0);
    }

    dynamic_cast_bool_exp1->token = (dynamic_cast_bool_exp1->token && dynamic_cast_bool_exp2->token);
    return dynamic_cast_bool_exp1;
}

STypeBoolPtr ParseUtils::ParseOr(int lineno, STypePtr bool_exp1, STypePtr bool_exp2) {
    auto dynamic_cast_bool_exp1 = dynamic_pointer_cast<STypeBool>(bool_exp1);
    auto dynamic_cast_bool_exp2 = dynamic_pointer_cast<STypeBool>(bool_exp2);

    if (!semantic_checks.IsBoolType(dynamic_cast_bool_exp1->general_type)){
        errorMismatch(lineno);
        exit(0);
    }

    if (!semantic_checks.IsBoolType(dynamic_cast_bool_exp2->general_type)){
        errorMismatch(lineno);
        exit(0);
    }

    dynamic_cast_bool_exp1->token = (dynamic_cast_bool_exp1->token || dynamic_cast_bool_exp2->token);
    return dynamic_cast_bool_exp1;
}

STypeBoolPtr ParseUtils::ParseRelOp(int lineno, STypePtr exp1, STypePtr exp2) {
    if (!semantic_checks.IsLegalRelopTypes(exp1->general_type, exp2->general_type)){
        errorMismatch(lineno);
        exit(0);
    }

    auto bool_pointer = make_shared<STypeBool>(true);
    return bool_pointer;
}

STypePtr ParseUtils::ParseCast(int lineno, STypePtr type, STypePtr exp) {
    auto dynamic_cast_type = dynamic_pointer_cast<STypeCType>(type);

    if(!semantic_checks.IsLegalCast(dynamic_cast_type->type, exp->general_type)){
        errorMismatch(lineno);
        exit(0);
    }

    exp->general_type = dynamic_cast_type->type;
    return exp;
}

void ParseUtils::ParseCaseList(int lineno) {

}

void ParseUtils::ParseCaseDefault(int lineno) {

}

void ParseUtils::ParseCaseDecl(int lineno) {

}

void ParseUtils::ParsePushStatementScope(int lineno) {
    symbol_table.PushScope(STATEMENT_SCOPE);
}

void ParseUtils::ParsePushWhileScope(int lineno) {
    symbol_table.PushScope(WHILE_SCOPE);
}

void ParseUtils::ParsePushSwitchScope(int lineno) {
    symbol_table.PushScope(SWITCH_SCOPE);
}

void ParseUtils::ParsePopScope(int lineno) {
    symbol_table.PopScope();
}
