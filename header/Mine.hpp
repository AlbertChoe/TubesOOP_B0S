#ifndef MINE_HPP
#define MINE_HPP

#include "MineObject.hpp"
#include "Player.hpp"
#include "Grid.hpp"
#include <cstdlib>
#include <iostream>
using namespace std;

#define MINE_SIZE 7

class Mine {
private:
    Grid<shared_ptr<MineObject>> mine;
public:
    Mine();
    void displayMine();
    void refreshMine();
    void openAllSlot();
    int countDiamond();
    void playMine(shared_ptr<Player>& player);
};

#endif