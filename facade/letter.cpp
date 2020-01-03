/*
* 设计模式：门面模式
*
* 增加一个 ModenPostOffice 类，负责对一个比较复杂的信件处理过程的封装，然后高层模块只要和它有交互就行。
*
* 扩展性提高了，例：增加一项安全检查，增加了一个Police类，负责对信件进行检查
*
*/

#include <iostream>
using namespace std;

//写信过程接口
class ILetterProcess
{
public:
    virtual void    writeContext(string context) = 0;  //写信内容
    virtual void    fillEnvelope(string address) = 0;  //写信封
    virtual void    letterInotoEnvelope()         = 0;  //信放入信封
    virtual void    sendLetter()                  = 0;  //邮递
};

//写信过程实现
class LetterProcessImpl:public ILetterProcess
{
public:
    virtual void writeContext(string context)
    {
        cout << "write " << context << endl;
    }

    virtual void    fillEnvelope(string address)
    {
        cout << "add " << address << endl;
    }

    virtual void    letterInotoEnvelope()
    {
        cout << "put the letter into envelope" << endl;
    }

    virtual void    sendLetter()
    {
        cout << "send Letter" << endl;
    }
};

class Police
{
public:
    void checkLetter(ILetterProcess *letterProcess)
    {
        cout << "is safe" << endl;
    }
};


class ModenPostOffice
{
public:
    ModenPostOffice()
    {
        this->m_letterProcess = new LetterProcessImpl();
    }
    ~ModenPostOffice()
    {
        delete this->m_letterProcess;
    }
    void    sendLetter(string context, string address)
    {
        this->m_letterProcess->writeContext(context);
        this->m_letterProcess->fillEnvelope(address);
        this->m_letterPolice.checkLetter(this->m_letterProcess);
        this->m_letterProcess->letterInotoEnvelope();
        this->m_letterProcess->sendLetter();
    }

private:
    ILetterProcess *m_letterProcess;
    Police          m_letterPolice;
};

int main()
{
    ModenPostOffice office;
    string address = "sichuan";
    string context = "aaaa";
    office.sendLetter(context, address);

    return 0;
}
 
