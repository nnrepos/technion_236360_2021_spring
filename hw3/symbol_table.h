#ifndef HW3_SYMBOL_TABLE_H
#define HW3_SYMBOL_TABLE_H

#include "typedefs.h"
#include "hw3_output.hpp"

using namespace output;

enum ScopeType {
    STATEMENT_SCOPE,
    FUNCTION_SCOPE,
    WHILE_SCOPE,
    SWITCH_SCOPE,
    GLOBAL_SCOPE
};

class Scope {
public:
    ScopeType scope_type;
    int offset;
    vector<STypeSymbolPtr> symbols;
    Type ret_type;
    int while_switch_count;

    Scope(ScopeType scope_type, int offset, Type ret_type, int while_switch_count);
};

class SymbolTable {
public:
    int current_offset;
    unordered_map<string, STypeSymbolPtr> symbols_map;
    stack<Scope *> scope_stack;

    void PushDefaultFunctions();

    void PushScope(ScopeType scope_type);

    void PushFunctionScope(ScopeType scope_type, Type ret_type);

    void PopScope();

    SymbolTable();

    void AddVariable(const STypeSymbolPtr& symbol);

    void AddFunction(const STypeFunctionSymbolPtr & symbol);

    bool IsSymbolDefined(string &symbol_name);

    STypeSymbolPtr GetDefinedSymbol(string& symbol_name);

};


#endif //HW3_SYMBOL_TABLE_H
