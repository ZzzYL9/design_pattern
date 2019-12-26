#ifndef QMMDECORATORBAG_H
#define QMMDECORATORBAG_H

#include <iostream>
#include "decoratorbag.h"

class CQmmDecoratorBag: public CDecoratorBag
{
public:
    CQmmDecoratorBag(CBag *pBag): CDecoratorBag{pBag}{}

    virtual ~CQmmDecoratorBag(){}

    virtual void operation() override
    {
//        m_pBag->operation();
        CDecoratorBag::operation();
        Hang();
    }

protected:
    void Hang()
    {
        cout << "添加装饰QMM" << endl;
    }
};

#endif // QMMDECORATORBAG_H
