/*
 * 策略模式
 *
 * 情景：诸葛亮给赵云三个锦囊
 *
 * 采用策略模式实现这个情景的应用。
 */

#include <iostream>

class IStrategy{
public:
    virtual void operate()=0;
};

//策略一
class BackDoor: public IStrategy{
public:
    virtual void operate() override{ std::cout << "乔国老开后门" << std::endl; }
};

//策略二
class GreenLight: public IStrategy{
public:
    virtual void operate() override{ std::cout << "吴国太开绿灯" << std::endl; }
};

//策略三
class SunAttack: public IStrategy{
public:
    virtual void operate() override{ std::cout << "孙夫人断后" << std::endl; }
};

//锦囊
class Context{
public:
    Context(IStrategy *strategy):m_strategy{strategy}{}

    void operate(){ m_strategy->operate(); }

private:
    IStrategy *m_strategy;
};

int main()
{
    IStrategy *backDoor      = new BackDoor();
    IStrategy *greenLight    = new GreenLight();
    IStrategy *block         = new SunAttack();

    Context *context = new Context(backDoor);
    context->operate();

    context = new Context(greenLight);
    context->operate();

    context = new Context(block);
    context->operate();

    return 0;
}



 
