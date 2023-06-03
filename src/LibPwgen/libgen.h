#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int dlin;
    int up;
    int down;
    int spets;
    int kolvo;

} libgen;

int Getrand(int min, int max, double time, double pusk);
void Ui(libgen* t);
void Good(libgen* t);
void Generation(libgen* t, int* good);
void Output(int* arr, int i, int dlin);
double wtime();