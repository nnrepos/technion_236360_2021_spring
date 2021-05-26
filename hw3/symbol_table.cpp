#include "symbol_table.h"


void SymbolTable::PushDefaultFunctions() {
    // push print
    string message_name = "message";
    STypeSymbol print_param_symbol(message_name, -1,STRING_TYPE);

    string print_name = "print";
    ArgList print_args;
    print_args.emplace_back(print_param_symbol);
    auto print_func = make_shared<STypeFunctionSymbol>(print_name, VOID_TYPE, print_args);
    AddFunction(print_func);

    // push printi
    string number_name = "number";
    STypeSymbol printi_param_symbol(number_name, -1,INT_TYPE);

    string printi_name = "printi";
    ArgList printi_args;
    printi_args.emplace_back(printi_param_symbol);
    auto printi_func = make_shared<STypeFunctionSymbol>(printi_name, VOID_TYPE, printi_args);
    AddFunction(printi_func);
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

    scope_stack.push(make_shared<Scope>(scope_type, current_offset, ret_type, while_switch_count));
}

void SymbolTable::PushFunctionScope(ScopeType scope_type, Type ret_type, STypeFunctionSymbolPtr function_symbol) {
    assert(!scope_stack.empty());
    int while_switch_count = scope_stack.top()->while_switch_count;
    scope_stack.push(make_shared<Scope>(scope_type, current_offset, ret_type, while_switch_count));

    for (auto param:function_symbol->parameters){
        auto param_symbol = make_shared<STypeSymbol>(param);
        AddParam(param_symbol);
    }
}

void SymbolTable::PopScope() {
    endScope();

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


    current_offset = scope_stack.top()->offset;
    scope_stack.pop();
}

SymbolTable::SymbolTable() : current_offset(0), symbols_map(), scope_stack() {
    PushScope(GLOBAL_SCOPE);
    PushDefaultFunctions();

}

void SymbolTable::AddParam(const STypeSymbolPtr &symbol) {
    assert(!scope_stack.empty());
    scope_stack.top()->symbols.push_back(symbol);
    symbols_map.emplace(symbol->name, symbol);
}

void SymbolTable::AddVariable(const STypeSymbolPtr &symbol) {
    // add params only after adding the function
    assert(!scope_stack.empty());
    symbol->offset = current_offset++;
    scope_stack.top()->symbols.push_back(symbol);
    symbols_map.emplace(symbol->name, symbol);
}

void SymbolTable::AddFunction(const STypeFunctionSymbolPtr &symbol) {
    assert(!scope_stack.empty());

    // set offsets
    symbol->offset = 0;
    auto curr_param_offset = 0;
    for (auto& param:symbol->parameters){
        param.offset = --curr_param_offset;
    }

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
        : scope_type(scope_type), offset(offset), ret_type(ret_type), while_switch_count(while_switch_count) {

}
