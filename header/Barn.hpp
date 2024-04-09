#ifndef BARN_HPP
#define BARN_HPP

#include "Grid.hpp"
#include "Livestock.hpp"
#include <iostream>
using namespace std;

class Barn
{
private:
    Grid<shared_ptr<Livestock>> barn;

public:
    void addLivestock(shared_ptr<Livestock> livestock, string location);
    void feedLivestock(int food, string location);
    void harvestLivestock();
    void display();
    int countEmpty();
    bool isEmpty();
    bool isEmpty(string location);
    bool isFull();
};

#endif