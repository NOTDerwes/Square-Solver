#include <math.h>
#include <assert.h>

#include "solve_equation.h"
#include "double_operations.h"

void solve_square_equation(struct Coeffs equation_coeffs,
                           struct Roots *equation_roots) { ///function solves equation
    double a = equation_coeffs.a, b = equation_coeffs.b, c = equation_coeffs.c;
    double *x1 = &(equation_roots -> x1), *x2 = &(equation_roots -> x2);
    int *roots_amount = &(equation_roots -> amount);

    ///checking of programmer errors
    assert(x1 || "NULL pointer on x1");
    assert(x2 || "NULL pointer on x2");
    assert(!isnan(a) || "a is nan");
    assert(!isnan(b) || "b is nan");
    assert(!isnan(c) || "c is nan");

    *roots_amount = ZeroRoots; ///default amount of roots

    if (equal_doubles(a, ZERO)) { ///equation of type bx+c=0
        solve_linear_equation(b, c, x1, roots_amount);
        return;
    }
    else { ///square equation of type ax^2+bx+c=0, a != 0
        double discriminant = b * b - 4 * a * c; ///discriminant
        if (discriminant > 0) { ///2 roots
            *x1 = (-b - sqrt(discriminant)) / (2 * a); ///smaller root
            *x2 = (-b + sqrt(discriminant)) / (2 * a); ///bigger root
            *roots_amount = TwoRoots;
        }
        else if (equal_doubles(discriminant, ZERO)) { ///one root
            *x1 = -b / (2 * a);
            *roots_amount = OneRoot;
        }
    }

    ///if root equals -0, turn it to 0
    if (equal_doubles(*x1, ZERO))
        *x1 = 0;

    if (equal_doubles(*x2, ZERO))
        *x2 = 0;
}


void solve_linear_equation(double k, double b,
                           double *x,
                           int *roots_amount) { ///solves equations of type kx+b=0
    if (equal_doubles(k, ZERO)) { ///equation of type b=0
            if (equal_doubles(b, ZERO))
                *roots_amount = UndefinedRoot; ///undefined root
        }
        else { ///equation of type kx+b=0, k != 0
            *x = -b / k;
            *roots_amount = OneRoot;
        }
    ///if root equals -0, turn it to 0
    if (equal_doubles(*x, ZERO))
        *x = 0;
}
