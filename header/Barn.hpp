#include <iostream>
#include "Grid.hpp"
#include "Livestock.hpp"
using namespace std;

#ifndef BARN_HPP
#define BARN_HPP



class Barn {
private:
    Grid<Livestock> barn;
public:
    void addLivestock(Livestock livestock);
    void feedLivestock();
    void harvestLivestock();
    void display();
};

#endif