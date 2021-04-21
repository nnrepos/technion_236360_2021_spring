#include "output.hpp"
#include "parser.tab.hpp"

// used in scanner.lex
char textbuff[1024];
char* textbuffptr;

int main()
{
    yyparse();
	return 0;
}
