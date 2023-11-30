#include "../headers/RBT.h"
#include <stack>

RBT::RBT() {
    root = nullptr;
    size = 0;
}

RBT::~RBT() {
    clearStruct();
}

int RBT::loadFromFile(string fileName) {
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
                } else {
                    addValue(val);
                }
            }
        file.close();
    } else
        cout << "File error - OPEN" << endl;
    return 0;
}

bool RBT::isValueInStruct(int val) {
    RBTNode *p = root;
    while (p) {
        if (p->key == val) return true;
        if (val < p->key) p = p->left;
        else p = p->right;
    }
    return false;
}

void RBT::addValue(int index, int value) {}

void RBT::deleteFromStruct(int val) {
    // usuniecie
    RBTNode *p = findValue(val);
    RBTNode *u, *v, *s, *r;
    bool v_isRed;
    if (p->left== nullptr || p->right== nullptr) v = p;
    else v = findSuccessor(p);
    if (v->left != nullptr) u=v->left;
    else u = v->right;
    if (u != nullptr) u->up = v->up;
    if (v->up == nullptr) root = u;
    else
    {
        if (v == v->up->left) v->up->left = u;
        else v->up->right = u;
    }
    if (v != p) p->key = v->key;
    v_isRed = v->isRed;
    if (p->up) p=p->up;
    delete v;
    size--;

    // naprawa drzewa
        if (size>2)
        {
            if ((!v_isRed && u == nullptr) || (!v_isRed && !u->isRed)) //3
            {
                bool isDoubleBlack = true; //3.1

                //3.2
                while (isDoubleBlack && u!=root)
                {
                    // wyznaczenie rodzica
                    if (u!= nullptr && u->up) p = u->up;

                    // wyznaczenie brata
                    if (u==p->left) s = p->right;
                    else s = p->left;

                    if (!s->isRed && ((s->left && s->left->isRed) || (s->right && s->right->isRed))) //a
                    {
                        if (s==p->left && (s->left && s->left->isRed)) //I
                        {
                            r = s->left;
                            rotateRight(p);
                            r->isRed=false;
                        }
                        else if ((s==p->left && (s->right && s->right->isRed))) //II
                        {
                            r = s->right;
                            rotateLeft(s);
                            r->isRed=false;
                            rotateRight(p);
                        }
                        else if (s==p->right && (s->right && s->right->isRed)) //III
                        {
                            r = s->right;
                            rotateLeft(p);
                            r->isRed=false;
                        }
                        else if ((s==p->right && (s->left && s->left->isRed))) //IV
                        {
                            r = s->left;
                            rotateRight(s);
                            r->isRed=false;
                            rotateLeft(p);
                        }
                        isDoubleBlack= false;
                    }
                    else if (!s->isRed && ((!s->left || !s->left->isRed) && (!s->right || s->right->isRed))) //b
                    {
                        if (p->isRed)
                        {
                            p->isRed = false;
                            isDoubleBlack = false;
                        }
                        s->isRed=true;
                        u = p;
                    }
                    else if (s->isRed) //c
                    {
                        if (s==p->left) //I
                        {
                            rotateRight(p);
                            p->isRed = !p->isRed;
                            s->isRed = !s->isRed;
                        }
                        else if (s==p->right) //II
                        {
                            rotateLeft(p);
                            p->isRed = !p->isRed;
                            s->isRed = !s->isRed;
                        }
                    }
                }

            }
            if (u != nullptr)
            {
                if (u->isRed) u->isRed = false; //2

            }
        }

    if (root) root->isRed = false;
}

void RBT::addValue(int value) {
    // dodanie wezla
    auto *p = new RBTNode;
    p->key = value;
    p->isRed = true;
    RBTNode *p1 = root;
    if (!root) {
        root = p;
        root->up = nullptr;
    } else {
        while (p1) {
            if (value < p1->key) {
                if (p1->left) p1 = p1->left;
                else break;
            } else {
                if (p1->right) p1 = p1->right;
                else break;
            }
        }
        if (value < p1->key) p1->left = p;
        else p1->right = p;
        p->up = p1;
    }
    p->left = p->right = nullptr;
    size++;

    // naprawa drzewa
    while (p!=root && p->up->isRed)
    {
        if (p->up == p->up->up->left)
        {
            p1 = p->up->up->right;
            if (p1 != nullptr && p1->isRed)
            {
                p->up->isRed=false;
                p1->isRed=false;
                p->up->up->isRed=true;
                p = p->up->up;
            } else
            {
                if (p == p->up->right)
                {
                    p = p->up;
                    rotateLeft(p);
                }
                p->up->isRed= false;
                p->up->up->isRed = true;
                rotateRight(p->up->up);
            }
        } else
        {
            p1 = p->up->up->left;
            if (p1 != nullptr && p1->isRed)
            {
                p->up->isRed=false;
                p1->isRed=false;
                p->up->up->isRed=true;
                p = p->up->up;
            } else
            {
                if (p == p->up->left)
                {
                    p = p->up;
                    rotateRight(p);
                }
                p->up->isRed= false;
                p->up->up->isRed = true;
                rotateLeft(p->up->up);
            }
        }
    }
    root->isRed= false;
}

