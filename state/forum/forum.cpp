/*
* 设计模式：状态模式
*
* 从类图可知，ForumnAccount（论坛账户类）互相关联AbstractState（抽象状态类），
* 账户类的downloadFile、writeNote和replyNote等操作都由状态类的相关函数来操作，方便进行状态之前的转换。
*
* 论坛有三种账号等级状态
*
* 每种账号等级能够执行的操作不同，避免使用if-else
*
* 将账号状态抽象出一个状态类,将三个状态分为三个状态类，每个类执行各自的操作
*
* 一个类集中管理一个状态；在多状态的情况下，简化了程序的维护和管理，让程序结构简明化，同时也易于扩展。
*
* 避免写成以下形式：
*
* 。。。。。。。。
* void downloadFile(int score){
*   if(state == primary){
*
*   }else if(state == middle){
*
*   }else if()
* 。。。。。。。。。。
* }
*
*/

#include <iostream>
using namespace std;

class AbstractState;

//Context类
//环境类ForumAccount（论坛账号类)
class ForumAccount{
public:
    ForumAccount(string name);

    void setState(AbstractState *state){
        this->state = state;
    }

    AbstractState* getState(){
        return this->state;
    }

    string getName(){
        return this->m_name;
    }

    void downloadFile(int score);

    void writeNote(int score);

    void replyNote(int score);

private:
    AbstractState *state;
    string m_name;
};

//抽象类AbstractState(账号状态类)
class AbstractState{
public:
    virtual void checkState(int score)=0;

    virtual void downloadFile(int score){
        cout << acc->getName() << "下载文件，扣除" << score << "积分." << endl;
        this->point -= score;
        checkState(score);
        cout << "剩余积分为：" << this->point << ",当前级别为：" << acc->getState()->getStateName() << "。" <<  endl;
    }

    virtual void writeNote(int score){
        cout << acc->getName() << "发布留言,增加" << score << "积分。" << endl;
        this->point += score;
        checkState(score);
        cout << "剩余积分为：" << this->point << "，当前级别为："  << acc->getState()->getStateName() << "。" <<  endl;
    }

    virtual void replyNote(int score){
        cout << acc->getName() << "回复留言，增加" << score << "积分。" << endl;
        this->point += score;
        checkState(score);
        cout << "剩余积分为：" << this->point << "，当前级别为："  << acc->getState()->getStateName() << "。" <<  endl;
    }

    void setPoint(int point){
        this->point = point;
    }

    int getPoint(){
        return this->point;
    }

    void setStateName(string stateName){
        this->stateName = stateName;
    }

    ForumAccount* getAcc(){
        return acc;
    }

    string getStateName(){
        return stateName;
    }

protected:
    ForumAccount *acc;
    int point;
    string stateName;
};

//具体状态类PrimaryState（新手状态类）
class PrimaryState: public AbstractState{
public:
    PrimaryState(AbstractState *state){
        this->acc = state->getAcc();
        this->point = state->getPoint();
        this->stateName = "新手";
    }

    PrimaryState(ForumAccount *acc){
        this->acc = acc;
        this->point = 0;
        this->stateName = "新手";
    }

    void downloadFile(int score) override{
        cout << "对不起，" << acc->getName() << ",您没有下载文件的权限" << endl;
    }

    void checkState(int score) override;
};

//高手状态类
class MiddleState: public AbstractState{
public:
    MiddleState(AbstractState *state){
        this->acc = state->getAcc();
        this->point = state->getPoint();
        this->stateName = "高手";
    }

    void writeNote(int score) override{
        cout << acc->getName() << "发布留言，增加" << score << "*2个积分" << endl;
        this->point += score*2;
        checkState(score);
        cout << "剩余积分为：" << this->point << ",当前级别为" << acc->getState()->getStateName() <<endl;
    }

    void checkState(int score) override;
};

//专家状态类
class HighState: public AbstractState{
public:
    HighState(AbstractState *state){
        this->acc = state->getAcc();
        this->point = state->getPoint();
        this->stateName = "专家";
    }

    void writeNote(int score){
        cout << acc->getName() << "发布留言，增加" << score << "*2个积分。" << endl;
        this->point += score*2;
        checkState(score);
        cout << "剩余积分为：" << this->point << "，当前级别为："  << acc->getState()->getStateName() << "。" <<  endl;
    }

    void downloadFile(int score){
        cout << acc->getName() << "下载文件，扣除" << score << "/2个积分。" << endl;
        this->point -= score/2;
        checkState(score/2);
        cout << "剩余积分为：" << this->point << "，当前级别为："  << acc->getState()->getStateName() << "。" <<  endl;
    }

    void checkState(int score) override;
};

ForumAccount::ForumAccount(string name){
    this->m_name = name;
    this->state = new PrimaryState(this);
    cout << this->m_name << "注册成功!" << endl;
}

void ForumAccount::downloadFile(int score){
    state->downloadFile(score);
}

void ForumAccount::writeNote(int score){
    state->writeNote(score);
}

void ForumAccount::replyNote(int score){
    state->replyNote(score);
}

//**************************************
//存在内存泄露，可改为智能指针
void PrimaryState::checkState(int score)
{
    if(point >= 1000){
        acc->setState(new HighState(this));
    }else if(point >= 100){
        acc->setState(new MiddleState(this));
    }
}

void MiddleState::checkState(int score)
{
    if(point >= 1000){
        acc->setState(new HighState(this));
    }else if(point < 0){
        cout << "余额不足，操作失败!" << endl;
        this->point += score;
    }else if(point <= 100){
        acc->setState(new PrimaryState(this));
    }
}

void HighState::checkState(int score)
{
    if(point<0){
            cout << "余额不足，操作失败!" << endl;
            this->point += score;
        }else if(point<=1000){
            acc->setState(new MiddleState(this));
        }else if(point<=100){
            acc->setState(new PrimaryState(this));
    }
}
//*****************************************************

//客户端测试
int main(void){
    //注册用户
    ForumAccount account("张三");

    //操作
    account.writeNote(20);
    account.downloadFile(20);
    account.replyNote(100);
    account.writeNote(40);
    account.downloadFile(80);
    account.downloadFile(150);
    account.writeNote(1000);
    account.downloadFile(80);
    return 0;
}
