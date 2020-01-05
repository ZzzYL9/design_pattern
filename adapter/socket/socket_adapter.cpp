/*
* 设计模式：适配器模式（对象适配器）
*
* SocketPackage就是成熟的套接字软件包，也就是Adaptee适配者类，
* 包含创建套接字、绑定套接字、监听套接字、连接套接字等成熟方法；
* Socket是目标抽象类Target，定义了客户希望的方法；
* SocketAdapter为适配器类，将成熟软件包里面的方法转为Socket类中客户希望的方法。
*
* SocketAdapter套接字适配器类和SocketPackage套接字包是一种组合的关系，
* 当调用套接字适配器类中的相应方法时，将调用套接字包对应的方法，通过组合的方式，
* 实现对套接字软件包模块的复用。
* 客户端不需要直接操作这个已经成熟的套接字软件包，而是由套接字适配器类进行委托操作，
* 降低了客户端和适配者类的耦合。
*
*/

#include <iostream>
using namespace std;

//成熟的套接字包（可以被复用）
class SocketPackage{
public:
    void CreateSpecificSocket(){
        cout << "创建套接字" << endl;
    }
    void BindSpecificSocket(){
        cout << "绑定套接字" << endl;
    }
    void ListenSpecificSocket(){
        cout << "监听套接字" << endl;
    }
    void ConnectSpecifictSocket(){
        cout << "连接套接字" << endl;
    }
};

//抽象套接字类
class Socket{
public:
    Socket(){}
    virtual ~Socket(){}

    //创建套接字
    virtual void CreateSocket()=0;

    //绑定套接字
    virtual void BindSocket()=0;

    //监听套接字
    virtual void ListenSocket()=0;

    //连接套接字
    virtual void ConnectSocket()=0;
};

//套接字适配器
class SocketAdapter: public Socket{
private:
    SocketPackage *m_pSocketPackage;

public:
    //构造函数，创建一个需要复用的套接字包对象
    SocketAdapter(){
        m_pSocketPackage = new SocketPackage();
    }

    ~SocketAdapter(){
        if(m_pSocketPackage != nullptr){
            delete m_pSocketPackage;
            m_pSocketPackage = nullptr;
        }
    }

    //创建套接字
    void CreateSocket() override{
        m_pSocketPackage->CreateSpecificSocket();
    }

    //绑定套接字
    void BindSocket() override{
        m_pSocketPackage->BindSpecificSocket();
    }

    //监听套接字
    void ListenSocket() override{
        m_pSocketPackage->ListenSpecificSocket();
    }

    //连接套接字
    void ConnectSocket() override{
        m_pSocketPackage->ConnectSpecifictSocket();
    }
};

int main()
{
    //创建套接字适配器对象
    Socket *pSocketAdapter = new SocketAdapter();

    //使用适配器进行套接字操作
    pSocketAdapter->CreateSocket();
    pSocketAdapter->BindSocket();
    pSocketAdapter->ListenSocket();
    pSocketAdapter->ConnectSocket();

    //销毁操作
    delete pSocketAdapter;
    pSocketAdapter = nullptr;

    return 0;
}
 
