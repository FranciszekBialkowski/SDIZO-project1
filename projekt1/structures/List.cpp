#include <windows.h>
#include "../headers/List.h"
#include <string>
#include <iostream>
#include <random>
#include <fstream>
#include <iomanip>

List::List() {
    front = back = nullptr;
    size = 0;
}

List::~List() {
    auto *p = new listElement;
    while (front) {
        p = front->next;
        delete front;
        front = p;
    }
    delete p;
}

int List::loadFromFile(string fileName) {
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
                    addValue(size,val);
                }
            }
        file.close();
    } else
        cout << "File error - OPEN" << endl;
    return 0;
}

bool List::isValueInStruct(int val) {
    listElement *p = front;
    for (int i = 0; i < size; ++i) {
        if (p->key == val) return true;
        p = p->next;
    }
    return false;
}

void List::addValue(int index, int value) {
    auto *p = new listElement;
    p->key = value;
    // na poczatek listy
    if (index == 0) {
        p->next = front;
        p->prev = nullptr;
        if (front) front->prev = p;
        front = p;
        if (!back) back = front;
        size++;
    } else if (index == size) // na koniec listy
    {
        if (back) back->next = p;
        p->next = nullptr;
        p->prev = back;
        back = p;
        if (!front) front = back;
        size++;
    } else // w wybrane miejsce listy
    {
        listElement *p1 = findIndex(index);
        p->next = p1;
        p->prev = p1->prev;
        p1->prev = p;
        if (p->prev) p->prev->next = p;
        else front = p;
        size++;
    }
}

void List::deleteFromStruct(int index) {
    listElement * p;
    p = findIndex(index);

    if(p->prev) p->prev->next = p->next;
    else front = p->next;
    if(p->next) p->next->prev = p->prev;
    else back = p->prev;
    size--;
    delete p;
}

void List::display() {
    listElement *p;
    cout << "Od poczatku: ";
    if (front) {
        p = front;
        while (p) {
            cout << "|" << p->key;
            p = p->next;
        }
        cout << "|" << endl;
    }
    cout << "Od konca: ";
    if (back) {
        p = back;
        while (p) {
            cout << "|" << p->key;
            p = p->prev;
        }
        cout << "|" << endl;
    }
}

void List::generateStruct(int siz) {
    clearStruct();
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dist(1, 99999999);;
    for (int i = 0; i < siz; ++i) {
        addValue(size, dist(gen));
    }
}

void List::clearStruct() {
    listElement *p;
    while (front) {
        p = front->next;
        delete front;
        front = p;
        size--;
    }
    back = nullptr;
}

void List::test(int repeat, int num, int *values) {
    long long int frequency, start, elapsed;
    double sum, time;
    ofstream resultFile;
    resultFile.open("..\\resultsFiles\\resultsList");

    QueryPerformanceFrequency((LARGE_INTEGER *) &frequency);

    // Usuwanie elementu
    resultFile << "---- Usuwanie pierwszego elementu z listy ---" << endl;
    resultFile << "Rozmiar listy\\Czas[ns];";
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

            time = (1000000000.0 * elapsed) / (frequency);
//            resultFile  << fixed << setprecision(0) << time << ";";
            sum += time;
        }
        resultFile << fixed << setprecision(0) << sum/repeat << ";";
    }
    resultFile << endl << endl;

    resultFile << "---- Usuwanie ostatniego elementu z listy ---" << endl;
    resultFile << "Rozmiar listy\\Czas[ns];";
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
            deleteFromStruct(num-1);
            elapsed = read_QPC() - start;

            time = (1000000000.0 * elapsed) / frequency;
//            resultFile << fixed << setprecision(0) << time << ";";
            sum += time;
        }
        resultFile << fixed << setprecision(0) << sum/repeat << ";";
    }
    resultFile << endl << endl;

    resultFile << "---- Usuwanie losowego elementu z listy ---" << endl;
    resultFile << "Rozmiar listy\\Czas[us];";
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
    resultFile << "---- Dodawanie elementu na początek listy ---" << endl;
    resultFile << "Rozmiar listy\\Czas[ns];";
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

            time = (1000000000.0 * elapsed) / frequency;
//            resultFile << fixed << setprecision(0) << time << ";";
            sum += time;
        }
        resultFile << fixed << setprecision(0) << sum/repeat << ";";
    }
    resultFile << endl << endl;

    resultFile << "---- Dodawanie elementu na koniec listy ---" << endl;
    resultFile << "Rozmiar listy\\Czas[ns];";
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

            time = (1000000000.0 * elapsed) / frequency;
//            resultFile << fixed << setprecision(0) << time << ";";
            sum += time;
        }
        resultFile << fixed << setprecision(0) << sum/repeat << ";";
    }
    resultFile << endl << endl;

    resultFile << "---- Dodawanie elementu w losowe miejsce listy ---" << endl;
    resultFile << "Rozmiar listy\\Czas[us];";
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
    resultFile << "---- Wyszukiwanie losowej wartosci w liscie ---" << endl;
    resultFile << "Rozmiar listy\\Czas[us];";
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

listElement *List::findIndex(int index) {
    listElement *p;
    if (index == size) return back->next;
    else if (index < size / 2)
    {
        p = front;
        while(index){
            p = p->next;
            index--;
        }
        return p;
    } else
    {
        p = back;
        while(size>++index) {
            p = p->prev;
        }
        return p;
    }
}
