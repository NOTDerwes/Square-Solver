#include <math.h>
#include <float.h>
#include <stdbool.h>

enum doubles_compare_flag {
    Smaller = -1,
    Equal,
    Bigger
};

bool is_double(double num);
int compare_doubles(double first, double second);
bool equal_doubles(double first, double second);
bool same_double_type(double first, double second);


bool is_double(double num) { //checks if number is double-like
    return !isnan(num) && !isinf(num);
}


int compare_doubles(double first, double second) {
    double delta = first - second;
    if (delta < -DBL_EPSILON)
        return Smaller;
    else if (delta > DBL_EPSILON)
        return Bigger;
    return Equal;
}


bool same_double_type(double first, double second) {
    if(isinf(first) && isinf(second))
        return signbit(first) == signbit(second);
    return (isnan(first) && isnan(second)) ||
            (is_double(first) && is_double(second));
}


bool equal_doubles(double first, double second) {
    if (same_double_type(first, second)) {
        if (is_double(first))
            return compare_doubles(first, second) == Equal;
        return true;
    }
    return false;
}
