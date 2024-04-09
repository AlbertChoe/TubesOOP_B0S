#include "header/Breeder.hpp"
#include "header/Exception.hpp"

void Breeder::addLivestock() {
    try {
        inventory.display();// INI DICEK LAGI 

        string selectedLocation;
        cout << "Pilih hewan dari penyimpanan : ";
        cin >> selectedLocation;
        Item* selectedAnimal = inventory.getItem(selectedLocation); //INI HARUS RETURN POINTER DI BOS

        if (selectedAnimal == nullptr || (selectedAnimal->getType() != "HERBIVORE" && selectedAnimal->getType() != "CARNIVORE" && selectedAnimal->getType() != "OMNIVORE")) {
            throw InvalidTypeException();
        }

        cout << "Pilih petak tanah yang akan ditinggali : ";
        barn.display();
        string barnLocation;
        cin >> barnLocation;

        if (barn.get(barnLocation) != nullptr) { //INI HARUS RETURN POINTER DI BOS
            throw FullSlotException();
        }

        Livestock* livestock = dynamic_cast<Livestock*>(selectedAnimal); // INI JUGA HARUS DICEK
        if (livestock == nullptr) {
            throw InvalidTypeException();
        }

        barn.addLivestock(livestock, barnLocation);
        inventory.removeItem(selectedLocation);
        cout << "Dengan hati-hati, kamu meletakkan seekor " << livestock->getName() << " di kandang." << endl;
    } catch (const exception& e) {
        cout << e.what() << endl;
    }
}

void Breeder::feedLivestock() {
    try {
        if (barn.countEmpty() == barn.getRow() * barn.getCol()) {
            throw NothingToFeed();
        }

        barn.display();
        string location;
        cout << "Pilih petak kandang yang akan ditinggali: ";
        cin >> location;
        Livestock* livestock = dynamic_cast<Livestock*>(barn.get(location));

        if (livestock == nullptr) {
            throw InvalidTypeException();
        }
        cout << "Kamu memilih " << livestock->getName() << " untuk diberi makan.\nPilih pangan yang akan diberikan: ";

        displayInventory();
        string slot;
        cin >> slot;
        Consumable* food = dynamic_cast<Consumable*>(inventory.getItem(slot));

        if (food == nullptr) {
            throw InvalidTypeException();
        }

        livestock->eat(food->getAddedWeight());
        cout << livestock->getName() << " berhasil diberi makan dan beratnya menjadi " << livestock->getWeight() << endl;
        inventory.removeItem(slot);
    } catch (const exception& e) {
        cout << e.what() << endl;
    }
}

// map<string, int> Breeder::countReadyToHarvest() {
//     map<string, int> readyToHarvest;
//     for (int i = 0; i < barn.getRow(); i++) {
//         for (int j = 0; j < barn.getCol(); j++) {
//             Livestock* livestock = barn.get(i, j);
//             if (livestock != nullptr && livestock->isReadyToHarvest()) {
//                 readyToHarvest[livestock->getCode()]++;
//             }
//         }
//     }
//     return readyToHarvest;
// }


void Breeder::displayBarn() {
    barn.display();
}
void Breeder::harvestLivestock() {
    try {
        displayBarn();

        map<string, int> readyToHarvest = countReadyToHarvest();
        if (readyToHarvest.empty()) {
            throw HarvestNotReadyException();
        }

        int count = 1;
        map<int, string> harvestOptions;
        cout << "Pilih hewan siap panen yang kamu miliki: ";
        for (auto& pair : readyToHarvest) {
            cout << count << ". " << pair.first << " (" << pair.second << " petak siap panen)" << endl;
            harvestOptions[count] = pair.first;
            count++;
        }

        int choice;
        cout << "Pilih Nomor hewan yang ingin dipanen: ";
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

        int requiredSpace = (selectedType == "OMNIVORE") ? 2 * numToHarvest : numToHarvest;
        if (requiredSpace > inventory.countEmpty()) {
            throw NotEnoughInventoryException();
        }

        map<string, vector<string>> harvestedLocations;
        while (numToHarvest > 0) {
            string location;
            cout << "Pilih lokasi petak yang akan dipanen (misal: A1): ";
            cin >> location;
            Livestock* livestock = barn.get(location);
            if (livestock != nullptr && livestock->getCode() == selectedType && livestock->isReadyToHarvest()) {
                vector<Consumable> harvestResult = livestock->harvest();
                for (const Consumable& item : harvestResult) {
                    inventory.addItem(item);
                }
                barn.remove(location);
                harvestedLocations[selectedType].push_back(location);
                numToHarvest--;
            } else {
                 cout << "Petak " << location << " tidak valid atau tidak siap dipanen." << endl;
            }
        }

        cout << "Berhasil memanen:" << endl;
        for (const auto& pair : harvestedLocations) {
            cout << pair.second.size() << " petak hewan " << pair.first << " pada petak ";
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
int Breeder::getTaxable() {
    int netWealth = 0;

    // Menghitung nilai dari hewan yang ada di peternakan
    for (int i = 0; i < barn.getRow(); i++) {
        for (int j = 0; j < barn.getCol(); j++) {
            Livestock* livestock = barn.get(i, j);
            if (livestock != nullptr) {
                netWealth += livestock->getPrice();
            }
        }
    }

    // Menghitung nilai dari barang yang ada di penyimpanan
    for (int i = 0; i < inventory.getRow(); i++) {
        for (int j = 0; j < inventory.getCol(); j++) {
            Item* item = inventory.get(i, j);
            if (item != nullptr) {
                netWealth += item->getPrice();
            }
        }
    }

    // Menambahkan jumlah uang saat ini
    netWealth += gulden;

    // Menghitung Kekayaan Kena Pajak (KKP)
    int KKP = netWealth - 11; // KTKP untuk peternak adalah 11 gulden

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





