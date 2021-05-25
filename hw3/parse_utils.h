#ifndef HW3_PARSE_UTILS_H
#define HW3_PARSE_UTILS_H

#include "typedefs.h"
#include "symbol_table.h"
#include "hw3_output.hpp"
#include "semantics.h"

using namespace output;

void yyerror(const char *);


class ParseUtils {
public:
    SymbolTable symbol_table;
    SemanticChecks semantic_checks;

    ParseUtils();

    void ParseProgram(int lineno);

    void ParseFuncs(int lineno);

    void ParseFuncDecl(int lineno, STypePtr function_head);

    STypePtr ParseFuncHead(int lineno, STypePtr ret_type, STypePtr id, STypePtr formals);

    STypePtr ParseRetType(int lineno, STypePtr type);

    STypePtr ParseRetType(int lineno);

    STypePtr ParseFormals(int lineno);

    STypePtr ParseFormals(int lineno, STypePtr x);

    STypePtr ParseFormalsList(int lineno);

    STypePtr ParseFormalsList(int lineno, STypePtr x);

    STypePtr ParseFormalDecl(int lineno);

    STypePtr ParseStatements(int lineno);

    STypePtr ParseStatements(int lineno, STypePtr x);

    STypePtr ParseStatementOfStatements(int lineno);

    STypePtr ParseStatementType(int lineno);

    STypePtr ParseStatementTypeAssign(int lineno);

    STypePtr ParseStatementAssign(int lineno);

    STypePtr ParseStatementCall(int lineno);

    STypePtr ParseStatementReturn(int lineno);

    STypePtr ParseStatementReturnExp(int lineno);

    STypePtr ParseStatementIf(int lineno);

    STypePtr ParseStatementIfElse(int lineno);

    STypePtr ParseStatementWhile(int lineno);

    STypePtr ParseStatementBreak(int lineno);

    STypePtr ParseStatementContinue(int lineno);

    STypePtr ParseStatementSwitch(int lineno);

    STypePtr ParseCall(int lineno);

    STypePtr ParseCall(int lineno, STypePtr x);

    STypePtr ParseExplist(int lineno);

    STypePtr ParseExplist(int lineno, STypePtr x);

    STypePtr ParseInt(int lineno);

    STypePtr ParseByte(int lineno);

    STypePtr ParseBool(int lineno);

    STypePtr ParseParentheses(int lineno);

    STypePtr ParseBinop(int lineno);

    STypePtr ParseID(int lineno);

    STypePtr ParseCallExp(int lineno);

    STypePtr ParseNum(int lineno);

    STypePtr ParseNumB(int lineno);

    STypePtr ParseString(int lineno);

    STypePtr ParseTrue(int lineno);

    STypePtr ParseFalse(int lineno);

    STypePtr ParseNot(int lineno);

    STypePtr ParseAnd(int lineno);

    STypePtr ParseOr(int lineno);

    STypePtr ParseRelOp(int lineno);

    STypePtr ParseCast(int lineno);

    STypePtr ParseCaseList(int lineno);

    STypePtr ParseCaseList(int lineno, STypePtr x);

    STypePtr ParseCaseDefault(int lineno);

    STypePtr ParseCaseDecl(int lineno);


    static ParseUtils &instance();
};


#endif //HW3_PARSE_UTILS_H