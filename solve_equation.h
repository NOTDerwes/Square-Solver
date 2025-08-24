#ifndef SOLVE_EQUATION_H
#define SOLVE_EQUATION_H

/** Possible values of amount of roots */
enum roots_count {
    UndigistedRoot = 3,
    UndefinedRoot = -1,
    ZeroRoots = 0,
    OneRoot = 1,
    TwoRoots = 2,
};

/** Coeffs structure stores coefficients of the recieved square equation ax^2+bx+c=0 */
struct Coeffs {
    double a;
    double b;
    double c;
};

/** Roots structure stores amount of roots of the equation.
"x1" - smaller root of equation (equals NAN if equation has zero or undefined roots)
"x2" - bigger root of equation (equals NAN if equation has one, zero or undefined roots)
"amount" - amount of roots of the equation (cases of it's value are declared in "roots_count") */
struct Roots {
    double x1;
    double x2;
    enum roots_count amount;
};

/** Solves square equation tof type ax^2+bx+c=0
"equation_coeffs" - coefficients of recieved square equation
"*equation_roots" - potinter to structure Roots where is stored informtion about roots
Function doesn't return values, but change value of Roots variables */
void solve_square_equation(struct Coeffs equation_coeffs,
                           struct Roots *equation_roots);

/** Solves linear equation of type kx+b=0
"*x" - pointer to the root of equation (equals NAN if equation has zero or undefined roots)
"*roots_amount" - pointer to the amount of roots (take the values of one, zero or undefined roots) */
void solve_linear_equation(double k, double b,
                           double *x,
                           int *roots_amount);

#endif
