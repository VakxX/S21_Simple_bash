#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct opt {
  int e;
  char patternE[1024];
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  char patternF[1024];
};

void parcer(int argc, char **argv, struct opt *options);
void output(int argc, char **argv, struct opt options);
void print_str(FILE *f, regex_t *r, struct opt options, int num, char *arr,
               int f_str);
int t_regex(regex_t *regex, char *array, struct opt options);
void flag_v(int *sym, struct opt options);
int flag_i(struct opt options);

#endif