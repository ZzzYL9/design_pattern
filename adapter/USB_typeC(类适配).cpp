/*
* 设计模式：适配器模式（类适配器）
*
* 场景：手机接口有USB和TypeC，适配器就是一个USB转为Type C的一个转换器。
*/

#include <iostream>
using namespace std;

class Target{
public:
    Target(){ cout << "USB" << endl; }
    virtual ~Target(){}
    virtual void Request(){
        cout << "This is USB connector" << endl;
    }
};

class Adaptee{
public:
    Adaptee(){ cout << "TypeC" << endl; }
    virtual ~Adaptee(){}
    virtual void SpecificalRequest(){
        cout << "This is TypeC connector" << endl;
    }
};

//这里通过private继承，表示转化是单向的，只能把Target转化为Adaptee
class Adapter: public Target, private Adaptee{
public:
    Adapter(){ cout << "Switch" << endl; }
    ~Adapter(){}
    void Request() override{
        this->SpecificalRequest();
    }
};

int main()
{
    Target *t = new Adapter();
    t->Request();

    return 0;
}
