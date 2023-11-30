#ifndef LIST_H

#define LIST_H

#include "Table.h"
#include "Structure.h"

using namespace std;

struct listElement
{
    listElement * next, * prev;
    int key;
};

class List : public Structure
{
private:
    listElement * front, * back;
public:
    List();     //konstruktor - wywoływany automatycznie przy tworzeniu obieku
    ~List();    //destrukor - wywływany automatycznie przy usuwaniu obiektu

    int loadFromFile(string fileName) override;

    bool isValueInStruct(int val) override;

    void addValue(int index, int value) override;

    void deleteFromStruct(int index) override;

    void display() override;

    void generateStruct(int siz) override;

    void clearStruct() override;

    void test(int repeat, int num, int *values) override;

    listElement *findIndex(int index);
};



#endif
