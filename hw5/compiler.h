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

// note: should've removed all the lineno args and used the global instead.
class Compiler {
public:
    SymbolTable symbol_table;
    SemanticChecks semantic_checks;
    CodeGen code_gen;

    Compiler();

    void ParseProgram(int lineno);

    void ParseFuncs(int lineno);

    void ParseFuncDecl(int lineno, const STypePtr& statements, const STypePtr& next_label);

    void ParseFuncHead(int lineno, const STypePtr &ret_type, const STypePtr &id, const STypePtr &formals);

    STypePtr ParseRetType(int lineno, STypePtr type);

    STypeCTypePtr ParseRetType(int lineno);

    STypeArgListPtr ParseFormals(int lineno);

    STypeArgListPtr ParseFormals(int lineno, const STypePtr &formals);

    static STypeArgListPtr ParseFormalsList(int lineno, const STypePtr &formal);

    static STypeArgListPtr ParseFormalsList(int lineno, const STypePtr &formal, const STypePtr &formals_list);

    STypeSymbolPtr ParseFormalDecl(int lineno, const STypePtr &type, const STypePtr &id);

    static STypeStatementPtr
    ParseStatements(int lineno, STypePtr &statement, const STypePtr& next_list_as_statement);

    STypeStatementPtr
    ParseStatements(int lineno, const STypePtr& statements, const STypePtr& old_next_list_as_statement, const STypePtr& next_label,
                    const STypePtr& next_statement, const STypePtr& my_next_list_as_statement);

    static STypeStatementPtr ParseStatementOfStatements(int lineno, STypePtr &statements);

    STypeStatementPtr ParseStatementType(int lineno, const STypePtr &type, const STypePtr &id);

    STypeStatementPtr
    ParseStatementTypeAssign(int lineno, const STypePtr &type, const STypePtr &id, const STypePtr &exp);

    STypeStatementPtr ParseStatementAssign(int lineno, const STypePtr &id, const STypePtr &exp);

    static STypeStatementPtr ParseStatementCall(int lineno);

    STypeStatementPtr ParseStatementReturn(int lineno);

    STypeStatementPtr ParseStatementReturnExp(int lineno, const STypePtr &exp);

    STypeStatementPtr ParseStatementIf(int lineno, const STypePtr& exp, const STypePtr& if_label, const STypePtr& if_statement,
                                       const STypePtr& if_list_as_statement);

    STypeStatementPtr
    ParseStatementIfElse(int lineno, const STypePtr& exp, const STypePtr& if_label, const STypePtr& if_statement,
                         STypePtr if_list_as_statement, const STypePtr& else_label,
                         const STypePtr& else_statement);

    STypeStatementPtr
    ParseStatementWhile(int lineno, STypePtr start_list_as_statement, const STypePtr& while_head_label, const STypePtr& exp,
                        const STypePtr& while_body_label, const STypePtr& while_statement, const STypePtr& end_list_as_statement);

    STypeStatementPtr ParseStatementBreak(int lineno);

    STypeStatementPtr ParseStatementContinue(int lineno);

    STypeStatementPtr
    ParseStatementSwitch(int lineno, STypePtr exp, STypePtr switch_list_as_statement, STypePtr case_list);

    STypePtr ParseCall(int lineno, const STypePtr &id, const STypePtr &exp_list);

    STypePtr ParseCall(int lineno, const STypePtr &id);

    static STypePtr ParseExplist(int lineno, const STypePtr &exp);

    static STypePtr ParseExplist(int lineno, const STypePtr &exp, const STypePtr &exp_list);

    static STypeCTypePtr ParseInt(int lineno);

    static STypeCTypePtr ParseByte(int lineno);

    static STypeCTypePtr ParseBool(int lineno);

    static STypePtr ParseParentheses(int lineno, STypePtr exp);

    STypeRegisterPtr ParseBinop(int lineno, const STypePtr &exp1, STypePtr &binop, const STypePtr &exp2);

    STypePtr ParseID(int lineno, const STypePtr &id);

    STypePtr ParseCallExp(int lineno, STypePtr call_exp);

    static STypeNumberPtr ParseNum(int lineno, const STypePtr &num);

    STypePtr ParseNumB(int lineno, STypePtr num);

    STypeRegisterPtr ParseString(int lineno, const STypePtr &stype_string);

    STypeBoolExpPtr ParseTrue(int lineno);

    STypeBoolExpPtr ParseFalse(int lineno);

    STypeBoolExpPtr ParseNot(int lineno, const STypePtr& bool_exp);

    STypeBoolExpPtr ParseAnd(int lineno, const STypePtr& bool_exp1, const STypePtr& and_label, const STypePtr &bool_exp2);

    STypeBoolExpPtr ParseOr(int lineno, const STypePtr& bool_exp1, const STypePtr& or_label, const STypePtr &bool_exp2);

    STypeBoolExpPtr ParseRelOp(int lineno, const STypePtr &exp1, STypePtr &relop, const STypePtr &exp2);

//    STypePtr ParseCast(int lineno, const STypePtr& type, STypePtr exp);

    STypeStringPtr ParseGenIfLabel(int lineno);

    STypeStringPtr ParseGenElseLabel(int lineno);

    STypeStringPtr ParseGenWhileHeadLabel(int lineno);

    STypeStringPtr ParseGenWhileBodyLabel(int lineno);

    STypeStringPtr ParseGenAndLabel(int lineno);

    STypeStringPtr ParseGenOrLabel(int lineno);

    STypeStringPtr ParseGenNextLabel(int lineno);

    STypeStringPtr ParseGenDefaultLabel(int lineno);

    STypeStringPtr ParseGenCaseDeclLabel(int lineno);


    STypeCaseListPtr ParseCaseList(int lineno, STypePtr case_decl, STypePtr next_list, STypePtr case_list);

    STypeCaseListPtr ParseCaseList(int lineno, STypePtr case_decl);

    STypeCaseListPtr
    ParseCaseDefault(int lineno, STypePtr list_as_statement, STypePtr default_label, STypePtr statements);

    STypeCaseDeclPtr ParseCaseDecl(int lineno, STypePtr num, STypePtr list_as_statement, STypePtr case_decl_label,
                                   STypePtr statements);

    void ParsePushStatementScope(int lineno);

    void ParsePushWhileScope(int lineno, const STypePtr& while_head_label);

    void ParsePushSwitchScope(int lineno, const STypePtr& switch_head_label);

    void ParsePopScope(int lineno);

    void ParseCheckSwitchExp(int lineno, const STypePtr &num_exp);

    void ParseCheckBool(int lineno, const STypePtr &bool_exp);

    STypeStatementPtr ParseBranchNext(int lineno);

    STypeStatementPtr ParseBranchWhileHead(int lineno);

    STypeStatementPtr ParseBranchIfNext(int lineno);

    STypeStatementPtr ParseBranchSwitchHead(int lineno);

    STypeStatementPtr ParseBranchCaseHead(int lineno);

    STypeStatementPtr ParseBranchDefaultHead(int lineno);

    STypePtr ParseConvertBool(int lineno, STypePtr exp);

    static Compiler &instance();

};


#endif //HW3_PARSE_UTILS_H