#include "../headers/Table.h"
#include "../headers/Menu.h"
#include <string>
#include <iostream>

using namespace std;

Menu::Menu(Table *myTab, List *myList, Heap *myHeap, BST *myBST, RBT *myRBT)
{
    this -> myTab = *myTab;
    this -> myList = *myList;
    this -> myHeap = *myHeap;
    this -> myBST = *myBST;
    this -> myRBT = *myRBT;
}

Menu::~Menu()
= default;

void Menu::structMenu(const string& info)
{
	cout << endl;
	cout << info << endl;
	cout << "1.Wczytaj z pliku" << endl;
	cout << "2.Usun" << endl;
	cout << "3.Dodaj" << endl;
	cout << "4.Znajdz" << endl;
	cout << "5.Utworz losowo" << endl;
	cout << "6.Wyswietl" << endl;
    if (info=="--- DRZEWO BST ---")
    {
        cout << "7.Rotacja w prawo" << endl;
        cout << "8.Rotacja w lewo" << endl;
        cout << "9.Rownowazenie metoda DSW" << endl;
        cout << "t.Test (pomiary)" << endl;
    } else
    {
        cout << "7.Test (pomiary)" << endl;
    }
    cout << "0.Powrot do menu" << endl;
	cout << "Podaj opcje:";
}

void Menu::menuMain()
{
    do{
        cout << endl;
        cout << "==== MENU GLOWNE ===" << endl;
        cout << "1.Tablica" << endl;
        cout << "2.Lista" << endl;
        cout << "3.Kopiec" << endl;
        cout << "4.Drzewo BST" << endl;
        cout << "5.Drzewo czerwono-czarne" << endl;
        cout << "t.Testy dla wszystkich struktur" << endl;
        cout << "0.Wyjscie" << endl;
        cout << "Podaj opcje:";
        cin >> option;
        cout << endl;

        switch (option){
            case '1':
                menuTable();
                option = ' ';
                break;

            case '2':
                menuList();
                option = ' ';
                break;

            case '3':
                menuHeap();
                option = ' ';
                break;

            case '4':
                menuBST();
                option = ' ';
                break;

            case '5':
                menuRBT();
                option = ' ';
                break;

            case 't':
                myTab.test(repeat,num,values);
                myList.test(repeat,num,values);
                myHeap.test(repeat,num,values);
                myBST.test(repeat,num,values);
                option = ' ';
                break;
        }

    } while (option != '0');
}

