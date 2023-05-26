#include "s21_stack_char.h"
#include "s21_stack_node.h"
#include <ctype.h>
#include <math.h>

#ifndef S21_CALCULATION_H
#define S21_CALCULATION_H

#define S21_INF 1.0 / 0.0

s21_node *s21_calculation(s21_stack_char *stackChar, double *x);
double s21_get_operator(char *opr, double first, double *second);
double s21_get_function(char *fun, double arg);
void s21_time_to_clean_up(s21_stack_char *stackChar);

#endif // S21_CALCULATION_H
