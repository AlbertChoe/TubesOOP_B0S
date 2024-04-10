#ifndef STORE_HPP
#define STORE_HPP

#include "Item.hpp"
#include "Player.hpp"
#include "Config.hpp"
#include <map>
#include <iostream>
using namespace std;

#define UNLIMITED 999999;

class Store {
private:
    map<string, pair<shared_ptr<Item>, int>> store;
public:
    Store();
    ~Store();
    void initStore(const CropConfig& cropConfig, const LivestockConfig& livestockConfig);
    void refreshStore();
    void addItem(shared_ptr<Item> item, int quantity);
    void removeItem(string code, int quantity);
    shared_ptr<Item> getItem(string code);
    int getQuantity(string code);
    void display();
};

#endif