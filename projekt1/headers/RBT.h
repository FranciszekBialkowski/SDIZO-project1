#include <windows.h>
#include "Structure.h"
#include <string>
#include <iostream>
#include <random>
#include <fstream>
#include <iomanip>
#include <cmath>

#ifndef RBTREE_H
#define RBTREE_H


struct RBTNode
{
    RBTNode * up, * left, * right;
    int key;
    bool isRed;
};

class RBT : public Structure{
private:
    RBTNode * root;
public:
    RBT();     //konstruktor - wywoływany automatycznie przy tworzeniu obieku
    ~RBT();    //destrukor - wywływany automatycznie przy usuwaniu obiektu

    int loadFromFile(string fileName) override;

    bool isValueInStruct(int val) override;

    void addValue(int index, int value) override;

    /// Usuniecie podanej wartosci z drzewa
    void deleteFromStruct(int val) override;

    /// Dodanie elementu to struktury
    void addValue(int value);

    /// Znalezienie wezla minimalnego w podrzewie zaczynajacym sie od podanego wezla
    RBTNode* findMin(RBTNode *p);

    /// Znalezenie nastepnika podanego wezla
    RBTNode* findSuccessor(RBTNode *p);

    /// Znalezienie wezla z podana wartoscia
    RBTNode* findValue(int val);

    void display() override;

    /// Ladne wyswietlenie drzewa czerwono-czarnego
    void printTree(const string &prefix, const RBTNode *node, bool isLeft);

    void generateStruct(int siz) override;

    void clearStruct() override;

    /// Usuwanie wezlow drzewa w kolejnosci postorder
    void postorderDelete(RBTNode *p);

    /// Rotacja w lewo wzgledem podanego wezla
    void rotateLeft(RBTNode *a);

    /// Rotacja w prawo wzgledem podanego wezla
    void rotateRight(RBTNode *a);

    void test(int repeat, int num, int *values) override;

};
#endif