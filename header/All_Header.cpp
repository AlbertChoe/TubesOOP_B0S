#include <map>
#include <vector>
#include <iostream>
using namespace std;

class GameConfig {
private:
    int guldenToWin;
    int weightToWin;
    int inventoryRow;
    int inventoryCol;
    int fieldRow;
    int fieldCol;
    int barnRow;
    int barnCol;

public:
    GameConfig();
    GameConfig(int guldenToWin, int weighToWin, int inventoryRow, int inventoryCol, int fieldRow, int fieldCol, int barnRow, int barnCol);
    void getGuldenToWin();
    void getWieghToWin();
    void getInventoryRow();
    void getInvetoryCol();
    void getFieldRow();
    void getFieldCol();
    void getBarnRow();
    void getBarnCol();
};

class CropConfig {
private:
    map<string, Crop> config;
public:
    CropConfig();
    void addConfig(string code, Crop config);
    Crop getConfig(string code);
};

class LivestockConfig {
private:
    map<string, Livestock> config;
public:
    LivestockConfig();
    ~LivestockConfig();
    void addConfig(string code, Livestock config);
    Livestock getConfig(string code);
};

class ConsumableConfig {
private:
    map<string, Consumable> config;
public:
    ConsumableConfig();
    ~ConsumableConfig();
    void addConfig(string code, Consumable config);
    Consumable getConfig(string code);

};

class BuildingConfig {
private:
    map<string, Building> recipe;
public:
    BuildingConfig();
    ~BuildingConfig();
    void addConfig(string code, Building config);
    Building getConfig(string code);

};

class Game {
private:
    static GameConfig gameConfig;
    static CropConfig cropConfig;
    static LivestockConfig livestockConfig;
    static ConsumableConfig consumableConfig;
    static BuildingConfig buildingConfig;
    Store store;
    vector<Player> players;
    int currentIndex;
public:
    Game();
    ~Game();
    void loadGameConfig();
    void loadCropConfig();
    void loadLiveStockConfig();
    void loadComsumableConfig();
    void load();
    void newGame();
    void save();
    void handleInput();
    void run();
};

class Building: public Item {
private:
    int id;
    string code;
    string name;
    int price;
    map<string, int> material;
public:
};

template<typename T>
class Grid {
private:
    vector<vector<T>> grid;
public:
    void add(T item, string location);
    void remove(string location);
    void print(string title);
};

class Item {
protected:
    int id;
    string code;
    string name;
    string type;
    int price;
public:
    friend ostream& operator<<(ostream& os, const Item& item);
};

class Livestock : public Item {
private:
    int harvestWeight;
public:
    void eat(Consumable food);
    friend ostream& operator<<(ostream& os, const Crop& livestock);
};

class Crop : public Item {
private:
    int harvestDuration;
public:
    void incrementDuration();
    friend ostream& operator<<(ostream& os, const Crop& crop);
};

class Consumable : public Item {
private:
    string origin;
    int addedWeight;
public:
};

class Inventory {
private:
    Grid<Item> inventory;
public:
    void addItem(Item item);
    Item getItem(string location);
    void removeItem(string location);
    void display();
};

class Field {
private:
    Grid<Crop> field;
public:
    void incrementAllCropDuration();
    void addCrop();
    void harvestCrop();
    void display();
};

class Barn {
private:
    Grid<Livestock> barn;
public:
    void addLivestock(Livestock livestock);
    void feedLivestock();
    void harvestLivestock();
    void display();
};

class Store {
private:
    map<string, pair<Item, int>> store;
public:
    void initStore(const CropConfig& cropConfig, const LivestockConfig& livestockConfig);
    bool buyItem(Player& player, const string itemCode, int quantity);
    bool sellItem(Player& player, const string itemCode, int quantity);
};

class Player {
protected:
    string name;
    int weight;
    int gulden;
    Inventory inventory;
public:
    void eat();
    void displayInventory();
    virtual int getTaxable() = 0;
};

class Mayor : public Player {
public:
    void addNewPlayer(vector<Player>& players);
    void collectTax(vector<Player>& players);
    void buildBuilding(const BuildingConfig& recipe);
    int getTaxable();
};

class Farmer : public Player {
private:
    Field field;
public:
    void plantCrop();
    void harvestCrop();
    void displayField();
    int getTaxable();
};

class Breeder : public Player {
private:
    Barn barn;
public:
    void addLivestock();
    void feedLivestock();
    void harvestLivestock();
    void displayBarn();
    int getTaxable();
};