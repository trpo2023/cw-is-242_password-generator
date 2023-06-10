#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include "libgen.h"

int Getrand(int min, int max, double time, double pusk)
{
    srand(time + pusk);
    return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

void Ui(libgen* t)
{
    t = malloc(sizeof(libgen) * t->kolvo);
    char flag;

    printf("Write the password length (digit)\n");
    scanf(" %d", &t->dlin);

    printf("Use capital letters?(y/n)\n");
    scanf(" %c", &flag);
    if (flag == 'y')
        t->up = 1;

    printf("Use small letters?(y/n)\n");
    scanf(" %c", &flag);
    if (flag == 'y')
        t->down = 1;

    printf("Use special characters?(y/n)\n");
    scanf(" %c", &flag);
    if (flag == 'y')
        t->spets = 1;

    printf("Write down how many passwords you need to generate (digit)\n");
    scanf(" %d", &t->kolvo);
    Good(t);
}

void Good(libgen* t)
{
    int good[123];

    for (int i = 33; i < 122; i++) {
        good[i] = 1;
    }

    for (int i = 91; i <= 96; i++) {
        good[i] = 0;
    }

    if (t->up == 0) {
        for (int i = 65; i <= 90; i++) {
            good[i] = 0;
        }
    }

    if (t->down == 0) {
        for (int i = 97; i <= 122; i++) {
            good[i] = 0;
        }
    }

    if (t->spets == 0) {
        for (int i = 33; i <= 47; i++) {
            good[i] = 0;
        }

        for (int i = 58; i <= 64; i++) {
            good[i] = 0;
        }
    }
    Generation(t, good);
}

void Generation(libgen* t, int* good)
{
    double time = 0;
    double pusk = 0;
    int arr[t->dlin];
    int i = 0;
    int min = 33;
    int max = 122;
    time = wtime();
    int tmp = Getrand(min, max, time, pusk);
    pusk += 1;

    for (i = 1; i < t->kolvo + 1; i++) {
        for (int j = 0; j < t->dlin; j++) {
            while (good[tmp] == 0) {
                time = wtime();
                tmp = Getrand(min, max, time, pusk);
                pusk += 1;
            }
            arr[j] = tmp;
            time = wtime();
            tmp = Getrand(min, max, time, pusk);
            pusk += 1;
        }

        Output(arr, i, t->dlin);
    }
    // free(t);
}

void Output(int* arr, int i, int dlin)
{
    FILE* file = fopen("Results-passwords/Results.txt", "a");
    fprintf(file, "Password №%d:\n ", i);
    printf("Password №%d:\n", i);
    for (int x = 0; x < dlin; x++) {
        printf("%c", arr[x]);
        fprintf(file, "%c", arr[x]);
    }
    for (int rev = 0; rev < 2; rev++) {
        printf("\n");
        fprintf(file, "\n");
    }
    fclose(file);
}