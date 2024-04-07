#include "header/Barn.hpp"

void Barn::addLivestock(Livestock *livestock)
{
    barn.add(livestock);
}

void Barn::feedLivestock(Consumable food, string location)
{
    Livestock **data;
    int row = this->barn.getRow();
    int col = this->barn.getCol();
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            data = this->barn.get(i, j);
            Livestock *data1 = *data;
            data1->eat(food);
        }
    }
}
void Barn::harvestLivestock()
{
    Livestock **data;
    int row = this->barn.getRow();
    int col = this->barn.getCol();
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            data = this->barn.get(i, j);
            Livestock *data1 = *data;
            // get data harvesresult and do someting??
            this->barn.remove(i, j);
        }
    }
}
void Barn::display()
{
    this->barn.print("===barn===");
}