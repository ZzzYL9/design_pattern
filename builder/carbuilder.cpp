/*
* 设计模式：建造者模式
*
*
*
*/

#include <iostream>
using namespace std;

//产品基类
class Car{
public:
    //获取产品部件函数
    string GetEngine() { return m_engine; }
    string GetGearBox() { return m_gearbox; }
    string GetChassis() { return m_chassis; }

    //设置产品部件函数
    void SetEngine(string engine){
        m_engine = engine;
        cout << "Create " << engine.c_str() << endl;
    }
    void SetGearBox(string gearbox){
        m_gearbox = gearbox;
        cout << "Create " << gearbox.c_str() << endl;
    }
    void SetChassis(string chassis){
        m_chassis = chassis;
        cout << "Create " << chassis.c_str() << endl;
    }

private:
    string m_engine; //引擎
    string m_gearbox; //变速箱
    string m_chassis; //底盘
};

//产品子类（Product)
//宝马车产品
class BMWCar: public Car{
public:
    BMWCar(){ cout << "Start build BMW." << endl; }
};

//奔驰车产品
class BenzCar: public Car{
public:
    BenzCar(){ cout << "Start build Benz." << endl; }
};

//抽象建造者类（Builder）
class CarBuilder{
public:
    virtual Car *BuildCar(){}  //造整车
    virtual void BuildEngine(){} //造引擎
    virtual void BuildGearBox(){} //造变速箱
    virtual void BuildChassis(){} //造底盘
};

//具体建造者类（ConcreteBuilder)
//具体宝马建造者类
class BMWCarBuilder: public CarBuilder{
public:
    BMWCarBuilder(){
        m_car = new BMWCar();
    }
    void BuildEngine() override{
        m_car->SetEngine("BMW Engine.");
    }
    void BuildGearBox() override{
        m_car->SetGearBox("BMW GearBox.");
    }
    void BuildChassis() override{
        m_car->SetChassis("BMW Chassis");
    }
    Car * BuildCar() override{
        return m_car;
    }
private:
    Car *m_car;
};

//具体奔驰建造者类
class BenzCarBuilder: public CarBuilder{
public:
    BenzCarBuilder(){
        m_car = new BenzCar();
    }
    void BuildEngine() override{
        m_car->SetEngine("Benz Engine.");
    }
    void BuildGearBox() override{
        m_car->SetGearBox("Benz GearBox.");
    }
    void BuildChassis() override{
        m_car->SetChassis("Benz Chassis");
    }
    Car * BuildCar() override{
        return m_car;
    }

private:
    Car *m_car;
};

//指导者（Director）
class CarDirector{
public:
    Car *ConstructCar(CarBuilder *carBuilder){
        carBuilder->BuildEngine();
        carBuilder->BuildChassis();
        carBuilder->BuildChassis();
        cout << "Car build finished." << endl << endl;
        return carBuilder->BuildCar();
    }
};

int main()
{
    CarDirector *carDirector = new CarDirector();
    Car *bmwCar = carDirector->ConstructCar(new BMWCarBuilder());
    Car *benzCar = carDirector->ConstructCar(new BenzCarBuilder());

    delete bmwCar;
    delete benzCar;
    delete carDirector;

    bmwCar = nullptr;
    benzCar = nullptr;
    carDirector = nullptr;
}

 
