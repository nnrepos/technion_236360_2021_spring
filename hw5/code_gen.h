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

    STypeRegisterPtr EmitBinop(const STypePtr& exp1, string binop, const STypePtr& exp2);

    void EmitCheckDivZero(const STypePtr& exp);

    void EmitFuncHead(STypeFunctionSymbolPtr symbol);
    void EmitFuncDecl();
    STypeStatementPtr EmitStatementType(string id);
    STypeStatementPtr EmitStatementAssign(string id, const STypePtr &exp);
    STypeStatementPtr EmitStatementCall();
    STypeStatementPtr EmitStatementReturn();
    STypeStatementPtr EmitStatementReturnExp(STypePtr exp);
    STypeStatementPtr EmitStatementIf();
    STypeStatementPtr EmitStatementIfElse();
    STypeStatementPtr EmitStatementWhile();
    STypeStatementPtr EmitStatementBreak();
    STypeStatementPtr EmitStatementContinue();
    STypeStatementPtr EmitStatementSwitch();
    STypeRegisterPtr EmitCall(const STypeFunctionSymbolPtr& func, const STypeExpListPtr& exp_list);
    STypeRegisterPtr EmitCall(const STypeFunctionSymbolPtr& func);
    STypeBoolExpPtr EmitTrue();
    STypeBoolExpPtr EmitFalse();
    STypeBoolExpPtr EmitNot(STypePtr bool_exp);
    STypeBoolExpPtr EmitAnd(STypePtr bool_exp1, STypePtr bool_exp2);
    STypeBoolExpPtr EmitOr(STypePtr bool_exp1, STypePtr bool_exp2);
    STypeBoolExpPtr EmitRelOp(const STypePtr& exp1, STypePtr &relop, const STypePtr& exp2);
    STypeRegisterPtr EmitCast(STypePtr type, STypePtr exp);
    void EmitCaseList();
    void EmitCaseDefault();
    void EmitCaseDecl();
    void EmitProgram();

    string GetNonBoolExpString(const STypePtr& exp);

    string OffsetToRegister(int offset);

    string GetLLVMType(const Type &type) const;

    void EmitStoreVar(int offset, const register_name& reg_to_store);
};


#endif //HW5_CODE_GEN_H
