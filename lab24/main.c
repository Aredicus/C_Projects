#include <stdio.h>
#include "s21_calculation.h"
#include "s21_parser.h"

int main() {
    char *str = calloc(256, sizeof(char));
    scanf("%s", str);
    char *res = calloc(256, sizeof(char));
    res = strcpy(res, "Correct\n");
    s21_stack_char TMP, RESULT;
    s21_init_stack_char(&TMP);
    s21_init_stack_char(&RESULT);
    s21_parse(&TMP, &RESULT, str);
    if (RESULT.is_correct && TMP.is_correct) {
        s21_node *result;
        s21_stack_char TMP1;
        s21_reverse_stack_char(&RESULT);
        s21_copy_stack(RESULT, &TMP1);
        result = s21_calculation(&TMP1, NULL);
        if (TMP1.is_correct == 1) {
            s21_show_tree(result, 0);
            s21_prime(&result);
            s21_show_tree(result,0);
            char *r = reverse(result);
            printf("%s\n", r);
            free(r);
        } else if (TMP1.is_correct == 1) {
            res = strcpy(res, "Not correct\n");
        } else {
            res = strcpy(res, "Деление на 0\n");
        }
        s21_remove_stack_char(&TMP1);
        if(result != NULL) {
            s21_remove_tree(&result);
        }
    } else {
        res = strcpy(res, "Not correct\n");
    }
    printf("%s", res);
    free(res);
    free(str);
    s21_remove_stack_char(&TMP);
    s21_remove_stack_char(&RESULT);
    return 0;
}
