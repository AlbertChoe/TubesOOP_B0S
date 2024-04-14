#include "../../header/Breeder.hpp"
#include "../../header/Exception.hpp"
#include <stdexcept> 
#include <limits>
#include <vector>
#include <map>
#include <cmath> 

void Breeder::addLivestock() {
    try {
        if (inventory.isEmpty()){
            throw EmptySlotInputException();
        }
        string selectedLocation;
        inventory.display();
        cout << "Pilih hewan dari penyimpanan : ";
        cin >> selectedLocation;
        auto selectedAnimal = inventory.getItem(selectedLocation);

        auto livestock = dynamic_pointer_cast<Livestock>(selectedAnimal);
        if (!livestock) {
            throw InvalidTypeException();
        }
        
        barn.display();
        cout << "Pilih petak tanah yang akan ditinggali : ";
        string barnLocation;
        cin >> barnLocation;

        if ( !barn.isEmpty(barnLocation) ) { 
            throw FullSlotException();
        }

        auto livestockClone = make_shared<Livestock>(*livestock);

        barn.addLivestock(livestockClone, barnLocation);
        inventory.removeItem(selectedLocation);
        cout << "Dengan hati-hati, kamu meletakkan seekor " << livestock->getName() << " di kandang." << endl;
        cout <<livestock->getName()<< "telah menjadi peliharaanmu sekarang!" << endl;
    } catch (const exception& e) {
        cout << e.what() << endl;
    }
}

void Breeder::feedLivestock() {
    try {
        if (barn.isEmpty()) {
            throw NothingToFeedException();
        }

        barn.display();
        string location;
        cout << "Pilih petak kandang: ";
        cin >> location;
        auto livestock = dynamic_pointer_cast<Livestock>(barn.getElement(location));

        if (!livestock) {
            throw InvalidTypeException();
        }
        cout << "Kamu memilih " << livestock->getName() << " untuk diberi makan.\nPilih pangan yang akan diberikan: ";
        cout << "Pilih pangan yang akan diberikan: ";

        displayInventory();
        string slot;
        cin >> slot;
        auto food = dynamic_pointer_cast<Consumable>(inventory.getItem(slot));

        if (!food) {
            throw InvalidTypeException();
        }

        livestock->eat(food->getAddedWeight());
        cout << livestock->getName() << " berhasil diberi makan dan beratnya menjadi " << livestock->getCurrentWeight() << endl;
        inventory.removeItem(slot);
    } catch (const exception& e) {
        cout << e.what() << endl;
    }
}


void Breeder::displayBarn() {
    barn.display();
}
void Breeder::harvestLivestock() {
    try {
        displayBarn();

        auto readyToHarvest = barn.countReadyToHarvest();
        if (readyToHarvest.empty()) {
            throw HarvestNotReadyException();
        }

        int count = 1;
        map<int, string> harvestOptions;
        cout << "Pilih hewan siap panen yang kamu miliki: ";
        for (const auto& pair : readyToHarvest) {
            cout << count << ". " << pair.first << " (" << pair.second << " petak siap panen)" << endl;
            harvestOptions[count++] = pair.first;
        }

        int choice;
        cout << "Pilih Nomor hewan yang ingin dipanen: ";
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

        auto livestock = barn.getElement(selectedType);
        int requiredSpace = livestock->isOmnivore() ? 2 * numToHarvest : numToHarvest;
        if (requiredSpace > inventory.countEmpty()) {
            throw NotEnoughInventoryException();
        }

        map<string, vector<string>> harvestedLocations;
        while (numToHarvest > 0) {
            string location;
            cout << "Pilih lokasi petak yang akan dipanen (misal: A1): ";
            cin >> location;
            auto livestock = barn.getElement(location);
            if (livestock && livestock->getCode() == selectedType && livestock->isReadyToHarvest()) {
                vector<Consumable> harvestResult = livestock->getHarvestResult();
                for (const Consumable& item : harvestResult) {
                    auto itemPtr = std::make_shared<Consumable>(item);
                    inventory.addItem(itemPtr);
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


int Breeder::getTaxable() {
    int netWealth = 0;

    // Menghitung nilai dari hewan yang ada di peternakan dan inventory
    int barnWealth = barn.countWealth();
    int inventoryWealth = inventory.countWealth();
    netWealth += barnWealth + inventoryWealth;


    netWealth += gulden;

    
    int KKP = netWealth - 11;

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

PlayerType Breeder::getType() {
    return PlayerType::Breeder;
}

Barn& Breeder::getRefBarn() {
    return this->barn;
}