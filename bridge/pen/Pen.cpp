/*
* 设计模式之桥接模式
*
* 场景：将毛笔的笔的大小作为抽象部分与作为实现部分的毛笔颜色相分离
*/
#include <iostream>
using namespace std;

//实现类接口（颜色）
class Color{
public:
    Color(){}
    virtual void bepaint(string penType, string name) = 0;
    virtual ~Color(){}
};

//具体实现类Red
class Red: public Color{
public:
    void bepaint(string penType, string name) override{
        cout << penType + "红色的" + name + "." << endl;
    }
};

//具体实现类Green
class Green: public Color{
public:
    void bepaint(string penType, string name) override{
        cout << penType + "绿色的" + name + "." << endl;
    }
};

//具体实现类Blue
class Blue: public Color{
public:
    void bepaint(string penType, string name) override{
        cout << penType + "蓝色的" + name + "." << endl;
    }

};

//具体实现类White
class White: public Color{
public:
    void bepaint(string penType, string name) override{
        cout << penType + "白色的" + name + "." << endl;
    }
};

//具体实现类Black
class Black: public Color{
public:
    void bepaint(string penType, string name) override{
        cout << penType + "黑色的" + name + "." << endl;
    }
};

//抽象类Pen
class Pen{
public:
    Pen(){}
    virtual void draw(string name) = 0;
    void setColor(Color* color){
        m_color = color;
    }
    virtual ~Pen(){}
protected:
    Color* m_color;
};

//扩充抽象类BigPen
class BigPen: public Pen{
public:
    void draw(string name) override{
        string penType = "大号毛笔绘制";
        m_color->bepaint(penType, name);
    }
};

//扩充抽象类SmallPen
class Smallpen: public Pen{
public:
    void draw(string name) override{
        string penType = "小号毛笔绘制";
        m_color->bepaint(penType, name);
    }
};

//扩充抽象类MiddlePen
class MiddlePen: public Pen{
public:
    void draw(string name) override{
        string penType = "中号毛笔绘制";
        m_color->bepaint(penType, name);
    }
};

int main()
{
    Color *color = new Red();
    Pen *pen = new Smallpen();
    pen->setColor(color);
    pen->draw("苹果");

    color = new Blue();
    pen = new MiddlePen();
    pen->setColor(color);
    pen->draw("蓝精灵");

    delete color;
    delete pen;

    return 0;
}
