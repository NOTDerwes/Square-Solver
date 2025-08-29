.PHONY: clean run debug test release doxy-docs doxy-open help
#Compiler and flags
CC = gcc
DIR = src
DEBUG_FLAG = -DNDEBUG -D_DEBUG
CFLAGS = -ggdb3 -std=c17 -O0 -Wall -Wextra \
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
SRCS = $(DIR)/main.c $(DIR)/double_operations.c $(DIR)/solve_equation.c \
$(DIR)/unit_tests.c $(DIR)/user_interaction.c $(DIR)/string_operations.c \
$(DIR)/cats.c $(DIR)/flags.c
OBJS = $(SRCS:.c=.o)
TARGET = square_solver
DOCFILE = ./documentation/html/index.html
BROWSER = firefox #might be set to "google-chrome"

# Colors for output
BLACK = \033[0;30m
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
MAGENTA = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m
ORANGE = \033[38;5;208m
PURPLE = \033[38;5;93m
PINK = \033[38;5;199m
LIME = \033[38;5;118m
TEAL = \033[38;5;30m
LAVENDER = \033[38;5;183m
CORAL = \033[38;5;203m
GOLD = \033[38;5;220m
SILVER = \033[38;5;7m
MAROON = \033[38;5;88m
NC = \033[0m

#Main target
$(TARGET): $(OBJS)
	@echo "$(BLUE)Сборка ...$(NC)"
	@if $(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS); then \
                echo "$(GREEN)Сборка проведена успешно в $(TARGET)!$(NC)"; \
        else \
                echo "$(RED)Ошибка при сборке$(NC)"; \
				echo "$(YELLOW)Удаление объектных файлов...$(NC)"; \
                rm -f $(OBJS) *.gcno *.gcda; \
        fi
	@echo "$(RED)ДЕЛАЙ COMMIT НА GITHUB!!!$(NC)"

#Compile .c to .o
%.o: %.c
	@echo "$(BLUE)Компиляция ...$(NC)"
	$(CC) $(CFLAGS) $(SANITIZERS) -c $< -o $@
	@echo "$(GREEN)Компиляция проведена успешно!$(NC)"
	@echo "$(RED)ДЕЛАЙ COMMIT НА GITHUB!!!$(NC)"

#Clean build files
clean:
	@echo "$(BLUE)Очистка...$(NC)"
	rm -f $(OBJS) $(TARGET) *.gcno *.gcda
	@echo "$(GREEN)Очистка завершена!$(NC)"
	@echo "$(RED)ДЕЛАЙ COMMIT НА GITHUB!!!$(NC)"

#Run the program
run: $(TARGET)
	@echo "$(CYAN)=== ЗАПУСК ПРОГРАММЫ ===$(NC)"
	./$(TARGET)
	@echo "$(GREEN)=== ПРОГРАММА ЗАВЕРШЕНА ===$(NC)"
	@echo "$(RED)ДЕЛАЙ COMMIT НА GITHUB!!!$(NC)"

#Run with debugger
debug: $(TARGET)
	@echo "$(BLUE)=== ЗАПУСК ОТЛАДКИ ===$(NC)"
	gdb -q ./$(TARGET)
	@echo "$(RED)ДЕЛАЙ COMMIT НА GITHUB!!!$(NC)"

#Run tests
test: $(TARGET)
	@echo "$(MAGENTA)=== ЗАПУСК ТЕСТОВ ===$(NC)"
	./$(TARGET) --test $(TEST_PATH)
	@echo "$(MAGENTA)=== ТЕСТЫ ЗАВЕРШЕНЫ ===$(NC)"
	@echo "$(RED)ДЕЛАЙ COMMIT НА GITHUB!!!$(NC)"

doxy-docs:
	doxygen Doxyfile
	@echo "$(RED)ДЕЛАЙ COMMIT НА GITHUB!!!$(NC)"

doxy-open:
	$(BROWSER) $(DOCFILE)
	@echo "$(RED)ДЕЛАЙ COMMIT НА GITHUB!!!$(NC)"

help:
	@echo "$(BLUE)Доступные команды:$(NC)"
	@echo "	$(MAGENTA)Команды по работе с файлами проекта:$(NC)"
	@echo "		$(CYAN)make all$(NC) - собрать обычную версию программы"
	@echo "		$(CYAN)make test TEST_PATH=default$(NC) - собрать тестовую версию и запустить тесты.\n\
			Для тестирования своих тестов нужно указать путь до тестируемого файла в TEST_PATH.\n\
			По умолчанию открывает файл с авторскими тестами"
	@echo "		$(CYAN)make clean$(NC) - очистить сборочные файлы"
	@echo "	$(MAGENTA)Команды по работе с документацией:$(NC)"
	@echo "		$(CYAN)make doxy-docs$(NC) - сгенерировать документацию по проекту"
	@echo "		$(CYAN)make doxy-open$(NC) - открыть документацию по проекту"
	@echo "	$(MAGENTA)Другие команды:$(NC)"
	@echo "		$(CYAN)make help$(NC) - показать эту справку"
