#include "s21_cat.h"

int main(int argc, char *argv[]) {
  if (argc > 1) {
    opt options = {0};
    parcer(argc, argv, &options);
    if (options.b) {
      options.n = 0;
    }
    while (optind < argc) {
      reader(argv, &options);
      optind++;
    }
  }

  return 0;
}

void parcer(int argc, char *argv[], opt *options) {
  int opt = 0;
  static struct option long_options[] = {{"number-nonblank", 0, 0, 'b'},
                                         {"number", 0, 0, 'n'},
                                         {"squeeze-blank", 0, 0, 's'},
                                         {0, 0, 0, 0}};

  while ((opt = getopt_long(argc, argv, "+benstvTE", long_options, 0)) != -1) {
    switch (opt) {
      case 'v':
        options->v = TRUE;
        break;
      case 'b':
        options->b = TRUE;
        break;
      case 'e':
        options->e = TRUE;
        options->v = TRUE;
        break;
      case 'n':
        options->n = TRUE;
        break;
      case 's':
        options->s = TRUE;
        break;
      case 't':
        options->t = TRUE;
        options->v = TRUE;
        break;
      case 'T':
        options->t = TRUE;
        break;
      case 'E':
        options->e = TRUE;
        break;
      default:
        fprintf(stderr, "usage: [benstvTE] [file ...]");
        exit(1);
    }
  }
}

void reader(char *argv[], opt *options) {
  FILE *f = fopen(argv[optind], "r");

  if (f == NULL) {
    fprintf(stderr, "s21_cat: %s: No such file or directory\n", argv[optind]);
  } else {
    int cur;
    int prev = '\n';
    int str_count = 0;
    int counter = 0;
    int blank_line = 0;
    while ((cur = fgetc(f)) != EOF) {
      if (options->s && cur == '\n') {
        if (prev == '\n') {
          if (blank_line) {
            continue;
          } else {
            blank_line = 1;
          }
        } else {
          blank_line = 0;
        }
      }
      flag_b(options, &counter, prev, cur, &str_count);
      flag_n(options, &counter, prev, &str_count);
      flag_e(options, cur);
      flag_t(options, &cur);
      flag_v(options, &cur);
      putc(cur, stdout);
      prev = cur;
    }
    fclose(f);
  }
}

void flag_e(opt *options, int cur) {
  if (options->e && cur == '\n') {
    fputc('$', stdout);
  }
}

void flag_v(opt *options, int *cur) {
  if (options->v) {
    if (*cur > 127 && *cur < 160) printf("M-^");
    if ((*cur < 32 && *cur != '\n' && *cur != '\t') || *cur == 127) printf("^");
    if ((*cur < 32 || (*cur > 126 && *cur < 160)) && *cur != '\n' &&
        *cur != '\t') {
      if (*cur > 126) {
        *cur = *cur - 128 + 64;
      } else {
        *cur = *cur + 64;
      }
    }
  }
}

void flag_n(opt *options, int *counter, int prev, int *str_count) {
  if (options->n && prev == '\n') {
    if (*counter == 0) {
      *str_count = *str_count + 1;
      printf("%6d\t", *str_count);
      *counter = 1;
    }
  } else {
    *counter = 0;
  }
}

void flag_b(opt *options, int *counter, int prev, int cur, int *str_count) {
  if (options->b && prev == '\n' && cur != '\n') {
    if (*counter == 0) {
      *str_count = *str_count + 1;
      printf("%6d\t", *str_count);
      *counter = 1;
    }
  } else {
    *counter = 0;
  }
}

void flag_t(opt *options, int *cur) {
  if (options->t && *cur == '\t') {
    fputc('^', stdout);
    *cur = '\t' + 64;
  }
}