#include "header/Field.hpp"

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
    field.add(item, location);
}

void Field::harvestCrop(string location)
{
    // masih blm pasti
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
    return field.isEmpty(location);
}
bool Field::isFull()
{
    return field.isFull();
}

void Field::display()
{
    field.print("===LADANG===");
}