/*
* 设计模式：中介者模式
*
* 定义一个中介对象来封装系列对象之间的交互
*
*/

#include <iostream>
using namespace std;

class Mediator;

//Collegue抽象类
class Person{
public:
    Person(string name, int sex, int condition, Mediator* mediator):m_name{name}, m_sex{sex}, m_condition{condition}, m_mediator{mediator}{}
    virtual ~Person(){}

    int getCondition(){
        return m_condition;
    }

    int getSex(){
        return m_sex;
    }

    string getName(){
        return m_name;
    }

    virtual void getParter(Person* p)=0;

protected:
    string m_name;
    int m_sex;
    int m_condition;
    Mediator* m_mediator;
};

//Mediator类
class Mediator{
public:
    void getParter(){
        if(man->getSex() == woman->getSex()){
            cout << "I am not gay" << endl;
            return;
        }
        if(man->getCondition() == woman->getCondition()){
            cout << man->getName() << "==" << woman->getName() << endl;
        }else{
            cout << man->getName() << "!=" << woman->getName() << endl;
        }
    }

    void setMan(Person* man){
        this->man = man;
    }

    void setWoman(Person* woman){
        this->woman = woman;
    }

private:
    Person* man;
    Person* woman;
};

//ConcreteColleague具体同事类1
class Woman:public Person{
public:
    Woman(string name, int sex, int condition, Mediator* mediator): Person(name, sex, condition, mediator){}

    int getCondition() {
        return m_condition;
    }
    virtual void getParter(Person* p) {
        m_mediator->setWoman(this);
        m_mediator->setMan(p);
        m_mediator->getParter();
    }
};

//ConcreteColleague具体同事类2
class Man:public Person{
public:
    Man(string name, int sex, int condition, Mediator* mediator): Person(name, sex, condition, mediator){}

    int getCondition() {
        return m_condition;
    }
    virtual void getParter(Person* p) {
        m_mediator->setWoman(this);
        m_mediator->setMan(p);
        m_mediator->getParter();
    }
};

int main()
{
    Mediator* mediator = new Mediator();

    Person* woman1 = new Woman("woman1", 0, 5, mediator);
    Person* woman2 = new Woman("woman2", 0, 5, mediator);
    Person* man1 = new Man("man1", 1, 6, mediator);
    Person* man2 = new Man("man2", 1, 5, mediator);

    woman1->getParter(woman2);
    woman2->getParter(man1);
    woman2->getParter(man2);

    delete woman1;
    delete woman2;
    delete man1;
    delete man2;
    delete mediator;

    woman1=nullptr;
    woman2=nullptr;
    man1=nullptr;
    man2=nullptr;
    mediator=nullptr;

    return 0;
}
 
