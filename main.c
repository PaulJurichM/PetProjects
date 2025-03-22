Отлично! Тогда начнём финальный этап — сборку всех модулей в одну целостную программу, которая:

1. принимает на вход строку с выражением `f(x)`,
2. разбивает её на лексемы (лексер),
3. переводит в польскую нотацию (RPN),
4. вычисляет значения функции по x (evaluate_rpn),
5. строит график (draw_graph).

---

### 📁 Структура проекта
```
.
├── src/
│   ├── main.c
│   ├── s21_string.h / s21_string.c
│   ├── s21_stack.h / s21_stack.c
│   ├── s21_rpn.h   / s21_rpn.c
│   ├── s21_lexer.h / s21_lexer.c
│   ├── s21_graph.h / s21_graph.c
│   └── s21_math.h  / s21_math.c   (если оборачиваешь math.h)
└── Makefile
```

---

### 🧠 Главная логика: `main.c`

```c
#include <stdio.h>
#include <math.h>
#include "s21_lexer.h"
#include "s21_rpn.h"
#include "s21_stack.h"
#include "s21_string.h"
#include "s21_graph.h"

// Настройки графика
#define WIDTH 80
#define HEIGHT 25
#define X_START 0.0
#define X_END (4 * M_PI)
#define Y_MIN -1.0
#define Y_MAX 1.0

int main() {
    const char *input_expr = "sin(x)";  // Можно заменить на ввод через scanf
    token_list_t tokens = tokenize(input_expr);
    if (tokens.size == 0) {
        printf("Ошибка лексера\n");
        return 1;
    }

    token_list_t rpn = convert_to_rpn(tokens);
    if (rpn.size == 0) {
        printf("Ошибка при преобразовании в RPN\n");
        return 1;
    }

    double y_values[WIDTH];
    double step = (X_END - X_START) / WIDTH;

    for (int i = 0; i < WIDTH; ++i) {
        double x = X_START + i * step;
        double y = evaluate_rpn(rpn, x);
        y_values[i] = y;
    }

    draw_graph(y_values, WIDTH, HEIGHT, Y_MIN, Y_MAX);

    free_tokens(&tokens);
    free_tokens(&rpn);

    return 0;
}
```

---

### 🎯 Что нужно реализовать/проверить

1. `tokenize()` — возвращает список лексем из строки (модуль лексера).
2. `convert_to_rpn()` — преобразует лексемы в обратную польскую нотацию.
3. `evaluate_rpn(rpn, x)` — подставляет x и возвращает значение выражения.
4. `draw_graph(y_values, WIDTH, HEIGHT, Y_MIN, Y_MAX)` — рисует график.

---

### 🧱 Принципы Дейкстры, которые использованы:

- **Каждая функция делает только одну вещь.**
  - `tokenize` только парсит строку, `evaluate_rpn` только считает и т.д.
- **Отделение ввода/вывода от логики.**
  - Всё, что связано с отрисовкой, — только в `draw_graph`.
- **Минимизация побочных эффектов.**
  - Нет глобальных переменных, работа ведётся с локальными копиями.
- **Ясная структура кода.**
  - Разделение по модулям, понятные интерфейсы.

---

Если у тебя всё готово — можем:
1. Отладить `main.c`,
2. Написать `Makefile`,
3. Добавить возможность считывать выражение через `scanf()` или аргумент командной строки.

Готов двигаться дальше?
