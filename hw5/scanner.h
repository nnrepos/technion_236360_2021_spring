#ifndef HW3_SCANNER_H
#define HW3_SCANNER_H

#include "typedefs.h"
#include "parser.tab.hpp"
#include "hw3_output.hpp"

using namespace output;

char HexaToChar(const char f, const char s) {
    int sum = 0;

    switch (f) {
        case 'a':
            sum += 10;
            break;
        case 'b':
            sum += 11;
            break;
        case 'c':
            sum += 12;
            break;
        case 'd':
            sum += 13;
            break;
        case 'e':
            sum += 14;
            break;
        case 'f':
            sum += 15;
            break;
        case 'A':
            sum += 10;
            break;
        case 'B':
            sum += 11;
            break;
        case 'C':
            sum += 12;
            break;
        case 'D':
            sum += 13;
            break;
        case 'E':
            sum += 14;
            break;
        case 'F':
            sum += 15;
            break;
        default:
            sum += (f - '0');
    }

    sum *= 16;

    switch (s) {
        case 'a':
            sum += 10;
            break;
        case 'b':
            sum += 11;
            break;
        case 'c':
            sum += 12;
            break;
        case 'd':
            sum += 13;
            break;
        case 'e':
            sum += 14;
            break;
        case 'f':
            sum += 15;
            break;
        case 'A':
            sum += 10;
            break;
        case 'B':
            sum += 11;
            break;
        case 'C':
            sum += 12;
            break;
        case 'D':
            sum += 13;
            break;
        case 'E':
            sum += 14;
            break;
        case 'F':
            sum += 15;
            break;
        default:
            sum += (s - '0');
    }
    return char(sum);
}

int LexToken(int bison_enum, string token) {
    STypePtr result = nullptr;

    switch (bison_enum) {
        case NUM: {
            result.reset(new STypeNumber(token));

        }
            break;

        case MULT_DIV:
        case PLUS_MINUS:
        case ID:
        case STRING:
        case INEQUALITY:
        case EQUAL_UNEQUAL: {
            result.reset(new STypeString(token));
        }
            break;

        default:
            break;
    }

    yylval = result;

    return bison_enum;
}

void errorLexAndExit(int lineno){
    errorLex(lineno);
    exit(0);
}

#endif //HW3_SCANNER_H
