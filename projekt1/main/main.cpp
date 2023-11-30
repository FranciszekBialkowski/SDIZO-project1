#include "../headers/Structure.h"
#include "../headers/Table.h"
#include "../headers/List.h"
#include "../headers/Heap.h"
#include "../headers/BST.h"
#include "../headers/RBT.h"
#include "../headers/Menu.h"

using namespace std;



int main()
{
        auto *myTable = new Table;
        auto *myList = new List;
        auto *myHeap = new Heap;
        auto *myBST = new BST;
        auto *myRBT = new RBT;

        Menu menu(myTable,myList,myHeap,myBST,myRBT);

        menu.menuMain();

        delete myTable;
        delete myList;
        delete myHeap;
        delete myBST;
        delete myRBT;

	return 0;
}
