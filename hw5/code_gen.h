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

    void EmitFuncHead(STypeFunctionSymbolPtr symbol);

    void EmitFuncDecl(STypePtr statements, STypePtr next_list_as_statement, STypePtr next_label);

    STypeStatementPtr EmitStatementType(string id);

    STypeStatementPtr EmitStatementAssign(string id, const STypePtr &exp);

    STypeStatementPtr EmitStatementCall();

    STypeStatementPtr EmitStatementReturn();

    STypeStatementPtr EmitStatementReturnExp(const STypePtr &exp);

    STypeStatementPtr EmitStatementIf(STypePtr exp, STypePtr if_label, STypePtr if_statement);

    STypeStatementPtr
    EmitStatementIfElse(STypePtr exp, STypePtr if_label, STypePtr if_statement, STypePtr else_label,
                        STypePtr else_statement);

    STypeStatementPtr
    EmitStatementWhile(STypePtr while_head_label, STypePtr exp, STypePtr while_body_label,
                       STypePtr while_statement, STypePtr list_as_statement,
                       branch_list_ptr break_list);

    STypeStatementPtr EmitStatementBreak();

    STypeStatementPtr EmitStatementContinue();

    STypeStatementPtr EmitStatementSwitch();

    STypeRegisterPtr EmitCall(const STypeFunctionSymbolPtr &func, const STypeExpListPtr &exp_list);

    STypeRegisterPtr EmitCall(const STypeFunctionSymbolPtr &func);

    STypeBoolExpPtr EmitTrue();

    STypeBoolExpPtr EmitFalse();

    STypeBoolExpPtr EmitNot(STypePtr bool_exp);

    STypeBoolExpPtr EmitAnd(STypePtr bool_exp1, STypePtr and_label, STypePtr bool_exp2);

    STypeBoolExpPtr EmitOr(STypePtr bool_exp1, STypePtr or_label, STypePtr bool_exp2);

    STypeBoolExpPtr EmitRelOp(const STypePtr &exp1, STypePtr &relop, const STypePtr &exp2);

    STypeRegisterPtr EmitCast(STypePtr type, STypePtr exp);

    void EmitCaseList();

    void EmitCaseDefault();

    void EmitCaseDecl();

    void EmitProgram();

    string GetNonBoolExpString(const STypePtr &exp);


    string SymbolToRegister(int offset, Type type);

    string GetLLVMType(const Type &type) const;

    void EmitStoreRegister(int offset, const register_name &reg_to_store);

    STypeRegisterPtr EmitLoadRegister(int offset, Type type);

    STypeStatementPtr EmitBranchNext();

    STypeRegisterPtr EmitString(const STypePtr &stype_string);

    STypePtr EmitID(STypeSymbolPtr symbol);

    void EmitBoolExpToRegister(const STypePtr &exp, const register_name &reg_result);

    STypePtr RegisterToBoolExp(string &reg_source);

    STypeStatementPtr EmitBranchWhileHead();
};


#endif //HW5_CODE_GEN_H
