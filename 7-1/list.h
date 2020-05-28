#pragma once

#include <iostream>
using namespace std;

template <typename T>
struct ListItem
{
    T data;
    ListItem *next;
    ListItem *prev;
};

template <typename T>
class List
{
private:
    ListItem<T> *beg;
    ListItem<T> *end;
    int length;

public:
    List();
    List(T*, T*);

    ~List();

    bool push(const T&);
    T pop();

    // bool unshift(const T&);
    // T shift();

    void deleteByIndex(const int);
    void unbindAndDelete(ListItem<T>*);

    ListItem<T>* begin();
    ListItem<T>* next(ListItem<T>*);

    int getLength();

    T& operator[] (const int);
};



// Constructors, destructors
template <typename T>
List<T>::List() : beg(nullptr), end(nullptr), length(0)
{}

template <typename T>
List<T>::List(T *beg, T *end) : beg(nullptr), end(nullptr), length(0)
{
    for (T *it = beg; it <= end; it++)
        this->push(*it);
}

template <typename T>
List<T>::~List()
{
    while (beg != nullptr)
    {
        ListItem<T> *temp = beg;
        beg = beg->next;
        delete temp;
    }
}



// Push, pop
template <typename T>
bool List<T>::push(const T &item)
{
    ListItem<T> *list_item = new ListItem<T>;

    list_item->data = item;
    list_item->next = nullptr;

    if (length == 0)
    {
        list_item->prev = nullptr;
        beg = end = list_item;
    }
    else
    {
        list_item->prev = end;
        end->next = list_item;
        end = list_item;
    }

    length++;

    return true;
}

template <typename T>
T List<T>::pop()
{
    if (length == 0)
        throw logic_error("Empty list");

    T data = beg->data;
    
    if (length-- == 1)
    {
        delete beg;
        beg = end = nullptr;
    }
    else
    {
        ListItem<T> *prev = end->prev;
        delete end;

        prev->next = nullptr;
        end = prev;
    }

    return data;
}



// Operators
template <typename T>
T& List<T>::operator[] (const int index)
{
    ListItem<T> *temp = beg;
    for (int i = 0; i < index; i++)
        temp = temp->next;

    return temp->data;
}



// Iterator
template <typename T>
ListItem<T>* List<T>::begin()
{
    return beg;
}

template <typename T>
ListItem<T>* List<T>::next(ListItem<T> *current)
{
    return current->next;
}


template <typename T>
int List<T>::getLength()
{
    return this->length;
}

template <typename T>
void List<T>::deleteByIndex(const int index)
{
    if (index < 0 || index >= length)
        throw logic_error("Index is out of range");

    ListItem<T> *item = beg;
    for (int i = 0; i < index; i++)
        this->next(item);

    this->unbindAndDelete(item);
}

template <typename T>
void List<T>::unbindAndDelete(ListItem<T> *item)
{
    if (item->prev != nullptr)
        item->prev->next = item->next;
    else
        beg = item->next;

    if (item->next != nullptr)
        item->next->prev = item->prev;
    else
        end = item->prev;

    length--;

    delete item;
}
