#include "semantics.h"

SemanticChecks::SemanticChecks(SymbolTable &table) : table_ref(table) {

}

bool SemanticChecks::IsSymbolDefined() {
    return false;
}

bool SemanticChecks::IsMainDefined() {
    return false;
}

bool SemanticChecks::IsLegalAssignTypes(Type &first, Type &second) {
    return false;
}

bool SemanticChecks::IsLegalCallTypes(STypeFunctionSymbol &func, STypeArgList &arg_list) {
    return false;
}

bool SemanticChecks::IsLegalReturnType(Type &type) {
    return false;
}

bool SemanticChecks::IsBoolExp(Type &type) {
    return false;
}

bool SemanticChecks::IsBreakContinueScope() {
    return false;
}

bool SemanticChecks::IsByteOverflow(int &num) {
    return false;
}

bool SemanticChecks::IsLegalRelopTypes(Type &first, string &relop, Type &second) {
    return false;
}

Type SemanticChecks::CheckAndGetBinOpType(Type &first, string &binop, Type &second) {
    return VARIABLE_TYPE;
}

bool SemanticChecks::IsLegalCast(Type &first, Type &second) {
    return false;
}

