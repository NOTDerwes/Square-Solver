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

#include "../headers/solve_equation.h"
#include "../headers/double_operations.h"
#include "../headers/myassert.h"

int solve_square_equation(SquareEquation *equation) {
    double a = equation -> coeffs.a;
    double b = equation -> coeffs.b;
    double c = equation -> coeffs.c;
    double *x1 = &(equation -> roots.x1);
    double *x2 = &(equation -> roots.x2);
    int *roots_amount = &(equation -> roots.amount);

    #ifdef NDEBUG
        MYASSERT(x1, "NULL pointer on x1");
        MYASSERT(x2, "NULL pointer on x2");
        MYASSERT(!isnan(a), "a is nan");
        MYASSERT(!isnan(b), "b is nan");
        MYASSERT(!isnan(c), "c is nan");
    #endif

    if (!is_normal_double(a) || !is_normal_double(b) || !is_normal_double(c)) {
        fprintf(stderr, CONSOLE_ERROR_MESSAGE("GOT NAN COEFFICIENT"));
        return WRONGARG;
    }

    *roots_amount = ZeroRoots;

    if (is_zero(a)) {
        if (solve_linear_equation(b, c, x1, roots_amount) == SOLVED)
            return SOLVED;
        else
            return RESERR;
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

    if (*roots_amount == ZeroRoots || *roots_amount == UndefinedRoot) {
        if (is_normal_double(*x1) || is_normal_double(*x2))
            return RESERR;
    }
    else if (*roots_amount == OneRoot) {
        if (!is_normal_double(*x1) || is_normal_double(*x2))
            return RESERR;
    }
    else if (*roots_amount == TwoRoots) {
        if (!is_normal_double(*x1) || !is_normal_double(*x2))
            return RESERR;
    }

    return SOLVED;
}


int solve_linear_equation(double k, double b,
                          double *x,
                          int *roots_amount) {
    if (!is_normal_double(k) || !is_normal_double(b))
        return WRONGARG;

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

    if (*roots_amount == UndefinedRoot && is_normal_double(*x))
        return RESERR;
    else if (*roots_amount == OneRoot && !is_normal_double(*x))
        return RESERR;

    return SOLVED;
}


int reset_structs(SquareEquation *reseting_equation) { /// set all Coeffs and Roots structure elements default value
    reseting_equation -> coeffs.a = NAN;
    reseting_equation -> coeffs.b = NAN;
    reseting_equation -> coeffs.c = NAN;
    reseting_equation -> roots.x1 = NAN;
    reseting_equation -> roots.x2 = NAN;
    reseting_equation -> roots.amount = UndigistedRoot;

    return SOLVED;
}
