#ifndef S21_PARSER_H
#define S21_PARSER_H

#include "s21_stack_char.h"
#include <ctype.h>
#include <string.h>

void s21_parse(s21_stack_char *stackChar, s21_stack_char *stackResult,
               const char *string);
void s21_push_double(s21_stack_char *stackChar, char *string);
void s21_push_fun(s21_stack_char *stackChar, char *string);
void s21_push_operator(s21_stack_char *stackChar, s21_stack_char *stackResult,
                       char *string, int un_min);
int s21_get_priority(char *opr);

#endif // S21_PARSER_H
