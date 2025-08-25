/*!
 * @file double_operations.c
 * @brief Модуль операций над числами типа double
 * @author NOTDerwes
 * @date 25.08.2025
 *
 * Модуль предоставляет функции для работы с числами типа double,
 * включая сравнение, проверку специальных значений и операции с учётом
 * погрешности вычислений с плавающей точкой.
 * @note Описание функций см. в double_operations.h
 */

#include <float.h>
#include <math.h>

#include "double_operations.h"

bool is_double(double num) {
    return !isnan(num) && !isinf(num);
}


int compare_doubles(double first, double second) {
    double delta = first - second;

    if (!is_double(first) || !is_double(second))
        return NotDouble;

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


bool absolutely_same_doubles(double first, double second) {
    if (same_double_type(first, second)) {
        if (is_double(first))
            return compare_doubles(first, second) == Equal;
        return true;
    }
    return false;
}


void swap_doubles(double *first, double *second) {
    double temp = *first;
    *first = *second;
    *second = temp;
}

bool is_zero(double number) {
    return absolutely_same_doubles(number, ZERO);
}
