/*
* 设计模式：装饰模式
*
* 场景：有两个背包outdoor和sport使用，可以在背包上分别装饰一些装饰：QMM、QGG
*/

#include <iostream>
#include "bag.h"
#include "sportbag.h"
#include "outdoorbag.h"
#include "decoratorbag.h"
#include "qggdecoratorbag.h"
#include "qmmdecoratorbag.h"

using namespace std;

int main()
{
    //创建sport类型的背包
    CBag* sportBag = new CSportBag();
    //创建outdoor类型的背包
    CBag* outdoorBag = new COutdoorBag();

    //给sport添加QGG装饰
    CBag* QGGdec = new CQggDecoratorBag(sportBag);
    QGGdec->operation();
    cout << endl;

    //创建QMM装饰
    CBag* QMMdec = new CQmmDecoratorBag(outdoorBag);
    QMMdec->operation();
    cout << endl;

    //给soprt在添加了QGG装饰的基础上继续添加装饰QMM
    QGGdec = new CQmmDecoratorBag(QGGdec);
    QGGdec->operation();

    delete sportBag;
    delete outdoorBag;
    delete QGGdec;
    delete QMMdec;

    return 0;
}
