#ifndef HEAP_H
#define HEAP_H


#include "Structure.h"

class Heap : public Structure
{
    int *heap;   // wkaznik na pierwszy element tablicy
public:
    Heap();     //konstruktor - wywoływany automatycznie przy tworzeniu obieku
    ~Heap();    //destrukor - wywływany automatycznie przy usuwaniu obiektu

    int loadFromFile(string fileName) override;

    bool isValueInStruct(int val) override;

    void addValue(int index, int value) override;

    void deleteFromStruct(int index) override;

    void addValue(int value);

    void deleteFromStruct();

    void display() override;

    void generateStruct(int siz) override;

    void clearStruct() override;

    void test(int repeat, int num, int *values) override;
};


#endif
