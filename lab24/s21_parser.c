#include "s21_parser.h"

// функция проверки на валидность входной строки
// s21_stack_char *stackChar - врменный стек, необходимой для проверки корректности и занесения операций
// s21_stack_char *stackResult - результирующий стек
// const char *string - входная строка
void s21_parse(s21_stack_char *stackChar, s21_stack_char *stackResult,
               const char *string) {
    // переменная для проверки на унарный минус
    // в данном алгоритме унарный минус существует только в двух ситуациях:
    // 1) Начало строки
    // 2) После открывающей скобки
    // ситуации по типу 1*-1 считаются ошибкой, корректная запись: 1*(-1)
  int un_min = 1;
  // вводим "бегунок" по строке" отвечающий за текущее положение в строке
  char *tmp = (char *)string;
  // Цикл, пока не дойдем до конца строки
  for (; *tmp != '\0'; tmp++) {
      // Алгоритм считает эквивалентными записи "1+1" и "1 + 1"
    if (*tmp == ' ') {
      continue;
        //  Алгоритм поддерживает переменные типа
        //  Pi - Число пи
        //  e - Число е
        //  x - Переменная; в данном случаи пропускается и в дальнейшем будет выставлено или стартовое значение
        //  или дополнительно указанное
    } else if (isdigit(*tmp) || *tmp == 'P' || *tmp == 'e' || *tmp == 'x') {
      //числа и константы сразу добавляются в результирующий стек согласно алгоритму Дейкстри
      s21_push_double(stackResult, tmp);
      // Двигаем бегунок на размер числа или длину названия константы
      if (isdigit(*tmp)) {
        for (; isdigit(*tmp) || *tmp == '.'; tmp++);
      } else {
        for (; isalpha(*tmp); tmp++)
          ;
      }
      tmp--;
      //Так как ввели число, по условию далее унарного минуса быть не может
      un_min = 0;
    //Проверка на функцию, типа sin(), tan() и т.д. Общим словом тригонометрические (так как mod считается операцией)
    } else if (isalpha(*tmp) && *tmp != 'm') {
      //Так как у функций есть приоритет, сначала кидаем их во временный стек
      s21_push_fun(stackChar, tmp);
      //Пропускаем длину названия функции
      for (; isalpha(*tmp); tmp++)
        ;
      tmp--;
      //Унарного минуса уже быть не может (Тут после будет отдельно проверка на "(", а значит унарный минус появится
      un_min = 0;
    // Остаются только операторы
    } else {
      s21_push_operator(stackChar, stackResult, tmp, un_min);
      if (*tmp == '(')
          //Появление унарного минуса при открывающейся скобке
        un_min = 1;
      else
        un_min = 0;
      // Так как у нас есть операция mod, то надо пройти её длину
      if (isalpha(*tmp)) {
        for (; isalpha(*tmp); tmp++)
          ;
        tmp--;
      }
    }
  }
  //По окончанию пробега по строке происходит проверка на коректнсоть строки, а также получение результирующего стека
  while (!s21_is_empty_stack_char(*stackChar)) {
      // Так как при добавлении в стек ")" мы удаляем оттуда "(", то появление в стеке "(" значит некоректный ввод
    if (strcmp(s21_show_top_char(stackChar), "(") == 0)
      s21_ERROR(stackResult);
    //Разворачиваем дополнительный стек согласно алгоритма Дейкстры
    s21_push_stack_char(stackResult, s21_pop_stack_char(stackChar));
  }
}

//Функция добавления числа в стек
//Внтри функции также проверяется, что число существующего формата: 1.1 или 1, а не 1.1.1 или 1фф! или иное
//s21_stack_char *stackChar - стек, куда добавляем число
//char *string - исходная строка
void s21_push_double(s21_stack_char *stackChar, char *string) {
  // Счетчик длины числа
  int i = 0;
  //Местный "бегунок"
  char *tmp = string;
  //Специальное условие для констант
  if (isalpha(*tmp)) {
    for (; isalpha(*tmp); tmp++) {
      i++;
    }
  // Условие для чисел
  } else {
    // Переменная для учета точки
    int is_p = 0;
    // Бежим по числу
    for (; isdigit(*tmp) || *tmp == '.'; tmp++, i++) {
      // Проверяем, что точка встречается впервые
      if (*tmp == '.' && is_p == 0)
        is_p = 1;
      //Иначе помечаем ошибкой
      else if (*tmp == '.' && is_p == 1) {
        s21_ERROR(stackChar);
      }
    }
  }
  //Выдделяем память на новое число
  char *tmp_number = calloc(256, sizeof(char));
  //копируем его в новую память
  tmp_number = strncpy(tmp_number, string, i);
  //проверяем, что корректный формат
  if (isdigit(*tmp_number) || s21_is_fun(tmp_number)) {
    // Пушим в наш стек
    s21_push_stack_char(stackChar, tmp_number);
    if (strcmp(tmp_number, "x") == 0)
      // Если же встречаем x, то делаем пометку
      stackChar->is_x++;
  // иначе помечаем ошибкой
  } else {
    s21_ERROR(stackChar);
    free(tmp_number);
  }
}

