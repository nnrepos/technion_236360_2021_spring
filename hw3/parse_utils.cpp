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
    auto casted_id = dynamic_pointer_cast<STypeString>(id);
    auto casted_ret_type = dynamic_pointer_cast<STypeCType>(ret_type);
    auto casted_formals = dynamic_pointer_cast<STypeArgList>(formals);

    if (symbol_table.IsSymbolDefined(casted_id->token)) {
        errorDef(lineno, casted_id->token);
        exit(0);
    }

    symbol_table.PushFunctionScope(FUNCTION_SCOPE, ret_type->general_type);
    auto function_symbol = make_shared<STypeFunctionSymbol>(casted_id->token, casted_ret_type->type, 0,
                                                            casted_formals->arg_list);
    return function_symbol;
}

void ParseUtils::ParseFuncDecl(int lineno, STypePtr function_head) {
    auto casted_function = dynamic_pointer_cast<STypeFunctionSymbol>(function_head);
    symbol_table.AddFunction(casted_function);
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
    auto casted_formals = dynamic_pointer_cast<STypeArgList>(formals);

    auto formals_pointer = make_shared<STypeArgList>();
    for (auto symbol:casted_formals->arg_list) {
        formals_pointer->arg_list.push_back(symbol);
    }
    return formals_pointer;
}

STypeArgListPtr ParseUtils::ParseFormalsList(int lineno, STypePtr formal) {
    auto casted_formal = dynamic_pointer_cast<STypeSymbol>(formal);

    auto arg_list_pointer = make_shared<STypeArgList>();
    arg_list_pointer->arg_list.push_back(*casted_formal);
    return arg_list_pointer;
}

STypeArgListPtr ParseUtils::ParseFormalsList(int lineno, STypePtr formal, STypePtr formals_list) {
    auto casted_formals_list = dynamic_pointer_cast<STypeArgList>(formals_list);
    auto casted_formal = dynamic_pointer_cast<STypeSymbol>(formal);

    casted_formals_list->arg_list.push_back(*casted_formal);
    return casted_formals_list;
}

STypeSymbolPtr ParseUtils::ParseFormalDecl(int lineno, STypePtr type, STypePtr id) {
    auto casted_type = dynamic_pointer_cast<STypeCType>(type);
    auto casted_id = dynamic_pointer_cast<STypeString>(id);

    auto symbol_pointer = make_shared<STypeSymbol>(casted_id->token, symbol_table.scope_stack.top()->offset,
                                                   casted_type->type);
    return symbol_pointer;
}

void ParseUtils::ParseStatements(int lineno) {

}

void ParseUtils::ParseStatements(int lineno, STypePtr x) {

}

void ParseUtils::ParseStatementOfStatements(int lineno) {

}

void ParseUtils::ParseStatementType(int lineno, STypePtr type, STypePtr id) {
    auto casted_type = dynamic_pointer_cast<STypeCType>(type);
    auto casted_id = dynamic_pointer_cast<STypeString>(id);

    if (semantic_checks.IsSymbolDefined(casted_id->token)) {
        errorDef(lineno, casted_id->token);
        exit(0);
    }
    const auto symbol = make_shared<STypeSymbol>(casted_id->token, 0, casted_type->type);
    symbol_table.AddVariable(symbol);
}

void ParseUtils::ParseStatementTypeAssign(int lineno, STypePtr type, STypePtr id, STypePtr exp) {
    auto casted_type = dynamic_pointer_cast<STypeCType>(type);
    auto casted_id = dynamic_pointer_cast<STypeString>(id);

    if (!semantic_checks.IsLegalAssignTypes(casted_type->type, exp->general_type)) {
        errorMismatch(lineno);
        exit(0);
    }
    if (semantic_checks.IsSymbolDefined(casted_id->token)) {
        errorDef(lineno, casted_id->token);
        exit(0);
    }
    const auto symbol = make_shared<STypeSymbol>(casted_id->token, 0, casted_type->type);
    symbol_table.AddVariable(symbol);
}

