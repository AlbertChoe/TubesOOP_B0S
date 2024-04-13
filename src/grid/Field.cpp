#include "../../header/Field.hpp"

Field::Field(int row, int col) : field(row, col)
{
}

void Field::incrementAllCropDuration()
{
    int row = this->field.getRow();
    int col = this->field.getCol();
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            auto data = this->field.get(i, j);
            data->incrementDuration();
        }
    }
}

void Field::addCrop(shared_ptr<Crop> item, string location)
{
    // do something? or try catch

    if (field.isValid(location))
    {
        field.add(item, location);
    }
    return;
}

void Field::harvestCrop(string location)
{
    // masih blm pasti
    if (field.isValid(location))
    {
        field.remove(location);
    }
    return;
}

int Field::countEmpty()
{
    return field.countEmpty();
}

bool Field::isEmpty()
{
    return field.isEmpty();
}
bool Field::isEmpty(string location)
{

    if (field.isValid(location))
    {
        return field.isEmpty(location);
    }
    return false;
}
bool Field::isFull()
{
    return field.isFull();
}

void Field::display()
{
    field.print("===LADANG===");
    // print element location
    int row = field.getCol();
    int col = field.getRow();

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            auto data = this->field.get(i, j);
            if (data != nullptr)
            {
                char r = i + 'A';
                cout << r << endl;
                cout << setfill('0') << setw(2) << j;
                cout << " : " << data->getName() << endl;
            }
        }
    }
    // print element type

    map<string, string> mp;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            auto data = this->field.get(i, j);
            if (data != nullptr)
            {
                mp[data->getCode()] = data->getName();
            }
        }
    }
    map<string, string>::iterator it = mp.begin();
    while (it != mp.end())
    {
        cout << it->first << ": "
             << it->second << endl;
        ++it;
    }
}

shared_ptr<Crop> Field::getElement(string location)
{

    if (field.isValid(location))
    {
        return this->field.get(location);
    }
    return nullptr;
}

map<string, int> Field::countReadyToHarvest()
{
    map<string, int> readyToHarvest;
    for (int i = 0; i < field.getRow(); i++)
    {
        for (int j = 0; j < field.getCol(); j++)
        {
            auto crop = field.get(i, j);
            if (crop != nullptr && crop->isReadyToHarvest())
            {
                readyToHarvest[crop->getCode()]++;
            }
        }
    }
    return readyToHarvest;
}

int Field::countWealth()
{
    int netWealth = 0;
    int row = this->field.getRow();
    int col = this->field.getCol();
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            auto item = this->field.get(i, j);
            if (item != nullptr)
            {
                netWealth += item->getPrice();
            }
        }
    }
    return netWealth;
}

void Field::remove(string location)
{
    if (field.isValid(location))
    {
        this->field.remove(location);
    }
    return;
}