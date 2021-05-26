#include "typedefs.h"

#include <utility>

STypeBase::STypeBase() : general_type(OTHER_TYPE) {}

STypeBase::STypeBase(Type type) : general_type(type) {}

STypeString::STypeString(string &token) : STypeBase(STRING_TYPE), token(token) {}

STypeNumber::STypeNumber(string &token_string) : STypeBase(INT_TYPE) {
    token = stoi(token_string);
}

STypeBool::STypeBool(bool token) : STypeBase(BOOL_TYPE), token(token) {
}

STypeCType::STypeCType(Type type) : STypeBase(TYPE_TYPE), type(type) {

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
    for (const auto &exp:arg_list) {
        string_vector.push_back(TypeToString(exp.general_type));
    }
}

STypeSymbol::STypeSymbol(string &name, int offset, Type type) : STypeBase(type), name(name),
                                                                offset(offset) {

}


STypeArgList::STypeArgList() : arg_list() {

}

STypeArgList::STypeArgList(ArgList &arg_list) : arg_list(arg_list) {

}

STypeFunctionSymbol::STypeFunctionSymbol(string &symbol_name, Type symbol_type, int offset, ArgList &arg_list)
        : STypeSymbol(symbol_name, offset, FUNCTION_TYPE), parameters(arg_list), ret_type(symbol_type) {

}

STypeExpList::STypeExpList(): exp_list() {

}

STypeExpList::STypeExpList(ExpList &exp_list): exp_list(exp_list) {

}
