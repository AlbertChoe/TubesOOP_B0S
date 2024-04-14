#include "../../header/Game.hpp"

Game::Game() {
    currentPlayer = 0;
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

    string line;
    while (getline(configFile, line)) {
        istringstream lineStream(line);

        int id, price;
        string code, name, materialName;
        int materialQuantity;

        if (!(lineStream >> id >> code >> name >> price)) {
            configFile.close();
            throw FailToLoadException("recipe.txt");
        }

        Building building(id, code, name, "BUILDING", price);
        map<string, int> materials;

        while (lineStream >> materialName >> materialQuantity) {
            materials[materialName] = materialQuantity;
        }

        if (lineStream.fail() && !lineStream.eof()) {
            configFile.close();
            throw FailToLoadException("recipe.txt");
        }

        building.setMaterial(materials);
        buildingConfig.addBuildingConfig(name, building);
    }

    if (configFile.bad()) {
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
        store.initStore(cropConfig, livestockConfig);
    } catch (const exception& e) {
        cout << e.what() << endl;
    }
}

void Game::newGame() {
    string username;
    cout << "Permainan baru telah dimulai!" << endl;

    auto newMayor = make_shared<Mayor>("", gameConfig.getInventoryRow(), gameConfig.getInventoryCol());
    auto newBreeder = make_shared<Breeder>("", gameConfig.getInventoryRow(), gameConfig.getInventoryCol(), gameConfig.getBarnRow(), gameConfig.getBarnCol());
    auto newFarmer = make_shared<Farmer>("", gameConfig.getInventoryRow(), gameConfig.getInventoryCol(), gameConfig.getFieldRow(), gameConfig.getFieldCol());
    
    cout << "Masukkan username untuk player Walikota baru: ";
    cin >> username;
    newMayor->setName(username);
    Utils::addNewPlayer(players, currentPlayer, newMayor);
    
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
    Utils::addNewPlayer(players, currentPlayer, newBreeder);
    
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
    Utils::addNewPlayer(players, currentPlayer, newFarmer);

    cout << "Seluruh player telah berhasil terdaftar, selamat bermain!" << endl;
}

