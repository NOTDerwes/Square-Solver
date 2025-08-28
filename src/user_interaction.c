#include <stdio.h>
#include <math.h>
#include <string.h>

#include "user_interaction.h"
#include "myassert.h"
#include "double_operations.h"
#include "string_operations.h"

void input(Coeffs *equation_coeffs)
{
    MYASSERT(equation_coeffs, "NULL pointer on equation_coeffs");
    printf("Введите коэффициенты квадратного трёхчлена.\n");
    input_coeff('a', &equation_coeffs->a);
    input_coeff('b', &equation_coeffs->b);
    input_coeff('c', &equation_coeffs->c);
}


void input_coeff(char curr_coeff, double *inputing_coeff) {
    MYASSERT(inputing_coeff, "NULL pointer on inputing_coeff");
    int attempts = 0;
    bool flag_retry = true;
    do {
        if (attempts == 10) {
            printf(BORDER_DASH "\n" RED BOLD \
            "Уважаемый пользователь, попробуйте включить мозгу и ввести коэффициент правильно\n" \
            GREEN "С надеждой на ваш интеллект, автор\n" NC BORDER_DASH "\n");
        }
        else if(attempts == 100) {
            printf(YELLOW "Ну лан, держи ачивку, заслужил\n" \
            GREEN BOLD "Ачивка \"Отчаянный математик\" получена \n" NC \
            MAGENTA "Цель: неправильно ввести коэффицицент 100 раз\n" NC);
        }
        printf("Введите коэффициент %c: ", curr_coeff);
        int scan_result = scanf("%lf", inputing_coeff);

        if (scan_result != 1 || letters_left() || !is_double(*inputing_coeff)) {
            printf("Коэффициент %c введен в неправильном формате! Попробуйте ещё раз\n", curr_coeff);
            clean_buffer();
        } else {
            flag_retry = false;
        }
        attempts++;
    } while(flag_retry);
}


bool continue_enter()
{
    char confirmation[INPUTSIZE] = "";
    printf("Введите \"Да\", если хотите продолжить:\n");
    scanf("%5s", confirmation);
    clean_buffer();

    if (strncmp(confirmation, YES_ANSWER, sizeof(YES_ANSWER)) != 0) {
        return false;
    }
    return true;
}


void print_ans(Roots equation_roots)
{
    double x1 = equation_roots.x1;
    double x2 = equation_roots.x2;
    int roots_amount = equation_roots.amount;

    MYASSERT(roots_amount != UndigistedRoot, "Roots not calculated");
    MYASSERT((!isnan(x1) || roots_amount < OneRoot), "Invalid root state");

    switch (roots_amount) {
        case ZeroRoots:
            printf("КОРНЕЙ НЕТ!!!\n\n");
            break;
        case UndefinedRoot:
            printf("Корень не определен\n\n");
            break;
        case OneRoot:
            printf("Корень равен %g\n\n", x1);
            break;
        case TwoRoots:
            printf("Меньший корень равен %g\nБольший корень равен %g\n\n", x1, x2);
            break;
        default:
            printf("Неизвестное количество корней: %d\n\n", roots_amount);
    }
}
