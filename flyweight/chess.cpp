/*
* 设计模式：享元模式
*
* 对于棋子来说，我们不用放一个棋子就new一个棋子对象，只需要在需要的时候，去请求获得对应的棋子对象，如果没有，就new一个棋子对象；如果有了，就直接返回棋子对象。
* 这里以五子棋为例子，进行分析，当玩家在棋盘上放入第一个白色棋子时，此时由于没有白色棋子，所以就new一个白色棋子；
* 当另一个玩家放入第一个黑色棋子时，此时由于没有黑色棋子，所以就需要new一个黑色棋子；
* 当玩家再次放入一个白色棋子时，就去查询是否有已经存在的白色棋子对象，
* 由于第一次已经new了一个白色棋子对象，所以，现在不会再次new一个白色棋子对象，
* 而是返回以前new的白色棋子对象；对于黑色棋子，亦是同理；
* 获得了棋子对象，我们只需要设置棋子的不同棋盘位置即可
*/

#include <iostream>
#include <map>
#include <vector>
using namespace std;

//坐标结构体
typedef struct pointTag
{
    int x;
    int y;

    pointTag(){}
    pointTag(int a, int b)
    {
        x = a;
        y = b;
    }

    bool operator <(const pointTag& other) const
    {
        if (x < other.x)
        {
            return true;
        }
        else if (x == other.x)
        {
            return y < other.y;
        }

        return false;
    }
}POINT;

//棋子颜色
typedef enum PieceColorTag
{
    BLACK,
    WHITE
}PIECECOLOR;

//棋子抽象类
class CPiece
{
public:
    CPiece(PIECECOLOR color) : m_color(color){}
    PIECECOLOR GetColor() { return m_color; }

    // 设置外部状态
    void SetPoint(POINT point) { m_point = point; }
    POINT GetPoint() { return m_point; }

protected:
    // 内部状态
    PIECECOLOR m_color;

    // 外部状态
    POINT m_point;
};

class CGomoku : public CPiece
{
public:
    CGomoku(PIECECOLOR color) : CPiece(color){}
};

//棋子享元工厂，构造一个池容器，同时从池中获得对象的方法
class CPieceFactory
{
public:
    CPiece *GetPiece(PIECECOLOR color)
    {
        CPiece *pPiece = nullptr;
        //如果保存棋子颜色（内部状态）的容器是空的，则新建一个具有color颜色的棋子对象并放入容器中
        if (m_vecPiece.empty())
        {
            pPiece = new CGomoku(color);
            m_vecPiece.push_back(pPiece);
        }
        else
        {
            //如果容器中有可共享对象，则遍历容器，查看是否有传入的color相同的状态的对象
            for (vector<CPiece *>::iterator it = m_vecPiece.begin(); it != m_vecPiece.end(); ++it)
            {
                //如果找到颜色相同的对象，则直接将该对象拷贝并返回
                if ((*it)->GetColor() == color)
                {
                    pPiece = *it;
                    break;
                }
            }
            //如果没有相同颜色的棋子对象，则新建一个对象保存在容器中并同时将该对象返回出去
            if (pPiece == nullptr)
            {
                pPiece = new CGomoku(color);
                m_vecPiece.push_back(pPiece);
            }
        }
        return pPiece;
    }

    ~CPieceFactory()
    {
        for (vector<CPiece *>::iterator it = m_vecPiece.begin(); it != m_vecPiece.end(); ++it)
        {
            if (*it != nullptr)
            {
                delete *it;
                *it = nullptr;
            }
        }
    }

private:
    vector<CPiece *> m_vecPiece; //保存暂时只有颜色没有坐标的棋子对象
};

//棋盘，保存了放置的黑白棋子，这就相当于在外部保存了共享对象的外部状态
class CChessboard
{
public:
    void Draw(CPiece *piece)
    {
        if (piece->GetColor())
        {
            cout<<"Draw a White"<<" at ("<<piece->GetPoint().x<<","<<piece->GetPoint().y<<")"<<endl;
        }
        else
        {
            cout<<"Draw a Black"<<" at ("<<piece->GetPoint().x<<","<<piece->GetPoint().y<<")"<<endl;
        }
        //保存下来，方便ShowAllPieces()函数使用
        m_mapPieces.insert(pair<POINT, CPiece *>(piece->GetPoint(), piece));
    }

    void ShowAllPieces()
    {
        for (map<POINT, CPiece *>::iterator it = m_mapPieces.begin(); it != m_mapPieces.end(); ++it)
        {
            if (it->second->GetColor())
            {
                cout<<"("<<it->first.x<<","<<it->first.y<<") has a White chese."<<endl;
            }
            else
            {
                cout<<"("<<it->first.x<<","<<it->first.y<<") has a Black chese."<<endl;
            }
        }
    }

private:
    map<POINT, CPiece *> m_mapPieces;
};

int main()
{
    CPieceFactory *pPieceFactory = new CPieceFactory();
    CChessboard *pCheseboard = new CChessboard();

    // The player1 get a white piece from the pieces bowl
    CPiece *pPiece = pPieceFactory->GetPiece(WHITE);
    pPiece->SetPoint(POINT(2, 3));
    pCheseboard->Draw(pPiece);

    // The player2 get a black piece from the pieces bowl
    pPiece = pPieceFactory->GetPiece(BLACK);
    pPiece->SetPoint(POINT(4, 5));
    pCheseboard->Draw(pPiece);

    // The player1 get a white piece from the pieces bowl
    pPiece = pPieceFactory->GetPiece(WHITE);
    pPiece->SetPoint(POINT(2, 4));
    pCheseboard->Draw(pPiece);

    // The player2 get a black piece from the pieces bowl
    pPiece = pPieceFactory->GetPiece(BLACK);
    pPiece->SetPoint(POINT(3, 5));
    pCheseboard->Draw(pPiece);

    /*......*/

    //Show all cheses
    cout<<"Show all cheses"<<endl;
    pCheseboard->ShowAllPieces();

    if (pCheseboard != nullptr)
    {
        delete pCheseboard;
        pCheseboard = nullptr;
    }
    if (pPieceFactory != nullptr)
    {
        delete pPieceFactory;
        pPieceFactory = nullptr;
    }
}
 
