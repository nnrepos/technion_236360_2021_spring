#ifndef HW3_SEMANTICS_H
#define HW3_SEMANTICS_H
#include "symbol_table.h"

class SemanticChecks {
public:
    SymbolTable &table_ref;
    explicit SemanticChecks(SymbolTable &table);

    bool IsSymbolDefined(string &name);
    bool IsMainDefined();
    bool IsLegalAssignTypes(Type first, Type second);
    bool IsLegalCallTypes(STypeFunctionSymbolPtr &func, STypeExpListPtr &exp_list);
    bool IsLegalReturnType(Type type);
    bool IsBoolType(Type type);
    bool IsVoidType(Type type);
    bool IsFunctionType(Type type);
    bool IsLegalBreak();
    bool IsLegalContinue();
    bool IsByteOverflow(int &num);
    bool IsLegalRelopTypes(Type first, Type second);
    bool IsLegalCast(Type first, Type second);


    Type CheckAndGetBinOpType(Type first, Type second);
};


#endif //HW3_SEMANTICS_H
