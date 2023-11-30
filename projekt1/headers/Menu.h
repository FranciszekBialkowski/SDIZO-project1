#ifndef MENU_H

#define MENU_H

#include "Table.h"
#include "List.h"
#include "Heap.h"
#include "BST.h"
#include "RBT.h"
#include <iostream>

using namespace std;

class Menu {
    char option{};
    Table myTab;
    List myList;
    Heap myHeap;
    BST myBST;
    RBT myRBT;

    const int repeat = 2000;
    static const int num = 7;
    int values[num] = {10000, 50000, 100000,200000, 300000,400000,500000};

public:

    Menu(Table *myTab, List *myList, Heap *myHeap, BST *myBST, RBT *myRBT);   //konstruktor - wywoływany
                                                                                    //automatycznie przy tworzeniu obieku
    ~Menu();            //destrukor - wywływany automatycznie przy usuwaniu obiektu

    /// Ogólne menu struktury
    static void structMenu(const string& info);

    /// Menu główne
    void menuMain();

    /// Menu tablicy dynamicznej
    void menuTable();

    /// Menu listy dwukierunkowej
    void menuList();

    /// Menu kopca binarnego
    void menuHeap();

    /// Menu drzewa BST
    void menuBST();

    /// Menu drzewa czerwono-czarnego
    void menuRBT();
};

#endif