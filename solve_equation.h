#ifndef SOLVE_EQUATION_H
#define SOLVE_EQUATION_H
#define ZERO 0

enum roots_count {
    UndigistedRoot = 3,
    UndefinedRoot = -1,
    ZeroRoots = 0,
    OneRoot = 1,
    TwoRoots = 2,
};

struct Coeffs {
    double a;
    double b;
    double c;
};

struct Roots {
    double x1;
    double x2;
    enum roots_count amount;
};

void solve_square_equation(struct Coeffs equation_coeffs,
                           struct Roots *equation_roots);
void solve_linear_equation(double k, double b,
                           double *x,
                           int *roots_amount);

#endif
