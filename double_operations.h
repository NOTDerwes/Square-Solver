enum doubles_compare_flag {
    Smaller = -1,
    Equal,
    Bigger
};

bool is_double(double num);
int compare_doubles(double first, double second);
bool equal_doubles(double first, double second);
bool same_double_type(double first, double second);
void swap_doubles(double *first, double *second);


bool is_double(double num) { //checks if number is double-like
    return !isnan(num) && !isinf(num);
}


int compare_doubles(double first, double second) { //compares double values
    double delta = first - second;
    if (delta < -DBL_EPSILON)
        return Smaller;
    else if (delta > DBL_EPSILON)
        return Bigger;
    return Equal;
}


bool same_double_type(double first, double second) { //checks if both doubles are nan, +-inf, jr both not
    if(isinf(first) && isinf(second))
        return signbit(first) == signbit(second);
    return (isnan(first) && isnan(second)) ||
            (is_double(first) && is_double(second));
}

/*checks if both doubles are equal within margin error
also returns TRUE if both of numvers are inf or nan*/
bool equal_doubles(double first, double second) { //
    if (same_double_type(first, second)) {
        if (is_double(first))
            return compare_doubles(first, second) == Equal;
        return true;
    }
    return false;
}


void swap_doubles(double *first, double *second) { //swaps two double numbers
    double temp = *first;
    *first = *second;
    *second = temp;
}
