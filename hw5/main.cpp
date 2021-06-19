#include "parser.tab.hpp"
#include "parse_utils.h"

char textbuff[1024];
char* textbuffptr;

int main(){
    yyparse();

    // moved parse program here because syntax error happens after the reduce
    ParseUtils::instance().ParseProgram(yylineno);
}