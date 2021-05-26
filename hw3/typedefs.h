#ifndef HW3_TYPEDEFS_H
#define HW3_TYPEDEFS_H

#include <cstdlib>
#include <iostream>
#include <stack>
#include <memory>
#include <vector>
#include <unordered_map>
#include <cassert>
#define YYSTYPE STypePtr

using std::cout;
using std::endl;
using std::stack;
using std::string;
using std::shared_ptr;
using std::pair;
using std::vector;
using std::unordered_map;
using std::dynamic_pointer_cast;

extern int yylineno;
extern char *yytext;

extern int yylex();

extern char textbuff[1024];
extern char *textbuffptr;


enum GeneralTypeEnum {
    VOID_TYPE,
    INT_TYPE,  // this might be a number literal or a variable (same for the others)
    BYTE_TYPE,
    BOOL_TYPE,
    STRING_TYPE,
    FUNCTION_TYPE,
    OTHER_TYPE

};

typedef GeneralTypeEnum Type;

class STypeBase {
    // must have at least one virtual method
public:

    explicit STypeBase(Type type);  // also used for expressions and types

    Type general_type;

    STypeBase();

    virtual ~STypeBase() = default;

};

typedef shared_ptr<STypeBase> STypePtr;
typedef vector<STypeBase> ExpList;

class STypeExpList : public STypeBase {
public:
    ExpList exp_list;
    STypeExpList();
    explicit STypeExpList(ExpList &exp_list);
};

typedef shared_ptr<STypeExpList> STypeExpListPtr;

class STypeCType : public STypeBase {
public:
    explicit STypeCType(Type type);
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

class STypeBool : public STypeBase {
public:
    bool token;
    explicit STypeBool(bool token);
};

typedef shared_ptr<STypeBool> STypeBoolPtr;

class STypeSymbol : public STypeBase {
    // must have at least one virtual method
public:
    string name;
    int offset;
    STypeSymbol(string &name, int offset, Type type);
    virtual ~STypeSymbol() = default;
};

typedef shared_ptr<STypeSymbol> STypeSymbolPtr;
typedef vector<STypeSymbol> ArgList;

class STypeArgList : public STypeBase {
public:
    ArgList arg_list;
    STypeArgList();
    explicit STypeArgList(ArgList &arg_list);
};

typedef shared_ptr<STypeArgList> STypeArgListPtr;


class STypeFunctionSymbol : public STypeSymbol {
public:
    ArgList parameters;
    Type ret_type;

    STypeFunctionSymbol(string &symbol_name, Type symbol_type, ArgList &arg_list);

};

typedef shared_ptr<STypeFunctionSymbol> STypeFunctionSymbolPtr;

extern string TypeToString(Type type);
extern void ArgListToStrings(ArgList &arg_list, vector<string> &string_vector);

#endif //HWw3_TYPEDEFS_H