
#include "dstack.h"
#include <iostream>
using namespace std;

DStack::DStack() {}

DStack::~DStack() {}

void DStack::Push(double x) {
    InsertAsFirstElement(x);
}

bool DStack::Pop(double &x) {
    return GetAndDeleteFirstElement(x);
}

void DStack::SPrintReverseByRecursion(ListNode* node) {
    if (node == nullptr) {
        return;
    }
    SPrintReverseByRecursion(node->next); //erklären
    cout << node->Element << endl;
}

void DStack::SPrintReverse(){
	SPrintReverseByRecursion(anchor);
}

double DStack::PrintValue(){
    return DList::PrintValue(); // erklären
}
