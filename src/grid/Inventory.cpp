#include "../../header/Inventory.hpp"

void Inventory::addItem(shared_ptr<Item> item)
{
    this->inventory.add(item);
}

shared_ptr<Item> Inventory::getItem(string location)
{
    auto data = this->inventory.get(location);
    return data;
}

void Inventory::removeItem(string location)
{
    this->inventory.remove(location);
}

void Inventory::display()
{
    this->inventory.print("===inventory===");
}

int Inventory::CountWealth()
{
    int netWealth = 0;
    int row = this->inventory.getRow();
    int col = this->inventory.getCol();
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            auto item = this->inventory.get(i, j);
            if (item != nullptr)
            {
                netWealth += item->getPrice();
            }
        }
    }
    return netWealth;
}

int Inventory::countEmpty()
{
    return inventory.countEmpty();
}
bool Inventory::isEmpty()
{
    return inventory.isEmpty();
}
bool Inventory::isEmpty(string location)
{
    return inventory.isEmpty(location);
}
bool Inventory::isFull()
{
    return inventory.isFull();
}
