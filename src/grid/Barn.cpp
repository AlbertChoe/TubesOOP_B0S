#include "../../header/Barn.hpp"

Barn::Barn(int row, int col) : barn(row, col)
{
}

void Barn::addLivestock(shared_ptr<Livestock> livestock, string location)
{
    if (barn.isValid(location))
    {
        barn.add(livestock, location);
    }
    return;
}

void Barn::feedLivestock(int food, string location)
{
    int row = this->barn.getRow();
    int col = this->barn.getCol();
    int a = location[0] - 'A';
    int b = 0;
    for (int i = 1; i < (int)location.size(); i++)
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
            if (data != nullptr)
            {
                // get data harvesresult and do someting??
                this->barn.remove(i, j);
            }
        }
    }
}
void Barn::display()
{
    this->barn.print("===barn===");
    // barn.printElemenetLoc();
    // print element location
    int row = barn.getRow();
    int col = barn.getCol();

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            auto data = this->barn.get(i, j);
            if (data != nullptr)
            {
                char r = i + 'A';
                cout << r;
                cout << setfill('0') << setw(2) << j + 1;
                cout << " : " << data->getName() << endl;
            }
        }
    }
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
        return barn.isEmpty(location);
    }
    return false;
}
bool Barn::isFull()
{
    return barn.isFull();
}

shared_ptr<Livestock> Barn::getElement(string location)
{
    if (barn.isValid(location))
    {
        return this->barn.get(location);
    }
    return nullptr;
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
        this->barn.remove(location);
    }
    return;
}

vector<vector<string>> Barn::getAllDetail()
{
    int row = barn.getRow();
    int col = barn.getCol();
    vector<vector<string>> listData;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            vector<string> detail;
            auto data = this->barn.get(i, j);
            if (data != nullptr)
            {
                char r = i + 'A';
                string loc;
                loc += r;
                if (j + 1 < 10)
                {
                    loc += '0';
                }
                loc += Utils::intToString(i + 1);
                detail.push_back(loc);
                detail.push_back(data->getName());
                string weight = Utils::intToString(data->getCurrentWeight());
                detail.push_back(weight);
                listData.push_back(detail);
            }
        }
    }
    return listData;
}