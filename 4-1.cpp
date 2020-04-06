#include <iostream>
#include <string>
#include <fstream>
#include <map>

using namespace std;

bool isLetter(char c, string& delimeters)
{
    for (int i = 0; i < delimeters.length(); i++)
        if (c == delimeters[i])
            return false;

    return true;
}

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

    map<string, int> counter;

    string word;
    string delimeters = "` .,'\":;!?\t()-1234567890";
    char c;
    int length = 0;

    int k;
    cout << "Enter k: "; cin >> k;

    while (fin.get(c))
    {
        if (isLetter(c, delimeters))
        {
            word += c;
            length++;
        }
        else if (length > 0)
        {
            counter[word] += 1;
            length = 0;
            word = "";
        }
    }
    if (length > 0)
    {
        counter[word] += 1;
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

            cout << "Word deleted: " << searchWord << endl;
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
        if (isLetter(c, delimeters))
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