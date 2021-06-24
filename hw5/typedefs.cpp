#include "typedefs.h"

#include <utility>

STypeBase::STypeBase() : general_type(ERROR_TYPE) {}

STypeBase::STypeBase(Type type) : general_type(type) {}

STypeString::STypeString(string &token) : STypeBase(STRING_TYPE), token(token) {}

STypeNumber::STypeNumber(string &token_string) : STypeBase(INT_TYPE) {
    token = stoi(token_string);
}

STypeCType::STypeCType(Type type) : STypeBase(type) {

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

STypeFunctionSymbol::STypeFunctionSymbol(string &symbol_name, Type symbol_type, ArgList &arg_list)
        : STypeSymbol(symbol_name, 0, FUNCTION_TYPE), parameters(arg_list), ret_type(symbol_type) {

}

STypeExpList::STypeExpList() : exp_list() {

}

STypeExpList::STypeExpList(ExpList &exp_list) : exp_list(exp_list) {

}

STypeRegister::STypeRegister(register_name reg_name, Type type) : STypeBase(type), reg_name(move(reg_name)) {

}

STypeStatement::STypeStatement(branch_list next_list) : STypeBase(STATEMENT_TYPE), next_list(move(next_list)) {

}

STypeBoolExp::STypeBoolExp(branch_list true_list, branch_list false_list) : STypeBase(BOOL_TYPE),
                                                                            true_list(move(true_list)),
                                                                            false_list(move(false_list)) {

}

STypeCaseList::STypeCaseList(case_label_list case_list, string default_label, branch_list next_list) :
        case_list(move(case_list)), default_label(move(default_label)), next_list(move(next_list)) {

}

STypeCaseDecl::STypeCaseDecl(int case_num, string case_label, branch_list next_list):
        case_num(case_num), case_label(move(case_label)), next_list(move(next_list)) {

}
