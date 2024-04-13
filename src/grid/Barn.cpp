#include "../../header/Barn.hpp"

Barn::Barn(int row, int col) : barn(row, col)
{
}

void Barn::addLivestock(shared_ptr<Livestock> livestock, string location)
{
    if (barn.isValid(location))
    {
        return;
    }
    barn.add(livestock, location);
}

void Barn::feedLivestock(int food, string location)
{
    int row = this->barn.getRow();
    int col = this->barn.getCol();
    int a = location[0] - 'A';
    int b = 0;
    for (int i = 1; i < (int) location.size(); i++)
    {
        b *= 10;
        b += location[i] - '0';
    }
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (a == i && b == j)
            {
                auto data = this->barn.get(i, j);
                data->eat(food);
                return;
            }
        }
    }
}
void Barn::harvestLivestock()
{
    shared_ptr<Livestock> data;
    int row = this->barn.getRow();
    int col = this->barn.getCol();
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            auto data = this->barn.get(i, j);
            // get data harvesresult and do someting??
            this->barn.remove(i, j);
        }
    }
}
void Barn::display()
{
    this->barn.print("===barn===");
}

int Barn::countEmpty()
{
    return barn.countEmpty();
}

bool Barn::isEmpty()
{
    return barn.isEmpty();
}
bool Barn::isEmpty(string location)
{
    if (barn.isValid(location))
    {
        return false;
    }
    return barn.isEmpty(location);
}
bool Barn::isFull()
{
    return barn.isFull();
}

shared_ptr<Livestock> Barn::getElement(string location)
{
    if (barn.isValid(location))
    {
        return nullptr;
    }
    return this->barn.get(location);
}

map<string, int> Barn::countReadyToHarvest()
{
    map<string, int> readyToHarvest;
    for (int i = 0; i < barn.getRow(); i++)
    {
        for (int j = 0; j < barn.getCol(); j++)
        {
            auto livestock = barn.get(i, j);
            if (livestock != nullptr && livestock->isReadyToHarvest())
            {
                readyToHarvest[livestock->getCode()]++;
            }
        }
    }
    return readyToHarvest;
}

int Barn::countWealth()
{
    int netWealth = 0;
    int row = this->barn.getRow();
    int col = this->barn.getCol();
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            auto item = this->barn.get(i, j);
            if (item != nullptr)
            {
                netWealth += item->getPrice();
            }
        }
    }
    return netWealth;
}

void Barn::remove(string location)
{

    if (barn.isValid(location))
    {
        return;
    }
    this->barn.remove(location);
}