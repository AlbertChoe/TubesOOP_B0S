#include "header/Farmer.hpp"
#include "header/Exception.hpp"
using namespace std;

void Farmer::plantCrop() {
    try {
        if (inventory.isEmpty()){
            throw EmptySlotInputException();
        }

        cout << "Pilih Tanaman di penyimpanan:" << endl;
        inventory.display();

        string locationInventory;
        cout << "Slot: ";
        cin >> locationInventory;
        auto item = inventory.getItem(locationInventory);

        if (item == nullptr || (item->getType() != "MATERIAL_PLANT" && item->getType() != "FRUIT_PLANT")) {
            throw InvalidTypeException();
        }
        cout <<"Kamu memilih "<< item->getName() <<"."<< endl;

        cout << "Pilih petak tanah yang akan ditanami:" << endl;
        field.display();
        string location;
        cout << "Petak tanah: ";
        cin >> location;

        if (!field.isEmpty(location)) {
            throw FullSlotException();
        }
        field.addCrop(dynamic_pointer_cast<Crop>(item), location);
        inventory.removeItem(locationInventory);

        cout << "Tanaman berhasil ditanam di " << location << "." << endl;
    } catch (const exception& e) {
        cout << e.what() << endl;
    }
}

// INI DI TEMPAT BOS 
map<string, int> Farmer::countReadyToHarvest() {
    map<string, int> readyToHarvest;
    for (int i = 0; i < field.getRow(); i++) {
        for (int j = 0; j < field.getCol(); j++) {
            Crop* crop = field.get(i, j);
            if (crop != nullptr && crop->isReadyToHarvest()) {
                readyToHarvest[crop->getCode()]++;
            }
        }
    }
    return readyToHarvest;
}

void Farmer::displayField() {
    field.display();
}
void Farmer::harvestCrop() {
    try {
        displayField();

        auto readyToHarvest = countReadyToHarvest();
        if (readyToHarvest.empty()) {
            throw HarvestNotReadyException();
        }

        int count = 1;
        map<int, string> harvestOptions;
        cout << "Pilih nomor tanaman yang ingin dipanen: ";
        for (auto& pair : readyToHarvest) {
            cout << count << ". " << pair.first << " (" << pair.second << " petak siap panen)" << endl;
            harvestOptions[count] = pair.first;
            count++;
        }

        int choice;
        cout << "Nomor tanaman yang ingin dipanen: ";
        cin >> choice;

        if (harvestOptions.find(choice) == harvestOptions.end()) {
            throw WrongInputException();
        }

        string selectedType = harvestOptions[choice];
        int numToHarvest;
        cout << "Berapa petak yang ingin dipanen: ";
        cin >> numToHarvest;

        if (numToHarvest > readyToHarvest[selectedType]) {
            throw NotEnoughToHarvestException();
        }
        if (numToHarvest > inventory.countEmpty()) {
            throw NotEnoughInventoryException();
        }

        map<string, vector<string>> harvestedLocations;
        while (numToHarvest > 0) {
            string location;
            cout << "Pilih lokasi petak yang akan dipanen (misal: A1): ";
            cin >> location;
            auto crop = field.get(location);
            if (crop != nullptr && crop->getCode() == selectedType && crop->isReadyToHarvest()) {
                auto harvestResult = crop->harvest();
                for (const auto& item : harvestResult) {
                    inventory.addItem(item);
                }
                field.remove(location);
                harvestedLocations[selectedType].push_back(location);
                numToHarvest--;
            } else {
                cout << "Petak " << location << " tidak sesuai pilihan atau tidak siap dipanen." << endl;
            }
        }

        cout << "Berhasil memanen:" << endl;
        for (const auto& pair : harvestedLocations) {
            cout << pair.second.size() << " petak tanaman " << pair.first << " pada petak ";
            for (size_t i = 0; i < pair.second.size(); ++i) {
                cout << pair.second[i];
                if (i < pair.second.size() - 1) {
                    cout << ", ";
                }
            }
            cout << " telah dipanen!" << endl;
        }
    } catch (const exception& e) {
        cout << e.what() << endl;
    }
}



// INI TINGGAL UBBAH FUNGIS DAIR BOS
int Farmer::getTaxable() {
    int netWealth = 0;

    // Menghitung nilai dari tanaman yang ada di lahan
    for (int i = 0; i < field.getRow(); i++) {
        for (int j = 0; j < field.getCol(); j++) {
            auto crop = field.get(i, j);
            if (crop != nullptr) {
                netWealth += crop->getPrice();
            }
        }
    }

    // Menghitung nilai dari barang yang ada di penyimpanan
    for (int i = 0; i < inventory.getRow(); i++) {
        for (int j = 0; j < inventory.getCol(); j++) {
            auto item = inventory.get(i, j);
            if (item != nullptr) {
                netWealth += item->getPrice();
            }
        }
    }

    // Menambahkan jumlah uang saat ini
    netWealth += gulden;

    // Menghitung Kekayaan Kena Pajak (KKP)
    int KKP = netWealth - 13; // KTKP untuk petani adalah 13 gulden

    // Menghitung pajak berdasarkan KKP
    int tax = 0;
    if (KKP > 0) {
        if (KKP <= 6) {
            tax = 0.05 * KKP;
        } else if (KKP <= 25) {
            tax = 0.15 * KKP;
        } else if (KKP <= 50) {
            tax = 0.25 * KKP;
        } else if (KKP <= 500) {
            tax = 0.30 * KKP;
        } else {
            tax = 0.35 * KKP;
        }
    }

    // Jika uang tidak cukup untuk membayar pajak, gunakan uang yang dimiliki saat ini
    tax = min(tax, gulden);

    return tax;
}