void ParseUtils::ParseStatementAssign(int lineno, STypePtr id, STypePtr exp) {
    auto casted_id = dynamic_pointer_cast<STypeString>(id);

    if (!semantic_checks.IsSymbolDefined(casted_id->token)) {
        errorUndef(lineno, casted_id->token);
        exit(0);
    }

    auto symbol_from_id = symbol_table.GetDefinedSymbol(casted_id->token);

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

void ParseUtils::ParseStatementSwitch(int lineno, STypePtr exp) {
    if (!semantic_checks.IsLegalAssignTypes(INT_TYPE,exp->general_type)){
        errorMismatch(lineno);
        exit(0);
    }
}

STypePtr ParseUtils::ParseCall(int lineno, STypePtr id, STypePtr exp_list) {
    auto casted_id = dynamic_pointer_cast<STypeString>(id);

    if (!semantic_checks.IsSymbolDefined(casted_id->token)) {
        errorUndefFunc(lineno, casted_id->token);
        exit(0);
    }

    auto symbol_from_id = symbol_table.GetDefinedSymbol(casted_id->token);

    if (!semantic_checks.IsFunctionType(symbol_from_id->general_type)){
        errorUndefFunc(lineno, casted_id->token);
        exit(0);
    }

    auto casted_func = dynamic_pointer_cast<STypeFunctionSymbol>(symbol_from_id);
    auto casted_exp_list = dynamic_pointer_cast<STypeExpList>(exp_list);

    if (!semantic_checks.IsLegalCallTypes(casted_func,casted_exp_list)){
        vector<string> expected_args;
        for(auto symbol:casted_func->parameters){
            expected_args.push_back(TypeToString(symbol.general_type));
        }
        errorPrototypeMismatch(lineno, casted_id->token, expected_args);
        exit(0);
    }

    auto ret_type_pointer = make_shared<STypeBase>(casted_func->ret_type);
    return ret_type_pointer;
}

STypePtr ParseUtils::ParseCall(int lineno, STypePtr id) {
    auto casted_id = dynamic_pointer_cast<STypeString>(id);

    if (!semantic_checks.IsSymbolDefined(casted_id->token)) {
        errorUndefFunc(lineno, casted_id->token);
        exit(0);
    }

    auto symbol_from_id = symbol_table.GetDefinedSymbol(casted_id->token);

    if (!semantic_checks.IsFunctionType(symbol_from_id->general_type)){
        errorUndefFunc(lineno, casted_id->token);
        exit(0);
    }

    auto casted_func = dynamic_pointer_cast<STypeFunctionSymbol>(symbol_from_id);
    auto empty_exp_list = STypeExpListPtr();

    if (!semantic_checks.IsLegalCallTypes(casted_func,empty_exp_list)){
        vector<string> expected_args;
        for(auto symbol:casted_func->parameters){
            expected_args.push_back(TypeToString(symbol.general_type));
        }
        errorPrototypeMismatch(lineno, casted_id->token, expected_args);
        exit(0);
    }

    auto ret_type_pointer = make_shared<STypeBase>(casted_func->ret_type);
    return ret_type_pointer;
}

STypePtr ParseUtils::ParseExplist(int lineno, STypePtr exp) {
    auto exp_list_pointer = make_shared<STypeExpList>();
    exp_list_pointer->exp_list.push_back(*exp);
    return exp_list_pointer;
}

STypePtr ParseUtils::ParseExplist(int lineno, STypePtr exp, STypePtr exp_list) {
    auto casted_exp_list = dynamic_pointer_cast<STypeExpList>(exp_list);

    casted_exp_list->exp_list.push_back(*exp);
    return casted_exp_list;
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

STypePtr ParseUtils::ParseBinop(int lineno) {
    return STypePtr();
}

STypePtr ParseUtils::ParseID(int lineno) {
    return STypePtr();
}

STypePtr ParseUtils::ParseCallExp(int lineno) {
    return STypePtr();
}

STypePtr ParseUtils::ParseNum(int lineno, STypePtr num) {
    return STypePtr(num);
}

STypePtr ParseUtils::ParseNumB(int lineno, STypePtr num) {
    auto casted_num = dynamic_pointer_cast<STypeNumber>(num);
    if (!semantic_checks.IsByteOverflow(casted_num->token)) {
        errorByteTooLarge(lineno, to_string(casted_num->token));
        exit(0);
    }
    num->general_type = BOOL_TYPE;
    return num;
}

STypePtr ParseUtils::ParseString(int lineno) {
    return STypePtr();
}

STypePtr ParseUtils::ParseTrue(int lineno) {
    return STypePtr();
}

STypePtr ParseUtils::ParseFalse(int lineno) {
    return STypePtr();
}

STypePtr ParseUtils::ParseNot(int lineno) {
    return STypePtr();
}

STypePtr ParseUtils::ParseAnd(int lineno) {
    return STypePtr();
}

STypePtr ParseUtils::ParseOr(int lineno) {
    return STypePtr();
}

STypePtr ParseUtils::ParseRelOp(int lineno) {
    return STypePtr();
}

STypePtr ParseUtils::ParseCast(int lineno) {
    return STypePtr();
}

STypePtr ParseUtils::ParseCaseList(int lineno) {
    return STypePtr();
}

STypePtr ParseUtils::ParseCaseList(int lineno, STypePtr x) {
    return STypePtr();
}

STypePtr ParseUtils::ParseCaseDefault(int lineno) {
    return STypePtr();
}

STypePtr ParseUtils::ParseCaseDecl(int lineno) {
    return STypePtr();
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
