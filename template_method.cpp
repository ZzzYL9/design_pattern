/*
* 设计模式：模板方法
* 模板方法是基于继承的代码复用技术的，在模板方法模式中，我们可以将相同部分的代码放在父类中，而将不同的代码放入不同的子类中。
* 也就是说我们需要声明一个抽象的父类，将部分逻辑以及具体方法让子类来实现剩余的逻辑，不同的子类可以以不同的方式来实现这些逻辑。
*
* 优点：
* ①模板方法在定义了一组算法，将具体的实现交由子类负责
* ②模板方法模式是一种代码复用技术
* ③模板方法模式导致一种反向的控制结构，通过一个父类调用其子类的操作，通过对子类的扩展增加新的行为，符合”开闭原则“
*
* 缺点：
* ①每一个不同的实现都需要一个子类来实现，导致类的个数增加，使得系统更加庞大
*
* 使用场景：
* ①一次性实现一个算法的不变的部分，并将可变行为留给子类来实现
* ②各子类中公共的行为应被提取出来并集中到一个公共父类中以避免代码重复
* ③控制子类的扩展
*
*/

#include <iostream>

using namespace std;

class Beverage{
public:
    Beverage(){}
    void prepareRecipe()
    {
        boilWater();
        brew();
        pourInCup();
        if(IsWantCondiment())
            addCondiments();
    }
    virtual void brew(){}
    virtual void addCondiments(){}
    virtual bool IsWantCondiment(){ return true; } //钩子函数，所谓钩子，就是一种被声明在抽象类中的方法，但只有空的或默认的实现

    void boilWater(){
        cout << "烧水ing..." << endl;
    }
    void pourInCup(){
        cout << "倒入杯子中..." << endl;
    }

    virtual ~Beverage(){ cout << "Beverage 析构..." << endl; }
};

class Coffee: public Beverage{
public:
    Coffee(){}
    // 这些重载函数的实现最好放在类的外面实现
    void addCondiments() override
    {
        cout << "加糖和牛奶..." << endl;
    }
    void brew() override
    {
        cout << "通过过滤器过滤咖啡..." << endl;
    }

    // 覆盖钩子，提供自己的实现方法
    bool IsWantCondiment() override
    {
        if(GetAnswer() == "y")
            return true;
        else
            return false;
    }

    string GetAnswer()
    {
        string ans;
        do{
            cout << "您是否想要加入condiments？(输入y或者n)" << endl;
            cin >> ans;
            if(ans == "y" || ans == "n")
                break;
        }while(1);
        return ans;
    }

    ~Coffee() override { cout << "Coffee 析构..." << endl; }
};

class Tea: public Beverage{
public:
    Tea(){}
    void addCondiments() override
    {
        cout << "加柠檬..." << endl;
    }
    void brew() override
    {
        cout << "泡茶..." << endl;
    }
    ~Tea() override { cout << "Tea 析构..." << endl;}
};

int main()
{
    Beverage *C = new Coffee();
    C->prepareRecipe();
    cout << endl;
    Beverage *T = new Tea();
    T->prepareRecipe();
    cout << endl << endl;
    delete C;
    delete T;
    return 0;
}
 
