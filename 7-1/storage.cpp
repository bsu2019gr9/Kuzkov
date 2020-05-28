#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "storage.h"

using namespace std;

const int W = 15;

ostream& operator<<(ostream &out, ConstructMat &mat)
{
    out << setw(W) << mat.id
        << setw(W) << mat.storeNumber
        << setw(W) << mat.distance
        << setw(W) << mat.quantity
        << setw(W) << mat.price
        << endl;
    return out;
}

istream& operator>>(istream &in, ConstructMat &mat)
{
    in  >> mat.id
        >> mat.storeNumber
        >> mat.distance
        >> mat.quantity
        >> mat.price;
    return in;
}



Storage::Storage(string filename) : fname(filename)
{
    ifstream fin(fname);

    if (fin.good())
    {
        SFHeader header;
        fin.read((char*) &header, sizeof(SFHeader));

        if (!(header.type == 0x5346 || header.type == 0x7366))
            throw logic_error("Wrong file format");

        ConstructMat temp;
        for (int i = 0; i < header.countOfObjects; i++)
        {
            fin.read((char*) &temp, sizeof(ConstructMat));
            list.push(temp);
        }
    }

    fin.close();
}

Storage::~Storage()
{
    ofstream fout(fname);

    SFHeader header;
    header.type = 0x5346;
    header.countOfObjects = list.getLength();

    fout.write((char*) &header, sizeof(SFHeader));

    for (auto *it = list.begin(); it != nullptr; it = list.next(it))
    {
        fout.write((char*) &(it->data), sizeof(it->data));
    }

    fout.close();
}

void Storage::addMaterial(const ConstructMat &mat)
{
    list.push(mat);
}

ConstructMat& Storage::getMaterial(int id)
{
    for (auto *it = list.begin(); it != nullptr; it = list.next(it))
        if (it->data.id == id)
            return it->data;

    throw logic_error("No item with that id");
}

void Storage::deleteMaterial(int id)
{
    for (auto *it = list.begin(); it != nullptr; it = list.next(it))
        if (it->data.id == id)
            list.unbindAndDelete(it);
}

void Storage::printAll()
{
    cout << setw(W) << "ID"
         << setw(W) << "StoreNum"
         << setw(W) << "Dist"
         << setw(W) << "Quant"
         << setw(W) << "Price"
         << endl;

    for (auto *it = list.begin(); it != nullptr; it = list.next(it))
        cout << it->data;
}

void Storage::inputMaterial()
{
    ConstructMat mat;
    cin >> mat;
    this->addMaterial(mat);
}



bool cmp_byStoreNumber(ConstructMat &m1, ConstructMat &m2)
{
    return m1.storeNumber > m2.storeNumber;
}

bool cmp_byDist(ConstructMat &m1, ConstructMat &m2)
{
    return m1.distance > m2.distance;
}

bool cmp_byId(ConstructMat &m1, ConstructMat &m2)
{
    return m1.id > m2.id;
}

bool cmp_byQuantity(ConstructMat &m1, ConstructMat &m2)
{
    return m1.quantity > m2.quantity;
}

bool cmp_byPrice(ConstructMat &m1, ConstructMat &m2)
{
    return m1.price > m2.price;
}



void Storage::sort(bool (*comp)(ConstructMat&, ConstructMat&))
{
    for (auto *i = list.begin(); i != nullptr; i = list.next(i))
        for (auto *j = list.next(i); j != nullptr; j = list.next(j))
            if (comp(i->data, j->data))
                swap(i->data, j->data);
}

int Storage::buyAmountOf(int id, int quantity)
{
    int res = 0;
    this->sort(cmp_byDist);
    for (auto *it = list.begin(); it != nullptr; it = list.next(it))
    {
        if (it->data.id != id) continue;

        if (it->data.quantity >= quantity)
        {
            res += quantity * it->data.price;
            it->data.quantity -= quantity;
            break;
        }
        else
        {
            res += it->data.quantity * it->data.price;
            quantity -= it->data.quantity;
            it->data.quantity = 0;
        }
    }
    return res;
}

int Storage::getAmountOf(int id, int storeNumber)
{
    int result = 0;

    for (auto *it = list.begin(); it != nullptr; it = list.next(it))
    {
        if (it->data.id == id && (storeNumber == -1 || it->data.storeNumber == storeNumber))
        {
            result += it->data.quantity;
        }
    }

    return result;
}