void Menu::menuTable()
{
	string fileName;
	int index, value;

	do{
        structMenu("--- TABLICA ---");
        cin >> option;
		cout << endl;
		switch (option){
		case '1': // wczytytwanie  tablicy z pliku
			cout << "Podaj nazwe pliku:";
			cin >> fileName;
            cout << endl;
			myTab.loadFromFile(fileName);
			myTab.display();
			break;

		case '2': // usuwanie elemenu z tablicy
            cout << endl << "----SKAD MA BYC USUNIETY ELEMENT TABLICY----" << endl;
            cout << "1.Usun z poczatku tablicy" << endl;
            cout << "2.Usun z konca tablicy" << endl;
            cout << "3.Usun z wybranego miejsce tablicy" << endl;
            cout << "Podaj opcje:";
            cin >> option;
            cout << endl;
            switch (option) {
                case '1':
                    index = 0;
                    break;
                case '2':
                    index = myTab.size-1;
                    break;
                case '3':
                    cout << endl << "Podaj indeks elementu do usuniecia" << endl;
                    cin >> index;
                    break;
            }
            if (index > myTab.size-1 || index < 0)
            {
                cout << endl << "Indeks wykroczyl poza liste" << endl;
                break;
            }
            myTab.deleteFromStruct(index);
			myTab.display();
			break;

		case '3': // dodawanie elemetu do tablicy
            cout << "Podaj wartosc:";
            cin >> value;
            cout << endl;
            cout << "---- GDZIE WARTOSC " << value << " MA ZOSTAC DODANA? ----" << endl;
            cout << "1.Dodaj na poczatek tablicy" << endl;
            cout << "2.Dodaj na koniec tablicy" << endl;
            cout << "3.Dodaj w wybrane miejsce tablicy" << endl;
            cout << "Podaj opcje:";
            cin >> option;
            cout << endl;
            switch (option) {
                case '1':
                    index = 0;
                    break;
                case '2':
                    index = myTab.size;
                    break;
                case '3':
                    cout << endl << "Podaj indeks w tablicy, w ktorym ma sie pojawic " << value << endl;
                    cin >> index;
                    break;
            }

            if (index > myTab.size || index < 0)
            {
                cout << endl << "Indeks wykroczyl poza liste" << endl;
                break;
            }
			myTab.addValue(index, value);
			myTab.display();			
			break;

		case '4': // znajdowanie elemetu w tablicy
			cout << "Podaj wartosc:";
			cin >> value;
            cout << endl;
			if (myTab.isValueInStruct(value))
				cout << "Podana wartosc jest w tablicy";
			else
				cout << "Podanej wartosci NIE ma w tablicy";
			break;

		case '5':  // generowanie  tablicy
			cout << "Podaj ilosc elementow tablicy:";
			cin >> value;
            cout << endl;
            myTab.generateStruct(value);
			myTab.display();
			break;

		case '6':  // wyświetlanie tablicy
            cout << "TABLICA" << endl;
			myTab.display();
			break;

		case '7': // funkcja do eksperymentów (pomiary czasów i generowanie danych)
            myTab.test(repeat,num,values);
			break;
		}


	} while (option != '0');
}

void Menu::menuList()
    {
        string fileName;
        int index, value;

        do{
            structMenu("--- LISTA ---");
            cin >> option;
            cout << endl;
            switch (option){
                case '1': // wczytytwanie  listy z pliku
                    cout << "Podaj nazwe pliku:";
                    cin >> fileName;
                    cout << endl;
                    myList.loadFromFile(fileName);
                    myList.display();
                    break;

                case '2': // usuwanie elemenu z listy
                    cout << endl << "---- SKAD MA BYC USUNIETY ELEMENT LISTY ----" << endl;
                    cout << "1.Usun z poczatku listy" << endl;
                    cout << "2.Usun z konca listy" << endl;
                    cout << "3.Usun z wybranego miejsce listy" << endl;
                    cout << "Podaj opcje:";
                    cin >> option;
                    cout << endl;
                    switch (option) {
                        case '1':
                            index = 0;
                            break;
                        case '2':
                            index = myList.size-1;
                            break;
                        case '3':
                            cout << endl << "Podaj indeks elementu do usuniecia:" << endl;
                            cin >> index;
                            break;
                    }
                    if (index > myList.size-1 || index < 0)
                    {
                        cout << endl << "Indeks wykroczyl poza liste" << endl;
                        break;
                    }
                    myList.deleteFromStruct(index);
                    myList.display();
                    break;

                case '3': //dodawanie elemetu do listy
                    cout << "Podaj wartosc:";
                    cin >> value;
                    cout << endl;
                    cout << "---- GDZIE WARTOSC " << value << " MA ZOSTAC DODANA? ----" << endl;
                    cout << "1.Dodaj na poczatek listy" << endl;
                    cout << "2.Dodaj na koniec listy" << endl;
                    cout << "3.Dodaj w wybrane miejsce listy" << endl;
                    cout << "Podaj opcje:";
                    cin >> option;
                    cout << endl;
                    switch (option) {
                        case '1':
                            index = 0;
                            break;
                        case '2':
                            index = myList.size;
                            break;
                        case '3':
                            do {
                                cout << endl << "Podaj indeks w liscie, w ktorym ma sie pojawic " << value << endl;
                                cin >> index;
                                if (index > myList.size || index < 0)
                                {
                                    cout << "Indeks wykroczył poza liste" << endl;
                                }
                            } while (index > myList.size);
                            break;
                    }

                    myList.addValue(index, value);
                    myList.display();
                    break;

                case '4': //znajdowanie elemetu w liście
                    cout << "Podaj wartosc:";
                    cin >> value;
                    cout << endl;
                    if (myList.isValueInStruct(value))
                        cout << "Podana wartosc jest w liscie" << endl;
                    else
                        cout << "Podanej wartosci NIE ma w liscie" << endl;
                    break;

                case '5':  //generowanie listy
                    cout << "Podaj ilosc elementow listy:";
                    cin >> value;
                    cout << endl;
                    myList.generateStruct(value);
                    myList.display();
                    break;

                case '6':  //wyświetlanie listy
                    cout << "LISTA" << endl;
                    myList.display();
                    break;

                case '7': //funkcja do eksperymentów (pomiary czasów i generowanie danych)
                    myList.test(repeat,num,values);
                    break;
            }

        } while (option != '0');
    }

