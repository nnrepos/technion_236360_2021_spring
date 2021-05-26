#include "semantics.h"

SemanticChecks::SemanticChecks(SymbolTable &table) : table_ref(table) {

}

bool SemanticChecks::IsSymbolDefined(string &name) {
    return table_ref.IsSymbolDefined(name);
}

bool SemanticChecks::IsMainDefined() {
    for (auto map_pair:table_ref.symbols_map) {
        if (map_pair.second->general_type == FUNCTION_TYPE) {
            auto dynamic_cast_function = dynamic_pointer_cast<STypeFunctionSymbol>(map_pair.second);
            if (dynamic_cast_function->name == "main") {
                if (dynamic_cast_function->parameters.empty() && dynamic_cast_function->ret_type == VOID_TYPE) {
                    return true;
                } else {
                    return false;
                }
            }
        }
    }
    return false;
}

bool SemanticChecks::IsLegalAssignTypes(Type first, Type second) {
    if (first == second) {
        return true;
    }
    if (first == INT_TYPE && second == BYTE_TYPE) {
        return true;
    }

    return false;
}

bool SemanticChecks::IsLegalCallTypes(STypeFunctionSymbolPtr &func, STypeExpListPtr &exp_list) {
    if (func->parameters.size() != exp_list->exp_list.size()) {
        return false;
    }

    for (size_t i = 0; i < func->parameters.size(); ++i) {
        if (!IsLegalAssignTypes(func->parameters[i].general_type, exp_list->exp_list[i].general_type)) {
            return false;
        }
    }

    return true;
}

bool SemanticChecks::IsLegalReturnType(Type type) {
    auto required_return_type = table_ref.scope_stack.top()->ret_type;
    return IsLegalAssignTypes(required_return_type, type);
}

bool SemanticChecks::IsBoolType(Type type) {
    return (type == BOOL_TYPE);
}

bool SemanticChecks::IsFunctionType(Type type) {
    return (type == FUNCTION_TYPE);
}

bool SemanticChecks::IsLegalBreak() {
    return (table_ref.scope_stack.top()->inside_while || table_ref.scope_stack.top()->inside_switch);
}

bool SemanticChecks::IsLegalContinue() {
    return (table_ref.scope_stack.top()->inside_while);
}

bool SemanticChecks::IsByteOverflow(int &num) {
    return (num >= 0 && num <= 255);
}

bool SemanticChecks::IsLegalRelopTypes(Type first, Type second) {
    // all numeric types are ok
    if (first == INT_TYPE || first == BYTE_TYPE) {
        if (second == INT_TYPE || second == BYTE_TYPE) {
            return true;
        }
    }
    return false;
}

Type SemanticChecks::CheckAndGetBinOpType(Type first, Type second) {
    if (!IsLegalRelopTypes(first, second)) {
        return OTHER_TYPE;
    }
    if (first == INT_TYPE || second == INT_TYPE) {
        return INT_TYPE;
    }
    return BYTE_TYPE;
}

bool SemanticChecks::IsLegalCast(Type first, Type second) {
    return IsLegalAssignTypes(first, second);
}


