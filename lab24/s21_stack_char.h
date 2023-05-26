
#ifndef S21_STACK_CHAR_H
#define S21_STACK_CHAR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s21_stack_char {
  char **chars;
  int size;
  int is_x;
  int is_correct;
} s21_stack_char;

void s21_copy_stack(s21_stack_char stack_src, s21_stack_char *stack_dst);
void s21_init_stack_char(s21_stack_char *stack);
void s21_push_stack_char(s21_stack_char *stack, char *symbols);
void s21_remove_stack_char(s21_stack_char *stack);
void s21_ERROR(s21_stack_char *stack);
char *s21_pop_stack_char(s21_stack_char *stack);
char *s21_show_top_char(s21_stack_char *stack);
int s21_is_empty_stack_char(s21_stack_char stack);
int s21_is_fun(char *fun);
void s21_reverse_stack_char(s21_stack_char *stack);

#endif // S21_STACK_CHAR_H
