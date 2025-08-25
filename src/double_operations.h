#ifndef DOUBLE_OPERATIONS_H
#define DOUBLE_OPERATIONS_H

#include <stdbool.h>

/*!
 * @file double_operations.h
 * @brief Модуль операций над числами типа double
 * @author NOTDerwes
 * @date 25.08.2025
 * @version Beta
 *
 * Модуль предоставляет функции для работы с числами типа double,
 * включая сравнение, проверку специальных значений и операции с учётом
 * погрешности вычислений с плавающей точкой.
 */

/*!
 * @def ZERO
 * @brief Нулевое значение для сравнений
 */
#define ZERO 0

/*!
 * @enum doubles_compare_flag
 * @brief Флаги сравнения двух чисел double
 *
 * Используется для определения отношения между двумя числами
 * с учётом погрешности вычислений с плавающей точкой.
 */
enum doubles_compare_flag {
    NotDouble = -3,  ///< Хотя бы одно из чисел не является нормальным числом double (см. is_double())
    Smaller = -1,   ///< Первое число меньше второго
    Equal = 0,      ///< Числа равны с учётом погрешности
    Bigger = 1      ///< Первое число больше второго
};

/*!
 * @brief Проверка числа на корректность
 *
 * Функция проверяет, что число является нормальным числом double,
 * а не специальным значением (NaN, Inf, -Inf).
 *
 * @param[in] num Проверяемое число
 * @return @b true если число является нормальным double
 * @return @b false если число NaN, Inf или -Inf
 *
 * @note Используется для валидации входных данных
 * @see same_double_type
 */
bool is_double(double num);

/*!
 * @brief Сравнение двух чисел double с учётом погрешности
 *
 * Функция сравнивает два числа типа double, учитывая погрешность
 * вычислений с плавающей точкой.
 *
 * @param[in] first Первое число для сравнения
 * @param[in] second Второе число для сравнения
 * @return @b NotDouble если хотя бы одно из переданных чисел не является нормальным числом double
 * @return @b Smaller если first < second
 * @return @b Equal если first ≈ second (с учётом погрешности)
 * @return @b Bigger если first > second
 *
 * @note Использует машинную точность для сравнения
 * @see absolutely_same_doubles
 */
int compare_doubles(double first, double second);

/*!
 * @brief Абсолютное сравнение двух чисел double
 *
 * Функция сравнивает два числа, включая специальные значения
 * (NaN, Inf, -Inf). Возвращает true только если числа идентичны.
 *
 * @param[in] first Первое число
 * @param[in] second Второе число
 * @return @b true если числа идентичны (включая представление NaN/Inf)
 * @return @b false если числа отличаются
 *
 * @note Используется same_double_type() и compare_doubles() для точного сравнения
 * @see same_double_type(), compare_doubles(), is_double()
 */
bool absolutely_same_doubles(double first, double second);

/*!
 * @brief Проверка совпадения типов чисел double
 *
 * Функция проверяет, что оба числа относятся к одному типу:
 * оба нормальные, оба NaN, оба Inf или оба -Inf.
 *
 * @param[in] first Первое число
 * @param[in] second Второе число
 * @return @b true если типы чисел совпадают
 * @return @b false если типы чисел различны
 *
 * @note Полезно для проверки корректности операций между числами
 * @see is_double()
 */
bool same_double_type(double first, double second);

/*!
 * @brief Обмен значений двух чисел double
 *
 * Функция меняет местами значения двух переменных типа double.
 *
 * @param[in,out] first Указатель на первое число
 * @param[in,out] second Указатель на второе число
 *
 * @warning Указатели не должны быть NULL
 * @note Работает с любыми значениями double, включая NaN и Inf
 */
void swap_doubles(double *first, double *second);

/*!
 * @brief Проверка числа на равенство нулю с учётом погрешности
 *
 * Функция проверяет, является ли число нулём в пределах машинной точности.
 *
 * @param[in] number Проверяемое число
 * @return @b true если число равно нулю с учётом погрешности
 * @return @b false если число отличается от нуля
 *
 * @note Использует машинный эпсилон для учёта погрешности
 * @see compare_doubles()
 */
bool is_zero(double number);

#endif
