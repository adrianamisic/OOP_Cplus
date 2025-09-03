#include "dlist.h"
using namespace std;

DList::DList() {}

DList::~DList() {
    ListNode* toBeDeleted = nullptr;
    while (anchor) {
        toBeDeleted = anchor;
        anchor = anchor->next;
        delete toBeDeleted;
    }
}

void DList::InsertAsFirstElement(double x) {
    ListNode* newNode = new ListNode;
    newNode->Element = x;
    newNode->next = anchor;
    anchor = newNode;
}

bool DList::GetAndDeleteFirstElement(double &x) {
    if (anchor) {
        x = anchor->Element;
        ListNode* temp = anchor;
        anchor = anchor->next;
        delete temp;
        return true;
    }
    return false;
}

void DList::LPrintForward(){
    ListNode* current = anchor;
    while (current) {
        cout << current->Element << endl;
        current = current->next;
    }
}

double DList::PrintValue(){
    if (anchor) {
        return anchor->Element;
    }
    return 0.0; // Oder ein anderer Wert, der anzeigt, dass die Liste leer ist
}
