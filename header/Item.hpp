#ifndef ITEM_HPP
#define ITEM_HPP

#include <iostream>
using namespace std;

class Item {
protected:
    int id;
    string code;
    string name;
    string type;
    int price;
public:
    friend ostream& operator<<(ostream& os, const Item& item);
};

#endif