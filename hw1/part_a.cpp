#include "tokens.hpp"

char textbuff[1024];
char* textbuffptr;



int main()
{
	int token;
	while((token = yylex())) {
        handleTokenA(token);
	}
	return 0;
}

void handleTokenA(int token) {
    switch (token) {
        case VOID:
            cout << yylineno << " VOID " << "void" << endl;
            break;
        case INT:
            cout << yylineno << " INT " << "int" << endl;
            break;
        case BYTE:
            cout << yylineno << " BYTE " << "byte" << endl;
            break;
        case B:
            cout << yylineno << " B " << "b" << endl;
            break;
        case BOOL:
            cout << yylineno << " BOOL " << "bool" << endl;
            break;
        case AND:
            cout << yylineno << " AND " << "and" << endl;
            break;
        case OR:
            cout << yylineno << " OR " << "or" << endl;
            break;
        case NOT:
            cout << yylineno << " NOT " << "not" << endl;
            break;
        case TRUE:
            cout << yylineno << " TRUE " << "true" << endl;
            break;
        case FALSE:
            cout << yylineno << " FALSE " << "false" << endl;
            break;
        case RETURN:
            cout << yylineno << " RETURN " << "return" << endl;
            break;
        case IF:
            cout << yylineno << " IF " << "if" << endl;
            break;
        case ELSE:
            cout << yylineno << " ELSE " << "else" << endl;
            break;
        case WHILE:
            cout << yylineno << " WHILE " << "while" << endl;
            break;
        case BREAK:
            cout << yylineno << " BREAK " << "break" << endl;
            break;
        case CONTINUE:
            cout << yylineno << " CONTINUE " << "continue" << endl;
            break;
        case SWITCH:
            cout << yylineno << " SWITCH " << "switch" << endl;
            break;
        case CASE:
            cout << yylineno << " CASE " << "case" << endl;
            break;
        case DEFAULT:
            cout << yylineno << " DEFAULT " << "default" << endl;
            break;
        case COLON:
            cout << yylineno << " COLON " << ":" << endl;
            break;
        case SC:
            cout << yylineno << " SC " << ";" << endl;
            break;
        case COMMA:
            cout << yylineno << " COMMA " << "," << endl;
            break;
        case LPAREN:
            cout << yylineno << " LPAREN " << "(" << endl;
            break;
        case RPAREN:
            cout << yylineno << " RPAREN " << ")" << endl;
            break;
        case LBRACE:
            cout << yylineno << " LBRACE " << "{" << endl;
            break;
        case RBRACE:
            cout << yylineno << " RBRACE " << "}" << endl;
            break;
        case ASSIGN:
            cout << yylineno << " ASSIGN " << "=" << endl;
            break;
        case RELOP:
            cout << yylineno << " RELOP " << yytext << endl;
            break;
        case BINOP:
            cout << yylineno << " BINOP " << yytext << endl;
            break;
        case COMMENT:
            cout << yylineno << " COMMENT " << "//" << endl;
            break;
        case ID:
            cout << yylineno << " ID " << yytext << endl;
            break;
        case NUM:
            cout << yylineno << " NUM " << yytext << endl;
            break;
        case STRING:
            cout << yylineno << " STRING " << textbuff << endl;
            break;
        default:
            break;
    }
}