RBTNode *RBT::findMin(RBTNode *p) {
    while (p->left != nullptr) p = p->left;
    return p;
}

RBTNode *RBT::findSuccessor(RBTNode *p) {
    if (p->right != nullptr) return findMin(p->right);
    RBTNode *p1 = p->up;
    while (p1 != nullptr && p1->left != p) {
        p = p1;
        p1 = p1->up;
    }
    return p1;
}

RBTNode *RBT::findValue(int val) {
    RBTNode *p = root;
    while (p) {
        if (p->key == val) return p;
        if (val < p->key) p = p->left;
        else p = p->right;
    }
    return nullptr;
}

void RBT::display() {
    if (size > 0) {
        printTree("", root, false);
    }
}

void RBT::printTree(const string &prefix, const RBTNode *p, bool isLeft) {
    if (p != nullptr) {
        cout << prefix;

        cout << (isLeft ? "|--" : "\\--");

        if (p->isRed) cout << "\033[1;31m" << p->key << "\033[0m" << endl;
        else cout << p->key << endl;

        printTree(prefix + (isLeft ? "|   " : "    "), p->left, true);
        printTree(prefix + (isLeft ? "|   " : "    "), p->right, false);
    }
}

void RBT::generateStruct(int siz) {
    clearStruct();
    size = 0;
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dist(1, 99999999);;
    for (int i = 0; i < siz; ++i) {
        addValue(dist(gen));
    }
}

void RBT::clearStruct() {
    if (size > 0) postorderDelete(root);
    root = nullptr;
}

void RBT::postorderDelete(RBTNode *p) {
    if (p == nullptr) return;
    postorderDelete(p->left);
    postorderDelete(p->right);
    delete p;
    size--;
}

void RBT::rotateLeft(RBTNode *a) {
    RBTNode *b = a->right;
    if (a == root) {
        b->up = nullptr;
        root = b;
    } else {
        if (a == a->up->right) a->up->right = b;
        else a->up->left = b;
        b->up = a->up;
    }
    if (b->left) {
        a->right = b->left;
    } else a->right = nullptr;
    a->up = b;
    b->left = a;
}

void RBT::rotateRight(RBTNode *a) {
    RBTNode *b = a->left;
    if (a == root) {
        b->up = nullptr;
        root = b;
    } else {
        if (a == a->up->right) a->up->right = b;
        else a->up->left = b;
        b->up = a->up;
    }
    if (b->right) {
        a->left = b->right;
    } else a->left = nullptr;
    a->up = b;
    b->right = a;
}

void RBT::test(int repeat, int num, int *values) {
    long long int frequency, start, elapsed;
    double sum, time;
    ofstream resultFile;
    resultFile.open("..\\resultsFiles\\resultsRBT");

    QueryPerformanceFrequency((LARGE_INTEGER *) &frequency);

    // Usuwanie elementu
    resultFile << "---- Usuwanie korzenia z drzewa czerwono-czarnego ---" << endl;
    resultFile << "Rozmiar drzewa\\Czas[ns];";
    for (int j = 0;  j < repeat; ++j) {
        resultFile << "t" << j+1 << ";";
    }
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
            resultFile << fixed << setprecision(0) << time << ";";
            sum += time;
        }
        resultFile << fixed << setprecision(0) << sum/repeat << ";";
    }
    resultFile << endl << endl;

    // Dodawanie elementu
    resultFile << "---- Dodawanie losowego elementu do drzewa czerwono-czarnego ---" << endl;
    resultFile << "Rozmiar drzewa\\Czas[ns];";
    for (int j = 0; j < repeat; ++j) {
        resultFile << "t" << j+1 << ";";
    }
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
            resultFile << fixed << setprecision(0) << time << ";";
            sum += time;
        }
        resultFile << fixed << setprecision(0) << sum/repeat << ";";
    }
    resultFile << endl << endl;

    // Wyszukiwanie elementu
    resultFile << "---- Wyszukiwanie losowej wartosci w drzewie czerwono-czarnym ---" << endl;
    resultFile << "Rozmiar drzewa\\Czas[ns];";
    for (int j = 0; j < repeat; ++j) {
        resultFile << "t" << j+1 << ";";
    }
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
            resultFile << fixed << setprecision(0) << time << ";";
            sum += time;
        }
        resultFile << fixed << setprecision(0) << sum/repeat << ";";
    }
    resultFile << endl << endl;

    resultFile.close();
    cout << "Zapis do pliku zakonczony" << endl;
}
