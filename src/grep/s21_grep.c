#include "s21_grep.h"

int main(int argc, char **argv) {
  struct opt options = {0};
  parcer(argc, argv, &options);
  output(argc, argv, options);
  return 0;
}

void parcer(int argc, char **argv, struct opt *options) {
  if (argc > 1) {
    int opt;
    while ((opt = getopt_long(argc, argv, "e:isvnhlc", 0, 0)) != -1) {
      switch (opt) {
        case 'e':
          if (!options->e) {
            options->e = 1;
            strcat(options->patternE, optarg);
          } else {
            strcat(options->patternE, "|\0");
            strcat(options->patternE, optarg);
          }
          break;
        case 'i':
          options->i = 1;
          break;
        case 'v':
          options->v = 1;
          break;
        case 'c':
          options->c = 1;
          break;
        case 'l':
          options->l = 1;
          break;
        case 'n':
          options->n = 1;
          break;
        case 'h':
          options->h = 1;
          break;
        case 's':
          options->s = 1;
          break;
        default:
          exit(EXIT_FAILURE);
          break;
      }
    }
  }
}

void output(int argc, char **argv, struct opt options) {
  int f_str = optind;
  FILE *f = NULL;
  if (options.e == 0) {
    f_str++;
  }
  regex_t regex;
  if (t_regex(&regex, argv[optind], options) == 0) {
    for (int i = 0; (f_str + i) < argc; i++) {
      f = fopen(argv[f_str + i], "r");
      if (f == NULL) {
        if (options.s == 0) {
          fprintf(stderr, "s21_grep: %s: No such file or directory\n",
                  argv[f_str + i]);
        }
      } else {
        print_str(f, &regex, options, argc, argv[f_str + i], f_str);
      }
    }
    fclose(f);
  }
  regfree(&regex);
}

int t_regex(regex_t *regex, char *array, struct opt options) {
  int flag_registr = flag_i(options);
  int error = 0;
  if (options.e) {
    error = regcomp(regex, options.patternE, flag_registr | REG_EXTENDED);
  } else {
    error = regcomp(regex, array, flag_registr | REG_EXTENDED);
  }
  if (error != 0) {
    exit(EXIT_FAILURE);
  }
  return 0;
}

void print_str(FILE *f, regex_t *regex, struct opt options, int num, char *arr,
               int f_str) {
  int count_n = 0;
  int count_c = 0;
  char buff[BUFSIZ] = {'\0'};
  int flag_l_ok = 0;
  while ((fgets(buff, BUFSIZ, f) != NULL) && flag_l_ok == 0) {
    count_n++;
    int success = regexec(regex, buff, 0, 0, 0);
    flag_v(&success, options);
    if (success == 0) {
      count_c++;
      if (options.l) {
        flag_l_ok = 1;
      }
      if (!options.c && !options.h && (num - f_str - 1) && !flag_l_ok) {
        printf("%s:", arr);
      }
      if (!options.c && options.n && !flag_l_ok) {
        printf("%d:", count_n);
      }
      if (!options.c && !flag_l_ok) {
        printf("%s", buff);
        if (buff[strlen(buff) - 1] != '\n') {
          printf("\n");
        }
      }
    }
  }
  if (options.c) {
    if (!options.h && (num - f_str - 1)) {
      printf("%s:", arr);
    }
    printf("%d\n", count_c);
  }
  if (options.l && flag_l_ok) {
    printf("%s\n", arr);
  }
}

void flag_v(int *sym, struct opt options) {
  if (options.v) {
    if (*sym == 0) {
      *sym = 1;
    } else {
      *sym = 0;
    }
  }
}

int flag_i(struct opt options) {
  int s = 0;
  if (options.i) {
    s = REG_ICASE;
  }
  return s;
}