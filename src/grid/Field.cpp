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
        return;
    }
    field.add(item, location);
}

void Field::harvestCrop(string location)
{
    // masih blm pasti
    if (field.isValid(location))
    {
        return;
    }
    field.remove(location);
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
        return false;
    }
    return field.isEmpty(location);
}
bool Field::isFull()
{
    return field.isFull();
}

void Field::display()
{
    field.print("===LADANG===");
    field.printElementType();
}

shared_ptr<Crop> Field::getElement(string location)
{

    if (field.isValid(location))
    {
        return nullptr;
    }
    return this->field.get(location);
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
        return;
    }
    this->field.remove(location);
}