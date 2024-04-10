#include "../../header/Game.hpp"

Game::Game() {
    currentPlayer = -1;
    previousPlayer = -1;
}

Game::~Game() {}

void Game::loadGameConfig() {
    ifstream configFile("config/misc.txt");
    if (!configFile) {
        throw FailToLoadException("misc.txt");
    }

    int guldenToWin, weightToWin;
    int inventoryRow, inventoryCol;
    int fieldRow, fieldCol;
    int barnRow, barnCol;

    configFile >> guldenToWin >> weightToWin;
    configFile >> inventoryRow >> inventoryCol;
    configFile >> fieldRow >> fieldCol;
    configFile >> barnRow >> barnCol;

    if (configFile.bad() || !configFile.eof()) {
        configFile.close();
        throw FailToLoadException("misc.txt");
    }

    gameConfig.setGameConfig(guldenToWin, weightToWin, inventoryRow, inventoryCol, fieldRow, fieldCol, barnRow, barnCol);
    
    configFile.close();
}

void Game::loadConsumableConfig() {
    ifstream configFile("config/product.txt");
    if (!configFile) {
        throw FailToLoadException("product.txt");
    }

    int id, price, addedWeight;
    string code, name, type, origin;

    while (configFile >> id >> code >> name >> type >> origin >> addedWeight >> price) {
        Consumable consumable(id, code, name, type, price, origin, addedWeight);
        consumableConfig.addConsumableConfig(code, consumable);
    }

    if (configFile.bad() || !configFile.eof()) {
        configFile.close();
        throw FailToLoadException("product.txt");
    }

    configFile.close();
}

void Game::loadBuildingConfig() {
    ifstream configFile("config/recipe.txt");
    if (!configFile) {
        throw FailToLoadException("recipe.txt");
    }

    int id, price;
    string code, name, materialCode;
    int materialQuantity;

    while (configFile >> id >> code >> name >> price) {
        Building building(id, code, name, "BUILDING", price);
        map<string, int> materials;

        while (configFile.peek() != '\n' && configFile >> materialCode >> materialQuantity) {
            materials[materialCode] = materialQuantity;
        }

        building.setMaterial(materials);
        buildingConfig.addBuildingConfig(code, building);
    }

    if (configFile.bad() || !configFile.eof()) {
        configFile.close();
        throw FailToLoadException("recipe.txt");
    }

    configFile.close();
}

void Game::loadCropConfig() {
    ifstream configFile("config/plant.txt");
    if (!configFile) {
        throw FailToLoadException("plant.txt");
    }

    int id, price, harvestDuration;
    string code, name, type;

    while (configFile >> id >> code >> name >> type >> harvestDuration >> price) {
        Crop crop(id, code, name, type, price, 0, harvestDuration);
        cropConfig.addCropConfig(code, crop);
    }

    if (configFile.bad() || !configFile.eof()) {
        configFile.close();
        throw FailToLoadException("plant.txt");
    }

    configFile.close();
}

void Game::loadLivestockConfig() {
    ifstream configFile("config/animal.txt");
    if (!configFile) {
        throw FailToLoadException("animal.txt");
    }

    int id, price, harvestWeight;
    string code, name, type;

    while (configFile >> id >> code >> name >> type >> harvestWeight >> price) {
        if (type == "HERBIVORE") {
            shared_ptr<Herbivore> herbivore = make_shared<Herbivore>(id, code, name, type, price, 0, harvestWeight);
            livestockConfig.addHerbivoreConfig(code, herbivore);
        } else if (type == "CARNIVORE") {
            shared_ptr<Carnivore> carnivore = make_shared<Carnivore>(id, code, name, type, price, 0, harvestWeight);
            livestockConfig.addCarnivoreConfig(code, carnivore);
        } else if (type == "OMNIVORE") {
            shared_ptr<Omnivore> omnivore = make_shared<Omnivore>(id, code, name, type, price, 0, harvestWeight);
            livestockConfig.addOmnivoreConfig(code, omnivore);
        } else {
            configFile.close();
            throw FailToLoadException("animal.txt");
        }
    }

    if (configFile.bad() || !configFile.eof()) {
        configFile.close();
        throw FailToLoadException("animal.txt");
    }

    configFile.close();
}

void Game::loadHarvestConfig() {
    for (const auto& consumablePair : consumableConfig.getRefConfigMap()) {
        Consumable consumable = consumablePair.second;
        bool found = false;
        
        for (auto& cropPair : cropConfig.getRefConfigMap()) {
            if (cropPair.second.getName() == consumable.getOrigin()) {
                cropPair.second.addHarvestResult(consumable);
                found = true;
                break;
            }
        }

        if (found) {
            continue;
        }

        for (auto& LivestockPair : livestockConfig.getRefConfigMap()) {
            if (LivestockPair.second->getName() == consumable.getOrigin()) {
                LivestockPair.second->addHarvestResult(consumable);
                break;
            }
        }
    }
}

void Game::loadConfig() {
    try {
        loadGameConfig();
        loadBuildingConfig();
        loadConsumableConfig();
        loadCropConfig();
        loadLivestockConfig();
        loadHarvestConfig();
    } catch (const exception& e) {
        cout << e.what() << endl;
    }
}

