/**
 * @file myassert.h
 * @brief Пользовательская реализация макроса assert с выводом ошибок
 * @author NOTDerwes
 * @date 25.08.2025
 * @version Beta
 *
 * Макрос для отладочных проверок с понятным выводом ошибок.
 * В отличие от стандартного assert, предоставляет кастомные сообщения об ошибках.
 */

#ifndef MYASSERT_H
#define MYASSERT_H

#include <stdio.h>
#include <stdlib.h>
#include "string_operations.h"

/**
 * @def MYASSERT(expr, err_out)
 * @brief Пользовательский макрос для проверки утверждений
 *
 * Макрос проверяет выражение `expr`.
 * Если выражение истинно (не ноль), выводит сообщение об успешной проверке.
 * Если выражение ложное (ноль), выводит сообщение об ошибке и завершает программу с кодом 1.
 *
 * @param[in] expr Выражение для проверки (должно быть истинно для продолжения)
 * @param[in] err_out Сообщение об ошибке для вывода при срабатывании assert
 *
 * @warning Не использовать в production-коде из-за вызова exit(1)
 * @note Для отладочных целей вместо стандартного assert
 *
 * @code
 * // Пример использования:
 * MYASSERT(ptr, "Указатель не должен быть NULL");
 * MYASSERT(x < 0, "Ожидалось отрицательное число");
 * @endcode
 *
 * @see assert из стандартной библиотеки
 */

#define MYASSERT(expr, fmt)                      \
do {                                             \
    if (!(expr)) {                               \
        WRITE_TO_FILE("./log-files/myassert.log",\
        ERROR_MESSAGE(fmt));                     \
        fprintf(stderr,                          \
        CONSOLE_ERROR_MESSAGE(fmt));             \
        exit(1);                                 \
    }                                            \
    else {                                       \
        WRITE_TO_FILE("./log-files/myassert.log",\
        SUCCESS_MESSAGE());                      \
    }                                            \
} while (0)

#endif
