#pragma once

void moveRight(int A[], int N);
void moveLeft(int A[], const int N);

void printArray(int[], const int);

void initArray(int[], const int, int A = -10, int B = 10);

void inputArray(int[], int);

int findMax(int[], int);
int findMin(int[], int);
void findMaxMin(int[], int, int&, int&);

int findSum(int[], int);
int findIdMax(int[], int);
int findIdMin(int[], int);

void howManyMaxMin(int[], const int, int&, int&);
int howMany(int[], const int, int);

void getPositiveNegativeArray(int[], const int, int&, int&);
void divArray(int[], const int, int[], int[]);
void halfArray(int[], const int, int[], int[]);

bool changeArray1(int[], const int);
bool changeArray2(int[], const int);
bool changeArray3(int[], const int);

int findIdFirstMax(int arr[], int N);
int findSumIf(int arr[], int n);
int findIdLastMin(int arr[], int N);