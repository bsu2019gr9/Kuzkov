#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "list.h"

using namespace std;

typedef uint16_t WORD;
typedef uint32_t D_WORD;

#pragma pack(push, 2)
struct SFHeader
{
    WORD type;
    D_WORD countOfObjects;
};
#pragma pack(pop)

struct ConstructMat
{
    int id;

    int storeNumber;
    double distance;

    int quantity;
    int price;

    friend ostream& operator<<(ostream&, ConstructMat&);
    friend istream& operator>>(istream&, ConstructMat&);
};


bool cmp_byStoreNumber(ConstructMat&, ConstructMat&);
bool cmp_byQuantity(ConstructMat&, ConstructMat&);
bool cmp_byPrice(ConstructMat&, ConstructMat&);
bool cmp_byDist(ConstructMat&, ConstructMat&);
bool cmp_byId(ConstructMat&, ConstructMat&);

class Storage
{
private:
    List<ConstructMat> list;
    string fname;

public:
    Storage(string);
    ~Storage();

    void printAll();
    void inputMaterial();

    void addMaterial(const ConstructMat&);
    ConstructMat& getMaterial(int);
    void deleteMaterial(int);

    void sort(bool (*comp)(ConstructMat&, ConstructMat&) = cmp_byStoreNumber);
    int buyAmountOf(int, int);
    int getAmountOf(int, int = -1);
};