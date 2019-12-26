#ifndef BAG_H
#define BAG_H

#include <iostream>

using namespace std;

class CBag{
public:
    CBag(){}
    virtual ~CBag(){}

    virtual void operation(){ cout << "普通包" << endl; }
};

#endif // BAG_H
