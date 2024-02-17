CC = gcc -std=c11
CFLAG = -Wall -Wextra -Werror

all: s21_cat

s21_cat: s21_cat.o
	$(CC) $(CFLAG) s21_cat.o -o s21_cat

s21_cat.o:
	$(CC) $(CFLAG) -c s21_cat.c

clean:
	rm -rf *.o s21_cat

rebuild:
	make clean && make all

style:
	clang-format -style=Google -n *.c *.h

test: rebuild style
	sh test.sh