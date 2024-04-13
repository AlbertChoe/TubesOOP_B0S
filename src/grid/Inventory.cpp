#include "../../header/Inventory.hpp"

Inventory::Inventory(int row, int col) : inventory(row, col)
{
}

void Inventory::addItem(shared_ptr<Item> item)
{
    this->inventory.add(item);
}

void Inventory::addItem(shared_ptr<Item> item, string location)
{
    if (inventory.isValid(location))
    {
        this->inventory.add(item, location);
    }
    return;
}

shared_ptr<Item> Inventory::getItem(string location)
{
    if (inventory.isValid(location))
    {
        return this->inventory.get(location);
    }
    return nullptr;
}

void Inventory::removeItem(string location)
{
    if (inventory.isValid(location))
    {
        this->inventory.remove(location);
    }
    return;
}

void Inventory::display()
{
    this->inventory.print("===inventory===");
}

int Inventory::countWealth()
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
    if (inventory.isValid(location))
    {
        return inventory.isEmpty(location);
    }
    return false;
}
bool Inventory::isFull()
{
    return inventory.isFull();
}

shared_ptr<Item> Inventory::getElement(string location)
{
    if (inventory.isValid(location))
    {
        return this->inventory.get(location);
    }
    return nullptr;
    
}

void Inventory::remove(string location)
{
    if (inventory.isValid(location))
    {
        this->inventory.remove(location);
    }
    return;
}

int Inventory::getCountItem()
{
    return this->inventory.getCol() * this->inventory.getRow() - countEmpty();
}

int Inventory::getCountNonBuilding()
{
    int res = 0;
    int row = this->inventory.getRow();
    int col = this->inventory.getCol();
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            auto item = this->inventory.get(i, j);
            if (item != nullptr) {
                ItemType itemtype = item->getItemType();
                if (itemtype != ItemType::Building)
                {
                    res++;
                }
            }
        }
    }
    return res;
}

int Inventory::getCountBuilding()
{
    return getCountItem() - getCountNonBuilding();
}

int Inventory::getItemCountByName(string name){
    int count = 0;
    int row = this->inventory.getRow();
    int col = this->inventory.getCol();
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            auto item = this->inventory.get(i, j);
            if (item!=nullptr)
            {
                if (item->getName()==name)
                {
                    count++;
                }
            }
        }
    }
    return count;
}