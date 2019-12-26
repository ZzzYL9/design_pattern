#ifndef SPORTBAG_H
#define SPORTBAG_H

#include <iostream>
#include "bag.h"

using namespace std;

class CSportBag: public CBag{
public:
    CSportBag(){}
    virtual ~CSportBag(){}

    virtual void operation() override
    {
        cout << "Sport bag" << endl;
    }
};

#endif // SPORTBAG_H
