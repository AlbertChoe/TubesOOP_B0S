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
    // Constructor
    Item();
    // Constructor user defined
    Item(int id, string code, string name, string type, int price);
    // Destructor
    ~Item();
    // Copy Constructor
    Item(const Item& other);
    // Check if item is empty
    bool isEmpty();
    // Getter
    int getID();
    string getCode();
    string getName();
    string getType();
    int getPrice();
    // Setter
    void setID(int id);
    void setCode(string code);
    void setName(string name);
    void setType(string type);
    void setPrice(int price);
    // Display item code in black
    friend ostream& operator<<(ostream& os, const Item& item);
};

#endif