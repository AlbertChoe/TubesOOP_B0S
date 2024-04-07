#ifndef BARN_HPP
#define BARN_HPP

#include "Grid.hpp"
#include "Livestock.hpp"
#include <iostream>
using namespace std;

class Barn
{
private:
    Grid<Livestock> barn;

public:
    void addLivestock(Livestock livestock);
    void feedLivestock();
    void harvestLivestock();
    void display();
};

#endif