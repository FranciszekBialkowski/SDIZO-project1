#ifndef TABLE_H

#define TABLE_H

#include "Table.h"
#include "Structure.h"

using namespace std;

class Table : public Structure
{
	int *tab;   // wskaźnik na pierwszy element tablicy
public:

	Table();    //konstruktor - wywoływany automatycznie przy tworzeniu obieku
	~Table();   //destrukor - wywływany automatycznie przy usuwaniu obiektu

	int loadFromFile(string fileName) override;

	bool isValueInStruct(int val) override;

	void addValue(int index, int value) override;

	void deleteFromStruct(int index) override;

	void display() override;

	void generateStruct(int siz) override;

    void clearStruct() override;

    void test(int repeat, int num, int* values) override;

};
#endif