#include "header/Inventory.hpp"

void Inventory::addItem(Item item)
{
    this->inventory.add(item);
}

Item Inventory::getItem(string location)
{
    Item *data;
    data = this->inventory.get(location);
    return *data;
}

void Inventory::removeItem(string location)
{
    this->inventory.remove(location);
}

void Inventory::display()
{
    this->inventory.print("===inventory===");
}