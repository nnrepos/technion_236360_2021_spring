#ifndef HW3_TYPEDEFS_H
#define HW3_TYPEDEFS_H

#include <cstdlib>
#include <iostream>
#include <stack>
#include <memory>
#include <vector>
#include <unordered_map>
#define YYSTYPE STypePtr

using std::cout;
using std::endl;
using std::stack;
using std::string;
using std::shared_ptr;
using std::pair;
using std::vector;
using std::unordered_map;

extern int yylineno;
extern char *yytext;

extern int yylex();

extern char textbuff[1024];
extern char *textbuffptr;


enum GeneralTypeEnum {
    VOID_TYPE,
    INT_TYPE,
    BYTE_TYPE,
    BOOL_TYPE,
    STRING_TYPE,
    FUNCTION_TYPE,
    VARIABLE_TYPE

};

typedef GeneralTypeEnum Type;

typedef vector<pair<Type, int>> ArgList;

class STypeBase {
public:
    explicit STypeBase(Type type);

    Type general_type;

    STypeBase();

};

typedef shared_ptr<STypeBase> STypePtr;

class STypeCType : public STypeBase {
public:
    Type type;
};

typedef shared_ptr<STypeCType> STypeCTypePtr;

class STypeString : public STypeBase {
public:
    string token;
    explicit STypeString(string& token);
};

typedef shared_ptr<STypeString> STypeStringPtr;

class STypeNumber : public STypeBase {
public:
    int token;
    explicit STypeNumber(string& token_string);
};

typedef shared_ptr<STypeNumber> STypeNumberPtr;

class STypeSymbol : public STypeBase {
public:
    string symbol_name;
    Type symbol_type;
    int offset;
};

typedef shared_ptr<STypeSymbol> STypeSymbolPtr;

class STypeArgList : public STypeBase {
public:
    ArgList arg_list;
};

typedef shared_ptr<STypeArgList> STypeArgListPtr;

class STypeVariableSymbol : public STypeSymbol {
public:
};

typedef shared_ptr<STypeVariableSymbol> STypeVariableSymbolPtr;


class STypeFunctionSymbol : public STypeSymbol {
public:
    ArgList parameters;
    Type return_type;
};

typedef shared_ptr<STypeFunctionSymbol> STypeFunctionSymbolPtr;

#endif //HW3_TYPEDEFS_H