//s21_stack_char *stackChar - стек, куда добавляем
//char *string - исходная строка
void s21_push_fun(s21_stack_char *stackChar, char *string) {
  // счетчик длины функции
  size_t i = 0;
  // местный "бегунок"
  char *tmp = string;
  for (; isalpha(*tmp); tmp++) {
    i++;
  }
  // копируем найденную функцию
  char *tmp_fun = calloc(256, sizeof(char));
  tmp_fun = memcpy(tmp_fun, string, i);
  // Проверяем, что функция валидная (из пула)
  if (s21_is_fun(tmp_fun)) {
    // Если валидная, то пушем
    s21_push_stack_char(stackChar, tmp_fun);
  } else {
    // Если не валидная, то помечаем ошибкой
    s21_ERROR(stackChar);
  }
}


//функция добавления операторов
//s21_stack_char *stackChar - временный стек
//s21_stack_char *stackResult -результирующйи стек
//char *string - исходная строка
//int un_min - текущее состояние унарного минуса
void s21_push_operator(s21_stack_char *stackChar, s21_stack_char *stackResult,
                       char *string, int un_min) {
  //создаем бегунок, которой либо равен 1, если не mod или 0
  size_t i = isalpha(*string) ? 0 : 1;
  char *tmp_s = string;
  for (; isalpha(*tmp_s); tmp_s++) {
    i++;
  }
  //копируем оператор
  char *tmp_op = calloc(i, sizeof(char));
  tmp_op = memcpy(tmp_op, string, i);
  //проверяем приоритетность
  int priority = s21_get_priority(tmp_op);
  int tmp;
  //отдельно проверяем на унарный минус и тогда меняем приоритет и символ, чтоб отличать от обычного минуса
  if (un_min && *tmp_op == '-') {
    *tmp_op = '~';
    priority = 3;
  }
  //проверка на невозможные варианты:
  //неизвестный оператор
  //оператор начинается на m но сам оператор не mod
  if (priority == -1 ||
      (priority == 2 && isalpha(*string) && !s21_is_fun(tmp_op))) {
    free(tmp_op);
    //Выдаем ошибку
    s21_ERROR(stackResult);
  // Если не закрывающаяся скобка или не второй аргумент
  } else if (priority != 4) {
    // Согласно алгоритма, мы вытаскиваем из временного стека в результирующий все переменные и функции, чей приоритет
    // Выше добавляемого, за исключением открывающей скобки
    while ((tmp = s21_get_priority(s21_show_top_char(stackChar))) >= priority &&
           tmp != -1 && priority != 5 && tmp != 5) {
      s21_push_stack_char(stackResult, s21_pop_stack_char(stackChar));
    }
    //Добавляем во временный стек наш оператор
    s21_push_stack_char(stackChar, tmp_op);
  // Если закрывающая скобка
  } else {
    // Вытаскиваем из временного стека все операторы до встречи с открывающей скобкой
    while ((tmp = s21_get_priority(s21_show_top_char(stackChar))) != 5 &&
           tmp != 4 && tmp != -1) {
      s21_push_stack_char(stackResult, s21_pop_stack_char(stackChar));
    }
    // Если не встретилась открывающая скобка, то выдаем ошибку
    if (tmp == -1) {
      s21_ERROR(stackResult);
    } else {
      // Если открывающая скобка и при этом наш оператор закрывающая скобка, то удаляем открывающую
      if (tmp == 5 && *tmp_op == ')')
        free(s21_pop_stack_char(stackChar));
      //Проверяем временный стек на пустоту (это нужно, чтоб обозначить, что скобка для аргументов функции
      if (!s21_is_empty_stack_char(*stackChar)) {
        // Проверяем, что там лежит функция
        if (isalpha(s21_show_top_char(stackChar)[0])) {
          // Пушим функцию в результирующий стек
          s21_push_stack_char(stackResult, s21_pop_stack_char(stackChar));
        }
      }
    }
    //При добавлении строки, мы создаем новую строку внутри стека, поэтому эту чистим, чтоб избежать утечки
    free(tmp_op);
  }
}

// функция определения приоритета операции
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

//Проверка, что функция валидная
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