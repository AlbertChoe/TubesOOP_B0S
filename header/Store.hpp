#ifndef STORE_HPP
#define STORE_HPP

#include "Item.hpp"
#include "Player.hpp"
#include "Config.hpp"
#include <map>
#include <iostream>
using namespace std;


class Store {
private:
    map<string, pair<Item, int>> store;
public:
    void initStore(const CropConfig& cropConfig, const LivestockConfig& livestockConfig);
    void refreshStore();
};

#endif