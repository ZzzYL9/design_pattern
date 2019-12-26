#ifndef DECORATORBAG_H
#define DECORATORBAG_H

#include "bag.h"

class CDecoratorBag: public CBag{
public:
    CDecoratorBag(CBag* pBag): m_pBag{pBag}{}

    virtual ~CDecoratorBag(){}

    virtual void operation() override
    {
        m_pBag->operation();
    }

//private:
protected:
    CBag *m_pBag;
};

#endif // DECORATORBAG_H
