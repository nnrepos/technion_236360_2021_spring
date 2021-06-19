#ifndef HW3_PARSE_UTILS_H
#define HW3_PARSE_UTILS_H

#include "typedefs.h"
#include "symbol_table.h"
#include "hw3_output.hpp"
#include "semantics.h"
#include "code_gen.h"
#include "bp.hpp"

using namespace output;

void yyerror(const char *);

// note: maybe it's wiser to create a `Parser` class which is stored here and move the functions there.
// it would require a lot of new functions though.
class Compiler {
public:
    SymbolTable symbol_table;
    SemanticChecks semantic_checks;
    CodeGen code_gen;

    Compiler();

    void ParseProgram(int lineno);

    void ParseFuncs(int lineno);

    void ParseFuncDecl(int lineno);

    STypePtr ParseFuncHead(int lineno, const STypePtr& ret_type, const STypePtr& id, const STypePtr& formals);

    STypePtr ParseRetType(int lineno, STypePtr type);

    STypeCTypePtr ParseRetType(int lineno);

    STypeArgListPtr ParseFormals(int lineno);

    STypeArgListPtr ParseFormals(int lineno, const STypePtr& formals);

    STypeArgListPtr ParseFormalsList(int lineno, const STypePtr& formal);

    STypeArgListPtr ParseFormalsList(int lineno, const STypePtr& formal, const STypePtr& formals_list);

    STypeSymbolPtr ParseFormalDecl(int lineno, const STypePtr& type, const STypePtr& id);

    void ParseStatements(int lineno);

    void ParseStatementOfStatements(int lineno);

    void ParseStatementType(int lineno, const STypePtr& type, const STypePtr& id);

    void ParseStatementTypeAssign(int lineno, const STypePtr& type, const STypePtr& id, const STypePtr& exp);

    void ParseStatementAssign(int lineno, const STypePtr& id, const STypePtr& exp);

    void ParseStatementCall(int lineno);

    void ParseStatementReturn(int lineno);

    void ParseStatementReturnExp(int lineno, const STypePtr& exp);

    void ParseStatementIf(int lineno);

    void ParseStatementIfElse(int lineno);

    void ParseStatementWhile(int lineno);

    void ParseStatementBreak(int lineno);

    void ParseStatementContinue(int lineno);

    void ParseStatementSwitch(int lineno);

    STypePtr ParseCall(int lineno, const STypePtr& id, const STypePtr& exp_list);

    STypePtr ParseCall(int lineno, const STypePtr& id);

    STypePtr ParseExplist(int lineno, const STypePtr& exp);

    STypePtr ParseExplist(int lineno, const STypePtr& exp, const STypePtr& exp_list);

    STypeCTypePtr ParseInt(int lineno);

    STypeCTypePtr ParseByte(int lineno);

    STypeCTypePtr ParseBool(int lineno);

    STypePtr ParseParentheses(int lineno, STypePtr exp);

    STypeRegisterPtr ParseBinop(int lineno, const STypePtr& exp1, string binop, const STypePtr& exp2);

    STypePtr ParseID(int lineno, const STypePtr& id);

    STypePtr ParseCallExp(int lineno, STypePtr call_exp);

    STypeNumberPtr ParseNum(int lineno, const STypePtr& num);

    STypePtr ParseNumB(int lineno, STypePtr num);

    STypeStringPtr ParseString(int lineno, const STypePtr& stype_string);

    STypeBoolPtr ParseTrue(int lineno);

    STypeBoolPtr ParseFalse(int lineno);

    STypePtr ParseNot(int lineno, STypePtr bool_exp);

    STypePtr ParseAnd(int lineno, STypePtr bool_exp1, const STypePtr& bool_exp2);

    STypePtr ParseOr(int lineno, STypePtr bool_exp1, const STypePtr& bool_exp2);

    STypeBoolPtr ParseRelOp(int lineno, const STypePtr& exp1, const STypePtr& exp2);

    STypePtr ParseCast(int lineno, const STypePtr& type, STypePtr exp);

    void ParseCaseList(int lineno);

    void ParseCaseDefault(int lineno);

    void ParseCaseDecl(int lineno);

    void ParsePushStatementScope(int lineno);

    void ParsePushWhileScope(int lineno);

    void ParsePushSwitchScope(int lineno);

    void ParsePopScope(int lineno);

    void ParseCheckSwitchExp(int lineno, const STypePtr& num_exp);

    void ParseCheckBool(int lineno, const STypePtr& bool_exp);

    static Compiler &instance();
};


#endif //HW3_PARSE_UTILS_H