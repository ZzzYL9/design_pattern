/*
* 设计模式：职责链模式
*
*
*
*/
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

//请求类LeaveReque
class LeaveRequest{
public:
    LeaveRequest(string leaveName,int leaveDays){
        this->leaveName = leaveName;
        this->leaveDays = leaveDays;
    }

    void setLeaveName(string leaveName){
        this->leaveName = leaveName;
    }

    void setLeaveDays(int leaveDays){
        this->leaveDays = leaveDays;
    }

    string getLeaveName() const{
        return this->leaveName;
    }

    int getLeaveDays() const{
        return this->leaveDays;
    }
private:
    string leaveName;
    int leaveDays;
};

//抽象处理者Leader
class Leader{
public:
    Leader(string name){ this->name = name; }

    void setSuccessor(weak_ptr<Leader> successor){
        this->successor = successor;
    }

    virtual void handleRequest(const LeaveRequest &request) = 0;

protected:
    string name;
    weak_ptr<Leader> successor;
};

//具体处理者Director
class Director: public Leader{
public:
    Director(string name): Leader(name){}

    void handleRequest(const LeaveRequest &request) override{
        //处理请求
        if(request.getLeaveDays()<3){
            cout << "主任" << this->name << "审批员工" << request.getLeaveName() << "的请假条，请假天数为"
                 << request.getLeaveDays() << "天" << endl;
        }else{
            if(this->successor.lock()!=nullptr){
                this->successor.lock()->handleRequest(request);
            }
        }
    }
};

//具体处理者Manager
class Manager: public Leader{
public:
    Manager(string name) : Leader(name){}

    void handleRequest(const LeaveRequest &request)
    {
        //处理请求
        if(request.getLeaveDays()<10){
            cout << "经理" << this->name << "审批员工" << request.getLeaveName() << "的请假条，请假天数为"
                 << request.getLeaveDays() << "天." << endl;
        }else{
            //无法处理此请求，则交给上级处理
            if(this->successor.lock()!=nullptr){
                this->successor.lock()->handleRequest(request);
            }
        }
    }

};

//具体处理者GeneralManager
class GeneralManager : public Leader{
public:
    GeneralManager(string name) : Leader(name){

    }

    void handleRequest(const LeaveRequest &request){
        //处理请求
        if(request.getLeaveDays()<30){
            cout << "总经理" << this->name << "审批员工" << request.getLeaveName() << "的请假条，请假天数为"
                 << request.getLeaveDays() << "天." << endl;
        }else{
            cout << "莫非" << request.getLeaveName() << "想辞职,居然请假"
                 << request.getLeaveDays() << "天." << endl;
        }
    }

};

//客户端测试
int main(void){
    shared_ptr<Leader> objDirector,objManager,objGeneralManager;

    //创建处理者
    objDirector = make_shared<Director>("王明");
    objManager = make_shared<Manager>("赵强");
    objGeneralManager = make_shared<GeneralManager>("李波");

    //设置上级
    objDirector->setSuccessor(objManager);
    objManager->setSuccessor(objGeneralManager);

    //职责链处理请求
    shared_ptr<LeaveRequest> lr1 = make_shared<LeaveRequest>("张三",2);
    objDirector->handleRequest(*lr1);

    shared_ptr<LeaveRequest> lr2 = make_shared<LeaveRequest>("李四",5);
    objDirector->handleRequest(*lr2);

    shared_ptr<LeaveRequest> lr3 = make_shared<LeaveRequest>("王五",15);
    objDirector->handleRequest(*lr3);

    shared_ptr<LeaveRequest> lr4 = make_shared<LeaveRequest>("赵六",45);
    objDirector->handleRequest(*lr4);

    return 0;
}
 
