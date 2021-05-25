#ifndef HW3_SCANNER_H
#define HW3_SCANNER_H

#include "typedefs.h"
#include "parser.tab.hpp"
#include "hw3_output.hpp"

using namespace output;




char HexaToChar(char f, char s);

int LexToken(int bison_enum, string token) {
    STypePtr result(nullptr);

    switch (bison_enum) {
        case ID: {
            STypeStringPtr new_result(new STypeString(token));
            result = new_result;
        }
            break;
        case NUM: {
            STypeNumberPtr new_result(new STypeNumber(token));
            result = new_result;
        }
            break;
        case MULT_DIV:
        case PLUS_MINUS: {
            STypeStringPtr new_result(new STypeString(token));
            result = new_result;
        }
            break;
        case STRING: {
            STypeStringPtr new_result(new STypeString(token));
            result = new_result;
        }
            break;
        case INEQUALITY:
        case EQUAL_UNEQUAL: {
            STypeStringPtr new_result(new STypeString(token));
            result = new_result;
        }
            break;
        default:
            break;

    }

    yylval = result;

    return bison_enum;
}

#endif //HW3_SCANNER_H
