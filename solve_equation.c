#include <math.h>
#include <assert.h>

#include "solve_equation.h"
#include "double_operations.h"

void solve_square_equation(struct Coeffs equation_coeffs,
                           struct Roots *equation_roots) {
    double a = equation_coeffs.a, b = equation_coeffs.b, c = equation_coeffs.c;
    double *x1 = &(equation_roots -> x1), *x2 = &(equation_roots -> x2);
    int *roots_amount = &(equation_roots -> amount);

    assert(x1 || "NULL pointer on x1");
    assert(x2 || "NULL pointer on x2");
    assert(!isnan(a) || "a is nan");
    assert(!isnan(b) || "b is nan");
    assert(!isnan(c) || "c is nan");

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
