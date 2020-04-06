#include <iostream>
#include <string>
#include <cstring>

using namespace std;

bool isLetter(char c, string& delimeters)
{
    for (int i = 0; i < delimeters.length(); i++)
        if (c == delimeters[i])
            return false;

    return true;
}

/*
 * В строке найти и вывести на экран все
 * слова максимальной длины, и удалить
 * за ними следующее слово.
 */
int main()
{
    setlocale(LC_ALL, "Russian");
    string str, word;
    string delimeters = "` .,'\":;!?\t()-1234567890";

    getline(cin, str);
    str =  str + ' ';

    int length = 0, max = 0;

    for (int i = 0; i < str.length(); i++)
    {
        if (isLetter(str[i], delimeters))
        {
            word += str[i];
            length++;
        }
        else if (length > 0)
        {
            cout << word << " (" << length << ") ";

            if (max < length)
                max = length;

            word = "";
            length = 0;
        }
    }
    cout << endl;

    bool wordAfterMax = false;
    string newStr = "";

    for (int i = 0; i < str.length(); i++)
    {
        if (isLetter(str[i], delimeters))
        {
            word += str[i];
            length++;
        }
        else if (length > 0)
        {
            if (length == max && wordAfterMax)
            {
                cout << "MAX: " << word << endl;
            }
            else if (length == max)
            {
                cout << "MAX: " << word << endl;
                newStr += word;
                wordAfterMax = true;
            }
            else if (wordAfterMax)
            {
                wordAfterMax = false;
            }
            else
            {
                newStr += word;
            }

            word = "";
            length = 0;
            newStr += str[i];
        }
        else
        {
            newStr += str[i];
        }
    }
    cout << newStr << endl;

    return 0;
}