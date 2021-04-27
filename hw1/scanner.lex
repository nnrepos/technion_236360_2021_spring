%{
#include "tokens.hpp"
%}

%option yylineno
%option noyywrap
%option nounput

digit			([0-9])
nonzerodigit	([1-9])
hexdigit		([0-9a-fA-F])
letter			([a-zA-Z])
leORdi			([0-9a-zA-Z])
lineComment		\/\/[^\n\r]*
whitespace		[ \t\r\n]
strsign			\"
EOF				\x0A
bs				\x5C
fs				\x2F
cr				\x0D
lf				\x0A

%x STR
%x STRES
%x STRESX
%x STRESE
%%

"void"						return VOID;
"int"						return INT;
"byte" 						return BYTE;
"b"							return B;
"bool"						return BOOL;
"and" 						return AND;
"or" 						return OR;
"not" 						return NOT;
"true" 						return TRUE;
"false" 					return FALSE;
"return" 					return RETURN;
"if" 						return IF;
"else" 						return ELSE;
"while" 					return WHILE;
"break" 					return BREAK;
"continue"					return CONTINUE;
"switch"					return SWITCH;
"case"		    			return CASE;
"default"					return DEFAULT;
":"	        				return COLON;
";" 						return SC;
"," 						return COMMA;
"(" 						return LPAREN;
")" 						return RPAREN;
"{" 						return LBRACE;
"}" 						return RBRACE;
[!<>=]"="					return RELOP;
[<>]						return RELOP;
"=" 						return ASSIGN;
[-+*]						return BINOP;
{fs}						return BINOP;
{lineComment}				return COMMENT;
{letter}{leORdi}*			return ID;
"0"							return NUM;
{nonzerodigit}{digit}* 		return NUM;
<INITIAL>{strsign}			textbuffptr = textbuff; BEGIN(STR);
<STR>{lf}					printf("Error unclosed string\n");	exit(1);
<STR>{cr}					printf("Error unclosed string\n");	exit(1);
<STR>{bs}					BEGIN(STRES)  ;
<STR>{strsign}				*textbuffptr = '\0';	BEGIN(INITIAL);	return STRING;
<STR>.						*textbuffptr = *yytext;	textbuffptr++;
<STRES>{strsign}			*textbuffptr = '\"';	textbuffptr++;	BEGIN(STR);
<STRES>"n"					*textbuffptr = '\n';	textbuffptr++;	BEGIN(STR);
<STRES>"r"					*textbuffptr = '\r';	textbuffptr++;	BEGIN(STR);
<STRES>{bs}					*textbuffptr = '\\';	textbuffptr++;	BEGIN(STR);
<STRES>"t"					*textbuffptr = '\t';	textbuffptr++;	BEGIN(STR);
<STRES>"0"					*textbuffptr = '\0';	textbuffptr++;	BEGIN(STR);
<STRES>"x"					BEGIN(STRESX);
<STRES>.					textbuffptr = textbuff;	*textbuffptr++ = *yytext; BEGIN(STRESE);
<STRESX>[0-7]{hexdigit}     *textbuffptr = hexaToChar(yytext[0], yytext[1]);	textbuffptr++;	BEGIN(STR);
<STRESX>{strsign}			printf("Error undefined escape sequence x\n");	exit(1);
<STRESX>({lf}|{cr})			printf("Error unclosed string\n");	exit(1);
<STRESX>.{strsign}			printf("Error undefined escape sequence x%c\n", yytext[0]);	exit(1);
<STRESX>.({lf}|{cr})		printf("Error unclosed string\n");	exit(1);
<STRESX>..					textbuffptr = textbuff; *textbuffptr++ = 'x';*textbuffptr++ = yytext[0]; *textbuffptr++ = yytext[1]; BEGIN(STRESE);
<STRESE>{strsign}			*textbuffptr = '\0';	printf("Error undefined escape sequence %s\n", textbuff);	exit(1);
<STRESE>({lf}|{cr})			printf("Error unclosed string\n");	exit(1);
<STRESE>.					;
<STR,STRES,STRESX><<EOF>>	printf("Error unclosed string\n");	exit(1);
{whitespace}				;
.							printf("Error %s\n", yytext);	exit(1);

%%

char hexaToChar(const char f,const char s){
	int sum = 0;

	switch(f){
	        case 'a': sum += 10; break;
            case 'b': sum += 11; break;
            case 'c': sum += 12; break;
            case 'd': sum += 13; break;
            case 'e': sum += 14; break;
            case 'f': sum += 15; break;
			case 'A': sum += 10; break;
			case 'B': sum += 11; break;
			case 'C': sum += 12; break;
			case 'D': sum += 13; break;
			case 'E': sum += 14; break;
			case 'F': sum += 15; break;
			default: sum += (f - '0');
	}

	sum *= 16;

	switch(s){
	        case 'a': sum += 10; break;
            case 'b': sum += 11; break;
            case 'c': sum += 12; break;
            case 'd': sum += 13; break;
            case 'e': sum += 14; break;
            case 'f': sum += 15; break;
			case 'A': sum += 10; break;
			case 'B': sum += 11; break;
			case 'C': sum += 12; break;
			case 'D': sum += 13; break;
			case 'E': sum += 14; break;
			case 'F': sum += 15; break;
			default: sum += (s - '0');
	}
	return char(sum);
}