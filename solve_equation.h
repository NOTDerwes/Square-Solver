#ifndef SOLVE_EQUATION_H
#define SOLVE_EQUATION_H

/** Possible amount of roots of square equation
* \param UndigistedRoot Initialization value
* \param UndeinedRoot Equation has infinity roots
* \param ZeroRoots Equation has no roots
* \param OneRoot Equation has 1 root
* \param TwoRoots Equation has 2 roots */
enum roots_count {
    UndigistedRoot = 3,
    UndefinedRoot = -1,
    ZeroRoots = 0,
    OneRoot = 1,
    TwoRoots = 2,
};

/** Coeffs structure stores coefficients of the recieved square equation ax^2+bx+c=0
\param a Coefficient of x^2
\param b Coefficient of x
\param c Free term */
struct Coeffs {
    double a;
    double b;
    double c;
};

/** Roots structure stores amount of roots of the equation.
\param x1 Smaller root of equation (equals NAN if equation has zero or undefined roots)
\param x2 Bigger root of equation (equals NAN if equation has one, zero or undefined roots)
\param amount Amount of roots of the equation (cases of it's value are declared in "roots_count") */
struct Roots {
    double x1;
    double x2;
    enum roots_count amount;
};

/** Solves square equation tof type ax^2+bx+c=0
\param equation_coeffs Coefficients of recieved square equation
\param *equation_roots Potinter to structure Roots where is stored informtion about roots
\warning Function doesn't return values, but change value of Roots variables */
void solve_square_equation(struct Coeffs equation_coeffs,
                           struct Roots *equation_roots);

/** Solves linear equation of type kx+b=0
\param k Coefficient of x
\param b Free term
\param *x Pointer to the root of equation (equals NAN if equation has zero or undefined roots)
\param *roots_amount Pointer to the amount of roots (take the values of one, zero or undefined roots) */
void solve_linear_equation(double k, double b,
                           double *x,
                           int *roots_amount);
void reset_structs(struct Coeffs *reseting_coeffs,
                   struct Roots *reseting_roots);

#endif
