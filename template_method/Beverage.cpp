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
 
