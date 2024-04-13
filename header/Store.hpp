#ifndef STORE_HPP
#define STORE_HPP

#include "Player.hpp"
#include "Item.hpp"
#include "Config.hpp"
#include <limits>
#include <map>
#include <iostream>
using namespace std;

#define UNLIMITED 999999

class Store {
private:
    map<string, pair<shared_ptr<Item>, int>> store;
public:
    Store();
    ~Store();
    void initStore(CropConfig& cropConfig, LivestockConfig& livestockConfig);
    void refreshStore();
    void buyTransaction(shared_ptr<Player> player);
    void sellTransaction(shared_ptr<Player> player);
    void display();
    int getQuantity(string code);
    int getNumItem();
    int getPrice(string code);
    shared_ptr<Item> getItem(string code);
    string getCodeByOrderNum(int num);
    void addItem(shared_ptr<Item> item);
};

#endif