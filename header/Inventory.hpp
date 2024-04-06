#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include "Item.hpp"
#include "Grid.hpp"
#include <iostream>
using namespace std;

class Inventory {
private:
    Grid<Item> inventory;
public:
    void addItem(Item item);
    Item getItem(string location);
    void removeItem(string location);
    void display();
};

#endif