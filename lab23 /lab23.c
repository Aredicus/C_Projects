#include "lab23.h"


node *initTree(int value) {
    node *res = malloc(sizeof(node)); // Выделение памяти
    if (res == NULL) { //  Если не выделилась
        error();
        exit(0);
    }
    res->value = value; // Начальная инициализация
    res->children = NULL;
    res->brothers = NULL;
    res->set = initSet(); // Добавляем в вершину стек
    addSet(res->set, value); // Добавляем в стек саму вершину
    return res; // Возвращение указателя на созданный узел
}

Set *initSet() {
    Set *set = (Set *) malloc(sizeof(Set)); // выделяем память
    if (set == NULL) { // Если не выделилась
        error();
        exit(0);
    }
    set->size = 0;
    set->capacity = 100; // текущее максимальное значение
    set->values = calloc(set->capacity, sizeof(int)); // выделение памяти под значения
    return set;
}

void destroySet(Set **set) {
    free((*set)->values); // чистим значения
    free(*set); // чистим стек
    (*set) = NULL; // NULL, чтоб все знали
}

bool addSet(Set *set, int val) {
    if (isSet(set, val)) { // Добавлять ли значение
        set->size++; // увеличиваем размер
        if (set->size == set->capacity) { // Если размер максимальный
            set->capacity *= 2; // увеличиваем вдвое
            int *tmp = realloc(set->values, set->capacity);
            set->values = tmp;
        }
        set->values[set->size - 1] = val; // выставляем значение
        return true; // говорим об успешности
    } else {
        return false; // если не добавляем
    }
}

bool isSet(Set *set, int val) {
    for (int i = 0; i < set->size; i++) { // бежим по сету
        if (set->values[i] == val) return false; // если встречаем, то false
    }
    return true;
}

void delSet(Set *set, int val) {
    if (!isSet(set, val)) { // Есть ли вообще удаляемое в сете
        int k = 0;
        for (int i = 0; i < set->size - 1; i++) {
            if (set->values[i] == val) k++;
            set->values[i] = set->values[i + k]; // перезаполняем сет
        }
        set->size--; // уменьшаем размер
    }
}

void addNode(node *tree, int where, int what) {
    if (isSet(tree->set, what)) { // Были ли вставляемая вершина раньше
        if (!isSet(tree->set, where)) {  // Если в дереве вершина, куда надо добавить новую
            addSet(tree->set, what); // добавляем в поддерева сведения о новой вершине
            if (tree->value == where) { // Если это вершина
                if (tree->children != NULL) { // Дети есть
                    node *tmp = tree->children;
                    while (tmp->brothers != NULL) { // Идем в конец братьев
                        tmp = tmp->brothers;
                    }
                    tmp->brothers = initTree( what); // к последнему брату добавляем новую вершину
                    addSet(tmp->set, what); // братья знают только о следующем после них
                } else {
                    tree->children = initTree(what); // если детей нет, то первенец
                }
            } else { // Продолжаем поиск куда вставлять
                if (tree->children != NULL) { // Идем по детям, если есть
                    addNode(tree->children, where, what);
                }
                if (tree->brothers != NULL) { // Идем по братьям, если есть
                    addNode(tree->brothers, where, what);
                }
            }
        } else if (tree->brothers != NULL) { // в силу того, что братья не знают всех своих братьев, а значит и их детей
            addNode(tree->brothers, where, what);  // То надо проверить их всех
        }
    }
}

void sumSet(Set *dst, Set src) {
    for (int i = 0; i < src.size; i++) { // идем по src
        if (!isSet(dst, src.values[i])) { //  Если в dst нет элемента из src
            addSet(dst, src.values[i]);
        }
    }
}

