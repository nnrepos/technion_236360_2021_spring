#include "tokens.hpp"

char textbuff[1024];
char *textbuffptr;

int main() {
    int token;
    stack<char> paren_stack;
    int tabs = 0;
    while ((token = yylex())) {
        tabs = handleTokenB(token, tabs, paren_stack);
    }
    if (tabs > 0){
        cout << "Error: Bad Expression" << endl;
        exit(1);
    }
    return 0;
}

int handleTokenB(int token, int tabs, stack<char> &paren_stack) {
    switch (token) {
        case VOID:
            cout << "Error: VOID" << endl;
            exit(1);
        case INT:
            cout << "Error: INT" << endl;
            exit(1);
        case BYTE:
            cout << "Error: BYTE" << endl;
            exit(1);
        case B:
            cout << "Error: B" << endl;
            exit(1);
        case BOOL:
            cout << "Error: BOOL" << endl;
            exit(1);
        case AND:
            cout << "Error: AND" << endl;
            exit(1);
        case OR:
            cout << "Error: OR" << endl;
            exit(1);
        case NOT:
            cout << "Error: NOT" << endl;
            exit(1);
        case TRUE:
            cout << "Error: TRUE" << endl;
            exit(1);
        case FALSE:
            cout << "Error: FALSE" << endl;
            exit(1);
        case RETURN:
            cout << "Error: RETURN" << endl;
            exit(1);
        case IF:
            cout << "Error: IF" << endl;
            exit(1);
        case ELSE:
            cout << "Error: ELSE" << endl;
            exit(1);
        case WHILE:
            cout << "Error: WHILE" << endl;
            exit(1);
        case BREAK:
            cout << "Error: BREAK" << endl;
            exit(1);
        case CONTINUE:
            cout << "Error: CONTINUE" << endl;
            exit(1);
        case SWITCH:
            cout << "Error: SWITCH" << endl;
            exit(1);
        case CASE:
            cout << "Error: CASE" << endl;
            exit(1);
        case DEFAULT:
            cout << "Error: DEFAULT" << endl;
            exit(1);
        case COLON:
            cout << "Error: COLON" << endl;
            exit(1);
        case SC:
            cout << "Error: SC" << endl;
            exit(1);
        case COMMA:
            cout << "Error: COMMA" << endl;
            exit(1);
        case LPAREN:
            paren_stack.push('(');
            cout << string(tabs, '\t') << "(" << endl;
            return (tabs + 1);
        case RPAREN:
            if (paren_stack.empty() || paren_stack.top() != '(') {
                cout << "Error: Bad Expression" << endl;
                exit(1);
            } else {
                paren_stack.pop();
            }
            tabs--;
            cout << string(tabs, '\t') << ")" << endl;
            return (tabs);
        case LBRACE:
            paren_stack.push('{');
            cout << string(tabs, '\t') << "{" << endl;
            return (tabs + 1);
        case RBRACE:
            if (paren_stack.empty() || paren_stack.top() != '{') {
                cout << "Error: Bad Expression" << endl;
                exit(1);
            } else {
                paren_stack.pop();
            }
            tabs--;
            cout << string(tabs, '\t') << "}" << endl;
            return (tabs);
        case ASSIGN:
            cout << "Error: ASSIGN" << endl;
            exit(1);
        case RELOP:
            cout << "Error: RELOP" << endl;
            exit(1);
        case BINOP:
            cout << "Error: BINOP" << endl;
            exit(1);
        case COMMENT:
            cout << "Error: COMMENT" << endl;
            exit(1);
        case ID:
            cout << "Error: ID" << endl;
            exit(1);
        case NUM:
            cout << "Error: NUM" << endl;
            exit(1);
        case STRING:
            cout << "Error: STRING" << endl;
            exit(1);
        default:
            break;
    }
    return tabs;
}