/*
* 创建了两种时钟，如果时间timer改变则两个时钟都会被更新并正确的重新显示
*/
#include <iostream>
#include <list>

using namespace std;

class Subject;
class Widget{

};

class Observer{
public:
    virtual ~Observer();
    // 该实现方式支持一个观察者有多个目标，当观察者观察多个目标时，
    // 作为参数传递给Update操作的目标让观察者可以判定是那个目标发生了改变
    virtual void Update(Subject *theChangedSubject) = 0;
protected:
    Observer();
};

class Subject{
public:
    virtual ~Subject();

    virtual void Attach(Observer*);
    virtual void Detach(Observer*);
    virtual void Notify();

protected:
    Subject();
private:
    list<Observer*> *_observers;
};

void Subject:: Attach(Observer *o)
{
    _observers->push_back(o);
}

void Subject:: Detach(Observer *o)
{
    _observers->remove(o);
}

void Subject::Notify()
{
    for(list<Observer*>::iterator it=_observers->begin(); it!=_observers->end(); it++){
        (*it)->Update(this);
    }
}

// ClockTimer是一个用于存储和维护一天时间的具体目标。
// 它每秒钟通知一次它的观察者。
class ClockTimer: public Subject{
public:
    ClockTimer();

    virtual int GetHour(); // 取出单个的时间单位
    virtual int GetMinute();
    virtual int GetSecond();

    // Tick()操作由一个内部计时器以固定的时间间隔调用，从而提供一个精准的时间基准
    void Tick();
};

void ClockTimer::Tick()
{
    // 更新内部状态并调用Notify通知观察者
    //......
    Notify();
}

// 定义一个类来显示时间，它从一个用户界面箱提供的Widget类继承了它的图形功能。
class DigitalClock: public Widget, public Observer{
public:
    DigitalClock(ClockTimer*);
    virtual ~DigitalClock();

    virtual void Update(Subject *theChangedSubject) override;

    // 重载Widget操作，定义如何画时钟图形
    virtual void Draw();

private:
    ClockTimer* _subject;
};

DigitalClock::DigitalClock(ClockTimer* s)
{
    _subject = s;
    _subject->Attach(this);
}

DigitalClock::~DigitalClock()
{
    _subject->Detach(this);
}

void DigitalClock::Update(Subject *theChangedSubject)
{
    // 在调用Draw之前进行检查，保证发出通知的目标是该时钟的目标
    if(theChangedSubject == _subject){
        Draw();
    }
}

void DigitalClock::Draw(){
    //获取新值
    int hour = _subject->GetHour();
    int minute = _subject->GetMinute();
    //....
    //画时钟
    //.....

}

// 用同样的方法定义一个观察者
class AnalogClock: public Widget, public Observer{
public:
    AnalogClock(ClockTimer*);
    virtual void Update(Subject *theChangedSubject) override;
    virtual void Draw();
};

int main()
{
    ClockTimer* timer = new ClockTimer;
    AnalogClock* analogClock = new AnalogClock(timer);
    DigitalClock* digitalClock = new DigitalClock(timer);
    return 0;
}
 
