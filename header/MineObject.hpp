#ifndef MINEOBJECT_HPP
#define MINEOBJECT_HPP

#include "../src/pcolor/pcolor.hpp"
#include <iostream> 
using namespace std;

class MineObject {
private:
    string type;
    bool opened;
public:
    // Constructor
    MineObject();
    //Constructor user defined
    MineObject(string type);
    // Destructor
    ~MineObject();
    // Copy Constructor
    MineObject(const MineObject& other);
    void setClose();
    void setOpen();
    void setDiamond();
    void setBomb();
    string getType();
    bool isOpened();
    friend ostream& operator<<(ostream& os, const MineObject& mo);
};


#endif