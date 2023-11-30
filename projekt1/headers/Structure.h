#ifndef STRUCTURE_H

#define STRUCTURE_H

#include <windows.h>
#include <iostream>

using namespace std;

class Structure
{
public:
    int size;   //ilość elementów w strukturze

    /// Ładowanie danych z pliku tekstowego
    virtual int loadFromFile(string fileName) = 0;

    /// Sprawdzenie czy wartość jest w strukturze
    virtual bool isValueInStruct(int val) = 0;

    /// Dodanie wartości do struktury na podany indeks
    virtual void addValue(int index, int value)= 0;

    /// Usunięcie elementu struktury o podanym indeksie
    virtual void deleteFromStruct(int index) = 0;

    /// Wyświetlenie aktualnej zawartości struktury
    virtual void display() = 0;

    /// Wygenerowanie struktury o podanym rozmiarze z losowymi wartościami
    virtual void generateStruct(int siz) = 0;

    /// Wyczyszczenie struktury
    virtual void clearStruct() = 0;

    /// Testowanie czasów wykonywania różnych operacji na strukturze i zapisanie wyników do pliku tekstowego
    virtual void test(int repeat, int num, int* values) = 0;

    /// Sprawdzenie aktualnego czasu
    virtual long long int read_QPC()
    {
        LARGE_INTEGER count;
        QueryPerformanceCounter(&count);
        return ((long long int) count.QuadPart);
    }
};

#endif
