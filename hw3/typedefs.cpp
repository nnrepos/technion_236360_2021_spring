#include "typedefs.h"

#include <utility>

STypeBase::STypeBase() : general_type(OTHER_TYPE) {}

STypeBase::STypeBase(Type type) : general_type(type) {}

STypeString::STypeString(string &token) : STypeBase(STRING_TYPE), token(token) {}

STypeNumber::STypeNumber(string &token_string) : STypeBase(INT_TYPE) {
    token = stoi(token_string);
}

STypeCType::STypeCType(Type &type) : type(type) {

}

string TypeToString(Type type) {

    switch (type) {
        case VOID_TYPE:
            return "VOID";
        case INT_TYPE:
            return "INT";
        case BYTE_TYPE:
            return "BYTE";
        case BOOL_TYPE:
            return "BOOL";
        case STRING_TYPE:
            return "STRING";
        default:
            return "OH NOES";
    }

}

void ArgListToStrings(ArgList &arg_list, vector<string> &string_vector) {
    string_vector.clear();
    for (const auto &variable:arg_list) {
        string_vector.push_back(TypeToString(variable.symbol_ret_type));
    }
}

STypeSymbol::STypeSymbol(string &symbol_name, Type symbol_type, int offset) : symbol_name(symbol_name),
                                                                              symbol_ret_type(symbol_type),
                                                                              offset(offset) {

}


STypeVariableSymbol::STypeVariableSymbol(string &symbol_name, Type symbol_type, int offset)
        : STypeSymbol(symbol_name, symbol_type, offset) {

}

STypeArgList::STypeArgList() : arg_list() {

}

STypeArgList::STypeArgList(ArgList &arg_list) : arg_list(arg_list) {

}

STypeFunctionSymbol::STypeFunctionSymbol(string &symbol_name, Type symbol_type, int offset, ArgList &arg_list)
        : STypeSymbol(symbol_name, symbol_type, offset), parameters(arg_list) {

}