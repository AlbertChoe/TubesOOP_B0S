#include "header/Inventory.hpp"

void Inventory::addItem(Item item)
{
}

// Item Inventory::getItem(string location)
// {
//     return this->inventory.get(location);
// }

void Inventory::removeItem(string location)
{
    this->inventory.remove(location);
}

void Inventory::display()
{
    this->inventory.print("===inventory===");
}