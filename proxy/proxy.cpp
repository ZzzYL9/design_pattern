/*
* 设计模式：代理模式
*
*
*/

#include <iostream>
using namespace std;

// 定义了Proxy和ConcreteSubject的公有接口,
// 这样就可以在任何需要使用到ConcreteSubject的地方都使用Proxy.
class Subject
{
public:
    virtual ~Subject();
    virtual void Request()=0;
protected:
    Subject();
};

class ConcreteSubject : public Subject
{
public:
    ConcreteSubject();
    ~ConcreteSubject();
    virtual void Request();
};

//定义代理类
class Proxy : public Subject
{
public:
    Proxy();
    ~Proxy();
    void DoSomething1();
    virtual void Request();
    void DoSomething2();
private:
    Subject* _subject;
};


Subject::Subject()
{}

Subject::~Subject()
{}

ConcreteSubject::ConcreteSubject()
{}

ConcreteSubject::~ConcreteSubject()
{}

void ConcreteSubject::Request()
{
    cout << "ConcreteSubject::Request" << endl;
}

Proxy::Proxy() : _subject(NULL)
{}

Proxy::~Proxy()
{}

void Proxy::DoSomething1()
{
    cout << "Proxy::DoSomething1" << endl;
}

void Proxy::DoSomething2()
{
    cout << "Proxy::DoSomething2" << endl;
}

void Proxy::Request()
{
    if(NULL == this->_subject)
    {
        this->_subject = new ConcreteSubject();
    }

    this->DoSomething1();//表示额外附加的操作

    this->_subject->Request();//代理的实体类操作

    this->DoSomething2();//表示额外附加的操作
}

int main()
{
    Proxy* proxy = new Proxy();
    proxy->Request();

    return 0;
}
 
