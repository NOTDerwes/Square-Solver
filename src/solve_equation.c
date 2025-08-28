/*!
 * @file solve_equation.c
 * @brief Модуль решения квадратных и линейных уравнений
 * @author NOTDerwes
 * @date 25.08.2025
 *
 * Модуль предоставляет функции для решения квадратных уравнений вида @f$ ax^2 + bx + c = 0 @f$
 * и линейных уравнений вида @f$ kx + b = 0 @f$ с решением частных случаев.
 * @note Описание функций см. в solve_equation.h
 */

#include <math.h>

#include "solve_equation.h"
#include "double_operations.h"
#include "myassert.h"

void solve_square_equation(Coeffs equation_coeffs,
                           Roots *equation_roots) {
    double a = equation_coeffs.a;
    double b = equation_coeffs.b;
    double c = equation_coeffs.c;
    double *x1 = &(equation_roots -> x1);
    double *x2 = &(equation_roots -> x2);
    int *roots_amount = &(equation_roots -> amount);

    MYASSERT(x1, "NULL pointer on x1");
    MYASSERT(x2, "NULL pointer on x2");
    MYASSERT(!isnan(a), "a is nan");
    MYASSERT(!isnan(b), "b is nan");
    MYASSERT(!isnan(c), "c is nan");


    *roots_amount = ZeroRoots;

    if (is_zero(a)) {
        solve_linear_equation(b, c, x1, roots_amount);
        return;
    }
    else {
        double discriminant = b * b - 4 * a * c;
        if (discriminant > 0) {
            *x1 = (-b - sqrt(discriminant)) / (2 * a);
            *x2 = (-b + sqrt(discriminant)) / (2 * a);
            *roots_amount = TwoRoots;
        }
        else if (is_zero(discriminant)) {
            *x1 = -b / (2 * a);
            *roots_amount = OneRoot;
        }
    }

    if (is_zero(*x1))
        *x1 = 0;

    if (is_zero(*x2))
        *x2 = 0;
}


void solve_linear_equation(double k, double b,
                           double *x,
                           int *roots_amount) {
    if (is_zero(k)) {
            if (is_zero(b))
                *roots_amount = UndefinedRoot;
        }
        else {
            *x = -b / k;
            *roots_amount = OneRoot;
        }
    if (is_zero(*x))
        *x = 0;
}


void reset_structs(Coeffs *reseting_coeffs,
                   Roots *reseting_roots) { /// set all Coeffs and Roots structure elements default value
    reseting_coeffs -> a = NAN;
    reseting_coeffs -> b = NAN;
    reseting_coeffs -> c = NAN;
    reseting_roots -> x1 = NAN;
    reseting_roots -> x2 = NAN;
    reseting_roots -> amount = UndigistedRoot;
}
