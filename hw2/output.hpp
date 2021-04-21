#ifndef _236360_2_
#define _236360_2_

#include <string>
#include <iostream>
#include <sstream>
using std::cout;
using std::endl;
using std::string;

extern int yylineno;
extern char* yytext;
extern int yylex();
extern int yyparse();
int yyerror(const char * message);

extern char textbuff[1024];
extern char* textbuffptr;

namespace output {
	extern const string rules[];
    void printProductionRule(int ruleno);
    void errorLex(int lineno);
    void errorSyn(int lineno);
};

using namespace output;

#endif
