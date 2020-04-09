#pragma once

void createArray(int*&, const int);
int* createArray(const int);
void freeMemory(int*&, const int);
void initArray(int[], const int, int = -10, int = 10);
void printArray(int[], const int);

int indexOfMax(int[], int);
int indexOfMin(int[], int);

void inputArray(int[], int);

int findMax(int[], int);
int findMin(int[], int);
void findMaxMin(int[], int, int&, int&);

int getSum(int[], int);

void howManyMaxMin(int[], const int, int&, int&);
int howMany(int[], const int, int);

void divArray(int[], const int, int[], int[]);
void halfArray(int[], const int, int[], int[]);

void reverse(int[], const int);

void shiftRight(int[], int);
void shiftLeft(int[], const int);