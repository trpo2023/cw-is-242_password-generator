#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int dlin ;
    int up ;
    int down ;
    int spets ;
    int kolvo ;

} libgen;

int Getrand(int min, int max);
libgen Ui(int x /*int* dlin, int* up, int* down, int* spets, int* kolvo*/);
int Good( int* good /*int dlin, int up, int down, int spets*/);
int Generation(int* arr, /*int dlin, int kolvo,*/ int* good);
int Output(int* arr, int i, int dlin);
