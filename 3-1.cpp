#include <iostream>
#include <string>

using namespace std;

bool isLetter(char letter)
{
    if (65 <= letter && letter <= 87 || // A-Z
        97 <= letter && letter <= 119)  // a-z
        return true;
    return false;
}

/*
 * В строке найти и вывести на экран все
 * слова максимальной длины, и удалить
 * за ними следующее слово.
 */
int main()
{
    string str, word;

    getline(cin, str);
    str =  str + ' ';

    int length = 0, max = 0;

    for (int i = 0; i < str.length(); i++)
    {
        if (isLetter(str[i]))
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
        if (isLetter(str[i]))
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