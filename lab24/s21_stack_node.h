#ifndef S21_STACK_NODE_H
#define S21_STACK_NODE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

enum {
    NUM = 1,
    OPR = 2,
    FUN = 3,
    UNO = 4
};

typedef struct s21_node {
    int type;
    char *val;
    struct s21_node *left;
    struct s21_node *right;
} s21_node;

typedef struct s21_stack_node {
    s21_node **nodes;
    int size;
} s21_stack_node;

void s21_init_stack_node(s21_stack_node *stack);

void s21_push_stack_node(s21_stack_node *stack, char *str);

void s21_remove_stack_node(s21_stack_node *stack);

s21_node *s21_pop_stack_node(s21_stack_node *stack);

int s21_is_empty_stack_node(s21_stack_node stack);

void s21_show_tree(s21_node *tree, int i);

void s21_remove_tree(s21_node **tree);

void s21_prime(s21_node **tree);

char *reverse(s21_node *tree);


#endif // S21_STACK_NODE_H
