#include <iostream>

using namespace std;

void clearscr()
{
#ifdef WINDOWS
    system("cls");
#else
    system("clear");
#endif
}

void pausescr()
{
    cin.ignore(256, '\n');
    string dummy;
    cout << "\n\nEnter to continue...";
    getline(cin, dummy);
}

struct Item
{
    string code;
    string name;
    int amount;
};

void printItem(Item item, int itemNumber)
{
    cout << itemNumber << ".\tCode\t: " << item.code << endl;
    cout << "\tNama\t: " << item.name << endl;
    cout << "\tJumlah\t: " << item.amount << endl;
    cout << endl;
}

void printItems(Item *items, int &size)
{
    if (size == 0)
    {
        cout << "\nTidak ada barang di inventory." << endl;
    }

    for (int i = 0; i < size; i++)
    {
        printItem(items[i], i + 1);
    }
}

Item *appendToItems(Item *items, Item newItem, int &size)
{
    Item *newItems = new Item[size + 1];

    for (int i = 0; i < size; i++)
    {
        newItems[i] = items[i];
    }

    newItems[size] = newItem;

    delete[] items;

    size++;

    return newItems;
}

Item *deleteFromItems(int index, Item *items, int &size)
{
    Item *newItems = new Item[size - 1];

    int count = 0;
    for (int i = 0; i < size; i++)
    {
        if (i == index)
        {
            continue;
        }
        newItems[count] = items[i];
        count++;
    }

    delete[] items;

    size--;

    return newItems;
}

Item *deleteItem(Item *items, int &size)
{
    if (size == 0) {
        cout << "\nTidak ada barang di inventory." << endl;
        return items;
    }
    Item *newItems = new Item[size - 1];
    int itemNumber = -1;
    int oldSize = size;

    printItems(items, size);

    cout << "Masukan nomor barang yang ingin dihapus : ";
    cin >> itemNumber;

    if (itemNumber > size || itemNumber < 0) {
        cout << "\nTidak ada barang di inventory." << endl;
        return items;
    }

    printItem(items[itemNumber - 1], itemNumber);

    newItems = deleteFromItems(itemNumber - 1, items, size);

    if (oldSize > size) {
        
        cout << "Barang nomor " << itemNumber << " berhasil dihapus!";
    } else {
        cout << "Barang nomor " << itemNumber << " gagal dihapus!";
    }


    return newItems;
}

Item *addItem(Item *items, int &size)
{
    Item newItem;
    newItem.code = "B" + to_string(size + 1);
    cout << "Masukan nama barang : ";
    getline(cin, newItem.name);
    cout << "Masukan jumlah barang : ";
    cin >> newItem.amount;
    cout << endl;

    printItem(newItem, 1);

    return appendToItems(items, newItem, size);
}

Item *pilihMenu(Item *items, int &size)
{
    int pilihanMenu;

    clearscr();
    cout << "\n\n=============================\n";
    cout << "Muhamad Fadil – 2109994 – 2B\n\n";
    cout << "Pilih Menu (1-2)\n";
    cout << "1. Daftar barang\n2. Tambah barang\n3. Hapus barang\n4. Keluar\n";
    cout << "Pilihan: ";
    cin >> pilihanMenu;
    cin.ignore(256, '\n');
    cout << "\n=============================\n\n";

    clearscr();

    switch (pilihanMenu)
    {
    case 1:
        printItems(items, size);
        break;
    case 2:
        items = addItem(items, size);
        break;
    case 3:
        items = deleteItem(items, size);
        break;
    default:
        return items;
    }

    pausescr();

    pilihMenu(items, size);
}

int main()
{
    Item *items = new Item[5];
    int itemsSize = 0;

    items = pilihMenu(items, itemsSize);
}
