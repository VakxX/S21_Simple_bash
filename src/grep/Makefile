CC = gcc -std=c11
CFLAGS = -Wall -Werror -Wextra

all: s21_grep

s21_grep: s21_grep.o
	$(CC) $(CFLAGS) s21_grep.o -o s21_grep

s21_grep.o:
	$(CC) $(CFLAGS) -c s21_grep.c

clean:
	rm -rf *.o s21_grep

rebuild: 
	make clean && make all

style:
	clang-format -style=Google -n *.c *.h 

test: rebuild style
	sh test_grep.sh