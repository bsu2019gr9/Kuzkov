#include <iostream>
#include "storage.h"

void printMenu()
{
    cout << "1 - Add, 2 - Update, 3 - Delete, 4 - Buy Amount, 0 - Quit" << endl;
}

int main()
{
    Storage store("storage.dat");

    while (1)
    {
        store.printAll();

        printMenu();
        int choice; cin >> choice;
        int id, amount;

        switch(choice)
        {
            case 1:
                store.inputMaterial();
            break;
            case 2:
            {
                cin >> id;
                ConstructMat& mat = store.getMaterial(id);
                cin >> mat;
                break;
            }
            case 3:
                cin >> id;
                store.deleteMaterial(id);
            break;
            case 4:
                cin >> id >> amount;
                store.buyAmountOf(id, amount);
            break;
            case 0:
                return 0;
            break;
        }
    }

    return 0;
}
