#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libgen.h"

int Getrand(int min, int max)
{
    return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

libgen Ui(int* dlin, int* up, int* down, int* spets, int* kolvo)
{
    char flag;
    libgen data;
    printf("Write the password length (digit)\n");
    scanf("%d", &dlin);

    printf("Use capital letters?(y/n)\n");
    scanf("%c", &flag);
    if (flag == 'y')
    {
        *up = 1;
    }
    else
    {
        *up = 0;
    }

    printf("Use small letters letters?(y/n)\n");
    scanf("%c", &flag);
    if (flag == 'y')
    {
        *down = 1;
    }
    else
    {
        *down = 0;
    }

    printf("Use special characters?(y/n)\n");
    scanf("%c", &flag);
    if (flag == 'y')
    {
        *spets = 1;
    }
    else
    {
        *spets = 0;
    }

    printf("Write down how many passwords you need to generate (digit)\n");
    scanf("%d", &kolvo);
    
    return data;
}

int Good(int* good, int dlin, int up, int down, int spets)
{
    for (int i = 91; i < 96; i++) {
        good[i] = 0;
    }

    if (up == 0) {
        for (int i = 65; i < 90; i++) {
            good[i] = 0;
        }
    }

    if (down == 0) {
        for (int i = 97; i < 122; i++) {
            good[i] = 0;
        }
    }

    if (spets == 0) {
        for (int i = 33; i < 47; i++) {
            good[i] = 0;
        }

        for (int i = 58; i < 64; i++) {
            good[i] = 0;
        }
    }
}

int Generation(int* arr, int dlin, int kolvo, int* good)
{
    int i = 0;
    int min = 33;
    int max = 122;
    int tmp = Getrand(min, max);

    for (i = 1; i < kolvo + 1; i++) {
        for (int j = 0; j < dlin; j++) {
            while (good[tmp] == 0) {
                tmp = Getrand(min, max);
            }
            arr[j] = tmp;
            tmp = Getrand(min, max);
        }

        Output(arr, i, dlin);
    }
}

int Output(int* arr, int i, int dlin)
{
    printf("Password №%d:\n", i);
    for (int x = 0; x < dlin; x++)
        printf("%c", arr[x]);
    printf("\n");
}

// int Total()
// {
//     int a;
//     int b;
//     int c;
//     int d;
//     int e;
//     Ui(&a, &b, &c, &d, &e);
//     char r[a];
//     Good();
// }