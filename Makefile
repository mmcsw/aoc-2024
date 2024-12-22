# Highly inspired by the stackoverflow answer here:
# https://stackoverflow.com/questions/28425130/understanding-the-dependencies-of-a-makefile-c

CC := clang
# don't forget to add -O3 if you need to
CFLAGS := -x c -MMD -MP -std=c11 -Wall -Wextra -Wpedantic -O3 -fsanitize=address
# LDFLAGS :=
LDLIBS := -lm -fsanitize=address

SOURCES := $(wildcard *.c) $(wildcard src/*.c)
OBJECTS := $(SOURCES:%.c=%.o)
DEPENDS := $(SOURCES:%.c=%.d)

main: $(OBJECTS)

-include $(DEPENDS)

clean:
	\rm -f main *.o *.d **/*.o **/*.d
