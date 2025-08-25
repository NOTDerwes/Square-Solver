#Compiler and flags
CC = gcc
CFLAGS = -D_DEBUG -ggdb3 -std=c17 -O0 -Wall -Wextra \
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
        -Wstack-usage=8192 -pie -fPIE -Werror=vla

#Sanitizers
SANITIZERS = -fsanitize=address,alignment,bool,bounds,enum,$\
            float-cast-overflow,float-divide-by-zero,$\
            integer-divide-by-zero,leak,nonnull-attribute,$\
            null,object-size,return,returns-nonnull-attribute,$\
            shift,signed-integer-overflow,undefined,$\
            unreachable,vla-bound

LDFLAGS = $(SANITIZERS) -pie -fPIE -lm

#Source files
SRCS = ./src/main.c ./src/double_operations.c ./src/solve_equation.c ./src/unit_tests.c
OBJS = $(SRCS:.c=.o)
TARGET = square_solver

# Colors for output
GREEN = \033[0;32m
RED = \033[0;31m
BLUE = \033[0;34m
NC = \033[0m

#Main target
$(TARGET): $(OBJS)
	@echo "$(BLUE)Сборка ...$(NC)"
	@if $(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS); then \
                echo "$(GREEN)Сборка проведена успешно в $(TARGET)!$(NC)"; \
        else \
                echo "$(RED)✗ Ошибка при сборке$(NC)"; \
		exit 1; \
        fi

#Compile .c to .o
%.o: %.c
	@echo "$(BLUE)Компиляция ...$(NC)"
	$(CC) $(CFLAGS) $(SANITIZERS) -c $< -o $@
	@echo "$(GREEN)Компиляция проведена успешно!$(NC)"

#Clean build files
clean:
	@echo "$(BLUE)Очистка...$(NC)"
	rm -f $(OBJS) $(TARGET) *.gcno *.gcda
	@echo "$(GREEN)Очистка завершена!$(NC)"

#Run the program
run: $(TARGET)
	@echo "$(BLUE)Запуск программы ...$(NC)"
	./$(TARGET)
	@echo "$(GREEN)Программа завершена!$(NC)"

#Run with debugger
debug: $(TARGET)
	@echo "$(BLUE)=== ЗАПУСК ОТЛАДКИ ===$(NC)"
	gdb -q ./$(TARGET)

#Run tests
test: $(TARGET)
	@echo "$(BLUE)=== ЗАПУСК ТЕСТОВ ===$(NC)"
	./$(TARGET) --test
	@echo "$(BLUE)=== ТЕСТЫ ЗАВЕРШЕНЫ ===$(NC)"

help:
	@echo "$(BLUE)Доступные команды:$(NC)"
	@echo "  make all     - собрать обычную версию программы"
	@echo "  make test    - собрать тестовую версию и запустить тесты"
	@echo "  make clean   - очистить сборочные файлы"
	@echo "  make help    - показать эту справку"

.PHONY: clean run debug test
