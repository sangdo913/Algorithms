CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O2 -m32 -MMD -MP -g

OUT = mtest
SRC = mtest.c mm.c memlib.c
OBJ = $(SRC:.c=.o)

.PHONY: all clean
.DEFAULT_GOAL := all

all: $(OUT)

$(OUT): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ -lm

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

-include $(OBJ:.o=.d)

clean:
	rm -rf *.o *.d $(OUT)
