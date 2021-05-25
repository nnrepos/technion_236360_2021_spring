#include "parse_utils.h"



ParseUtils &ParseUtils::instance()
{
    static ParseUtils parse_utils;
    return parse_utils;
}

void ParseUtils::ParseProgram(int lineno) {

}

void ParseUtils::ParseFuncs(int lineno) {

}

void ParseUtils::ParseFuncDecl(int lineno, STypePtr function_head) {

}

STypePtr ParseUtils::ParseFuncHead(int lineno, STypePtr ret_type, STypePtr id, STypePtr formals) {
    return STypePtr();
}

STypePtr ParseUtils::ParseRetType(int lineno, STypePtr type) {
    return STypePtr();
}

STypePtr ParseUtils::ParseRetType(int lineno) {
    return STypePtr();
}

STypePtr ParseUtils::ParseFormals(int lineno) {
    return STypePtr();
}

STypePtr ParseUtils::ParseFormals(int lineno, STypePtr x) {
    return STypePtr();
}

STypePtr ParseUtils::ParseFormalsList(int lineno) {
    return STypePtr();
}

STypePtr ParseUtils::ParseFormalsList(int lineno, STypePtr x) {
    return STypePtr();
}

STypePtr ParseUtils::ParseFormalDecl(int lineno) {
    return STypePtr();
}

STypePtr ParseUtils::ParseStatements(int lineno) {
    return STypePtr();
}

STypePtr ParseUtils::ParseStatements(int lineno, STypePtr x) {
    return STypePtr();
}

STypePtr ParseUtils::ParseStatementOfStatements(int lineno) {
    return STypePtr();
}

STypePtr ParseUtils::ParseStatementType(int lineno) {
    return STypePtr();
}

STypePtr ParseUtils::ParseStatementTypeAssign(int lineno) {
    return STypePtr();
}

STypePtr ParseUtils::ParseStatementAssign(int lineno) {
    return STypePtr();
}

STypePtr ParseUtils::ParseStatementCall(int lineno) {
    return STypePtr();
}

STypePtr ParseUtils::ParseStatementReturn(int lineno) {
    return STypePtr();
}

STypePtr ParseUtils::ParseStatementReturnExp(int lineno) {
    return STypePtr();
}

STypePtr ParseUtils::ParseStatementIf(int lineno) {
    return STypePtr();
}

STypePtr ParseUtils::ParseStatementIfElse(int lineno) {
    return STypePtr();
}

STypePtr ParseUtils::ParseStatementWhile(int lineno) {
    return STypePtr();
}

STypePtr ParseUtils::ParseStatementBreak(int lineno) {
    return STypePtr();
}

STypePtr ParseUtils::ParseStatementContinue(int lineno) {
    return STypePtr();
}

STypePtr ParseUtils::ParseStatementSwitch(int lineno) {
    return STypePtr();
}

STypePtr ParseUtils::ParseCall(int lineno) {
    return STypePtr();
}

STypePtr ParseUtils::ParseCall(int lineno, STypePtr x) {
    return STypePtr();
}

STypePtr ParseUtils::ParseExplist(int lineno) {
    return STypePtr();
}

STypePtr ParseUtils::ParseExplist(int lineno, STypePtr x) {
    return STypePtr();
}

STypePtr ParseUtils::ParseInt(int lineno) {
    return STypePtr();
}

STypePtr ParseUtils::ParseByte(int lineno) {
    return STypePtr();
}

STypePtr ParseUtils::ParseBool(int lineno) {
    return STypePtr();
}

STypePtr ParseUtils::ParseParentheses(int lineno) {
    return STypePtr();
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

STypePtr ParseUtils::ParseNum(int lineno) {
    return STypePtr();
}

STypePtr ParseUtils::ParseNumB(int lineno) {
    return STypePtr();
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
