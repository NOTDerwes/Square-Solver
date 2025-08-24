#ifndef DOUBLE_OPERATIONS_H
#define DOUBLE_OPERATIONS_H
#include <stdbool.h>

/** Zero value */
#define ZERO 0

/** Flags of comparing two double numbers */
enum doubles_compare_flag {
    Smaller = -1,
    Equal = 0,
    Bigger = 1
};

/** Returns true if double isn't inf, -inf and NAN, reurns false otherwise */
bool is_double(double num);
/** Function compare two double values.
Returns Smaller if first double smaller than second,
returns Bigger if first double bigger than second,
returns Equals if first double equals second */
int compare_doubles(double first, double second);
/** Returns true if both numbers have same value (including NAN, inf, -inf), returns 0 otherwise */
bool absolutely_same_doubles(double first, double second);
/** Returns true if both numbers are NAN, inf or -inf or both are not NAN, inf and -inf,
returns false otherwise*/
bool same_double_type(double first, double second);
/** Swap values of two double numbers */
void swap_doubles(double *first, double *second);
/** Returns true if number equals zero within the margin of error, retuns false otherwise */
bool is_zero(double number)

#endif
