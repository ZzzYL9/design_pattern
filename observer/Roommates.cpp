/*
 * 观察者模式
 *
 * 假设三个同学逃课，没有点名时A、B、C正在分别做不同的事情，而点名时，他们三个都收到了信息而赶去教室
 *
 * 采用观察者模式实现这个情景的应用。
 */

#include <iostream>
#include <string>
#include <list>

//using namespace std;
class Observer;

// 观察目标抽象类
class Subject{
public:
    Subject(){}
    virtual ~Subject() { std::cout << "delete Subject" << std::endl; }
    virtual void registerObserver(Observer* obs)=0; //注册观察者
    virtual void removeObserver(Observer* obs)=0; //移除观察者
    virtual void notifyObservers(const std::string &msg)=0; //通知观察者
};

//观察者抽象类
class Observer{
public:
    virtual ~Observer(){}
    virtual void Update(const std::string &msg)=0; //当收到数据变化信息后更新（就本例来说是更新学生的动作）
    virtual std::string getName()=0;

protected:
    Observer(){}
};

class QQgroup: public Subject
{
public:
    QQgroup() { _observers = new std::list<Observer*>(); }
    void registerObserver(Observer *obs) override;
    void removeObserver(Observer *obs) override;
    void notifyObservers(const std::string &msg) override;

private:
    std::list<Observer*> *_observers;
};

void QQgroup::registerObserver(Observer *obs)
{
    _observers->push_back(obs);
}

void QQgroup::removeObserver(Observer *obs)
{
    if(_observers->size() > 0)
        _observers->remove(obs);
}

void QQgroup::notifyObservers(const std::string &msg)
{
    std::cout << "群消息：" << msg << std::endl;
    for(std::list<Observer*>::iterator it=_observers->begin(); it!=_observers->end(); it++){
        (*it)->Update(msg);
    }
}

class RoomMate: public Observer{
public:
    RoomMate(std::string name, std::string now, std::string action):_name{name}, _action{action}, _now{now}{}
    void Update(const std::string &msg) override;
    std::string getName() override;
    ~RoomMate() override{}

private:
    std::string _name;
    std::string _action;
    std::string _now;
};

std::string RoomMate::getName()
{
    return _name;
}

void RoomMate::Update(const std::string &msg)
{
    std::cout << "这是" << _name << std::endl;
    if(msg == "点名了")
        std::cout << "动作：" << _action << std::endl << std::endl;
    else
        std::cout << "继续：" << _now << std::endl << std::endl;
}

int main()
{
    RoomMate *A = new RoomMate("A", "睡觉", "穿上衣服去教室");
    RoomMate *B = new RoomMate("B", "玩游戏", "关了电脑去教室");
    RoomMate *C = new RoomMate("C", "打球", "放下球去教室");

    QQgroup *qqgroup = new QQgroup();
    qqgroup->registerObserver(A);
    qqgroup->registerObserver(B);
    qqgroup->registerObserver(C);

    qqgroup->notifyObservers("没点名");
    qqgroup->notifyObservers("点名了");


    return 0;
}
 
