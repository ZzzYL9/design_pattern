#include <iostream>
using namespace std;

//抽象产品类
class BMW{
public:
    BMW(){}
    virtual void GetCar() = 0;
    virtual ~BMW(){}
};

//具体产品1
class BMW320: public BMW{
public:
    BMW320(){}
    void GetCar() override{
        cout << "生产BMW320" << endl;
    }
};

//具体产品2
class BWM520: public BMW{
public:
    BWM520(){}
    void GetCar() override{
        cout << "生产BMW520" << endl;
    }
};

//工厂方法与简单工厂有基本相同的产品，区别在于抽象非具体的工厂
//抽象工厂类
class Factory{
public:
    Factory(){}
    virtual BMW *CreateCar() = 0;
    virtual ~Factory(){}
};

//具体工厂1
class BMW320Factory: public Factory{
public:
    BMW * CreateCar() override{
        return new BMW320();
    }
};

//具体工厂2
class BMW520Factory: public Factory{
public:
    BMW * CreateCar() override{
        return new BWM520();
    }
};

int main()
{
    Factory *factory1 = new BMW320Factory();
    Factory *factory2 = new BMW520Factory();

    BMW *car1 = factory1->CreateCar();
    BMW *car2 = factory2->CreateCar();

    car1->GetCar();
    car2->GetCar();

    delete factory1;
    delete factory2;
    return 0;
}
