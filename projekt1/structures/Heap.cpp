#include <windows.h>
#include "../headers/Heap.h"
#include <string>
#include <iostream>
#include <random>
#include <fstream>
#include <iomanip>
#include <cmath>
#include<algorithm>

Heap::Heap() {
    size = 0;
    heap = new int[size];
}

Heap::~Heap() {
    delete[] heap;
}

int Heap::loadFromFile(string fileName) {
    ifstream file("..\\loadFiles\\" + fileName);
    int val;
    int siz;
    if (file.is_open()) {
        file >> siz;
        clearStruct();
        size = 0;
        heap = new int[size];
        if (file.fail())
            cout << "File error - READ SIZE" << endl;
        else
            for (int i = 0; i < siz; i++) {
                file >> val;
                if (file.fail()) {
                    cout << "File error - READ DATA" << endl;
                    break;
                } else
                    addValue(val);
            }
        file.close();
    } else
        cout << "File error - OPEN" << endl;
    return 0;
}

bool Heap::isValueInStruct(int val) {
    for (int i = 0; i < size; ++i) {
        if (heap[i] == val) return true;
    }
    return false;
}

void Heap::addValue(int value) {
    int *tmpheap;
    tmpheap = new int[++size];
    for (int i = 0, j = 0; i < size; i++) {
        tmpheap[i] = heap[j];
        j++;
    }

    int i = size-1;
    int j = (i-1)/2;
    while (i>0 && heap[j]<value)
    {
        tmpheap[i]=tmpheap[j];
        i = j;
        j = (i-1)/2;
    }
    tmpheap[i] = value;
    delete[] heap;
    heap = tmpheap;
    tmpheap = nullptr;
}

void Heap::deleteFromStruct() {
    int *tmpheap;
    tmpheap = new int[--size];
    int value = heap[size];
    tmpheap[0] = value;
    for (int i = 1, j = 1; j < size; i++) {
        tmpheap[i] = heap[j];
        j++;
    }
    int i = 0;
    int j = 1;
    while (j < size){
        if (j + 1 < size && tmpheap[j+1]>tmpheap[j]) j++;
        if (value >= tmpheap[j]) break;
        tmpheap[i] = tmpheap[j];
        i = j;
        j = 2*j+1;
    }
    tmpheap[i]=value;
    heap = tmpheap;
    tmpheap = nullptr;
}

void Heap::display() {
    int height = floor(log2(size))+1; // wysokosc kopca
    int index = 0;

    for (int i = 0; i < height; i++) {
        int numNodes = pow(2, i); // ilosc wezlow na tym poziomie
        for (int j = 0; j < numNodes && index < size; j++) {
            // wypisywanie wezlow
            cout << heap[index] << " ";
            index++;
        }
        cout << endl;
    }
}

void Heap::generateStruct(int siz) {
    clearStruct();
    size = siz;
    heap = new int[size];
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dist(1, 99999999);;
    for (int i = 0; i < siz; ++i) {
        heap[i] = dist(gen);
    }
    sort(heap,heap+size, greater<int>());
}

void Heap::clearStruct() {
    delete[] heap;
}

void Heap::test(int repeat, int num, int *values) {
    long long int frequency, start, elapsed;
    double sum, time;
    ofstream resultFile;
    resultFile.open("..\\resultsFiles\\resultsHeap");

    QueryPerformanceFrequency((LARGE_INTEGER *) &frequency);

    // Usuwanie elementu
    resultFile << "---- Usuwanie korzenia z kopca ---" << endl;
    resultFile << "Rozmiar kopca\\Czas[us];";
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
            deleteFromStruct();
            elapsed = read_QPC() - start;

            time = (1000000.0 * elapsed) / frequency;
//            resultFile << fixed << setprecision(1) << time << ";";
            sum += time;
        }
        resultFile << fixed << setprecision(1) << sum/repeat << ";";
    }
    resultFile << endl << endl;

    // Dodawanie elementu do kopca
    resultFile << "---- Dodawanie elementu do kopca ---" << endl;
    resultFile << "Rozmiar kopca\\Czas[us];";
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
            addValue(0);
            elapsed = read_QPC() - start;

            time = (1000000.0 * elapsed) / frequency;
//            resultFile << fixed << setprecision(1) << time << ";";
            sum += time;
        }
        resultFile << fixed << setprecision(1) << sum/repeat << ";";
    }
    resultFile << endl << endl;

    // Wyszukiwanie elementu
    resultFile << "---- Wyszukiwanie losowej wartosci w kopcu ---" << endl;
    resultFile << "Rozmiar kopca\\Czas[us];";
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

            time = (1000000.0 * elapsed) / frequency;
//            resultFile << fixed << setprecision(1) << time << ";";
            sum += time;
        }
        resultFile << fixed << setprecision(1) << sum/repeat << ";";
    }
    resultFile << endl << endl;

    resultFile.close();
    cout << "Zapis do pliku zakonczony" << endl;
}

void Heap::addValue(int index, int value) {}

void Heap::deleteFromStruct(int index) {}
