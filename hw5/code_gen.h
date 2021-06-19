#ifndef HW5_CODE_GEN_H
#define HW5_CODE_GEN_H

#include "typedefs.h"
#include "bp.hpp"
#include "semantics.h"

class CodeGen {
public:
    int register_count;
    CodeBuffer code_buffer;
    SemanticChecks semantic_ref;

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

    STypePtr EmitFuncHead();
    STypePtr EmitFuncDecl();
    STypePtr EmitStatementType(STypePtr type, STypePtr id);
    STypePtr EmitStatementTypeAssign(STypePtr type, STypePtr id, STypePtr exp);
    STypePtr EmitStatementAssign(STypePtr id, STypePtr exp);
    STypePtr EmitStatementCall();
    STypePtr EmitStatementReturn();
    STypePtr EmitStatementReturnExp(STypePtr exp);
    STypePtr EmitStatementIf();
    STypePtr EmitStatementIfElse();
    STypePtr EmitStatementWhile();
    STypePtr EmitStatementBreak();
    STypePtr EmitStatementContinue();
    STypePtr EmitStatementSwitch();
    STypeRegisterPtr EmitCall(const STypeFunctionSymbolPtr& func, const STypeExpListPtr& exp_list);
    STypeRegisterPtr EmitCall(const STypeFunctionSymbolPtr& func);
    STypeBoolPtr EmitTrue();
    STypeBoolPtr EmitFalse();
    STypePtr EmitNot(STypePtr bool_exp);
    STypePtr EmitAnd(STypePtr bool_exp1, STypePtr bool_exp2);
    STypePtr EmitOr(STypePtr bool_exp1, STypePtr bool_exp2);
    STypeBoolPtr EmitRelOp(STypePtr exp1, STypePtr exp2);
    STypePtr EmitCast(STypePtr type, STypePtr exp);
    void EmitCaseList();
    void EmitCaseDefault();
    void EmitCaseDecl();

    string GetExpString(STypePtr exp);

    string OffsetToRegister(int offset);
};


#endif //HW5_CODE_GEN_H
