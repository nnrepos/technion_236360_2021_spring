#ifndef HW3_SYMBOL_TABLE_H
#define HW3_SYMBOL_TABLE_H
#include "typedefs.h"
#include "hw3_output.hpp"
using namespace output;

enum ScopeType{
    NORMAL_SCOPE,
    WHILE_SCOPE,
    SWITCH_SCOPE,
    GLOBAL_SCOPE
};

class Scope{
public:
    ScopeType type;
    int offset;
    vector<STypeSymbolPtr> symbols;

    Scope(ScopeType type, int offset);
};

class SymbolTable {
public:
    int current_offset;
    unordered_map<string, STypeSymbolPtr> symbols_map;
    stack<Scope*> scope_stack;

    void PushDefaultFunctions();

    void PushScope(ScopeType scope_type);

    void PopScope();
    SymbolTable();

};


#endif //HW3_SYMBOL_TABLE_H
