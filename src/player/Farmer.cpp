#include "../../header/Farmer.hpp"
#include "../../header/Exception.hpp"
#include <stdexcept> 
#include <limits>
#include <vector>
#include <map>
#include <cmath>

void Farmer::plantCrop() {
    try {
        if (inventory.isEmpty()){
            throw EmptySlotInputException();
        }

        inventory.display();
        cout << "Pilih Tanaman di penyimpanan:" << endl;

        string locationInventory;
        cout << "Slot: ";
        cin >> locationInventory;
        auto item = inventory.getItem(locationInventory);

        if (item == nullptr || (item->getType() != "MATERIAL_PLANT" && item->getType() != "FRUIT_PLANT")) {
            throw InvalidTypeException();
        }
        cout <<"Kamu memilih "<< item->getName() <<"."<< endl;

        field.display();
        cout << "Pilih petak tanah yang akan ditanami:" << endl;
        string location;
        cout << "Petak tanah: ";
        cin >> location;

        if (!field.isEmpty(location)) {
            throw FullSlotException();
        }
        auto cropItem = dynamic_pointer_cast<Crop>(item);
        if (!cropItem) {
            throw InvalidTypeException();  
        }

        auto clonedCrop = make_shared<Crop>(*cropItem);
        field.addCrop(clonedCrop, location);
        inventory.removeItem(locationInventory);

        cout << "Cangkul, cangkul, cangkul yang dalam~!\n" <<clonedCrop->getName()<<"berhasil ditanam!"<< endl;
    
    } catch (const exception& e) {
        cout << e.what() << endl;
    }
}

void Farmer::displayField() {
    field.display();
}
void Farmer::harvestCrop() {
    try {
        displayField();

        map<string, int> readyToHarvest = field.countReadyToHarvest();
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
        if (cin.fail() || choice < 1 || choice > (int) harvestOptions.size()) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            throw invalid_argument("Input tidak valid. Harap masukkan nomor yang benar.");
        }

        if (harvestOptions.find(choice) == harvestOptions.end()) {
            throw WrongInputException();
        }

        string selectedType = harvestOptions[choice];
        int numToHarvest;
        cout << "Berapa petak yang ingin dipanen: ";
        cin >> numToHarvest;
        if (cin.fail() || choice < 1 ) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            throw invalid_argument("Input tidak valid. Harap masukkan nomor yang benar.");
        }

        if (numToHarvest > readyToHarvest[selectedType]) {
            throw NotEnoughToHarvestException();
        }
        if (numToHarvest > inventory.countEmpty()) {
            throw NotEnoughInventoryException();
        }

        map<string, vector<string>> harvestedLocations;
        while (numToHarvest > 0) {
            string location;
            cout << "Pilih petak yang akan dipanen (misal: A1): ";
            cin >> location;
            auto crop = field.getElement(location);
            if (crop != nullptr && crop->getCode() == selectedType && crop->isReadyToHarvest()) {
                vector<Consumable> harvestResult = crop->getHarvestResult();
                for (const auto& item : harvestResult) {
                    auto itemPtr = make_shared<Consumable>(item);
                    inventory.addItem(itemPtr);
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


int Farmer::getTaxable() {
    int netWealth = 0;

    // Menghitung nilai dari hewan yang ada di peternakan dan inventory
    int fieldWealth = field.countWealth();
    int inventoryWealth = inventory.countWealth();
    netWealth += fieldWealth + inventoryWealth;

    netWealth += gulden;

  
    int KKP = netWealth - 13; 

    double tax = 0;
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
    int roundedTax = round(tax);

    // Jika uang tidak cukup untuk membayar pajak, gunakan uang yang dimiliki saat ini
    tax = min(roundedTax, gulden);

    return tax;
}

PlayerType Farmer::getType() {
    return PlayerType::Farmer;
}