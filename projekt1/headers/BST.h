#ifndef BST_H
#define BST_H

#include "Structure.h"

struct BSTNode
{
    BSTNode * up, * left, * right;
    int key;
};

class BST : public Structure {
private:
    BSTNode * root;
public:
    BST();     //konstruktor - wywoływany automatycznie przy tworzeniu obieku
    ~BST();    //destrukor - wywływany automatycznie przy usuwaniu obiektu

    int loadFromFile(string fileName) override;

    bool isValueInStruct(int val) override;

    void addValue(int index, int value) override;

    /// Usuniecie podanej wartosci z drzewa
    void deleteFromStruct(int val) override;

    /// Dodanie elementu to struktury
    void addValue(int value);

    /// Znalezienie wezla minimalnego w podrzewie zaczynajacym sie od podanego wezla
    BSTNode* findMin(BSTNode *p);

    /// Znalezenie nastepnika podanego wezla
    BSTNode* findSuccessor(BSTNode *p);

    /// Znalezienie wezla z podana wartoscia
    BSTNode* findValue(int val);

    void display() override;

    /// Ladne wyswietlenie drzewa BST
    void printTree(const string &prefix, const BSTNode *node, bool isLeft);

    void generateStruct(int siz) override;

    void clearStruct() override;

    /// Usuwanie wezlow drzewa w kolejnosci postorder
    void postorderDelete(BSTNode *p);

    /// Rotacja w lewo wzgledem podanego wezla
    void rotateLeft(BSTNode *a);

    /// Rotacja w prawo wzgledem podanego wezla
    void rotateRight(BSTNode *a);

    /// Rownowazenie drzewa metoda DSW
    void DSW();

    void test(int repeat, int num, int *values) override;

};


#endif
