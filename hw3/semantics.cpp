#include "semantics.h"

SemanticChecks::SemanticChecks(SymbolTable &table) : table_ref(table) {

}

bool SemanticChecks::IsSymbolDefined(string &name) {
    return table_ref.IsSymbolDefined(name);
}

bool SemanticChecks::IsMainDefined() {
    return true;
}

bool SemanticChecks::IsLegalAssignTypes(Type first, Type second) {
    return true;
}

bool SemanticChecks::IsLegalCallTypes(STypeFunctionSymbolPtr &func, STypeExpListPtr &arg_list) {
    return false;
}

bool SemanticChecks::IsLegalReturnType(Type type) {
    return false;
}

bool SemanticChecks::IsBoolType(Type type) {
    return (type == BOOL_TYPE);
}

bool SemanticChecks::IsFunctionType(Type type) {
    return (type == FUNCTION_TYPE);
}

bool SemanticChecks::IsLegalBreakContinue() {
    return (table_ref.scope_stack.top()->while_switch_count > 0);
}

bool SemanticChecks::IsByteOverflow(int &num) {
    return (num >= 0 && num <= 255);
}

bool SemanticChecks::IsLegalRelopTypes(Type first, string &relop, Type second) {
    return false;
}

Type SemanticChecks::CheckAndGetBinOpType(Type first, string &binop, Type second) {
    return OTHER_TYPE;
}

bool SemanticChecks::IsLegalCast(Type first, Type second) {
    return false;
}


