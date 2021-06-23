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

    void ParseFuncHead(int lineno, const STypePtr& ret_type, const STypePtr& id, const STypePtr& formals);

    STypePtr ParseRetType(int lineno, STypePtr type);

    STypeCTypePtr ParseRetType(int lineno);

    STypeArgListPtr ParseFormals(int lineno);

    STypeArgListPtr ParseFormals(int lineno, const STypePtr& formals);

    STypeArgListPtr ParseFormalsList(int lineno, const STypePtr& formal);

    STypeArgListPtr ParseFormalsList(int lineno, const STypePtr& formal, const STypePtr& formals_list);

    STypeSymbolPtr ParseFormalDecl(int lineno, const STypePtr& type, const STypePtr& id);

    STypeStatementPtr ParseStatements(int lineno, STypePtr &statement);

    STypeStatementPtr ParseStatements(int lineno, STypePtr &statements, STypePtr &statement);

    STypeStatementPtr ParseStatementOfStatements(int lineno, STypePtr &statements);

    STypeStatementPtr ParseStatementType(int lineno, const STypePtr& type, const STypePtr& id);

    STypeStatementPtr ParseStatementTypeAssign(int lineno, const STypePtr& type, const STypePtr& id, const STypePtr& exp);

    STypeStatementPtr ParseStatementAssign(int lineno, const STypePtr& id, const STypePtr& exp);

    STypeStatementPtr ParseStatementCall(int lineno);

    STypeStatementPtr ParseStatementReturn(int lineno);

    STypeStatementPtr ParseStatementReturnExp(int lineno, const STypePtr& exp);

    STypeStatementPtr ParseStatementIf(int lineno, STypePtr exp, STypePtr if_label, STypePtr if_statement);

    STypeStatementPtr
    ParseStatementIfElse(int lineno, STypePtr exp, STypePtr if_label, STypePtr if_statement, STypePtr else_label,
                         STypePtr else_statement);

    STypeStatementPtr
    ParseStatementWhile(int lineno, STypePtr while_head_label, STypePtr exp, STypePtr while_body_label,
                        STypePtr while_statement);

    STypeStatementPtr ParseStatementBreak(int lineno);

    STypeStatementPtr ParseStatementContinue(int lineno);

    STypeStatementPtr ParseStatementSwitch(int lineno);

    STypePtr ParseCall(int lineno, const STypePtr& id, const STypePtr& exp_list);

    STypePtr ParseCall(int lineno, const STypePtr& id);

    STypePtr ParseExplist(int lineno, const STypePtr& exp);

    STypePtr ParseExplist(int lineno, const STypePtr& exp, const STypePtr& exp_list);

    STypeCTypePtr ParseInt(int lineno);

    STypeCTypePtr ParseByte(int lineno);

    STypeCTypePtr ParseBool(int lineno);

    STypePtr ParseParentheses(int lineno, STypePtr exp);

    STypeRegisterPtr ParseBinop(int lineno, const STypePtr& exp1, STypePtr &binop, const STypePtr& exp2);

    STypePtr ParseID(int lineno, const STypePtr& id);

    STypePtr ParseCallExp(int lineno, STypePtr call_exp);

    STypeNumberPtr ParseNum(int lineno, const STypePtr& num);

    STypePtr ParseNumB(int lineno, STypePtr num);

    STypeStringPtr ParseString(int lineno, const STypePtr& stype_string);

    STypeBoolExpPtr ParseTrue(int lineno);

    STypeBoolExpPtr ParseFalse(int lineno);

    STypeBoolExpPtr ParseNot(int lineno, STypePtr bool_exp);

    STypeBoolExpPtr ParseAnd(int lineno, STypePtr bool_exp1, const STypePtr& bool_exp2);

    STypeBoolExpPtr ParseOr(int lineno, STypePtr bool_exp1, const STypePtr& bool_exp2);

    STypeBoolExpPtr ParseRelOp(int lineno, const STypePtr &exp1, STypePtr &relop, const STypePtr &exp2);

//    STypePtr ParseCast(int lineno, const STypePtr& type, STypePtr exp);

    STypePtr ParseGenIfLabel(int lineno);

    STypePtr ParseGenElseLabel(int lineno);

    STypePtr ParseGenWhileHeadLabel(int lineno);

    STypePtr ParseGenWhileBodyLabel(int lineno);

    STypePtr ParseGenAndLabel(int lineno);

    STypePtr ParseGenOrLabel(int lineno);

    void ParseCaseList(int lineno);

    void ParseCaseDefault(int lineno);

    void ParseCaseDecl(int lineno);

    void ParsePushStatementScope(int lineno);

    void ParsePushWhileScope(int lineno, STypePtr while_head_label);

    void ParsePushSwitchScope(int lineno, STypePtr switch_head_label);

    void ParsePopScope(int lineno);

    void ParseCheckSwitchExp(int lineno, const STypePtr& num_exp);

    void ParseCheckBool(int lineno, const STypePtr& bool_exp);

    static Compiler &instance();
};


#endif //HW3_PARSE_UTILS_H