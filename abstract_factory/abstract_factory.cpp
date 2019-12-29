/*
* 设计模式：抽象工厂
*
* 当生产一系列的产品时，为保证产品是一个系列的，直接将每一个产品系列封装为一个工厂，该工厂生产的产品只能是该系列的
* 产品。
*/

#include <iostream>
using namespace std;

//键盘抽象类
class KeyBoard{
public:
    KeyBoard(){}
    virtual void show()=0;
    virtual ~KeyBoard(){}
};

class KeyBoardMicro: public KeyBoard{
public:
    void show() override{
        cout << "微软的键盘" << endl;
    }
};

class KeyBoardLenovo: public KeyBoard{
public:
    void show() override{
        cout <<"联想的键盘" << endl;
    }
};

//鼠标抽象类
class Mouse{
public:
    Mouse(){}
    virtual void show()=0;
    virtual ~Mouse(){}
};

class MouseMicro: public Mouse{
public:
    void show() override{
        cout << "微软的鼠标" << endl;
    }
};

class MouseLenovo: public Mouse{
public:
    void show() override{
        cout << "联想的鼠标" << endl;
    }
};

//抽象工厂类
class Factory{
public:
    Factory(){}
    virtual ~Factory(){}

    virtual KeyBoard* createKeyBoard() = 0;
    virtual Mouse* createMouse() = 0;

};

class FactoryMicro: public Factory{
public:
    KeyBoard * createKeyBoard() override{
        return new KeyBoardMicro();
    }

    Mouse * createMouse() override{
        return new MouseMicro();
    }
};

class FactoryLenovo: public Factory{
public:
    KeyBoard * createKeyBoard() override{
        return new KeyBoardLenovo();
    }

    Mouse * createMouse() override{
        return new MouseLenovo();
    }
};

int main()
{
    Factory *p = new FactoryMicro();
    KeyBoard *pKeyBoard = p->createKeyBoard();
    Mouse *pMouse = p->createMouse();
    pKeyBoard->show();
    pMouse->show();

    delete pKeyBoard;
    delete pMouse;
    delete p;

    p = new FactoryLenovo();
    pKeyBoard = p->createKeyBoard();
    pMouse = p->createMouse();
    pKeyBoard->show();
    pMouse->show();

    delete pMouse;
    delete pKeyBoard;
    delete p;

    return 0;
}
 
