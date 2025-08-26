#include <stdio.h>
#include "string_operations.h"

bool check_EOF(int symbol_eof) {
    return symbol_eof == EOF;
}


bool letters_left() {
    if (getchar() != '\n')
        return 1;
    return 0;
}


void clean_buffer() {
    while (getchar() != '\n') {}
}
