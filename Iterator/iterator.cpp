/*
* 设计模式：迭代器模式
*
* 提供一种方法顺序访问一个聚合对象中的各个元素，而又不暴露该对象的内部表示。
*
*/
#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Iterator
{
public:
    Iterator(){};
    virtual ~Iterator(){};
    virtual string First() = 0;
    virtual string Next() = 0;
    virtual string GetCur() = 0;
    virtual bool IsEnd() = 0;
};

class Aggregate
{
public:
    virtual int Count() = 0;
    virtual void Push(const string& strValue)=0;
    virtual string Pop(const int nIndex)=0;
    virtual Iterator* CreateIterator() = 0;
};

class ConcreteIterator : public Iterator
{
public:
    ConcreteIterator(Aggregate* pAggregate):m_nCurrent(0),Iterator()
    {
        m_Aggregate = pAggregate;
    }
    string First()
    {
        return m_Aggregate->Pop(0);
    }
    string Next()
    {
        string strRet;
        m_nCurrent++;
        if(m_nCurrent < m_Aggregate->Count())
        {
            strRet = m_Aggregate->Pop(m_nCurrent);
        }
        return strRet;
    }
    string GetCur()
    {
        return m_Aggregate->Pop(m_nCurrent);
    }
    bool IsEnd()
    {
        return ((m_nCurrent >= m_Aggregate->Count()) ? true: false);
    }
private:
    Aggregate* m_Aggregate{nullptr};
    int m_nCurrent{0};
};

class ConcreteAggregate : public Aggregate
{
public:
    ConcreteAggregate():m_pIterator(NULL)
    {
        m_vecItems.clear();
    }
    ~ConcreteAggregate()
    {
        if(NULL != m_pIterator)
        {
            delete m_pIterator;
            m_pIterator = NULL;
        }
    }
    Iterator* CreateIterator()
    {
        if(NULL == m_pIterator)
        {
            m_pIterator = new ConcreteIterator(this);
        }
        return m_pIterator;
    }
    int Count()
    {
        return m_vecItems.size();
    }
    void Push(const string& strValue)
    {
        m_vecItems.push_back(strValue);
    }
    string Pop(const int nIndex)
    {
        string strRet;
        if(nIndex < Count())
        {
            strRet = m_vecItems[nIndex];
        }
        return strRet;
    }
private:
    vector<string> m_vecItems;
    Iterator* m_pIterator;


};

int main()
{
    ConcreteAggregate* pName = NULL;
    pName = new ConcreteAggregate();
    if(NULL != pName)
    {
        pName->Push("1");
        pName->Push("2");
        pName->Push("3");
    }
    Iterator* iter = NULL;
    iter = pName->CreateIterator();
    if(NULL != iter)
    {
        string strItem = iter->First();
        while(!iter->IsEnd())
        {
            cout << iter->GetCur() << " is ok" << endl;
            iter->Next();
        }
    }

    return 0;
}
 
