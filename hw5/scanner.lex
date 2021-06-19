%{
#include "scanner.h"
%}

%option yylineno
%option noyywrap
%option nounput

digit			([0-9])
nonzerodigit	([1-9])
hexdigit		([0-9a-fA-F])
letter			([a-zA-Z])
alphanum		([0-9a-zA-Z])
lineComment		\/\/[^\n\r]*
whitespace		[ \t\r\n]
strsign			\"
EOF				\x0A
bs				\x5C
fs				\x2F
cr				\x0D
lf				\x0A
equalUnequal    (==|!=)
inequality      (<|>|<=|>=)
multDiv         (\*|[/])
plusMinus       (\+|-)

%x STR
%x STRES
%x STRESX
%x STRESE

%%

"void"						return LexToken(VOID, yytext);
"int"						return LexToken(INT, yytext);
"byte" 						return LexToken(BYTE, yytext);
"b"							return LexToken(B, yytext);
"bool"						return LexToken(BOOL, yytext);
"and" 						return LexToken(AND, yytext);
"or" 						return LexToken(OR, yytext);
"not" 						return LexToken(NOT, yytext);
"true" 						return LexToken(TRUE, yytext);
"false" 					return LexToken(FALSE, yytext);
"return" 					return LexToken(RETURN, yytext);
"if" 						return LexToken(IF, yytext);
"else" 						return LexToken(ELSE, yytext);
"while" 					return LexToken(WHILE, yytext);
"break" 					return LexToken(BREAK, yytext);
"continue"					return LexToken(CONTINUE, yytext);
"switch"					return LexToken(SWITCH, yytext);
"case"		    			return LexToken(CASE, yytext);
"default"					return LexToken(DEFAULT, yytext);
":"	        				return LexToken(COLON, yytext);
";" 						return LexToken(SC, yytext);
"," 						return LexToken(COMMA, yytext);
"(" 						return LexToken(LPAREN, yytext);
")" 						return LexToken(RPAREN, yytext);
"{" 						return LexToken(LBRACE, yytext);
"}" 						return LexToken(RBRACE, yytext);
{equalUnequal}				return LexToken(EQUAL_UNEQUAL, yytext);
{inequality}				return LexToken(INEQUALITY, yytext);
"=" 						return LexToken(ASSIGN, yytext);
{multDiv}					return LexToken(MULT_DIV, yytext);
{plusMinus}					return LexToken(PLUS_MINUS, yytext);
{lineComment}				;
{letter}{alphanum}*			return LexToken(ID, yytext);
"0"							return LexToken(NUM, yytext);
{nonzerodigit}{digit}* 		return LexToken(NUM, yytext);
<INITIAL>{strsign}			textbuffptr = textbuff; BEGIN(STR);
<STR>{lf}					errorLexAndExit(yylineno);
<STR>{cr}					errorLexAndExit(yylineno);
<STR>{bs}					BEGIN(STRES)  ;
<STR>{strsign}				*textbuffptr = '\0';	BEGIN(INITIAL);	return LexToken(STRING, string(textbuff));
<STR>.						*textbuffptr = *yytext;	textbuffptr++;
<STRES>{strsign}			*textbuffptr = '\"';	textbuffptr++;	BEGIN(STR);
<STRES>"n"					*textbuffptr = '\n';	textbuffptr++;	BEGIN(STR);
<STRES>"r"					*textbuffptr = '\r';	textbuffptr++;	BEGIN(STR);
<STRES>{bs}					*textbuffptr = '\\';	textbuffptr++;	BEGIN(STR);
<STRES>"t"					*textbuffptr = '\t';	textbuffptr++;	BEGIN(STR);
<STRES>"0"					*textbuffptr = '\0';	textbuffptr++;	BEGIN(STR);
<STRES>"x"					BEGIN(STRESX);
<STRES>.					textbuffptr = textbuff;	*textbuffptr++ = *yytext; BEGIN(STRESE);
<STRESX>[0-7]{hexdigit}     *textbuffptr = HexaToChar(yytext[0], yytext[1]);	textbuffptr++;	BEGIN(STR);
<STRESX>{strsign}			errorLexAndExit(yylineno);
<STRESX>({lf}|{cr})			errorLexAndExit(yylineno);
<STRESX>.{strsign}			errorLexAndExit(yylineno);
<STRESX>.({lf}|{cr})		errorLexAndExit(yylineno);
<STRESX>..					textbuffptr = textbuff; *textbuffptr++ = 'x';*textbuffptr++ = yytext[0]; *textbuffptr++ = yytext[1]; BEGIN(STRESE);
<STRESE>{strsign}			errorLexAndExit(yylineno);
<STRESE>({lf}|{cr})			errorLexAndExit(yylineno);
<STRESE>.					;
<STR,STRES,STRESX><<EOF>>	errorLexAndExit(yylineno);
{whitespace}				;
.							errorLexAndExit(yylineno);

%%
