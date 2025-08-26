#ifndef USER_INTERACTION_H
#define USER_INTERACTION_H

#include <stdbool.h>
#include "solve_equation.h"

#define INPUTSIZE 20 ///< Размер буфера для ввода
#define YES_ANSWER "Да" ///< Строка подтверждения продолжения

/**
 * @brief Ввод коэффициентов уравнения
 *
 * Запрашивает у пользователя ввод коэффициентов a, b, c
 * для квадратного уравнения @f$ ax^2 + bx + c = 0 @f$
 *
 * @param[out] equation_coeffs Указатель на структуру для коэффициентов
 *
 * @warning equation_coeffs не должен быть NULL
 * @see input_coeff
 */
void input(Coeffs *equation_coeffs);

/**
 * @brief Ввод отдельного коэффициента
 *
 * Запрашивает ввод конкретного коэффициента с проверкой
 * корректности ввода и обработкой ошибок
 *
 * @param[in] curr_coeff Обозначение коэффициента ('a', 'b' или 'c')
 * @param[out] inputing_coeff Указатель для сохранения коэффициента
 *
 * @warning inputing_coeff не должен быть NULL
 * @note Повторяет запрос при некорректном вводе
 * @see letters_left
 * @see clean_buffer
 * @see is_double
 */
void input_coeff(char curr_coeff, double *inputing_coeff);

/**
 * @brief Запрос на продолжение работы
 *
 * Запрашивает у пользователя подтверждение продолжения работы программы
 *
 * @return true если пользователь ввел "Да"
 * @return false если пользователь ввел что-то другое
 *
 * @see YES_ANSWER
 */
bool continue_enter();

/**
 * @brief Вывод результатов решения уравнения
 *
 * Выводит корни уравнения в зависимости от их количества
 * и типа (действительные, комплексные, специальные случаи)
 *
 * @param[in] equation_roots Структура с результатами решения
 *
 * @warning equation_roots.amount не должен быть UndigistedRoot
 * @note Форматирует вывод для разных случаев количества корней
 */
void print_ans(Roots equation_roots);

#endif