void Game::nextPlayer() {
    currentPlayer = (currentPlayer + 1) % players.size();
    for (auto& player : players) {
        if (player->getType() == PlayerType::Farmer) {
            auto farmer = dynamic_cast<Farmer*>(player.get());
            farmer->getRefField().incrementAllCropDuration();
        }
    }
    cout << endl << "Giliran " << players[currentPlayer]->getName() << "!" << endl << endl;
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
    currentPlayer = 0;
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

    auto farmer = (type == PlayerType::Farmer) ? dynamic_cast<Farmer*>(current.get()) : nullptr;
    auto breeder = (type == PlayerType::Breeder) ? dynamic_cast<Breeder*>(current.get()) : nullptr;
    auto mayor = (type == PlayerType::Mayor) ? dynamic_cast<Mayor*>(current.get()) : nullptr;

    string input;
    while (true) {
        try {
            cout << "> ";
            cin >> input;
            if (input == "NEXT") {
                nextPlayer();
            } else if (input == "CETAK_PENYIMPANAN") {
                current->displayInventory();
            } else if (input == "MAKAN") {
                current->eat();
            } else if (input == "BELI") {
                store.buyTransaction(current);
            } else if (input == "JUAL") {
                store.sellTransaction(current);
            } else if (input == "SIMPAN") {
                saveGameState();
            } else if (input == "CETAK_LADANG" && farmer) {
                farmer->displayField();
            } else if (input == "TANAM" && farmer) {
                farmer->plantCrop();
            } else if (input == "TERNAK" && breeder) {
                breeder->addLivestock();
            } else if (input == "CETAK_PETERNAKAN" && breeder) {
                breeder->displayBarn();
            } else if (input == "KASIH_MAKAN" && breeder) {
                breeder->feedLivestock();
            } else if (input == "PANEN" && (farmer || breeder)) {
                if (farmer) {
                    farmer->harvestCrop();
                } else {
                    breeder->harvestLivestock();
                }
            } else if (input == "BANGUN" && mayor) {
                mayor->buildBuilding(buildingConfig);
            } else if (input == "PUNGUT_PAJAK" && mayor) {
                mayor->collectTax(players);
            } else if (input == "TAMBAH_PEMAIN" && mayor) {
                mayor->addNewPlayer(players, currentPlayer, gameConfig);
            } else if (input == "CETAK_PEMAIN") {
                printPlayers();
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

void Game::loadGameState(string fileLocation) {
    players.clear();
    ifstream saveFile(fileLocation);
    if (!saveFile) {
        throw FailToLoadException("state.txt");
    }
    int n;
    saveFile >> n;
    for (int pl = 0; pl < n; pl++) {
        string username, role;
        int weight, gulden, invenCount;
        saveFile >> username >> role >> weight >> gulden >> invenCount;
        cout << "DEBUG>> load: " <<  username << " " << role << endl;
        if (role == "Petani") {
            auto player = make_shared<Farmer>(username, gameConfig.getInventoryRow(), gameConfig.getInventoryCol(), gameConfig.getFieldRow(), gameConfig.getFieldCol());
            for (int i = 0; i < invenCount; i++) {
                string itemName;
                saveFile >> itemName;
                shared_ptr<Item> item = buildingConfig.getNewPtrConfigByName(itemName);
                if (item == nullptr) {
                    item = consumableConfig.getNewPtrConfigByName(itemName);
                }
                if (item == nullptr) {
                    item = livestockConfig.getNewPtrConfigByName(itemName);
                }
                if (item == nullptr) {
                    item = cropConfig.getNewPtrConfigByName(itemName);
                }
                player->getRefInventory().addItem(item);
                cout << "DEBUG>> success in:" << i + 1 << endl;
            }
            int cropCount;
            saveFile >> cropCount;
            for (int i = 0; i < cropCount; i++) {
                string location, cropName;
                int duration;
                saveFile >> location >> cropName >> duration;
                auto crop = cropConfig.getNewPtrConfigByName(cropName);
                crop->setCurrentDuration(duration);
                player->getRefField().addCrop(crop, location);
                cout << "DEBUG>> Success cr:" << i + 1 << endl;
            }
            player->setGulden(gulden);
            player->setWeight(weight);
            Utils::addNewPlayer(players, currentPlayer, player);
        } else if (role == "Peternak") {
            auto player = make_shared<Breeder>(username, gameConfig.getInventoryRow(), gameConfig.getInventoryCol(), gameConfig.getBarnRow(), gameConfig.getBarnCol());
            for (int i = 0; i < invenCount; i++) {
                string itemName;
                saveFile >> itemName;
                shared_ptr<Item> item = buildingConfig.getNewPtrConfigByName(itemName);
                if (item == nullptr) {
                    item = consumableConfig.getNewPtrConfigByName(itemName);
                }
                if (item == nullptr) {
                    item = livestockConfig.getNewPtrConfigByName(itemName);
                }
                if (item == nullptr) {
                    item = cropConfig.getNewPtrConfigByName(itemName);
                }
                player->getRefInventory().addItem(item);
                cout << "DEBUG>> success in:" << i + 1 << endl;
            }
            int livestockCount;
            saveFile >> livestockCount;
            for (int i = 0; i < livestockCount; i++) {
                string location, livestockName;
                int weight;
                saveFile >> location >> livestockName >> weight;
                auto livestock = livestockConfig.getNewPtrConfigByName(livestockName);
                livestock->setCurrentWeight(weight);
                player->getRefBarn().addLivestock(livestock, location);
                cout << "DEBUG>> Success ls:" << i + 1 << endl;
            }
            player->setGulden(gulden);
            player->setWeight(weight);
            Utils::addNewPlayer(players, currentPlayer, player);
        } else if (role == "Walikota") {
            auto player = make_shared<Mayor>(username, gameConfig.getInventoryRow(), gameConfig.getInventoryCol());
            for (int i = 0; i < invenCount; i++) {
                string itemName;
                saveFile >> itemName;
                shared_ptr<Item> item = buildingConfig.getNewPtrConfigByName(itemName);
                if (item == nullptr) {
                    item = consumableConfig.getNewPtrConfigByName(itemName);
                }
                if (item == nullptr) {
                    item = livestockConfig.getNewPtrConfigByName(itemName);
                }
                if (item == nullptr) {
                    item = cropConfig.getNewPtrConfigByName(itemName);
                }
                player->getRefInventory().addItem(item);
                cout << "DEBUG>> success in:" << i + 1 << endl;
            }
            player->setGulden(gulden);
            player->setWeight(weight);
            Utils::addNewPlayer(players, currentPlayer, player);
        } else {
            throw FailToLoadException("state.txt");
        }
    }
    int countItem;
    saveFile >> countItem;
    for (int i = 0; i < countItem; i++) {
        string itemName;
        int quantity;
        saveFile >> itemName >> quantity;
        shared_ptr<Item> item = buildingConfig.getNewPtrConfigByName(itemName);
        if (item == nullptr) {
            item = consumableConfig.getNewPtrConfigByName(itemName);
        }
        store.addItem(item);
        store.setQuantity(item->getCode(), quantity);
    }
}

void Game::saveGameState() {
    string fileLocation;
    cout << endl << "Masukkan lokasi berkas state : ";
    cin >> fileLocation;
    
    fs::path path_obj(fileLocation);
    fs::path dir_path = path_obj.parent_path();

    if (!fs::exists(dir_path)) {
        cout << "Lokasi berkas tidak valid!" << endl;
        return;
    }

    if (!fs::is_directory(dir_path)) {
        cout << "Lokasi berkas tidak valid!" << endl;
        return;
    }

    ofstream saveFile(fileLocation);
    if (!saveFile.is_open()) {
        cout << "Gagal menyimpan!" << endl;
        return;
    }

    saveFile << players.size() << endl;
    for (int i = 0 ; i < (int) players.size(); i++) {
        saveFile << players[i]->getName() << " ";
        if (players[i]->getType() == PlayerType::Breeder) {
            saveFile << "Peternak" << " ";
        } else if (players[i]->getType() == PlayerType::Farmer) {
            saveFile << "Petani" << " ";
        } else {
            saveFile << "Walikota" << " ";
        }
        saveFile << players[i]->getWeight() << " " << players[i]->getGulden() << endl;
        auto inven = players[i]->getRefInventory();
        auto invenItem = inven.getAllItemName();
        saveFile << invenItem.size() << endl;
        for (int j = 0; j < (int) invenItem.size(); j++) {
            saveFile << invenItem[j] << endl;
        } 

        if (players[i]->getType() == PlayerType::Breeder) {
            auto breeder = dynamic_cast<Breeder*>(players[i].get());
            auto livestocks = breeder->getRefBarn().getAllDetail();
            saveFile << livestocks.size() << endl;
            for (int k = 0; k < (int) livestocks.size(); k++) {
                saveFile << livestocks[k][0] << " " << livestocks[k][1] << " " << livestocks[k][2] << endl;
            }
        } else if (players[i]->getType() == PlayerType::Farmer) {
            auto breeder = dynamic_cast<Farmer*>(players[i].get());
            auto crops = breeder->getRefField().getAllDetail();
            saveFile << crops.size() << endl;
            for (int k = 0; k < (int) crops.size(); k++) {
                saveFile << crops[k][0] << " " << crops[k][1] << " " <<  crops[k][2] << endl;
            }
        }
    }

    auto storeState = store.getNonCropAndLivestockItems();
    saveFile << storeState.size() << endl;
    for (int i = 0; i < (int) storeState.size(); i++) {
        saveFile << storeState[i].first << " " << storeState[i].second;
        if (i != (int) storeState.size() - 1) {
            saveFile << endl;
        }
    }

    cout << "State berhasil disimpan dalam file " << fileLocation << "!" << endl << endl;
    saveFile.close();
}

void Game::printPlayers() {
    cout << endl << "Total " << players.size() << " Pemain:" << endl;
    for (int i = 0; i < (int) players.size(); i++) {
        cout << i + 1 << ". Username: " << players[i]->getName() << " | Role: ";
        if (players[i]->getType() == PlayerType::Mayor) {
            cout << "Walikota";
        } else if (players[i]->getType() == PlayerType::Farmer) {
            cout << "Petani";
        } else {
            cout << "Peternak";
        }
        if (i == currentPlayer) {
            cout << "  [Current Player]";
        }
        cout << endl;
    }
    cout << endl;
}