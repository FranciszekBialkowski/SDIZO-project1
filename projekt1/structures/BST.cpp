#include <windows.h>
#include "../headers/BST.h"
#include <string>
#include <iostream>
#include <random>
#include <fstream>
#include <iomanip>
#include <cmath>

BST::BST()
{
    root = nullptr;
    size = 0;
}

BST::~BST()
{
    clearStruct();
}

int BST::loadFromFile(string fileName) {
    clearStruct();
    ifstream file("..\\loadFiles\\" + fileName);
    int val, siz;
    if (file.is_open()) {
        file >> siz;
        if (file.fail())
            cout << "File error - READ SIZE" << endl;
        else
            for (int i = 0; i < siz; i++) {
                file >> val;
                if (file.fail()) {
                    cout << "File error - READ DATA" << endl;
                    break;
                } else
                {
                    addValue(val);
                }
            }
        file.close();
    } else
        cout << "File error - OPEN" << endl;
    return 0;
}

bool BST::isValueInStruct(int val) {
    BSTNode *p = root;
    while (p)
    {
        if (p->key == val) return true;
        if (val < p->key) p = p->left;
        else p = p->right;
    }
    return false;
}

void BST::addValue(int value) {
    auto *p = new BSTNode;
    p->key = value;
    BSTNode *p1 = root;
    if (!root)
    {
        root = p;
        root->up= nullptr;
    } else
    {
        while (p1)
        {
            if (value<p1->key) {
                if(p1->left) p1=p1->left;
                else break;
            }
            else {
                if (p1->right) p1=p1->right;
                else break;
            }
        }
        if (value < p1->key) p1->left= p;
        else p1->right = p;
        p->up = p1;
    }
    p->left = p->right = nullptr;
    size++;
}

void BST::deleteFromStruct(int val) {
    BSTNode *p = findValue(val);
    BSTNode *x, *y;
    if (p->left== nullptr || p->right== nullptr) y = p;
    else y = findSuccessor(p);
    if (y->left!= nullptr) x=y->left;
    else x = y->right;
    if (x!= nullptr) x->up = y->up;
    if (y->up == nullptr) root = x;
    else
    {
        if (y==y->up->left) y->up->left = x;
        else y->up->right = x;
    }
    if (y!=p) p->key = y->key;
    delete y;
}

BSTNode* BST::findMin(BSTNode *p) {
    while (p->left!= nullptr) p=p->left;
    return p;
}

BSTNode* BST::findSuccessor(BSTNode *p) {
    if (p->right != nullptr) return findMin(p->right);
    BSTNode *p1 = p->up;
    while (p1!= nullptr && p1->left != p)
    {
        p = p1;
        p1 = p1->up;
    }
    return p1;
}

BSTNode* BST::findValue(int val) {
    BSTNode *p = root;
    while (p)
    {
        if (p->key == val) return p;
        if (val < p->key) p = p->left;
        else p = p->right;
    }
    return nullptr;
}

void BST::display() {
    if (size>0)
    {
        printTree("",root,false);
    }
}

void BST::printTree(const string &prefix, const BSTNode *p, bool isLeft)
{
    if(p != nullptr) {
        cout << prefix;

        cout << (isLeft ? "|--" : "\\--");

        cout << p->key << endl;

        printTree( prefix + (isLeft ? "|   " : "    "), p->left, true);
        printTree( prefix + (isLeft ? "|   " : "    "), p->right, false);
    }
}

void BST::generateStruct(int siz) {
    clearStruct();
    size = 0;
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dist(1, 99999999);;
    for (int i = 0; i < siz; ++i) {
        addValue(dist(gen));
    }
}

void BST::clearStruct() {
    if (size>0) postorderDelete(root);
    root= nullptr;
}

void BST::postorderDelete(BSTNode *p) {
    if (p == nullptr) return;
    postorderDelete(p->left);
    postorderDelete(p->right);
    delete p;
    size--;
}

void BST::rotateLeft(BSTNode *a) {
    BSTNode *b = a->right;
    if (a==root)
    {
        b->up= nullptr;
        root = b;
    } else
    {
        if (a==a->up->right) a->up->right = b;
        else a->up->left = b;
        b->up = a->up;
    }
    if (b->left)
    {
        a->right = b->left;
    } else a->right = nullptr;
    a->up=b;
    b->left=a;
}

void BST::rotateRight(BSTNode *a) {
    BSTNode *b = a->left;
    if (a==root)
    {
        b->up= nullptr;
        root = b;
    } else
    {
        if (a==a->up->right) a->up->right = b;
        else a->up->left = b;
        b->up = a->up;
    }
    if (b->right)
    {
        a->left = b->right;
    } else a->left = nullptr;
    a->up=b;
    b->right=a;
}

void BST::DSW() {
    // prostowanie
    BSTNode *p = root;
    while (p)
    {
        if (p->left)
        {
            rotateRight(p);
            p = p->up;
        } else p=p->right;
    }

    // rownowazenie
    p = root;
    int m = pow(2, floor(log2(size+1))) - 1;
    for (int i = 0; i < size-m; ++i) {
        rotateLeft(p);
        p = p->up->right;
    }
    while (m>1)
    {
        p = root;
        m = m/2;
        for (int i = 0; i < m; ++i) {
            rotateLeft(p);
            p = p->up->right;
        }
    }
}


