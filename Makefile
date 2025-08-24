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
SRCS = main.c double_operations.c solve_equation.c unit_tests.c
OBJS = $(SRCS:.c=.o)
TARGET = square_solver

#Main target
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)

#Compile .c to .o
%.o: %.c
	$(CC) $(CFLAGS) $(SANITIZERS) -c $< -o $@

#Clean build files
clean:
	rm -f $(OBJS) $(TARGET) *.gcno *.gcda

#Run the program
run: $(TARGET)
	./$(TARGET)

#Run with debugger
debug: $(TARGET)
	gdb -q ./$(TARGET)

#Run tests
test: $(TARGET)
	./$(TARGET) --test


.PHONY: clean run debug test
