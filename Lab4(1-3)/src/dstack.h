
#include "dlist.h"

class DStack: public DList {
public:
    DStack();
    ~DStack();

    void Push(double x);
    bool Pop(double &x);
    void SPrintReverse();
    double PrintValue();

private:
    void SPrintReverseByRecursion(ListNode* node);
};


