#ifndef HW3_SCANNER_H
#define HW3_SCANNER_H

#include "typedefs.h"
#include "parser.tab.hpp"
#include "hw3_output.hpp"

using namespace output;




char HexaToChar(char f, char s);

int LexToken(int bison_enum, string token) {
    STypePtr result = nullptr;

    switch (bison_enum) {
        case NUM: {
            result.reset(new STypeNumber(token));

        }
            break;

        case MULT_DIV:
        case PLUS_MINUS: {
            result.reset(new STypeString(token));
        }
            break;

        case ID:
        case STRING: {
            result.reset(new STypeString(token));
        }
            break;

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

#endif //HW3_SCANNER_H
