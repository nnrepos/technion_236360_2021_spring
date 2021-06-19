#include "parser.tab.hpp"
#include "compiler.h"

char textbuff[1024];
char* textbuffptr;

int main(){
    yyparse();

    // moved parse program here because syntax error happens after the reduce
    Compiler::instance().ParseProgram(yylineno);
}