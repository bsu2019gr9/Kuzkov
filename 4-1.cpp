#include <iostream>
#include <string>
#include <fstream>
#include <map>

using namespace std;

bool isLetter(char letter)
{
    if ('A' <= letter && letter <= 'Z' ||
        'a' <= letter && letter <= 'z')
        return true;
    return false;
}

string toLower(string str)
{
    for (int i = 0; i < str.length(); i++)
    {
        if ('A' <= str[i] && str[i] <= 'Z')
            str[i] = str[i] - ('Z' - 'z');
    }
    return str;
}

/*
 * Определить есть ли в тексте слово, которое встречается
 * ровно k раз, удалить все такие слова кроме последнего.
 */
int main()
{
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

    map<string, int> counter;

    string word;
    char c;
    int length = 0;

    int k;
    cout << "Enter k: "; cin >> k;

    while (fin.get(c))
    {
        if (isLetter(c))
        {
            word += c;
            length++;
        }
        else if (length > 0)
        {
            counter[toLower(word)] += 1;
            length = 0;
            word = "";
        }
    }
    if (length > 0)
    {
        counter[toLower(word)] += 1;
        length = 0;
        word = "";
    }
    cout << endl;

    int count = 0;
    string searchWord;

    for (auto it = counter.begin(); it != counter.end(); ++it)
    {
        if (it->second == k)
        {
            searchWord = it->first;
            count = it->second;
            break;
        }
    }

    if (!count)
    {
        exit(0);
    }

    fin.clear();
    fin.seekg(0, ios::beg);

    while (fin.get(c))
    {
        if (isLetter(c))
        {
            word += c;
            length++;
        }
        else if (length > 0)
        {
            if (word != searchWord || count == 1)
            {
                fout << word;
            }
            else
            {
                count -= 1;
            }

            length = 0;
            word = "";
            fout << c;
        }
        else
        {
            fout << c;
        }
    }
    if (length > 0)
    {
        if (word != searchWord || count == 1)
        {
            fout << word;
        }
    }

    if (!fin.eof())
        cout << "Error reading" << endl;

    fin.close();
    fout.close();

    return 0;
}