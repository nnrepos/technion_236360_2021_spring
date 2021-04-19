#include <iostream>
#include "output.hpp"
#include <sstream>

using namespace std;

const string output::rules[] = {
	"Program -> Funcs", // 1
	"Funcs -> epsilon",
	"Funcs -> FuncDecl Funcs",
	"FuncDecl -> RetType ID LPAREN Formals RPAREN LBRACE Statements RBRACE",
	"RetType -> Type", // 5
	"RetType ->  VOID",
	"Formals -> epsilon",
	"Formals -> FormalsList",
	"FormalsList -> FormalDecl",
	"FormalsList -> FormalDecl COMMA FormalsList", // 10
	"FormalDecl -> Type ID",
	"Statements -> Statement",
	"Statements -> Statements Statement",
	"Statement -> LBRACE Statements RBRACE",
	"Statement -> Type ID SC", // 15
	"Statement -> Type ID ASSIGN Exp SC",
	"Statement -> ID ASSIGN Exp SC",
	"Statement -> Call SC",
	"Statement -> RETURN SC",
	"Statement -> RETURN Exp SC", // 20
	"Statement -> IF LPAREN Exp RPAREN Statement",
	"Statement -> IF LPAREN Exp RPAREN Statement ELSE Statement",
	"Statement -> WHILE LPAREN Exp RPAREN Statement",
	"Statement -> BREAK SC",
	"Statement -> CONTINUE SC", // 25
	"Statement -> SWITCH LPAREN Exp RPAREN LBRACE CaseList RBRACE",
	"Call -> ID LPAREN ExpList RPAREN",
	"Call -> ID LPAREN RPAREN",
	"ExpList -> Exp",
	"ExpList -> Exp COMMA ExpList", // 30
	"Type -> INT", 
	"Type -> BYTE",
	"Type -> BOOL",
	"Exp -> LPAREN Exp RPAREN",
	"Exp -> Exp BINOP Exp", // 35
	"Exp -> ID",
	"Exp -> Call",
	"Exp -> NUM",
	"Exp -> NUM B",
	"Exp -> STRING", // 40
	"Exp -> TRUE",
	"Exp -> FALSE",
	"Exp -> NOT Exp",
	"Exp -> Exp AND Exp",
	"Exp -> Exp OR Exp", // 45
	"Exp -> Exp RELOP Exp",
	"Exp -> LPAREN Type RPAREN Exp",
	"CaseList -> CaseDecl CaseList",
	"CaseList -> CaseDecl",
	"CaseList -> DEFAULT COLON Statements", // 50
	"CaseDecl -> CASE NUM COLON Statements"
};

void output::printProductionRule(int ruleno) {
	cout << ruleno << ": " << output::rules[ruleno-1] << endl;
}

void output::errorLex(int lineno){
    cout << "line " << lineno << ": " << "lexical error" << endl;
}

void output::errorSyn(int lineno){
    cout << "line " << lineno << ": " << "syntax error" << endl;
}

