
#include <iostream>
using namespace std;

struct ListNode
{
    double Element;
    ListNode *next = nullptr;
};

class DList {
public:
    DList();
    virtual ~DList();
    void InsertAsFirstElement(double x);
    bool GetAndDeleteFirstElement(double &x);
    void LPrintForward();
    double PrintValue();

protected:
    ListNode* anchor = nullptr;
};


