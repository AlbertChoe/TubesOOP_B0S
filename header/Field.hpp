#ifndef FIELD_HPP
#define FIELD_HPP

#include "Grid.hpp"
#include "Crop.hpp"
#include <iostream>
using namespace std;

class Field
{
private:
    Grid<Crop> field;

public:
    void incrementAllCropDuration();
    void addCrop(Crop item, string location);
    void harvestCrop(string location);
    void countEmpty();
    void display();
};

#endif