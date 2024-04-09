#ifndef MAYOR_HPP
#define MAYOR_HPP

#include "Player.hpp"
#include "Config.hpp"
#include <vector>
using namespace std;

class Mayor : public Player {
public:
    void addNewPlayer(vector<Player>& players);
    void collectTax(vector<Player>& players);
    void buildBuilding(const BuildingConfig& recipe);
    int getTaxable();
    PlayerType getType();
};

#endif