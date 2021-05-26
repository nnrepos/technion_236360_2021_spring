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

    STypeCTypePtr ParseRetType(int lineno);

    STypeArgListPtr ParseFormals(int lineno);

    STypeArgListPtr ParseFormals(int lineno, STypePtr formals);

    STypeArgListPtr ParseFormalsList(int lineno, STypePtr formal);

    STypeArgListPtr ParseFormalsList(int lineno, STypePtr formal, STypePtr formals_list);

    STypeSymbolPtr ParseFormalDecl(int lineno, STypePtr type, STypePtr id);

    void ParseStatements(int lineno);

    void ParseStatements(int lineno, STypePtr x);

    void ParseStatementOfStatements(int lineno);

    void ParseStatementType(int lineno, STypePtr type, STypePtr id);

    void ParseStatementTypeAssign(int lineno, STypePtr type, STypePtr id, STypePtr exp);

    void ParseStatementAssign(int lineno, STypePtr id, STypePtr exp);

    void ParseStatementCall(int lineno);

    void ParseStatementReturn(int lineno);

    void ParseStatementReturnExp(int lineno, STypePtr exp);

    void ParseStatementIf(int lineno, STypePtr exp);

    void ParseStatementIfElse(int lineno, STypePtr exp);

    void ParseStatementWhile(int lineno, STypePtr exp);

    void ParseStatementBreak(int lineno);

    void ParseStatementContinue(int lineno);

    void ParseStatementSwitch(int lineno, STypePtr exp);

    STypePtr ParseCall(int lineno, STypePtr id, STypePtr exp_list);

    STypePtr ParseCall(int lineno, STypePtr id);

    STypePtr ParseExplist(int lineno, STypePtr exp);

    STypePtr ParseExplist(int lineno, STypePtr exp, STypePtr exp_list);

    STypeCTypePtr ParseInt(int lineno);

    STypeCTypePtr ParseByte(int lineno);

    STypeCTypePtr ParseBool(int lineno);

    STypePtr ParseParentheses(int lineno, STypePtr exp);

    STypePtr ParseBinop(int lineno);

    STypePtr ParseID(int lineno);

    STypePtr ParseCallExp(int lineno);

    STypePtr ParseNum(int lineno, STypePtr num);

    STypePtr ParseNumB(int lineno, STypePtr num);

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

    void ParsePushStatementScope(int lineno);

    void ParsePushWhileScope(int lineno);

    void ParsePushSwitchScope(int lineno);

    void ParsePopScope(int lineno);


    static ParseUtils &instance();
};


#endif //HW3_PARSE_UTILS_H