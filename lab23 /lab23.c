#include "lab23.h"


node *initTree(int value) {
    node *res = malloc(sizeof(node)); // Выделение памяти
    if (res == NULL) {
        error();
        exit(0);
    }
    res->value = value; // Начальная инициализация
    res->children = NULL;
    res->brothers = NULL;
    res->set = initSet();
    addSet(res->set, value);
    return res; // Возвращение указателя на созданный узел
}

Set *initSet() {
    Set *set = (Set *) malloc(sizeof(Set));
    if (set == NULL) {
        error();
        exit(0);
    }
    set->size = 0;
    set->capacity = 10;
    set->values = calloc(set->capacity, sizeof(int));
    return set;
}

void destroySet(Set **set) {
    free((*set)->values);
    free(*set);
    (*set) = NULL;
}

bool addSet(Set *set, int val) {
    if (isSet(set, val)) {
        set->size++;
        if (set->size == set->capacity) {
            set->capacity *= 2;
            int *tmp = realloc(set->values, set->capacity);
            set->values = tmp;
        }
        set->values[set->size - 1] = val;
        return true;
    } else {
        return false;
    }
}

bool isSet(Set *set, int val) {
    for (int i = 0; i < set->size; i++) {
        if (set->values[i] == val) return false;
    }
    return true;
}

void delSet(Set *set, int val) {
    if (!isSet(set, val)) {
        int k = 0;
        for (int i = 0; i < set->size - 1; i++) {
            if (set->values[i] == val) k++;
            set->values[i] = set->values[i + k];
        }
        set->size--;
    }
}

void addNode(node *tree, int where, int what) {
    if (isSet(tree->set, what)) {
        if (!isSet(tree->set, where)) {
            addSet(tree->set, what);
            if (tree->value == where) {
                if (tree->children != NULL) {
                    node *tmp = tree->children;
                    while (tmp->brothers != NULL) {
                        tmp = tmp->brothers;
                    }
                    tmp->brothers = initTree(what);
                    addSet(tmp->set, what);
                } else {
                    tree->children = initTree(what);
                }
            } else {
                if (tree->children != NULL) {
                    addNode(tree->children, where, what);
                }
                if (tree->brothers != NULL) {
                    addNode(tree->brothers, where, what);
                }
            }
        } else if (tree->brothers != NULL) {
            addNode(tree->brothers, where, what);
        }
    }
}

void sumSet(Set *dst, Set src) {
    for (int i = 0; i < src.size; i++) {
        if (!isSet(dst, src.values[i])) {
            addSet(dst, src.values[i]);
        }
    }
}

void delNode(node *tree, int what) {
    if (!isSet(tree->set, what)) {
        delSet(tree->set, what);
        if (tree->children != NULL) {
            if (tree->children->value == what) {
                node *del = tree->children;
                if (del->brothers != NULL) {
                    tree->children = del->brothers;
                    if (del->children != NULL) {
                        if (tree->children->brothers != NULL) {
                            node *tmp = tree->children->brothers;
                            while (tmp->brothers != NULL) {
                                tmp = tmp->brothers;
                            }
                            tmp->brothers = del->children;
                        } else {
                            tree->children->brothers = del->children;
                        }
                        delSet(del->set, del->value);
                        sumSet(tree->children->set, *(del->set));
                    }
                } else if (del->children != NULL) {
                    tree->children = del->children;
                } else {
                    tree->children = NULL;
                }
                destroySet(&(del->set));
                free(del);
                return;
            }
        }
        if (tree->brothers != NULL) {
            if (tree->brothers->value == what) {
                node *del = tree->brothers;
                if (del->brothers != NULL) {
                    tree->brothers = del->brothers;
                    if (del->children != NULL) {
                        if (tree->brothers->children != NULL) {
                            node *tmp = tree->brothers->children;
                            while (tmp->brothers != NULL) {
                                tmp = tmp->brothers;
                            }
                            tmp->brothers = del->children;
                        } else {
                            tree->brothers->children = del->children;
                        }
                        delSet(del->set, del->value);
                        sumSet(tree->brothers->set, *(del->set));
                    }
                } else if (del->children != NULL) {
                    if (tree->children != NULL) {
                        node *tmp = tree->children;
                        while (tmp->brothers != NULL) {
                            tmp = tmp->brothers;
                        }
                        tmp->brothers = del->children;
                    } else {
                        tree->children = del->children;
                    }
                } else {
                    tree->brothers = NULL;
                }
                destroySet(&del->set);
                free(del);
                return;
            }
        }
        if (tree->children != NULL) {
            delNode(tree->children, what);
        }
    } else if (tree->brothers != NULL) {
        delNode(tree->brothers, what);
    }
}

void showTree(node tmp, int i) {
    if (i == 0) {
        printf("\n\n\n");
    }
    for (int j = 0; j < i; j++) {
        printf("\t");
    }
    printf("%d\n", tmp.value);
    if (tmp.children != NULL) {
        node *t = tmp.children;
        while (t != NULL) {
            showTree(*t, i + 1);
            t = t->brothers;
        }
    }
}

void delTree(node **tree) {
    if ((*tree) != NULL) {
        destroySet(&((*tree)->set));
        if ((*tree)->children != NULL) {
            delTree(&(*tree)->children);
        }
        if ((*tree)->brothers != NULL) {
            delTree(&(*tree)->brothers);
        }
        free(*tree);
        (*tree) = NULL;
        tree = NULL;
    }
}

void rules() { // Правила
    printf("\n1. Создать дерево\n");
    printf("2. Добавить вершину\n");
    printf("3. Удалить вершину\n");
    printf("4. Показать дерево\n");
    printf("5. Найти значение нетерминальной вершины дерева с максимальной глубиной\n");
    printf("6. Удалить дерево\n");
    printf("7. Закончить программу\n");
    printf("\nВведите номер нужного пункта\n");
}

void error() { // Вывод ошибки
    printf("Что-то не так. Попробуй ещё раз\n");
    fflush(stdin); // Очистка буфера (на всякий)
    sleep(1); // Задержка, чтоб понять, что вообще происходит (френдли интерфейс, все дела)
}