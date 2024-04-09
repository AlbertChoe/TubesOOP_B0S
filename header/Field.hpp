#ifndef FIELD_HPP
#define FIELD_HPP

#include "Grid.hpp"
#include "Crop.hpp"
#include <iostream>
using namespace std;

class Field
{
private:
    Grid<shared_ptr<Crop>> field;

public:
    void incrementAllCropDuration();
    void addCrop(shared_ptr<Crop> item, string location);
    void harvestCrop(string location);
    int countEmpty();
    bool isEmpty();
    bool isEmpty(string location);
    bool isFull();
    void display();
};

#endif