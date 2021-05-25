#include "typedefs.h"

STypeBase::STypeBase(): general_type(STRING_TYPE){}
STypeBase::STypeBase(Type type): general_type(type){}

STypeString::STypeString(string& token):STypeBase(STRING_TYPE), token(token) {}

STypeNumber::STypeNumber(string& token_string):STypeBase(INT_TYPE) {
    token = stoi(token_string);
}
