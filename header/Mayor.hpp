#ifndef MAYOR_HPP
#define MAYOR_HPP

#include "Player.hpp"
#include "Config.hpp"
#include "Breeder.hpp"
#include "Farmer.hpp"
#include "Exception.hpp"
#include <vector>
using namespace std;

class Mayor : public Player {
public:
    void addNewPlayer(vector<shared_ptr<Player>>& players);
    void collectTax(vector<shared_ptr<Player>>& players);
    void buildBuilding(const BuildingConfig& recipe);
    int getTaxable();
    PlayerType getType();
};

#endif