//TODO: ctor mayor etc.
void Game::newGame() {
    string username;
    cout << "Permainan baru telah dimulai!" << endl;

    auto newMayor = make_shared<Mayor>(); //belum ctor player yang benar
    auto newBreeder = make_shared<Breeder>();
    auto newFarmer = make_shared<Farmer>();
    
    cout << "Masukkan username untuk player Walikota baru: ";
    cin >> username;
    newMayor->setName(username);
    Utils::addNewPlayer(players, newMayor);
    
    while (true) {
        cout << "Masukkan username untuk player Peternak baru: ";
        cin >> username;
        if (Utils::isNameInPlayers(players, username)) {
            cout << "Nama sudah diambil, pilih nama lain!" << endl;
        } else {
            newBreeder->setName(username);
            break;
        };
    }
    Utils::addNewPlayer(players, newBreeder);
    
    while (true) {
        cout << "Masukkan username untuk player Petani baru: ";
        cin >> username;
        if (Utils::isNameInPlayers(players, username)) {
            cout << "Nama sudah diambil, pilih nama lain!" << endl;
        } else {
            newFarmer->setName(username);
            break;
        };
    }
    Utils::addNewPlayer(players, newFarmer);

    store.initStore(cropConfig, livestockConfig);

    cout << "Seluruh player telah berhasil terdaftar, selamat bermain!" << endl;
}

void Game::nextPlayer() {
    previousPlayer = currentPlayer;
    currentPlayer = (currentPlayer + 1) % players.size();
    if (previousPlayer != -1) {
        if (players[currentPlayer]->getName() == players[previousPlayer]->getName()) {
            currentPlayer = (currentPlayer + 1) % players.size();
        }
    }
}

void Game::start() {
    loadConfig();
    string input;
    while (true) {
        cout << "Apakah Anda ingin memuat state? (y/n) ";
        cin >> input;
        if (input == "y" || input == "n") {
            break;
        } else {
            cout << "Hanya menerima input y/n!" << endl;
        }
    }

    string fileLocation;
    if (input == "y") {
        while (true) {
            cout << "Masukkan lokasi berkas state : ";
            cin >> fileLocation;
            try {
                loadGameState(fileLocation);
                break;
            } catch (const exception& e) {
                cout << e.what() << endl;
            }
        }
    } else {
        newGame();
    }
}

bool Game::isWinCondition() {
    return players[currentPlayer]->getGulden() >= gameConfig.getGuldenToWin() && players[currentPlayer]->getWeight() >= gameConfig.getWeightToWin();
}

void Game::run() {
    start();
    cout << "Permainan dimulai!" << endl;
    cout << "Giliran player " << players[currentPlayer]->getName() << " jalan!" << endl;
    while (!isWinCondition()) {
        handleInput();
    }
    cout << "Game telah dimenangkan oleh player " << players[currentPlayer]->getName() << "!" << endl;
    cout << "Karena telah memiliki " << players[currentPlayer]->getGulden() << " gulden dan berat " << players[currentPlayer]->getWeight() << " kg!";
}

void Game::handleInput() {
    auto current = players[currentPlayer];
    PlayerType type = current->getType();
    bool reach_win = false;
    string input;
    while (true) {
        try {
            cout << "> ";
            cin >> input;
            if (input == "NEXT") {
                nextPlayer();
            } else if (input == "CETAK_PENYIMPANAN") {

            } else if (input == "MAKAN") {
            
            } else if (input == "BELI") {
            
            } else if (input == "JUAL") {
            
            } else if (input == "SIMPAN") {
            
            } else if (input == "CETAK_LADANG" && type == PlayerType::Farmer) {

            } else if (input == "TANAM" && type == PlayerType::Farmer) {

            } else if (input == "TERNAK" && type == PlayerType::Breeder) {

            } else if (input == "CETAK_PETERNAKAN" && type == PlayerType::Breeder) {

            } else if (input == "KASIH_MAKAN" && type == PlayerType::Breeder) {

            } else if (input == "PANEN" && (type == PlayerType::Farmer || type == PlayerType::Breeder)) {

            } else if (input == "BANGUN" && type == PlayerType::Mayor) {
            
            } else if (input == "PUNGUT_PAJAK" && type == PlayerType::Mayor) {

            } else if (input == "TAMBAH_PEMAIN" && type == PlayerType::Mayor) {

            } else {
                throw WrongUserInputException();
            }
            break;
        } catch (const exception& e) {
            cout << e.what() << endl;
        }
    }
}

void Game::debugPrint() {
    cout << "Gulden to Win: " << gameConfig.getGuldenToWin() << endl;
    cout << "Weight to Win: " << gameConfig.getWeightToWin() << endl;
    cout << "Inventory Size: " << gameConfig.getInventoryRow() << " x " << gameConfig.getInventoryCol() << endl;
    cout << "Field Size: " << gameConfig.getFieldRow() << " x " << gameConfig.getFieldCol() << endl;
    cout << "Barn Size: " << gameConfig.getBarnRow() << " x " << gameConfig.getBarnCol() << endl;
}