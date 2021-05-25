#include "symbol_table.h"


Scope::Scope(ScopeType type, int offset) : type(type), offset(offset), symbols() {

}

void SymbolTable::PushDefaultFunctions() {
    // print print, then printi
}

void SymbolTable::PushScope(ScopeType scope_type) {
    scope_stack.push(new Scope(scope_type, current_offset));

}

void SymbolTable::PopScope() {
    // in global scope - functions only; in non-global scope - variables only
    if (scope_stack.top()->type == GLOBAL_SCOPE) {
        for (auto func_symbol:scope_stack.top()->symbols) {
            assert(func_symbol->general_type == FUNCTION_TYPE);
            auto casted_func = dynamic_pointer_cast<STypeFunctionSymbol>(func_symbol);
            vector<string> string_types;
            ArgListToStrings(casted_func->parameters, string_types);
            string ret_type = TypeToString(casted_func->symbol_ret_type);
            printID(casted_func->symbol_name, 0, makeFunctionType(ret_type, string_types));

        }

    } else {
        for (const auto& var_symbol:scope_stack.top()->symbols) {
            assert(var_symbol->general_type == VARIABLE_TYPE);
            auto casted_var = dynamic_pointer_cast<STypeVariableSymbol>(var_symbol);
            string type = TypeToString(casted_var->symbol_ret_type);
            printID(casted_var->symbol_name,casted_var->offset, type);

        }
    }

    scope_stack.pop();
    endScope();
}

SymbolTable::SymbolTable() : current_offset(0), symbols_map(), scope_stack() {
    PushScope(GLOBAL_SCOPE);
    PushDefaultFunctions();

}


