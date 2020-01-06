/*
* 设计模式：中介者模式
*
* 定义一个中介对象来封装系列对象之间的交互
*
*/

#include <iostream>
using namespace std;

class Colleague;

class Mediator
{
public:
    virtual void send(std::string  msg, Colleague * p) = 0;
};

class Colleague
{
protected:
    Mediator * m_mediator;
public:
    Colleague(Mediator * p)
    {
        m_mediator = p;
    }
    virtual void send(std::string msg) = 0;
    virtual void notify(std::string msg) = 0;
};

class ConcreteColleague_1 : public Colleague
{
public:
    ConcreteColleague_1(Mediator * p) : Colleague(p) {}
    void send(std::string msg)
    {
        m_mediator->send(msg, this);
    }
    void notify(std::string msg)
    {
        std::cout << "Colleague_1 收到了消息：" << msg << std::endl;
    }
};

class ConcreteColleague_2 : public Colleague
{
public:
    ConcreteColleague_2(Mediator * p) : Colleague(p) {}
    void send(std::string msg)
    {
        m_mediator->send(msg, this);
    }
    void notify(std::string msg)
    {
        std::cout << "Colleague_2 收到了消息：" << msg << std::endl;
    }
};

class ConcreteMediator : public Mediator
{
private:
    // 这里也可以是一个列表
    Colleague * m_p1;
    Colleague * m_p2;
public:
    void addColleague(Colleague * p1, Colleague * p2)
    {
        m_p1 = p1;
        m_p2 = p2;
    }
    void send(std::string msg, Colleague * p)
    {
        // 这里接受来自一个同事发过来的消息，具体应该给谁要根据需求来
        // 这里知识一个很简单的应用。比如该类总可以是有两个队列。
        // 一个队列是客户，一个队列是客服
        if (p == m_p1)
            m_p2->notify(msg);
        else
            m_p1->notify(msg);
    }
};

int main()
{
    using namespace std;
    // 中介者模式
    ConcreteMediator * p = new ConcreteMediator();
    Colleague * pCol1 = new ConcreteColleague_1(p);
    Colleague * pCol2 = new ConcreteColleague_2(p);
    p->addColleague(pCol1, pCol2);
    pCol1->send("你下班了吗？");
    pCol2->send("没呢，你呢？");
    delete pCol1;
    delete pCol2;
    delete p;

    return 0;
}
 
