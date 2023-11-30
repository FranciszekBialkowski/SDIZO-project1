#include <windows.h>
#include "../headers/Table.h"
#include <string>
#include <iostream>
#include <random>
#include <fstream>
#include <iomanip>
\
using namespace std;

Table::Table() {
    size = 0;
    tab = new int[size];
}

Table::~Table() {
    delete[] tab;
}

int Table::loadFromFile(string fileName) {
    ifstream file("..\\loadFiles\\" + fileName);
    int val;
    if (file.is_open()) {
        file >> size;
        clearStruct();
        int *tmptab;
        tmptab = new int[size];
        if (file.fail())
            cout << "File error - READ SIZE" << endl;
        else
            for (int i = 0; i < size; i++) {
                file >> val;
                if (file.fail()) {
                    cout << "File error - READ DATA" << endl;
                    break;
                } else
                    tmptab[i] = val;
            }
        tab = tmptab;
        tmptab = nullptr;
        file.close();
    } else
        cout << "File error - OPEN" << endl;
    return 0;
}

bool Table::isValueInStruct(int val) {
    for (int i = 0; i < size; ++i) {
        if (tab[i] == val) return true;
    }
    return false;
}

void Table::addValue(int index, int value) {
    int *tmptab;
    tmptab = new int[++size];

    for (int i = 0, j = 0; i < size; i++) {
        if (i == index) {
            tmptab[i] = value;
            continue;
        }
        tmptab[i] = tab[j];
        j++;
    }
    delete[] tab;
    tab = tmptab;
    tmptab = nullptr;
}

void Table::deleteFromStruct(int index) {
    int *tmptab;
    tmptab = new int[--size];

    for (int i = 0, j = 0; i < size + 1; i++) {
        if (i == index) continue;
        tmptab[j] = tab[i];
        j++;
    }
    tab = tmptab;
    tmptab = nullptr;
}

void Table::display() {
    for (int i = 0; i < size; ++i) {
        cout << "|" << *(tab + i);
    }
    cout << "|";
}

void Table::generateStruct(int siz) {
    clearStruct();
    size = siz;
    tab = new int[size];
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dist(1, 99999999);;
    for (int i = 0; i < siz; ++i) {
        tab[i] = dist(gen);
    }
}

void Table::clearStruct() {
    delete[] tab;
}

void Table::test(int repeat, int num, int *values) {
    long long int frequency, start, elapsed;
    double sum, time;
    ofstream resultFile;
    resultFile.open("..\\resultsFiles\\resultsTable");

    QueryPerformanceFrequency((LARGE_INTEGER *) &frequency);

    // Usuwanie elementu
    resultFile << "---- Usuwanie pierwszego elemnetu z tablicy ---" << endl;
    resultFile << "Rozmiar tablicy\\Czas[us];";
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
            deleteFromStruct(0);
            elapsed = read_QPC() - start;

            time = (1000000.0 * elapsed) / frequency;
//            resultFile << fixed << setprecision(1) << time << ";";
            sum += time;
        }
        resultFile << fixed << setprecision(1) << sum/repeat << ";";
    }
    resultFile  << endl << endl;

    resultFile << "---- Usuwanie ostatniego elementu z tablicy ---" << endl;
    resultFile << "Rozmiar tablicy\\Czas[us];";
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
            deleteFromStruct(num - 1);
            elapsed = read_QPC() - start;

            time = (1000000.0 * elapsed) / frequency;
//            resultFile << fixed << setprecision(1) << time << ";";
            sum += time;
        }
        resultFile << fixed << setprecision(1) << sum/repeat << ";";
    }
    resultFile << endl << endl;

    resultFile << "---- Usuwanie losowego elementu z tablicy ---" << endl;
    resultFile << "Rozmiar tablicy\\Czas[us];";
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
            uniform_int_distribution<> dist(0, values[i]);

            start = read_QPC();
            deleteFromStruct(dist(gen));
            elapsed = read_QPC() - start;

            time = (1000000.0 * elapsed) / frequency;
//            resultFile << fixed << setprecision(1) << time << ";";
            sum += time;
        }
        resultFile << fixed << setprecision(1) << sum/repeat << ";";
    }
    resultFile << endl << endl;


    // Dodawanie elementu
    resultFile << "---- Dodawanie elementu na początek tablicy ---" << endl;
    resultFile << "Rozmiar tablicy\\Czas[us];";
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
            addValue(0,0);
            elapsed = read_QPC() - start;

            time = (1000000.0 * elapsed) / frequency;
//            resultFile << fixed << setprecision(1) << time << ";";
            sum += time;
        }
        resultFile << fixed << setprecision(1) << sum/repeat << ";";
    }
    resultFile << endl << endl;

    resultFile << "---- Dodawanie elementu na koniec tablicy ---" << endl;
    resultFile << "Rozmiar tablicy\\Czas[us];";
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
            addValue(num-1,0);
            elapsed = read_QPC() - start;

            time = (1000000.0 * elapsed) / frequency;
//            resultFile << fixed << setprecision(1) << time << ";";
            sum += time;
        }
        resultFile << fixed << setprecision(1) << sum/repeat << ";";
    }
    resultFile << endl << endl;

    resultFile << "---- Dodawanie elementu w losowe miejsce tablicy ---" << endl;
    resultFile << "Rozmiar tablicy\\Czas[us];";
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
            uniform_int_distribution<> dist(0, values[i]);

            start = read_QPC();
            addValue(dist(gen),0);
            elapsed = read_QPC() - start;

            time = (1000000.0 * elapsed) / frequency;
//            resultFile << fixed << setprecision(1) << time << ";";
            sum += time;
        }
        resultFile << fixed << setprecision(1) << sum/repeat << ";";
    }
    resultFile << endl << endl;

    // Wyszukiwanie elementu
    resultFile << "---- Wyszukiwanie losowej wartości w tablicy ---" << endl;
    resultFile << "Rozmiar tablicy\\Czas[us];";
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
