/*
* 设计模式：原型模式
*
* 通过拷贝构造函数设计原型模式，虽然C++有默认的拷贝构造函数，但是 默认的拷贝构造函数只提供基本的值拷贝，
* 如果有在堆区开辟空间的成员呢？
* 所以我们要提供自己的拷贝构造函数进行深拷贝，
* 方便用户，还应该提供一个clone方法（实际就是去调用拷贝构造函数）
*
*/

#include <iostream>
#include <cstring>
using namespace std;

class Resume{
    friend ostream& operator << (ostream&, Resume& resume);
public:
    //默认构造函数
    Resume(){}
    //构造函数
    Resume(char* name)
    {
        this->m_name = new char[strlen(name) + 1]{ 0 };
        strcpy(this->m_name, name);
    }

    //拷贝构造函数(深拷贝)
    Resume(const Resume& resume)
    {
        this->m_sex = resume.m_sex;
        this->m_age = resume.m_age;
        this->m_workexper = resume.m_workexper;
        this->m_worktime = resume.m_worktime;
        this->m_name = new char[strlen(resume.m_name) + 1]{0};
        strcpy(this->m_name, resume.m_name);
    }

    void SetSex_Age(string sex, int age){
        this->m_sex = sex;
        this->m_age = age;
    }
    void Set_Workexper(string exper, string worktime){
        this->m_workexper = exper;
        this->m_worktime = worktime;
    }

    virtual Resume *clone()=0;

    virtual ~Resume(){
        if(m_name != nullptr){
            delete m_name;
        }
    }

private:
    char* m_name;
    string m_sex;
    string m_workexper;
    string m_worktime;
    int m_age;
};

//重载操作符
ostream& operator << (ostream&, Resume& resume)
{
    cout << "姓名：" << resume.m_name << endl;
    cout << "性别：" << resume.m_sex << endl;
    cout << "年龄：" << resume.m_age << endl;
    cout << "工作经历：" << endl << resume.m_worktime << "," << resume.m_workexper << endl;
    return cout;
}

class ResumeA: public Resume{
public:
    ResumeA(){}
    ResumeA(char* s): Resume(s){}
    ~ResumeA(){}

    Resume *clone(){
//        ResumeA *p = new ResumeA();
//        *p = *this;
//        return p;
        //执行拷贝构造函数
        return new ResumeA(*this);
    }

};

class ResumeB: public Resume{
public:
    ResumeB(){}
    ResumeB(char* s): Resume(s){}
    ~ResumeB(){}

    Resume *clone(){
//        ResumeB *p = new ResumeB();
//        *p = *this;
//        return p;
        return new ResumeB(*this);
    }
};

int main()
{
    Resume *r1 = new ResumeA("A");
    Resume *r2 = new ResumeB("B");
    r1->SetSex_Age("男", 16);
    r1->Set_Workexper("action", "1998-2010");
    r2->SetSex_Age("女", 23);
    r2->Set_Workexper("hah", "2001-2019");
    Resume *r3 = r1->clone();
    Resume *r4 = r2->clone();

    cout << *r1 << endl;
    cout << *r2 << endl;
    //删除r1,r2
    delete r1; delete r2;
    r1 = r2 = nullptr;
    //深拷贝所以对r3,r4无影响
    cout << *r3 << endl;
    cout << *r4 << endl;
    delete r3; delete r4;
    r3 = r4 = nullptr;
}

