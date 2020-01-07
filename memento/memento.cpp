/*
* 设计模式：备忘录模式
*
*
*
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

//备忘录
class STMemento{
private:
    int m_iVitality;
public:
    STMemento(){}
    STMemento(int iVitality):m_iVitality{iVitality}{}

    int GetVitality() const{
        return m_iVitality;
    }

};

//原发器：创建一个备忘录
class STOriginator{
private:
    int iVitality;
    string name;
public:
    STOriginator(string strName, int iVit): iVitality{iVit}, name{strName}{}

    //创建备忘录并记录当前时刻它的内部状态
    STMemento* SaveState(){
        return new STMemento(iVitality);
    }

    //使用备忘录恢复内部状态
    void RecoverState(const STMemento* stMemento){
        this->iVitality = stMemento->GetVitality();
    }

    void SetVitality(int iVit){
        this->iVitality = iVit;
    }

    void Show(){
        cout << "Name:" << name << endl;
        cout << "Live:" << iVitality << endl;
    }
};

//负责保存好备忘录Memento
class STCareTaker{
private:
    vector<STMemento*> vecStMemento;

public:
    void AddMemento(STMemento* stMemento){
        vecStMemento.push_back(stMemento);
    }

    STMemento* getMemento(int Iindex){
        if(Iindex >= vecStMemento.size())
            return NULL;
        else
            return vecStMemento[Iindex];
    }
};

int main()
{
    STOriginator* pstOriginator = new STOriginator("xxx", 100);
    cout << "原始状态" << endl;
    pstOriginator->Show();

    STCareTaker* pstCareTaker = new STCareTaker();
    pstCareTaker->AddMemento(pstOriginator->SaveState());

    pstOriginator->SetVitality(50);
    cout << "战斗后状态:" << endl;
    pstOriginator->Show();

    pstOriginator->RecoverState(pstCareTaker->getMemento(0));
    cout << "归档后状态：" << endl;
    pstOriginator->Show();

    return 0;
}
 