void BST::test(int repeat, int num, int *values) {
    long long int frequency, start, elapsed;
    double sum, time;
    ofstream resultFile;
    resultFile.open("..\\resultsFiles\\resultsBST");

    QueryPerformanceFrequency((LARGE_INTEGER *) &frequency);

    // Usuwanie elementu
    resultFile << "---- Usuwanie korzenia z drzewa BST ---" << endl;
    resultFile << "Rozmiar drzewa\\Czas[ns];";
//    for (int j = 0;  j < repeat; ++j) {
//        resultFile << "t" << j+1 << ";";
//    }
    resultFile << "t_avg";
    for (int i = 0; i < num; ++i) {
        sum = 0;
        resultFile << endl << values[i] << ";";
        for (int j = 0; j < repeat; ++j) {
            generateStruct(values[i]);

            start = read_QPC();
            deleteFromStruct(root->key);
            elapsed = read_QPC() - start;

            time = (1000000000.0 * elapsed) / frequency;
//            resultFile << fixed << setprecision(0) << time << ";";
            sum += time;
        }
        resultFile << fixed << setprecision(0) << sum/repeat << ";";
    }
    resultFile << endl << endl;

    // Dodawanie elementu
    resultFile << "---- Dodawanie losowego elementu do drzewa BST ---" << endl;
    resultFile << "Rozmiar drzewa\\Czas[ns];";
//    for (int j = 0; j < repeat; ++j) {
//        resultFile << "t" << j+1 << ";";
//    }
    resultFile << "t_avg";
    for (int i = 0; i < num; ++i) {
        sum = 0;
        resultFile << endl << values[i] << ";";
        for (int j = 0; j < repeat; ++j) {
            generateStruct(values[i]);
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> dist(1, 99999999);

            start = read_QPC();
            addValue(dist(gen));
            elapsed = read_QPC() - start;

            time = (1000000000.0 * elapsed) / frequency;
//            resultFile << fixed << setprecision(0) << time << ";";
            sum += time;
        }
        resultFile << fixed << setprecision(0) << sum/repeat << ";";
    }
    resultFile << endl << endl;

    // Wyszukiwanie elementu
    resultFile << "---- Wyszukiwanie losowej wartosci w drzewie BST ---" << endl;
    resultFile << "Rozmiar drzewa\\Czas[ns];";
//    for (int j = 0; j < repeat; ++j) {
//        resultFile << "t" << j+1 << ";";
//    }
    resultFile << "t_avg";
    for (int i = 0; i < num; ++i) {
        sum = 0;
        resultFile << endl << values[i] << ";";
        for (int j = 0; j < repeat; ++j) {
            generateStruct(values[i]);
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> dist(1, 99999999);

            start = read_QPC();
            isValueInStruct(dist(gen));
            elapsed = read_QPC() - start;

            time = (1000000000.0 * elapsed) / frequency;
//            resultFile << fixed << setprecision(0) << time << ";";
            sum += time;
        }
        resultFile << fixed << setprecision(0) << sum/repeat << ";";
    }
    resultFile << endl << endl;

    // Rotacja
    resultFile << "---- Rotacja korzenia w drzewie BST ---" << endl;
    resultFile << "Rozmiar drzewa\\Czas[ns];";
//    for (int j = 0; j < repeat; ++j) {
//        resultFile << "t" << j+1 << ";";
//    }
    resultFile << "t_avg";
    for (int i = 0; i < num; ++i) {
        sum = 0;
        resultFile << endl << values[i] << ";";
        for (int j = 0; j < repeat; ++j) {
            generateStruct(values[i]);

            start = read_QPC();
            rotateLeft(root);
            elapsed = read_QPC() - start;

            time = (1000000000.0 * elapsed) / frequency;
//            resultFile << fixed << setprecision(0) << time << ";";
            sum += time;
        }
        resultFile << fixed << setprecision(0) << sum/repeat << ";";
    }
    resultFile << endl << endl;

    // Rownowazenie drzewa metoda DSW
    resultFile << "---- Rownowazenie drzewa BST metoda DSW ---" << endl;
    resultFile << "Rozmiar drzewa\\Czas[ms];";
//    for (int j = 0; j < repeat; ++j) {
//        resultFile << "t" << j+1 << ";";
//    }
    resultFile << "t_avg";
    for (int i = 0; i < num; ++i) {
        sum = 0;
        resultFile << endl << values[i] << ";";
        for (int j = 0; j < repeat; ++j) {
            generateStruct(values[i]);

            start = read_QPC();
            DSW();
            elapsed = read_QPC() - start;

            time = (1000.0 * elapsed) / frequency;
//            resultFile << fixed << setprecision(1) << time << ";";
            sum += time;
        }
        resultFile << fixed << setprecision(1) << sum/repeat << ";";
    }
    resultFile << endl << endl;

    resultFile.close();
    cout << "Zapis do pliku zakonczony" << endl;


}

void BST::addValue(int index, int value) {}

