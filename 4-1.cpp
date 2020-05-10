#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

class String
{
private:
    char* str;
    int len;

public:
    String();
    String(const char);
    String(const char*);

    ~String();

    int length();

    const char operator[](const int);
    String& operator=(const String&);
    friend ostream& operator<<(ostream&, const String&);
    friend bool operator==(const String&, const String&);
    friend bool operator!=(const String&, const String&);
    friend const String operator+(const String&, const String&);
    friend String& operator+=(String&, const String&);
};

class Map
{
private:
    struct Item
    {
        String first;
        int second;
    };

    Item* items;
    Item* last_item;

public:
    Map();
    ~Map();

    Item* begin();
    Item* end();

    int& operator[] (const String&);
};

bool isLetter(char c);
String getNextWord(ifstream&);

String getRepeatingWord(ifstream&, int);
void deleteWordExceptLast(ifstream&, ofstream&, const String&, int);

const int MAX_SIZE = 100000;
String DELIMETERS = "` .,'\":;!?\t()-1234567890\n";

/*
 * Определить есть ли в тексте слово, которое встречается
 * ровно k раз, удалить все такие слова кроме последнего.
 */
int main()
{
    setlocale(LC_ALL, "Russian");

    ifstream fin("data.txt");
    ofstream fout("res.txt");
    if (!fin)
    {
        cout << "No File data.txt" << endl;
        exit(1);
    }
    if (!fout)
    {
        cout << "No File res.txt. Can't create" << endl;
        exit(1);
    }

    int k;
    cout << "Enter k: "; cin >> k;

    String searchWord = getRepeatingWord(fin, k);

    if (searchWord == "")
    {
        cout << "No word found" << endl;
        exit(0);
    }
    
    cout << "Word deleted: " << searchWord << endl;

    fin.clear();
    fin.seekg(0, ios::beg);

    deleteWordExceptLast(fin, fout, searchWord, k);

    if (!fin.eof())
        cout << "Error reading" << endl;

    fin.close();
    fout.close();

    return 0;
}

/* Functions */
bool isLetter(char c)
{
    for (int i = 0; i < DELIMETERS.length(); i++)
        if (c == DELIMETERS[i])
            return false;

    return true;
}
 
String getNextWord(ifstream &fin)
{
    String word = "";

    char c;
    fin.get(c);

    while(!fin.eof() && !isLetter(c))
        fin.get(c);

    while(!fin.eof() && isLetter(c))
    {
        word += c;
        fin.get(c);
    }

    return word;
}

String getRepeatingWord(ifstream &fin, int countOfRepeatings)
{
    Map counter;

    String word;
    while(!fin.eof())
    {
        word = getNextWord(fin);
        counter[word] += 1;
    }

    word = "";
    for (auto it = counter.begin(); it != counter.end(); ++it)
    {
        if (it->second == countOfRepeatings)
        {
            word = it->first;
            break;
        }
    }

    return word;
}

void deleteWordExceptLast(ifstream& fin, ofstream& fout, const String& searchWord, int countOfWords)
{
    String word = "";

    char c;
    fin.get(c);

    while(!fin.eof())
    {
        while(!fin.eof() && !isLetter(c))
        {
            fout << c;
            fin.get(c);
        }

        while(!fin.eof() && isLetter(c))
        {
            word += c;
            fin.get(c);
        }

        if (word != searchWord || (countOfWords--) == 1)
            fout << word;

        word = "";
    }
}


/* Map */
Map::Map()
{
    this->items = new Item[MAX_SIZE];
    this->last_item = items;
}

Map::~Map()
{
    delete[] this->items;
}

Map::Item* Map::begin()
{
    return this->items;
}

Map::Item* Map::end()
{
    return this->last_item;
}

int& Map::operator[] (const String& key)
{
    for (Item* it = this->begin(); it < this->end(); it++)
    {
        if (it->first == key)
        {
            return it->second;
        }
    }

    this->last_item->first = key;
    return (this->last_item++)->second;
}


/* String */
String::String() : len(0)
{
    this->str = new char[1] { '\0' };
}

String::String(const char c) : len(1)
{
    this->str = new char[2] { c, '\0' };
}

String::String(const char* str)
{
    this->len = strlen(str);
    this->str = new char[this->len + 1];

    memcpy(this->str, str, this->len);
    this->str[this->len] = '\0';
}

String::~String()
{
    delete[] this->str;
}

int String::length()
{
    return this->len;
}

String& String::operator=(const String &rhs)
{
    delete[] this->str;

    this->str = new char[rhs.len + 1];
    memcpy(this->str, rhs.str, rhs.len + 1);
    this->len = rhs.len;
    
    return *this;
}

ostream& operator<<(ostream& os, const String& str)
{
    os << str.str;
    return os;
}

bool operator==(const String &lhs, const String &rhs)
{
    return !strcmp(lhs.str, rhs.str);
}

bool operator!=(const String &lhs, const String &rhs)
{
    return !(lhs == rhs);
}

const String operator+(const String& lhs, const String& rhs)
{
    char* str = new char[lhs.len + rhs.len + 1];
    memcpy(str, lhs.str, lhs.len);
    memcpy(str + lhs.len, rhs.str, rhs.len + 1);
    return String(str);
}

String& operator+=(String& lhs, const String& rhs)
{
    return lhs = lhs + rhs;
}

const char String::operator[](const int i)
{
    return this->str[i];
}