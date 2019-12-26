#ifndef OUTDOORBAG_H
#define OUTDOORBAG_H

#include <iostream>
#include "bag.h"

class COutdoorBag: public CBag{
public:
    COutdoorBag(){}
    virtual ~COutdoorBag(){}

    virtual void operation() override
    {
        cout << "Outdoor bag" << endl;
    }
};

#endif // OUTDOORBAG_H
