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

    void ParseFuncDecl(int lineno);

    STypePtr ParseFuncHead(int lineno, STypePtr ret_type, STypePtr id, STypePtr formals);

    STypePtr ParseRetType(int lineno, STypePtr type);

    STypeCTypePtr ParseRetType(int lineno);

    STypeArgListPtr ParseFormals(int lineno);

    STypeArgListPtr ParseFormals(int lineno, STypePtr formals);

    STypeArgListPtr ParseFormalsList(int lineno, STypePtr formal);

    STypeArgListPtr ParseFormalsList(int lineno, STypePtr formal, STypePtr formals_list);

    STypeSymbolPtr ParseFormalDecl(int lineno, STypePtr type, STypePtr id);

    void ParseStatements(int lineno);

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

    STypePtr ParseBinop(int lineno, STypePtr exp1, STypePtr exp2);

    STypePtr ParseID(int lineno, STypePtr id);

    STypePtr ParseCallExp(int lineno, STypePtr call_exp);

    STypeNumberPtr ParseNum(int lineno, STypePtr num);

    STypePtr ParseNumB(int lineno, STypePtr num);

    STypeStringPtr ParseString(int lineno, STypePtr stype_string);

    STypeBoolPtr ParseTrue(int lineno);

    STypeBoolPtr ParseFalse(int lineno);

    STypePtr ParseNot(int lineno, STypePtr bool_exp);

    STypePtr ParseAnd(int lineno, STypePtr bool_exp1, STypePtr bool_exp2);

    STypePtr ParseOr(int lineno, STypePtr bool_exp1, STypePtr bool_exp2);

    STypeBoolPtr ParseRelOp(int lineno, STypePtr exp1, STypePtr exp2);

    STypePtr ParseCast(int lineno, STypePtr type, STypePtr exp);

    void ParseCaseList(int lineno);

    void ParseCaseDefault(int lineno);

    void ParseCaseDecl(int lineno);

    void ParsePushStatementScope(int lineno);

    void ParsePushWhileScope(int lineno);

    void ParsePushSwitchScope(int lineno);

    void ParsePopScope(int lineno);

    void ParseCheckSwitchExp(int lineno, STypePtr num_exp);

    void ParseCheckBool(int lineno, STypePtr bool_exp);

    static ParseUtils &instance();
};


#endif //HW3_PARSE_UTILS_H