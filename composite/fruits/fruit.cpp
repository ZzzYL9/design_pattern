/*
* 设计模式：组合模式
*
*
*
*/

#include <iostream>
#include <list>
using namespace std;

//抽象构建类MyElement
class MyElement{
public:
    virtual void eat()=0;
};

//叶子构件类Apple
class Apple: public MyElement{
public:
    void eat() override{
        cout << "吃苹果！" << endl;
    }
};

//叶子构件类Banana
class Banana: public MyElement{
public:
    void eat() override{
        cout  << "吃香蕉！" << endl;
    }
};

//叶子构件类Pear
class Pear: public MyElement{
public:
    void eat() override{
        cout << "吃梨子！" << endl;
    }
};

//容器构件类Plate
class Plate: public MyElement{
public:
    void add(MyElement *element){
        ls.push_back(element);
    }

    void remove(MyElement *element){
        ls.remove(element);
    }

    void eat() override{
        for(auto i : ls){
            i->eat();
        }
    }

private:
    list<MyElement*> ls;
};

int main()
{
    MyElement *obj1,*obj2,*obj3,*obj4,*obj5;
    Plate *plate1,*plate2,*plate3;

    obj1 = new Apple();
    obj2 = new Pear();
    plate1 = new Plate();
    plate1->add(obj1);
    plate1->add(obj2);

    obj3 = new Banana();
    obj4 = new Banana();
    plate2 = new Plate();
    plate2->add(obj3);
    plate2->add(obj4);

    obj5 = new Apple();
    plate3 = new Plate();
    plate3->add(plate1);
    plate3->add(plate2);
    plate3->add(obj5);

    plate3->eat();

    delete obj1;
    delete obj2;
    delete obj3;
    delete obj4;
    delete obj5;

    return 0;

}