void Menu::menuHeap()
{
    string fileName;
    int value;

    do{
        structMenu("--- KOPIEC ---");
        cin >> option;
        cout << endl;
        switch (option){
            case '1': // wczytywanie kopca z pliku
                cout << "Podaj nazwe pliku:";
                cin >> fileName;
                cout << endl;
                myHeap.loadFromFile(fileName);
                myHeap.display();
                break;

            case '2': // usuwanie korzenia z kopca
                if (myHeap.size == 0)
                {
                    cout << endl << "Kopiec nie ma elementow do usuniecia" << endl;
                    break;
                }
                myHeap.deleteFromStruct();
                myHeap.display();
                break;

            case '3': //dodawanie elemetu do kopca
                cout << "Podaj wartosc:";
                cin >> value;
                cout << endl;
                myHeap.addValue(value);
                myHeap.display();
                break;

            case '4': //znajdowanie elementu w kopcu
                cout << "Podaj wartosc:";
                cin >> value;
                cout << endl;
                if (myHeap.isValueInStruct(value))
                    cout << "Podana wartosc jest w kopcu" << endl;
                else
                    cout << "Podanej wartosci NIE ma w kopcu" << endl;
                break;

            case '5':  //generowanie kopca
                cout << "Podaj ilosc elementow kopca:";
                cin >> value;
                cout << endl;
                myHeap.generateStruct(value);
                myHeap.display();
                break;

            case '6':  //wyświetlanie kopca
                cout << "KOPIEC" << endl;
                myHeap.display();
                break;

            case '7': //funkcja do eksperymentów (pomiary czasów i generowanie danych)
                myHeap.test(repeat,num,values);
                break;
        }

    } while (option != '0');
}

