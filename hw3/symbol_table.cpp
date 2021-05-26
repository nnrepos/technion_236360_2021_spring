#include "symbol_table.h"


void SymbolTable::PushDefaultFunctions() {
    // push print, then printi
}

void SymbolTable::PushScope(ScopeType scope_type) {
    Type ret_type;
    int while_switch_count;

    if (scope_type == GLOBAL_SCOPE) {
        ret_type = OTHER_TYPE;
        while_switch_count = 0;
    } else {
        assert(!scope_stack.empty());
        ret_type = scope_stack.top()->ret_type;
        while_switch_count = scope_stack.top()->while_switch_count;
    }

    if (scope_type == WHILE_SCOPE || scope_type == SWITCH_SCOPE){
        while_switch_count++;
    }

    scope_stack.push(new Scope(scope_type, current_offset, ret_type, while_switch_count));
}

void SymbolTable::PushFunctionScope(ScopeType scope_type, Type ret_type) {
    assert(!scope_stack.empty());
    int while_switch_count = scope_stack.top()->while_switch_count;
    scope_stack.push(new Scope(scope_type, current_offset, ret_type, while_switch_count));
}

void SymbolTable::PopScope() {
    // in global scope - functions only; in non-global scope - variables only
    if (scope_stack.top()->scope_type == GLOBAL_SCOPE) {
        for (const auto &func_symbol:scope_stack.top()->symbols) {
            assert(func_symbol->general_type == FUNCTION_TYPE);
            auto dynamic_cast_func = dynamic_pointer_cast<STypeFunctionSymbol>(func_symbol);
            vector<string> string_types;
            ArgListToStrings(dynamic_cast_func->parameters, string_types);
            string ret_type = TypeToString(dynamic_cast_func->ret_type);
            printID(dynamic_cast_func->name, 0, makeFunctionType(ret_type, string_types));
            symbols_map.erase(dynamic_cast_func->name);
        }

    } else {
        for (const auto &basic_symbol:scope_stack.top()->symbols) {
            assert(basic_symbol->general_type != FUNCTION_TYPE);
            string type = TypeToString(basic_symbol->general_type);
            printID(basic_symbol->name, basic_symbol->offset, type);
            symbols_map.erase(basic_symbol->name);
        }
    }

    scope_stack.pop();
    endScope();
}

SymbolTable::SymbolTable() : current_offset(0), symbols_map(), scope_stack() {
    PushScope(GLOBAL_SCOPE);
    PushDefaultFunctions();

}

void SymbolTable::AddVariable(const STypeSymbolPtr &symbol) {
    assert(!scope_stack.empty());
    symbol->offset = (scope_stack.top()->offset)++;
    scope_stack.top()->symbols.push_back(symbol);
    symbols_map.emplace(symbol->name, symbol);
}

void SymbolTable::AddFunction(const STypeFunctionSymbolPtr &symbol) {
    assert(!scope_stack.empty());
    symbol->offset = 0;
    scope_stack.top()->symbols.push_back(symbol);
    symbols_map.emplace(symbol->name, symbol);
}

bool SymbolTable::IsSymbolDefined(string &symbol_name) {
    return (symbols_map.find(symbol_name) != symbols_map.end());
}

STypeSymbolPtr SymbolTable::GetDefinedSymbol(string &symbol_name) {
    return symbols_map[symbol_name];
}


Scope::Scope(ScopeType scope_type, int offset, Type ret_type, int while_switch_count)
        : scope_type(scope_type), offset(offset), ret_type(ret_type) {

}
