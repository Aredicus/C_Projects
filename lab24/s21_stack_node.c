#include "s21_stack_node.h"

//Инициализация дерева выражений
void s21_init_stack_node(s21_stack_node *stack) {
    stack->size = 0;
    stack->size = 0;
    stack->nodes = (s21_node **) calloc(256, sizeof(s21_node *));
}


//Добавления нового значения в дерево выражений
void s21_push_stack_node(s21_stack_node *stack, char *val) {
    //Создаем новую ноду
    s21_node *tmp = (s21_node *) malloc(sizeof(s21_node));
    tmp->val = val;
    //Если добавляемая нода - число
    if (isdigit(val[0]) || *val == 'e' || *val == 'P') {
        tmp->type = NUM;
        tmp->left = NULL;
        tmp->right = NULL;
    // Если добавляемая нода - функция
    } else if (isalpha(val[0]) && val[0] != 'm') {
        tmp->type = FUN;
        tmp->right = s21_pop_stack_node(stack);
    // Если добавляемся нода - оператор и не унарный минус
    } else if (val[0] != '~') {
        tmp->type = OPR;
        tmp->right = s21_pop_stack_node(stack);
        tmp->left = s21_pop_stack_node(stack);
    // Если добавляемая ноад унарный минус
    } else {
        tmp->type = UNO;
        tmp->right = s21_pop_stack_node(stack);
    }
    //Добавляем в дерево новую ноду
    stack->nodes[(stack->size)++] = tmp;
}


//Очистка дерева
void s21_remove_stack_node(s21_stack_node *stack) {
    stack->size = 0;
    free(stack->nodes);
}

//Извлечение значения из дерева выражений
s21_node *s21_pop_stack_node(s21_stack_node *stack) {
    if (stack->size == 0) {
        return NULL;
    } else {
        return stack->nodes[--(stack->size)];
    }
}

//Проверка на пустоту
int s21_is_empty_stack_node(s21_stack_node stack) {
    char res = 0;
    if (stack.size == 0)
        res++;
    return res;
}

//Отображение дерева
void s21_show_tree(s21_node *tree, int i) {
    if (i == 0) printf("\n\n\n");
    if (tree->right != NULL) {
        s21_show_tree(tree->right, i + 1);
    }
    for (int j = 0; j < i; ++j) {
        printf("\t");
    }
    printf("%s\n", tree->val);
    if (tree->left != NULL) {
        s21_show_tree(tree->left, i + 1);
    }
}

//Удаление дерева
void s21_remove_tree(s21_node **tree) {
    if (*tree != NULL) {
        if ((*tree)->right != NULL) {
            s21_remove_tree(&(*tree)->right);
        }
        if ((*tree)->left != NULL) {
            s21_remove_tree(&(*tree)->left);
        }
        free(*tree);
    }
}


//Убираем умножение на 1
void s21_prime(s21_node **tree) {
    if ((*tree)->right != NULL) {
        s21_prime(&(*tree)->right);
    }
    if ((*tree)->left != NULL) {
        s21_prime(&(*tree)->left);
    }
    if ((*tree)->val[0] == '*') {
        if ((*tree)->right->val[0] == '1' && strlen((*tree)->right->val) == 1) {
            s21_remove_tree(&((*tree)->right));
            s21_node *left = (*tree)->left;
            free(*tree);
            (*tree) = left;
        } else if ((*tree)->left->val[0] == '1' && strlen((*tree)->left->val) == 1) {
            s21_remove_tree(&((*tree)->left));
            s21_node *right = (*tree)->right;
            free((*tree));
            (*tree) = right;
        }
    }
}

//Перевод из дерева в вид выражения
char *reverse(s21_node *tree) {
    char *res = calloc(256, sizeof(char));

    if (tree->left != NULL) {
        strcat(res, reverse(tree->left));
    }

    strcat(res, tree->val);

    if (tree->right != NULL) {
        strcat(res, reverse(tree->right));
    }

    return res;
}