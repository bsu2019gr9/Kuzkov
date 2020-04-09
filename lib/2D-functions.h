#pragma once

int **createArray(const int, const int);
void freeMemory(int**&, const int, const int);
void initArray(int**, const int, const int, int = 10, int = -10);
void printArray(int**, const int, const int, const int = 3);
