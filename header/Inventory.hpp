#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include "Item.hpp"
#include "Grid.hpp"
#include <iostream>
using namespace std;

class Inventory
{
private:
    Grid<shared_ptr<Item>> inventory;

public:
    Inventory(int row, int col);
    void addItem(shared_ptr<Item> item);
    shared_ptr<Item> getItem(string location);
    void removeItem(string location);
    void display();
    int countWealth();
    int countEmpty();
    bool isEmpty();
    bool isEmpty(string location);
    bool isFull();
    shared_ptr<Item> getElement(string location);
};

#endif