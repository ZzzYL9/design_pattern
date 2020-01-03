/*
* 设计模式：单例模式
*
*Windows的Task Manager（任务管理器）就是很典型的单例模式，你不能同时打开两个任务管理器。Windows的回收站也是同理。
*应用程序的日志应用，一般都可以用单例模式实现，只能有一个实例去操作文件。
*读取配置文件，读取的配置项是公有的，一个地方读取了所有地方都能用，没有必要所有的地方都能读取一遍配置。
*数据库连接池，多线程的线程池。
*/

#include <iostream>
using namespace std;

//第一种
//*************************************************************
//懒汉式单例，可能会有线程安全问题：
//class Singleton{
//public:
//    static Singleton *GetInstance()
//    {
//        if(m_Instance == nullptr){ //判断是否第一次调用
//            //使用多线程时可能会造成两个线程同时执行下一句new
//            m_Instance = new Singleton();
//        }
//        return m_Instance;
//    }

//    static void DestoryInstance()
//    {
//        if(m_Instance != nullptr){
//            delete m_Instance;
//            m_Instance = nullptr;
//        }
//    }

//    int GetTest(){ return m_Test; }

//private:
//    Singleton(){ m_Test = 10; }
//    static Singleton *m_Instance;
//    int m_Test;
//};

//Singleton *Singleton::m_Instance = nullptr;

//int main()
//{
//    Singleton *singletonObj = Singleton::GetInstance();
//    cout << singletonObj->GetTest() << endl;
//    Singleton::DestoryInstance();
//    return 0;
//}

//********************************************************************

//第二种
//****************************************************************
//线程安全，锁的代价过高
//每次调用getInstance()都会加锁释放锁，而这个步骤只有在第一次new Singleton()才是有必要的，只要m_instance被创建出来了，不管多少线程同时访问，使用if (m_instance == nullptr) 进行判断都是足够的（只是读操作，不需要加锁），没有线程安全问题，加了锁之后反而存在性能问题。
//class Singleton{
//public:
//    static Singleton *GetInstance()
//    {
//        Lock(); // C++没有直接的Lock操作，请使用其它库的Lock，比如Boost，此处仅为了说明
//        if (m_Instance == NULL )
//        {
//            m_Instance = new Singleton ();
//        }
//        UnLock(); // C++没有直接的Lock操作，请使用其它库的Lock，比如Boost，此处仅为了说明

//        return m_Instance;
//    }

//    static void DestoryInstance()
//    {
//        if (m_Instance != NULL )
//        {
//            delete m_Instance;
//            m_Instance = NULL ;
//        }
//    }

//    int GetTest()
//    {
//        return m_Test;
//    }

//private:
//    Singleton(){ m_Test = 0; }
//    static Singleton *m_Instance;
//    int m_Test;
//};

//Singleton *Singleton ::m_Instance = NULL;

//int main(int argc , char *argv [])
//{
//    Singleton *singletonObj = Singleton ::GetInstance();
//    cout<<singletonObj->GetTest()<<endl;
//    Singleton ::DestoryInstance();

//    return 0;
//}

//****************************************************************

//第三种
//****************************************************************
//双检查锁，由于内存读写reorder导致不安全
class Singleton{
public:
    static Singleton *GetInstance()
    {
        //先判断是不是初始化了，如果初始化过，就再也不会使用锁了
        if (m_Instance == NULL )
        {
            Lock(); // C++没有直接的Lock操作，请使用其它库的Lock，比如Boost，此处仅为了说明
            if (m_Instance == NULL )
            {
                m_Instance = new Singleton ();
            }
            UnLock(); // C++没有直接的Lock操作，请使用其它库的Lock，比如Boost，此处仅为了说明
        }
        return m_Instance;
    }

    static void DestoryInstance()
    {
        if (m_Instance != NULL )
        {
            delete m_Instance;
            m_Instance = NULL ;
        }
    }

    int GetTest()
    {
        return m_Test;
    }

private:
    Singleton(){ m_Test = 0; }
    static Singleton *m_Instance;
    int m_Test;
};

Singleton *Singleton ::m_Instance = NULL;

int main(int argc , char *argv [])
{
    Singleton *singletonObj = Singleton ::GetInstance();
    cout<<singletonObj->GetTest()<<endl;
    Singleton ::DestoryInstance();

    return 0;
}

//********************************************************************

//第四种
//C++版本的跨平台实现
// atomic c++11中提供的原子操作
//std::atomic<Singleton*> Singleton::m_instance;
//std::mutex Singleton::m_mutex;

/*
* std::atomic_thread_fence(std::memory_order_acquire);
* std::atomic_thread_fence(std::memory_order_release);
* 这两句话可以保证他们之间的语句不会发生乱序执行。
*/
//Singleton* Singleton::getInstance() {
//    Singleton* tmp = m_instance.load(std::memory_order_relaxed);
//    std::atomic_thread_fence(std::memory_order_acquire);//获取内存fence
//    if (tmp == nullptr) {
//        std::lock_guard<std::mutex> lock(m_mutex);
//        tmp = m_instance.load(std::memory_order_relaxed);
//        if (tmp == nullptr) {
//            tmp = new Singleton;
//            std::atomic_thread_fence(std::memory_order_release);//释放内存fence
//            m_instance.store(tmp, std::memory_order_relaxed);
//        }
//    }
//    return tmp;
//}
 
