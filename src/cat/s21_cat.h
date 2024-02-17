#ifndef S21_CAT_H
#define S21_CAT_H

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1

typedef struct {
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
} opt;

void parcer(int argc, char *argv[], opt *options);

void flag_e(opt *options, int cur);
void flag_v(opt *options, int *cur);
void flag_n(opt *options, int *counter, int prev, int *str_count);
void flag_b(opt *options, int *counter, int prev, int cur, int *str_count);
void flag_t(opt *options, int *cur);

void reader(char *argv[], opt *options);

#endif