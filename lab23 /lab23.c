#include "lab23.h"


node *initTree(int value) {
    node *res = malloc(sizeof(node)); // Выделение памяти
    res->value = value; // Начальная инициализация
    res->children = NULL;
    res->f_child = NULL;
    res->brothers = NULL;
    res->set = initSet();
    addSet(res->set, value);
    return res; // Возвращение указателя на созданный узел
}

Set *initSet() {
    Set *set = (Set *) malloc(sizeof(Set));
    set->size = 0;
    set->capacity = 10;
    set->values = calloc(set->capacity, sizeof(int));
    return set;
}

void destroySet(Set **set) {
    free((*set)->values);
    free(*set);
    (*set)->size = 0;
    (*set)->capacity = 0;
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
        for (int i = 0; i < set->size; i++) {
            if (set->values[i] == val) k++;
            set->values[i] = set->values[i + k];
        }
        set->size--;
    }
}

void addNode(node *tree, int parent, int val) {
    if (!isSet(tree->set, parent) && isSet(tree->set, val)) {
        addSet(tree->set, val);
        if (tree->value == parent) {
            if (tree->f_child != NULL) {
                if (tree->children == NULL) {
                    tree->children = initTree(val);
                } else {
                    node *tmp = tree->children;
                    while (tmp->brothers != NULL) {
                        tmp = tmp->brothers;
                    }
                    tmp->brothers = initTree(val);
                }
            } else {
                tree->f_child = initTree(val);
            }
        } else if (tree->f_child != NULL) {
            addNode(tree->f_child, parent, val);
            if (tree->children != NULL) {
                node *tmp = tree->children;
                while (tmp != NULL) {
                    addNode(tmp, parent, val);
                    tmp = tmp->brothers;
                }
            }
        }
    }
}

void delNode(node *tree, int val) {
    if (!isSet(tree->set, val)) {
        delSet(tree->set, val);
        if (tree->f_child != NULL) {
            if (tree->f_child->value == val) {
                node *tmp = tree->f_child;
                tree->f_child = tmp->f_child;
                node *bro = tree->children;
                if (bro != NULL) {
                    while (bro->brothers != NULL) {
                        bro = bro->brothers;
                    }
                    bro->brothers = tmp->children;
                } else {
                    tree->children = tmp->children;
                }
                destroySet(&(tmp->set));
                free(tmp);
                return;
            }
        }
        if (tree->value == val) {

        }
        if (tree->children != NULL) {
            if (tree->children->value == val) {
                node *tmp = tree->children;
                if (tmp->brothers != NULL) {
                    tree->children = tmp->brothers;
                    node *child = tree->children->children;
                    if (child != NULL) {
                        while (child->brothers != NULL) {
                            child = child->brothers;
                        }
                    }
                    if (tmp->f_child != NULL) {
                        child = tmp->f_child;
                        child->brothers = tmp->children;
                    } else {
                        child = tmp->children;
                    }
                } else {
                    tree->children = tmp->f_child;
                    tree->children->brothers = tmp->children;
                }
                destroySet(&(tmp->set));
                free(tmp);
                return;
            }
        } else {
            delNode(tree->f_child, val);
            node *tmp = tree->children;
            while (tmp != NULL) {
                delNode(tmp, val);
                tmp = tmp->brothers;
            }
        }
    }
}

void showTree(node tmp, int i) {
    if (i == 0) {
        printf("\n\n\n");
    }
    if (tmp.f_child != NULL) {
        showTree(*tmp.f_child, i + 1);
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
        if ((*tree)->f_child != NULL) {
            delTree(&(*tree)->f_child);
        }
        if ((*tree)->brothers != NULL) {
            delTree(&(*tree)->brothers);
        }
        free(*tree);
        *tree = NULL;
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