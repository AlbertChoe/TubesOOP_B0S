#include "../../header/Store.hpp"

Store::Store() {}
Store::~Store() {}
void Store::initStore(CropConfig& cropConfig, LivestockConfig& livestockConfig) {
    auto cropConfigMap = cropConfig.getRefConfigMap();
    for (const auto& pair : cropConfigMap) {
        string code = pair.first;
        Crop crop = pair.second;
        shared_ptr<Item> cropItem = make_shared<Crop>(crop);
        store[code] = make_pair(cropItem, UNLIMITED);
    }

    auto livestockConfigMap = livestockConfig.getRefConfigMap();
    for (const auto& pair : livestockConfigMap) {
        string code = pair.first;
        shared_ptr<Livestock> livestock = pair.second;
        store[code] = make_pair(livestock, UNLIMITED);
    }
}

void Store::refreshStore() {
    for (auto& pair : store) {
        auto item = pair.second.first;
        if (item->getItemType() == ItemType::Livestock || item->getItemType() == ItemType::Crop) {
            pair.second.second = UNLIMITED;
        }
    }
}


void Store::display() {
    int num = 1;
    for (const auto& pair : store) {
        cout << num << ". " << pair.second.first->getName() << " - " << pair.second.first->getPrice();
        if (pair.second.second != UNLIMITED) {
            cout << " (Available: " << pair.second.second << ")";
        }
        cout << endl;
        num++;
    }
}

int Store::getQuantity(string code) {
    auto it = store.find(code);
    if (it != store.end()) {
        return it->second.second;
    }
    return 0;
}

void Store::setQuantity(string code, int quantity) {
    auto it = store.find(code);
    if (it != store.end()) {
        it->second.second = quantity;
    }
}

int Store::getPrice(string code) {
    auto it = store.find(code);
    if (it != store.end()) {
        return it->second.first->getPrice();
    }
    return 0;
}

int Store::getNumItem() {
    return store.size();
}

string Store::getCodeByOrderNum(int num) {
    auto it = store.begin();
    advance(it, num - 1);
    return it->first;
}

shared_ptr<Item> Store::getItem(string code) {
    auto it = store.find(code);
    if (it != store.end()) {
        return it->second.first;
    }
    return nullptr;
}


void Store::buyTransaction(shared_ptr<Player> player) {
    Inventory& inven = player->getRefInventory();
    if (inven.isFull()) {
        cout << "Penyimpanan full, tidak dapat melakukan pembelian!" << endl;
        return;
    }
    cout << "Selamat datang di toko!!" << endl;
    cout << "Berikut merupakan hal yang dapat Anda beli" << endl;
    display();
    cout << endl << "Uang Anda: " << player->getGulden() << endl;
    cout << "Slot penyimpanan tersedia: " << inven.countEmpty() << endl << endl;

    int num, quantity;
    while (true) {
        cout << "Barang yang ingin dibeli (0 = Tidak jadi membeli): ";
        if (!(cin >> num) || num < 0 || num > getNumItem()) {
            cout << "Nomor barang tidak valid!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        if (player->getType() == PlayerType::Mayor && getItem(getCodeByOrderNum(num))->getItemType() == ItemType::Building) {
            cout << "Mayor tidak dapat membeli bangunan!" << endl;
            continue;
        }
        break;
    }

    if (num == 0) {
        cout << "Tidak jadi membeli barang!" << endl;
        return;
    }

    string code = getCodeByOrderNum(num);

    while (true) {
        cout << "Kuantitas (0 = Tidak jadi membeli): ";
        if (!(cin >> quantity) || quantity < 0 || quantity > getQuantity(code) || quantity > inven.countEmpty() || player->getGulden() < quantity * getPrice(code)) {
            cout << "Kuantitas tidak valid atau uang tidak cukup!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        break;
    }

    if (quantity == 0) {
        cout << "Tidak jadi membeli barang!" << endl;
        return;
    }

    player->setGulden(player->getGulden() - (quantity * getPrice(code)));
    cout << "Selamat Anda berhasil membeli " << quantity << " " << getItem(code)->getName() << endl;
    cout << "Uang Anda tersisa " << player->getGulden() << " gulden." << endl << endl;
    cout << "Pilih petak untuk menyimpan barang yang Anda beli!" << endl;
    inven.display();
    string slot;
    int success = 0;
    while (success < quantity) {
        try {
            cout << "Pilihan petak " << success + 1 << ": ";
            cin >> slot;
            if (!inven.isEmpty(slot)) {
                cout << "Petak tidak dapat dipilih!" << endl;
                continue;
            }
            inven.addItem(getItem(code), slot);
            success++;
        } catch (const exception& e) {
            cout << e.what() << endl;
        }

    }
    refreshStore();
    cout << getItem(code)->getName() << " berhasil disimpan dalam penyimpanan!" << endl;
}

void Store::sellTransaction(shared_ptr<Player> player) {
    Inventory& inven = player->getRefInventory();
    PlayerType playerType = player->getType();
    if (inven.isEmpty()) {
        cout << "Penyimpanan kosong, tidak dapat melakukan penjualan!" << endl;
        return;
    }

    if ((playerType == PlayerType::Farmer || playerType == PlayerType::Breeder) && inven.getCountItem() == inven.getCountBuilding()) {
        cout << "Tidak ada barang yang dapat dijual! Petani/peternak tidak dapat menjual bangunan!" << endl;
        return;
    }

    cout << "Berikut merupakan penyimpanan Anda" << endl;
    inven.display();
    int n;
    while (true) {
        cout << "Masukkan berapa barang yang Anda ingin jual (0 = Tidak jadi menjual): ";
        if (!(cin >> n) || 
            ((playerType == PlayerType::Breeder || playerType == PlayerType::Farmer) && n > inven.getCountNonBuilding()) ||
            (playerType == PlayerType::Mayor && n > inven.getCountItem()) ||
            n < 0) {
            cout << "Masukan tidak valid atau jumlah barang yang bisa dijual lebih sedikit!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        break;
    }

    if (n == 0) {
        cout << "Tidak jadi menjual barang!" << endl;
        return;
    }

    cout << "Silahkan pilih petak yang ingin Anda jual!" << endl;
    int gulden = 0;
    string slot;
    int success = 0;
    while (success < n) {
        try {
            cout << "Pilihan petak " << success + 1 << ": ";
            cin >> slot;
            if (inven.isEmpty(slot)) {
                cout << "Petak tidak dapat dipilih!" << endl;
                continue;
            }
            if (inven.getItem(slot)->getItemType() == ItemType::Building &&
                (playerType == PlayerType::Farmer || playerType == PlayerType::Breeder)) {
                cout << "Tidak dapat menjual bangunan!" << endl;
                continue;
            }
            addItem(inven.getItem(slot));
            gulden += inven.getItem(slot)->getPrice();
            inven.remove(slot);
            success++;
        } catch (const exception& e) {
            cout << e.what() << endl;
        }
        
    }
    refreshStore();
    player->setGulden(player->getGulden() + gulden);
    cout << "Barang Anda berhasil dijual! Uang Anda bertambah " << gulden << " gulden!" << endl;
}

void Store::addItem(shared_ptr<Item> item) {
    string code = item->getCode();
    auto it = store.find(code);
    if (it != store.end()) {
        it->second.second++;
    } else {
        store[code] = make_pair(item, 1);
    }
}


