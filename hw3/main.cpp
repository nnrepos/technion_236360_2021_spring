#include "parser.tab.hpp"

char textbuff[1024];
char* textbuffptr;

int main(){
    return yyparse();
}