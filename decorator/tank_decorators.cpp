/*
*设计模式：装饰器模式
*
* 以装饰坦克为情景，坦克可以有加大火力和消音两个装饰器
*
* 特别注意装饰器类的继承和组合关系
*/

#include <iostream>
using namespace std;

//坦克抽象类component
class Tank{
public:
    Tank(){}
    virtual void shot(){ cout << "开炮！" << endl; }
    virtual ~Tank(){}
};

//concrete component
class T50: public Tank{
public:
    T50(){}
    void shot() override{ cout << "T50 开炮！" << endl; }
    ~T50() override{}
};


class T100: public Tank{
public:
    T100(){}
    void shot() override { cout << "T100开炮！" << endl; }
    ~T100() override {}
};

//装饰类继承于Tank,为了保持接口的一致性,装饰对象的接口必须与它所装饰的Component的接口是一致的
//因此所有的ConcreteDecorator类必须有一个公共的父类
//此处不应该是is_a关系，而是like_a
class Decorator: public Tank{
protected://必须是protect,因为其他继承Decorator的类要用
    Tank *tank;//has_a关系

public:
    void decorator(Tank *_tank) { tank = _tank; }
    void shot() override { tank->shot(); }

};

//装饰器一
class BigerShot: public Decorator{
public:
    void shot() override
    {
        cout << "加大火力" << endl;
        tank->shot();
    }
};

//装饰器二
class SilentShot: public Decorator{
public:
    void shot() override
    {
        cout << "开启消音" << endl;
        tank->shot();
    }
};

int main()
{
    Tank *ptank = new T50();
    Decorator *pDecorator = new Decorator();
    pDecorator->decorator(ptank);
    BigerShot *pBig = new BigerShot();
    pBig->decorator(pDecorator);
    SilentShot *pBigSlient = new SilentShot();
    pBigSlient->decorator(pBig);
    pBigSlient->shot();
    cout << endl << endl;

    Tank *Ttank = new T100();
    Decorator *Tdecorator = new Decorator();
    //添加基类装饰
    Tdecorator->decorator(Ttank);
    Tdecorator->shot();
    cout << endl;
    BigerShot *Bdecorator = new BigerShot();
    //将Tdecorator传入第一个装饰器中
    Bdecorator->decorator(Tdecorator);
    Bdecorator->shot();
    cout << endl;
    SilentShot *Sdecorator = new SilentShot();
    //在BigerShot装饰器的基础上再加一个装饰
    Sdecorator->decorator(Bdecorator);
    Sdecorator->shot();

        return 0;
}



