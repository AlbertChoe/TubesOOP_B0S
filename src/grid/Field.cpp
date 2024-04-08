#include "header/Field.hpp"

void Field::incrementAllCropDuration()
{
    Crop *data;
    int row = this->field.getRow();
    int col = this->field.getCol();
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            data = this->field.get(i, j);
            data->incrementDuration();
        }
    }
}

void Field::addCrop(Crop item, string location)
{
    // do something? or try catch
    field.add(item, location);
}

void Field::harvestCrop(string location)
{
    // masih blm pasti
    field.remove(location);
}

void Field::countEmpty()
{
    cout << field.countEmpty() << endl;
}

void Field::display()
{
    field.print("===LADANG===");
}