void delNode(node *tree, int what) {
    if (!isSet(tree->set, what)) { // Есть ли удаляемая вершина
        delSet(tree->set, what); // удаляем искомую вершину из сета
        if (tree->children != NULL) { // Если есть дети
            if (tree->children->value == what) { // Удаляемая вершина - первый ребенок?
                node *del = tree->children; // Записываем как удаляемую вершину
                if (del->brothers != NULL) { // есть братья?
                    tree->children = del->brothers; // ставим на место старой брата
                    if (del->children != NULL) { // были ли у старой дети?
                        if (tree->children->children != NULL) { // Если У новой есть дети, то спускаемся по ним
                            node *tmp = tree->children->children;
                            while (tmp->brothers != NULL) {
                                tmp = tmp->brothers;
                            }
                            tmp->brothers = del->children; // И ставим новыми братьями всех детей старой
                        } else {
                            tree->children->children = del->children; // иначе просто записываем в дети
                        }
                        delSet(del->set, del->value); // удаляем из сета удаляемую вершиныу
                        sumSet(tree->children->set, *(del->set)); // суммируем сет новой вершины и прошлой
                    }
                } else if (del->children != NULL) { // Если же есть только дети
                    tree->children = del->children; // Новой вершиной будет первый ребенок
                } else {
                    tree->children = NULL; // Просто удаляем
                }
                destroySet(&(del->set));
                free(del);
                return;
            }
        }
        if (tree->brothers != NULL) { // Есть ли братья?
            if (tree->brothers->value == what) { // удаляемая вершина - брат?
                node *del = tree->brothers; // брат становится удаляемой вершиной
                if (del->brothers != NULL) { // Были ли у него братья?
                    tree->brothers = del->brothers; // тогда новой вершиной становится брат
                    if (del->children != NULL) { // были ли у старой дети?
                        if (tree->brothers->children != NULL) { // Есть ли у новой дети?
                            node *tmp = tree->brothers->children; //Идем вниз по детям
                            while (tmp->brothers != NULL) {
                                tmp = tmp->brothers;
                            }
                            tmp->brothers = del->children; // и ставим им новых братиков
                        } else {
                            tree->brothers->children = del->children; // иначе дети старой становятся детьми новой
                            // (сурово)
                        }
                        delSet(del->set, del->value); //  Удаляем из сета удаляемую вершину
                        sumSet(tree->brothers->set, *(del->set)); // суммируем старый сет и новый
                    }
                } else if (del->children != NULL) { // Если не было братьев, но были дети
                    if (tree->children != NULL) { // ставим их братьями детей, если такие есть
                        node *tmp = tree->children;
                        while (tmp->brothers != NULL) {
                            tmp = tmp->brothers;
                        }
                        tmp->brothers = del->children;
                    } else {
                        tree->children = del->children; // иначе просто детьми
                    }
                    //Данный блок нужен, чтоб вообще новая вершина знала о существовании добавленных ей детей старой
                    delSet(del->set, del->value); //  Удаляем из сета удаляемую вершину
                    sumSet(tree->set, *(del->set)); // суммируем старый сет и новый
                } else { //  Если никого не было
                    tree->brothers = NULL; // просто удаляем
                }
                destroySet(&del->set); // удаляем сет
                free(del); // удаляем вершину
                return;
            }
        }
        if (tree->children != NULL) { // если есть дети
            delNode(tree->children, what); // идем искать по детям
        }
    } else if (tree->brothers != NULL) { // быть может она есть в братьях
        delNode(tree->brothers, what);
    }
}

void showTree(node tmp, int i) { // Показываем дерево
    if (i == 0) {
        printf("\n\n\n"); // отделяем от общего выводы
    }
    for (int j = 0; j < i; j++) { // табуляция
        printf("\t");
    }
    printf("%d\n", tmp.value); // само дерево
    if (tmp.children != NULL) { // дети (братья так и так покажутся)
        node *t = tmp.children;
        while (t != NULL) {
            showTree(*t, i + 1);
            t = t->brothers;
        }
    }
}

void delTree(node **tree) {
    if ((*tree) != NULL) { // Есть ли вообще удаляемое дерево
        destroySet(&((*tree)->set)); // удаляем сет
        if ((*tree)->children != NULL) { // Если есть дети, то идем удалять детей
            delTree(&(*tree)->children);
        }
        if ((*tree)->brothers != NULL) { // Если есть братья, то идем удалять братьев
            delTree(&(*tree)->brothers);
        }
        free(*tree); // Удаляем дерево
        (*tree) = NULL; // На всякий
    }
}

pair search(node *tree, int lvl) {
    pair res;
    res.i = lvl;
    res.value = tree->value;
    if (tree->children != NULL) { // Если у текущий вершины есть дети
        node *tmp = tree->children;
        if (tmp->children != NULL) { // Если у детей есть дети
            res = search(tmp, lvl + 1); // Идем вниз дальше
        }
    } else { // Если нет детей
        res.i = 0; // Не наша вершина
    }
    pair tmp;
    tmp.i = lvl;
    tmp.value = tree->value;
    if (tree->brothers != NULL) { // Проверим еще и братьев
        tmp = search(tree->brothers, lvl);
    } else {
        tmp.i = 0;
    }
    return tmp.i > res.i ? tmp : res; // вернем большое из братьев и детей
}

void deep(node *tree) {
    if (tree->children == NULL) { // Есть ли у дерева вообще дети
        printf("Таких вершин нет");
    } else {
        pair tmp = search(tree, 0); // Иначе запустим поиск
        printf("deep: %d value: %d", tmp.i, tmp.value);
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