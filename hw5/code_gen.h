#ifndef HW5_CODE_GEN_H
#define HW5_CODE_GEN_H

#include "typedefs.h"
#include "bp.hpp"
#include "semantics.h"

const int MAX_VARIABLES_PER_FUNCTION = 50;
const int VARIABLE_SIZE = 4;
const int STACK_SIZE = MAX_VARIABLES_PER_FUNCTION * VARIABLE_SIZE;

class CodeGen {
public:
    int register_count;
    CodeBuffer code_buffer;
    SemanticChecks semantic_ref;
    string stack_register;

    CodeGen(SemanticChecks &semantic_ref);

    register_name GenRegister();

    register_name GenGlobalRegister();

    void EmitGlobalFunctions();



//    STypeStringPtr EmitString(STypePtr stype_string);
//    STypeCTypePtr EmitInt();
//    STypeCTypePtr EmitByte();
//    STypeCTypePtr EmitBool();
//    STypeNumberPtr EmitNum(STypePtr num);
//    STypePtr EmitNumB(STypePtr num);
//    STypePtr EmitParentheses(STypePtr exp);
//    STypePtr EmitID(STypePtr id);
//    STypePtr EmitCallExp(STypePtr call_exp);

    STypeRegisterPtr EmitBinop(const STypePtr &exp1, string binop, const STypePtr &exp2);

    void EmitCheckDivZero(const STypePtr &exp);

    void EmitFuncHead(const STypeFunctionSymbolPtr &symbol);

    void EmitFuncDecl(const STypePtr &statements, const STypePtr &next_label);

    STypeStatementPtr EmitStatementType(string id);

    STypeStatementPtr EmitStatementAssign(string id, const STypePtr &exp);

    static STypeStatementPtr EmitStatementCall();

    STypeStatementPtr EmitStatementReturn();

    STypeStatementPtr EmitStatementReturnExp(const STypePtr &exp);

    STypeStatementPtr
    EmitStatementIf(const STypePtr &exp, const STypePtr &if_label, const STypePtr &if_statement,
                    const STypePtr &if_list_as_statement);

    STypeStatementPtr
    EmitStatementIfElse(const STypePtr &exp, const STypePtr &if_label, const STypePtr &if_statement,
                        STypePtr if_list_as_statement,
                        const STypePtr &else_label, const STypePtr &else_statement);

    STypeStatementPtr
    EmitStatementWhile(STypePtr start_list_as_statement, const STypePtr &while_head_label, const STypePtr &exp,
                       const STypePtr &while_body_label, const STypePtr &while_statement,
                       const STypePtr &end_list_as_statement, const branch_list_ptr &break_list);

    STypeStatementPtr EmitStatementBreak();

    STypeStatementPtr EmitStatementContinue();

    STypeStatementPtr
    EmitStatementSwitch(STypePtr exp, STypePtr switch_list_as_statement, STypePtr case_list,
                        branch_list_ptr break_list);

    STypeRegisterPtr EmitCall(const STypeFunctionSymbolPtr &func, const STypeExpListPtr &exp_list);

    STypeRegisterPtr EmitCall(const STypeFunctionSymbolPtr &func);

    STypeBoolExpPtr EmitTrue();

    STypeBoolExpPtr EmitFalse();

    static STypeBoolExpPtr EmitNot(const STypePtr &bool_exp);

    STypeBoolExpPtr EmitAnd(const STypePtr &bool_exp1, const STypePtr &and_label, const STypePtr &bool_exp2);

    STypeBoolExpPtr EmitOr(const STypePtr &bool_exp1, const STypePtr &or_label, const STypePtr &bool_exp2);

    STypeBoolExpPtr EmitRelOp(const STypePtr &exp1, STypePtr &relop, const STypePtr &exp2);

    STypeRegisterPtr EmitCast(STypePtr type, STypePtr exp);

    STypeCaseDeclPtr
    EmitCaseDecl(STypePtr num, STypePtr list_as_statement, STypePtr case_decl_label, STypePtr statements);

    STypeCaseListPtr EmitCaseDefault(STypePtr list_as_statement, STypePtr default_label, STypePtr statements);

    STypeCaseListPtr EmitCaseList(STypePtr case_decl);

    STypeCaseListPtr EmitCaseList(STypePtr case_decl, STypePtr next_label, STypePtr case_list);

    void EmitProgram();

    string GetNonBoolExpString(const STypePtr &exp);


    string SymbolToRegister(int offset, Type type);

    static string GetLLVMType(const Type &type);

    void EmitStoreRegister(int offset, const register_name &reg_to_store);

    STypeRegisterPtr EmitLoadRegister(int offset, Type type);

    STypeStatementPtr EmitBranchNext();

    STypeRegisterPtr EmitString(const STypePtr &stype_string);

    STypePtr EmitID(const STypeSymbolPtr &symbol);

    void EmitBoolExpToRegister(const STypePtr &exp, const register_name &reg_result);

    STypePtr RegisterToBoolExp(string &reg_source);

    STypeStatementPtr EmitBranchWhileHead();

    STypeStatementPtr EmitParseBranchIfNext();

    STypeStatementPtr EmitBranchSwitchHead();

    STypeStatementPtr EmitBranchCaseHead();

    STypeStatementPtr EmitBranchDefaultHead();

    STypePtr EmitCallExp(STypePtr call_exp);
};


#endif //HW5_CODE_GEN_H
