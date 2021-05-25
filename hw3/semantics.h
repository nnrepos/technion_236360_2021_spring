#ifndef HW3_SEMANTICS_H
#define HW3_SEMANTICS_H
#include "symbol_table.h"

class SemanticChecks {
public:
    SymbolTable &table_ref;
    explicit SemanticChecks(SymbolTable &table);

    bool IsSymbolDefined();
    bool IsMainDefined();
    bool IsLegalAssignTypes(Type &first, Type &second);
    bool IsLegalCallTypes(STypeFunctionSymbol &func, STypeArgList &arg_list);
    bool IsLegalReturnType(Type &type);
    bool IsBoolExp(Type &type);
    bool IsBreakContinueScope();
    bool IsByteOverflow(int &num);
    bool IsLegalRelopTypes(Type &first, string &relop, Type &second);
    Type CheckAndGetBinOpType(Type &first, string &binop, Type &second);
    bool IsLegalCast(Type &first, Type &second);


};


#endif //HW3_SEMANTICS_H
