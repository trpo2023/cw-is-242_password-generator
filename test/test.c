#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <string.h>
#include "../thirdparty/ctest.h"
#include "../src/LibPwgen/libgen.h"
    
CTEST(Getrand, returns_random_number_within_range)
{
    int min = 0;
    int max = 10;
    double time = 12345.0;
    double pusk = 6789.0;
    int result = Getrand(min, max, time, pusk);

    ASSERT_TRUE(result >= min && result <= max);
}

CTEST(wtime, returns_current_wall_time_in_seconds)
{
    double result1 = wtime();
    double result2 = wtime();

    ASSERT_TRUE(result1 <= result2);
}

// CTEST(Ui, fills_libgen_structure_with_user_input_values)
// {
//     // Создал фиктивный входной поток с тестовыми значениями
//     char input[] = "8\ny\nn\ny\n5\n";
//     FILE* mockstdin = fmemopen(input, sizeof(input), "r");

//     // Перенаправляю stdin и захватываю stdout
//     FILE* realstdin = stdin;
//     stdin = mockstdin;
//     char output[1000];
//     FILE* mockstdout = fmemopen(output, sizeof(output), "w");
//     FILE* realstdout = stdout;
//     stdout = mockstdout;

//     // Вызов тестируемой функции
//     libgen *t = malloc(sizeof(libgen));
//     Ui(t);

//     // Восстановить стандартный ввод и стандартный вывод
//     stdin = realstdin;
//     fclose(mockstdin);
//     fflush(stdout);
//     stdout = realstdout;

//     // Проверяем правильность заполнения структуры
//     ASSERT_EQUAL(8, t->dlin);
//     ASSERT_EQUAL(1, t->up);
//     ASSERT_EQUAL(0, t->down);
//     ASSERT_EQUAL(1, t->spets);
//     ASSERT_EQUAL(5, t->kolvo);
// }


// CTEST(Good, modifies_array_of_good_characters_according_to_libgen_structure)
// {
//     libgen t = { 8, 1, 0, 1, 5 };

//     int good[122];
//     for (int i = 33; i < 122; i++) {
//         good[i] = 1;
//     }

//     Good(&t);

//     ASSERT_FALSE(good['A']);
//     ASSERT_TRUE(good['a']);
//     ASSERT_TRUE(good['!']);
//     ASSERT_TRUE(good['@']);
//     ASSERT_TRUE(good['#']);
//     ASSERT_TRUE(good['$']);
//     ASSERT_TRUE(good['%']);
//     ASSERT_TRUE(good['^']);
//     ASSERT_TRUE(good['&']);
//     ASSERT_TRUE(good['*']);
//     ASSERT_FALSE(good['_']);
//     ASSERT_FALSE(good['`']);

//     // Другие символы не должны быть изменены
//     ASSERT_TRUE(good['B']);
//     ASSERT_TRUE(good['z']);
//     ASSERT_TRUE(good['~']);
// }


int is_good_password(char* password, size_t len, int* good)
{
    if (strlen(password) != len)
    {
        return 0;
    }
    for (size_t i = 0; i < len; i++) 
    {
        if (!good[(int)password[i]])
        {
            return 0;
        }
    }
    return 1;
}

int count_occurrences(const char* str, const char* substr) {
    int count = 0;
    size_t len_str = strlen(str);
    size_t len_substr = strlen(substr);
    if (len_str < len_substr) {
        return 0;
    }
    for (size_t i = 0; i <= len_str - len_substr; ++i) {
        if (strncmp(str + i, substr, len_substr) == 0) {
            ++count;
        }
    }
    return count;
}

// CTEST(Generation, generates_multiple_passwords_according_to_libgen_structure_and_array_of_good_characters)
// {
//     libgen t = { 8, 1, 0, 1, 5 };

//     int good[123];
//     for (int i = 33; i <= 122; i++) {
//         good[i] = 1;
//     }

//     // Перенаправляю stdout и захватываю вывод
//     char output[1000];
//     FILE* mockstdout = fmemopen(output, sizeof(output), "w");
//     FILE* realstdout = stdout;
//     stdout = mockstdout;

//     // Вызов тестируемой функции
//     Generation(&t, good);

//     // Восстанавливаю stdout
//     fflush(stdout);
//     stdout = realstdout;

//     // Проверяю, что было сгенерировано 5 паролей длиной 8
//     ASSERT_EQUAL(5, count_occurrences(output, "Password"));
//     ASSERT_EQUAL(40, strlen(strstr(output, "Password")));

//     // Проверяю, что все символы в каждом пароле подходят
//     char* p = strtok(output, "\n");
//     while (p != NULL) {
//         ASSERT_TRUE(is_good_password(p, t.dlin, good));
//         p = strtok(NULL, "\n");
//     }
// }

CTEST(test_generation, output_test) {
    // создаем структуру libgen для передачи её в функцию Generation
    libgen* t = (libgen*)malloc(sizeof(libgen));
    t->kolvo = 2;
    t->dlin = 5;

    // заполняем массив good значениями 1
    int good[1000];
    for (int i = 0; i < 1000; i++) {
        good[i] = 1;
    }
    char output[1000];
    // вызываем функцию Generation
    Generation(t, good);

    // сравниваем ожидаемый вывод с полученным
    char* p = strtok(output, "\n");
    while (p != NULL) {
        ASSERT_TRUE(is_good_password(p, t->dlin, good));
        p = strtok(NULL, "\n");
    }
}