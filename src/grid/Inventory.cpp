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
        return;
    }
    this->inventory.add(item, location);
}

shared_ptr<Item> Inventory::getItem(string location)
{
    if (inventory.isValid(location))
    {
        return nullptr;
    }
    auto data = this->inventory.get(location);
    return data;
}

void Inventory::removeItem(string location)
{
    if (inventory.isValid(location))
    {
        return;
    }
    this->inventory.remove(location);
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
        return false;
    }
    return inventory.isEmpty(location);
}
bool Inventory::isFull()
{
    return inventory.isFull();
}

shared_ptr<Item> Inventory::getElement(string location)
{
    if (inventory.isValid(location))
    {
        return nullptr;
    }
    return this->inventory.get(location);
}

void Inventory::remove(string location)
{

    if (inventory.isValid(location))
    {
        return;
    }
    this->inventory.remove(location);
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
            ItemType itemtype = item->getItemType();
            if (itemtype != ItemType::Building)
            {
                res++;
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
            if (item->getName()==name)
            {
                count++;
            }
        }
    }
    return count;
}