#ifndef QGGDECORATORBAG_H
#define QGGDECORATORBAG_H

#include <iostream>
#include "decoratorbag.h"

class CQggDecoratorBag: public CDecoratorBag
{
public:
    CQggDecoratorBag(CBag* pBag): CDecoratorBag{pBag}{}
    virtual ~CQggDecoratorBag(){}

    virtual void operation() override
    {
//        m_pBag->operation();
        CDecoratorBag::operation();
        Hang();
    }

protected:
    void Hang()
    {
        cout << "添加装饰QGG" << endl;
    }
};

#endif // QGGDECORATORBAG_H
