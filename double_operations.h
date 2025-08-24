#ifndef DOUBLE_OPERATIONS_H
#define DOUBLE_OPERATIONS_H
#include <stdbool.h>

enum doubles_compare_flag {
    Smaller = -1,
    Equal = 0,
    Bigger = 1
};

bool is_double(double num);
int compare_doubles(double first, double second);
bool equal_doubles(double first, double second);
bool same_double_type(double first, double second);
void swap_doubles(double *first, double *second);

#endif
