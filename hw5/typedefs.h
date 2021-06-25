#ifndef HW3_TYPEDEFS_H
#define HW3_TYPEDEFS_H

#include <cstdlib>
#include <iostream>
#include <stack>
#include <memory>
#include <vector>
#include <unordered_map>
#include <cassert>
#include "bp.hpp"

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
using std::to_string;
using std::move;

extern int yylineno;
extern char *yytext;

extern int yylex();

extern char textbuff[1024];
extern char *textbuffptr;
extern const bool PRINT_DEBUG;


enum GeneralTypeEnum {
    VOID_TYPE,
    INT_TYPE,  // this might be a number literal or a variable (same for the others)
    BYTE_TYPE,
    BOOL_TYPE,
    STRING_TYPE,
    FUNCTION_TYPE,
    STATEMENT_TYPE,
    ERROR_TYPE

};

typedef GeneralTypeEnum Type;
typedef string register_name;
typedef string label_name;

typedef pair<int,BranchLabelIndex> branch_pair;
typedef vector<branch_pair> branch_list;
typedef shared_ptr<branch_list> branch_list_ptr;

typedef pair<int, string> case_label_pair;
typedef vector<case_label_pair> case_label_list;
typedef shared_ptr<case_label_list> case_label_list_ptr;

// stands for... symbol? segfault? something? i dunno
class STypeBase {
    // must have at least one virtual method
public:

    explicit STypeBase(Type type);  // also used for expressions and types

    Type general_type;

    STypeBase();

    virtual ~STypeBase() = default;

};

typedef shared_ptr<STypeBase> STypePtr;
typedef vector<STypePtr> ExpList;

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

class STypeRegister : public STypeBase {
public:
    register_name reg_name;
    STypeRegister(register_name reg_name, Type type);
};

typedef shared_ptr<STypeRegister> STypeRegisterPtr;

class STypeBoolExp : public STypeBase {
public:
    branch_list true_list;
    branch_list false_list;
    STypeBoolExp(branch_list true_list, branch_list false_list);
};

typedef shared_ptr<STypeBoolExp> STypeBoolExpPtr;

class STypeStatement : public STypeBase {
public:
    branch_list next_list;
    explicit STypeStatement(branch_list next_list);
};

typedef shared_ptr<STypeStatement> STypeStatementPtr;

class STypeNumber : public STypeBase {
public:
    int token;
    explicit STypeNumber(string& token_string);
};

typedef shared_ptr<STypeNumber> STypeNumberPtr;

class STypeSymbol : public STypeBase {
    // no virtual method needed
public:
    string name;
    int offset;
    STypeSymbol(string &name, int offset, Type type);
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

class STypeCaseList : public STypeBase {
public:
    case_label_list case_list;
    string default_label;
    branch_list next_list;
    STypeCaseList(case_label_list case_list, string default_label, branch_list next_list);
};

typedef shared_ptr<STypeCaseList> STypeCaseListPtr;

class STypeCaseDecl : public STypeBase {
public:
    int case_num;
    string case_label;
    branch_list next_list;
    STypeCaseDecl(int case_num, string case_label, branch_list next_list);
};

typedef shared_ptr<STypeCaseDecl> STypeCaseDeclPtr;

extern string TypeToString(Type type);
extern void ArgListToStrings(ArgList &arg_list, vector<string> &string_vector);

class Scope;
typedef shared_ptr<Scope> ScopePtr;

#endif //HWw3_TYPEDEFS_H