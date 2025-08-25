# Решатель квадратных уравнений

## Содержание
1. [О проекте](#о-проекте)
2. [Возможности](#возможности)
3. [Структура проекта](#структура-проекта)
4. [Быстрый старт](#быстрый-старт)
   - [Сборка программы](#сборка-программы)
   - [Запуск программы](#запуск-программы)
   - [Пример работы](#пример-работы)
5. [Документация](#документация)
   - [Установка Doxygen](#установка-doxygen)
6. [Тестирование](#тестирование)
7. [Особенности реализации](#особенности-реализации)
   - [Обработка особых случаев](#обработка-особых-случаев)
   - [Работа с погрешностью](#работа-с-погрешностью)
   - [Математические формулы](#математические-формулы)
8. [Отладка](#отладка)

## О проекте
Программа для решения квадратных уравнений вида $ax^2 + bx + c = 0$ с обработкой частных случаев, валидацией ввода и модульным тестированием.

[Quadric Equation](https://en.wikipedia.org/wiki/Quadratic_equation)

[C language](https://en.wikipedia.org/wiki/C_(programming_language))

[Doxyge documentation](https://www.doxygen.nl/manual/)



## Возможности

- Решение квадратных уравнений
- Обработка линейных уравнений (вырожденный случай a = 0)
- Валидация входных данных (проверка на NaN, Inf)
- Работа с числами double с учётом погрешности
- Модульное тестирование
- Подробная документация Doxygen
- Защита от некорректного ввода

## Структура проекта
```
square-solver/
├── src/
│   ├── main.c                 # Главная программа
│   ├── solve_equation.c       # Решение уравнений
│   ├── solve_equation.h       # Заголовочный файл
│   ├── double_operations.c    # Операции с double
│   ├── double_operations.h    # Заголовочный файл
│   ├── unit_tests.c           # Модульные тесты
│   └── unit_tests.h           # Заголовочный файл
├── documentation/
│   └── html/                  # Документация Doxygen
├── tests/
│   └── test_input.txt         # Тестовые данные
├── Doxyfile                   # Конфигурация Doxygen
├── Makefile                   # Makefile для сборки
└── README.md                  # Этот файл
```

## Быстрый старт

### Сборка программы
```bash
# Клонирование репозитория
git clone https://github.com/NOTDerwes/Square-Solver.git
cd quadratic-solver

# Сборка с Makefile
make

# Или ручная компиляция из папки square-solver
gcc -D_DEBUG -ggdb3 -std=c17 -O0 -Wall -Wextra \
    -Waggressive-loop-optimizations \
    -Wmissing-declarations -Wcast-align -Wcast-qual \
    -Wchar-subscripts -Wconditionally-supported -Wconversion \
    -Wempty-body -Wfloat-equal \
    -Wformat-nonliteral -Wformat-security -Wformat-signedness \
    -Wformat=2 -Winline -Wlogical-op \
    -Wpacked -Wpointer-arith \
    -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion \
    -Wstrict-overflow=2 \
    -Wsuggest-attribute=noreturn \
    -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef \
    -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros \
    -Wno-missing-field-initializers -Wno-narrowing \
    -Wno-old-style-cast -Wno-varargs -Wstack-protector \
    -fstack-protector \
    -fstrict-overflow \
    -fno-omit-frame-pointer -Wlarger-than=8192 \
    -Wstack-usage=8192 -pie -fPIE -Werror=vla \
    ./src/main.c ./src/solve_equation.c ./src/double_operations.c ./src/unit_tests.c \
    -o quadratic_solver
```
### Запуск программы
```bash
#Запуск с Makefile
make run
```

#### Пример работы
```
Введите коэффициенты квадратного трёхчлена.
Введите коэффициент a: 1
Введите коэффициент b: -5
Введите коэффициент c: 6

Меньший корень равен 2
Больший корень равен 3

Введите "Да", если хотите продолжить:
Да

Введите коэффициент a: 0
Введите коэффициент b: 2
Введите коэффициент c: 4

Корень равен -2

Введите "Да", если хотите продолжить:
Нет
```

## Установка Doxygen (если не установлен)
```bash
sudo apt-get install doxygen doxygen-gui graphviz

# Генерация документации
doxygen Doxyfile

# Открыть документацию можно, перейдя в documentation/html/index.html в браузере
```
Документация включает:
- Подробное описание всех функций
- Математические формулы
- Графики вызовов функций
- Примеры использования

## Тестирование

Программа включает встроенные модульные тесты:
```bash
# Тесты запускаются при запуске
make test

# Свои тесты можете добавить в файл "test_input.txt" в формате, указанном в документации, \
# либо открыть файл "test_input.txt", в котором есть тестовые примеры
```
## Особенности реализации
### Обработка особых случаев
- $a = 0$ - линейное уравнение
- $D < 0$ - нет действительных корней
- $D = 0$ - один корень (двойной)
- $a = b = c = 0$ - бесконечно много корней
- $a = b = 0, c \neq 0$ - нет корней

### Работа с погрешностью
Используется машинная точность $\epsilon = 1e-12$:
- Сравнение: $|a - b| < \epsilon$
- Проверка на ноль: $|x| < \epsilon$

### Математические формулы
#### Квадратное уравнение
- $ax^2 + bx + c = 0$
#### Дискриминант
- $D = b^2 − 4ac$
#### Корни уравнения
- $x1,x2 = \frac{−b \pm \sqrt{D}}{2a}$
​​
## Отладка
```bash
# Запуск с отладочной информацией c помощью Makefile
make debug

# Запуск с отладочной информацией без помощи Makefile
gdb -q ./square_solver
```
