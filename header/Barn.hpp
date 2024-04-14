#ifndef BARN_HPP
#define BARN_HPP

#include "Grid.hpp"
#include "Livestock.hpp"
#include "Utils.hpp"
#include <iostream>
using namespace std;

class Barn
{
private:
    Grid<shared_ptr<Livestock>> barn;

public:
    Barn(int row, int col);
    void addLivestock(shared_ptr<Livestock> livestock, string location);
    void feedLivestock(int food, string location);
    void harvestLivestock();
    int countWealth();
    void display();
    int countEmpty();
    bool isEmpty();
    bool isEmpty(string location);
    bool isFull();
    shared_ptr<Livestock> getElement(string location);
    map<string, int> countReadyToHarvest();
    void remove(string location);
    vector<vector<string>> getallDetail()
};

#endif