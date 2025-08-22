#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <double.h>

void input(double *a, double *b, double *c);
void solve_equation(double a, double b, double c,
                           double *x1, double *x2,
                           int *roots_amount);
void print_ans(double x1, double x2, int roots_amount);


void input(double *a, double *b, double *c) { //function gets coeffs of equation
    printf("Введите коэффициенты квадратного трёхчлена через пробел:\n");
    scanf("%f %f %f", a, b, c);
}


void solve_equation(double a, double b, double c,
                           double *x1, double *x2,
                           int *roots_amount) { //function solves equation
    *roots_amount = 0;
    if (fabs(a) < FLT_EPSILON) { //equation of type bx+c=0
        if (fabs(b) < FLT_EPSILON) { //equation of type c=0
            if (fabs(c) < FLT_EPSILON)
                *roots_amount = -1; //undefined root
        }
        else { //equation of type bx+c=0, b != 0
            *x1 = -c / b;
            *roots_amount = 1;
        }
    }
    else { //square equation of type ax^2+bx+c=0, a != 0
        double discriminant = b * b - 4 * a * c; //discriminant
        if (discriminant > 0) { //2 roots
            *x1 = (-b - sqrt(discriminant)) / (2 * a); //smaller root
            *x2 = (-b + sqrt(discriminant)) / (2 * a); //bigger root
            *roots_amount = 2;
        }
        else if (fabs(discriminant) < DBL_EPSILON) { //one root
            *x1 = -b / (2 * a);
            *roots_amount = 1;
        }
    }

    //if root equals -0, turn it to 0
    if (fabs(*x1) < DBL_EPSILON)
        *x1 = 0;

    if (fabs(*x2) < DBL_EPSILON)
        *x2 = 0;
}


void print_ans(double x1, double x2,
               int roots_amount) { //print roots
    if (roots_amount == 0) //0 roots
            printf("КОРНЕЙ НЕТ!!!\n");
    else if (roots_amount == -1) //undefined root
        printf("Корень не определен\n");
    else if (roots_amount == 1) //1 root
        printf("Корень равен %g\n", x1);
    else if (roots_amount == 2) //2 roots
        printf("Меньший корень равен %g\nБольший корень равен %g\n", x1, x2);
    else //condition if roots_amount doesn't match values above
        printf("ERROR OF ROOTS");
}


int main() {
    double a = 0, b = 0, c = 0; //coeffs of equation
    double x1 = 0, x2 = 0; //roots of equation
    int roots_amount = 0; //amount of roots, default value - 0
    input(&a, &b, &c); //input of coeffs
    solve_equation(a, b, c, &x1, &x2, &roots_amount); //solving of the equation
    print_ans(x1, x2, roots_amount); //answer outputting
    return 0;
}