void Menu::menuBST()
{
    string fileName;
    int value;

    do{
        structMenu("--- DRZEWO BST ---");
        cin >> option;
        cout << endl;
        switch (option){
            case '1': // wczytywanie drzewa
                cout << "Podaj nazwe pliku:";
                cin >> fileName;
                cout << endl;
                myBST.loadFromFile(fileName);
                myBST.display();
                break;

            case '2': // usuwanie korzenia z drzewa
                cout << "Podaj wartosc do usuniecia:";
                cin >> value;
                cout << endl;
                if (!myBST.isValueInStruct(value))
                {
                    cout << endl << "W drzewie nie ma takiego elementu" << endl;
                    break;
                }
                myBST.deleteFromStruct(value);
                myBST.display();
                break;

            case '3': //dodawanie elemetu do drzewa
                cout << "Podaj wartosc:";
                cin >> value;
                cout << endl;
                myBST.addValue(value);
                myBST.display();
                break;

            case '4': //znajdowanie elementu w drzewie
                cout << "Podaj wartosc:";
                cin >> value;
                cout << endl;
                if (myBST.isValueInStruct(value))
                    cout << "Podana wartosc jest w drzewie" << endl;
                else
                    cout << "Podanej wartosci NIE ma w drzewie" << endl;
                break;

            case '5':  //generowanie drzewa
                cout << "Podaj ilosc elementow drzewa:";
                cin >> value;
                cout << endl;
                myBST.generateStruct(value);
                myBST.display();
                break;

            case '6':  //wyświetlanie drzewa
                cout << "DRZEWO BST" << endl;
                myBST.display();
                break;

            case '7':  //rotacja w prawo
                cout << "Podaj wartosc wezla:";
                cin >> value;
                cout << endl;
                if (!myBST.isValueInStruct(value)){
                    cout << "Nie ma takiego wezla" << endl;
                    break;
                }
                if (!myBST.findValue(value)->left){
                    cout << "Nie da sie wykonac rotacji (brak syna z lewej strony)" << endl;
                    break;
                }
                myBST.rotateRight(myBST.findValue(value));
                myBST.display();
                break;

            case '8':  //rotacja w lewo
                cout << "Podaj wartosc wezla" << endl;
                cin >> value;
                cout << endl;
                if (!myBST.isValueInStruct(value)){
                    cout << "Nie ma takiego wezla" << endl;
                    break;
                }
                if (!myBST.findValue(value)->right){
                    cout << "Nie da sie wykonac rotacji (brak syna z prawej strony)" << endl;
                    break;
                }
                myBST.rotateLeft(myBST.findValue(value));
                myBST.display();
                break;

            case '9':  //rownowazenie drzewa
                if (myBST.size == 0){
                    cout << "Drzewo jest puste" << endl;
                    break;
                }
                myBST.DSW();
                myBST.display();
                break;

            case 't': //funkcja do eksperymentów (pomiary czasów i generowanie danych)
                myBST.test(repeat,num,values);
                break;
        }

    } while (option != '0');
}

void Menu::menuRBT() {
    string fileName;
    int value;

    do {
        structMenu("--- DRZEWO CZERWONO-CZARNE ---");
        cin >> option;
        cout << endl;
        switch (option) {
            case '1': // wczytywanie drzewa
                cout << "Podaj nazwe pliku:";
                cin >> fileName;
                cout << endl;
                myRBT.loadFromFile(fileName);
                myRBT.display();
                break;

            case '2': // usuwanie korzenia z drzewa
                cout << "Podaj wartosc do usuniecia:";
                cin >> value;
                cout << endl;
                if (!myRBT.isValueInStruct(value)) {
                    cout << endl << "W drzewie nie ma takiego elementu" << endl;
                    break;
                }
                myRBT.deleteFromStruct(value);
                myRBT.display();
                break;

            case '3': //dodawanie elemetu do drzewa
                cout << "Podaj wartosc:";
                cin >> value;
                cout << endl;
                myRBT.addValue(value);
                myRBT.display();
                break;

            case '4': //znajdowanie elementu w drzewie
                cout << "Podaj wartosc:";
                cin >> value;
                cout << endl;
                if (myRBT.isValueInStruct(value))
                    cout << "Podana wartosc jest w drzewie" << endl;
                else
                    cout << "Podanej wartosci NIE ma w drzewie" << endl;
                break;

            case '5':  //generowanie drzewa
                cout << "Podaj ilosc elementow drzewa:";
                cin >> value;
                cout << endl;
                myRBT.generateStruct(value);
                myRBT.display();
                break;

            case '6':  //wyświetlanie drzewa
                cout << "DRZEWO CZERWONO-CZARNE" << endl;
                myRBT.display();
                break;

            case '7': //funkcja do eksperymentów (pomiary czasów i generowanie danych)
                myRBT.test(repeat, num, values);
                break;
        }

    } while (option != '0');
}