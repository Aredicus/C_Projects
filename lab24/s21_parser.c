#include "s21_parser.h"

void s21_parse(s21_stack_char *stackChar, s21_stack_char *stackResult,
               const char *string) {
  int un_min = 1;
  char *tmp = (char *)string;
  for (; *tmp != '\0'; tmp++) {
    if (*tmp == ' ') {
      continue;
    } else if (isdigit(*tmp) || *tmp == 'P' || *tmp == 'e' || *tmp == 'x') {
      s21_push_double(stackResult, tmp);
      if (isdigit(*tmp)) {
        for (; isdigit(*tmp) || *tmp == '.'; tmp++)
          ;
        tmp--;

      } else {
        for (; isalpha(*tmp); tmp++)
          ;
        tmp--;
      }
      un_min = 0;
    } else if (isalpha(*tmp) && *tmp != 'm') {
      s21_push_fun(stackChar, tmp);
      for (; isalpha(*tmp); tmp++)
        ;
      tmp--;
      un_min = 0;
    } else {
      s21_push_operator(stackChar, stackResult, tmp, un_min);
      if (*tmp == '(')
        un_min = 1;
      else
        un_min = 0;
      if (isalpha(*tmp)) {
        for (; isalpha(*tmp); tmp++)
          ;
        tmp--;
      }
    }
  }
  while (!s21_is_empty_stack_char(*stackChar)) {
    if (strcmp(s21_show_top_char(stackChar), "(") == 0)
      s21_ERROR(stackResult);
    s21_push_stack_char(stackResult, s21_pop_stack_char(stackChar));
  }
}

void s21_push_double(s21_stack_char *stackChar, char *string) {
  int i = 0;
  char *tmp = string;
  if (isalpha(*tmp)) {
    for (; isalpha(*tmp); tmp++) {
      i++;
    }
  } else {
    int is_p = 0;
    for (; isdigit(*tmp) || *tmp == '.'; tmp++, i++) {
      if (*tmp == '.' && is_p == 0)
        is_p = 1;
      else if (*tmp == '.' && is_p == 1) {
        s21_ERROR(stackChar);
      }
    }
  }
  char *tmp_number = calloc(256, sizeof(char));
  tmp_number = strncpy(tmp_number, string, i);
  if (isdigit(*tmp_number) || s21_is_fun(tmp_number)) {
    s21_push_stack_char(stackChar, tmp_number);
    if (strcmp(tmp_number, "x") == 0)
      stackChar->is_x++;
  } else {
    s21_ERROR(stackChar);
    free(tmp_number);
  }
}

void s21_push_fun(s21_stack_char *stackChar, char *string) {
  size_t i = 0;
  char *tmp = string;
  for (; isalpha(*tmp); tmp++) {
    i++;
  }
  char *tmp_fun = calloc(256, sizeof(char));
  tmp_fun = memcpy(tmp_fun, string, i);
  if (s21_is_fun(tmp_fun)) {
    s21_push_stack_char(stackChar, tmp_fun);
  } else {
    s21_ERROR(stackChar);
  }
}

void s21_push_operator(s21_stack_char *stackChar, s21_stack_char *stackResult,
                       char *string, int un_min) {
  size_t i = isalpha(*string) ? 0 : 1;
  char *tmp_s = string;
  for (; isalpha(*tmp_s); tmp_s++) {
    i++;
  }
  char *tmp_op = calloc(i, sizeof(char));
  tmp_op = memcpy(tmp_op, string, i);
  int priority = s21_get_priority(tmp_op);
  int tmp;
  if (un_min && *tmp_op == '-') {
    *tmp_op = '~';
    priority = 3;
  }
  if (priority == -1 ||
      (priority == 2 && isalpha(*string) && !s21_is_fun(tmp_op))) {
    free(tmp_op);
    s21_ERROR(stackResult);
  } else if (priority != 4) {
    while ((tmp = s21_get_priority(s21_show_top_char(stackChar))) >= priority &&
           tmp != -1 && priority != 5 && tmp != 5) {
      s21_push_stack_char(stackResult, s21_pop_stack_char(stackChar));
    }
    s21_push_stack_char(stackChar, tmp_op);

  } else {
    while ((tmp = s21_get_priority(s21_show_top_char(stackChar))) != 5 &&
           tmp != 4 && tmp != -1) {
      s21_push_stack_char(stackResult, s21_pop_stack_char(stackChar));
    }
    if (tmp == -1) {
      s21_ERROR(stackResult);
    } else {
      if (tmp == 5 && *tmp_op == ')')
        free(s21_pop_stack_char(stackChar));
      if (!s21_is_empty_stack_char(*stackChar)) {
        if (isalpha(s21_show_top_char(stackChar)[0])) {
          s21_push_stack_char(stackResult, s21_pop_stack_char(stackChar));
        }
      }
    }
    free(tmp_op);
  }
}

int s21_get_priority(char *opr) {
  int res;
  if (opr != NULL) {
    switch (*opr) {
    case '-':
    case '+':
      res = 1;
      break;
    case '~':
    case '*':
    case '/':
    case 'm':
      res = 2;
      break;
    case '^':
      res = 3;
      break;
    case ')':
    case ',':
      res = 4;
      break;
    case '(':
      res = 5;
      break;
    default:
      res = -1;
      break;
    }
  } else {
    res = -1;
  }
  return res;
}

int s21_is_fun(char *fun) {
  int res = 0;
  if (strcmp(fun, "sin") == 0 || strcmp(fun, "cos") == 0 ||
      strcmp(fun, "tan") == 0 || strcmp(fun, "acos") == 0 ||
      strcmp(fun, "asin") == 0 || strcmp(fun, "atan") == 0 ||
      strcmp(fun, "sqrt") == 0 || strcmp(fun, "ln") == 0 ||
      strcmp(fun, "log") == 0 || strcmp(fun, "x") == 0 ||
      strcmp(fun, "Pi") == 0 || strcmp(fun, "e") == 0 ||
      strcmp(fun, "mod") == 0) {
    res = 1;
  }
  return res;
}