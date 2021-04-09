#ifndef TOKENS_HPP_ 
#define TOKENS_HPP_
#include <cstdlib>

enum tokentype { 
	VOID = 1, 
	INT = 2, 
	BYTE = 3, 
	B = 4, 
	BOOL = 5, 
	AND = 6, 
	OR = 7, 
	NOT = 8, 
	TRUE = 9, 
	FALSE = 10, 
	RETURN = 11, 
	IF = 12, 
	ELSE = 13, 
	WHILE = 14, 
	BREAK = 15, 
	CONTINUE = 16,
	SWITCH = 17,
	CASE = 18,
	DEFAULT = 19,
	COLON = 20,
	SC = 21,
	COMMA = 22,
	LPAREN = 23,
	RPAREN = 24,
	LBRACE = 25,
	RBRACE = 26,
	ASSIGN = 27,
	RELOP = 28,
	BINOP = 29,
	COMMENT = 30,
	ID = 31,
	NUM = 32,
	STRING = 33
}; 
extern int yylineno;
extern char* yytext;
extern size_t yyleng;
extern int yylex(); 

#endif /* TOKENS_HPP_ */