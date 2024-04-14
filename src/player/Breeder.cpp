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
        string barnLocation;
        while (true) {
            cout << "Pilih petak tanah yang akan ditinggali (untuk keluar ketik 'KELUAR'): ";
            cin >> barnLocation;
            if ( barn.isEmpty(barnLocation) ) {
                break;
            }else if (barnLocation == "KELUAR"){
                throw CancelFunction();
            }else{
                cout << "Petak tanah yang anda pilih sudah penuh"<<endl;
            }
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

        displayInventory();
        string slot;
        while (true) {
            cout << "Pilih pangan yang akan diberikan (untuk keluar ketik 'KELUAR'): ";
            cin >> slot;
            auto food = dynamic_pointer_cast<Consumable>(inventory.getItem(slot));
            if (food) {
                break;
            }else if (slot == "KELUAR"){
                throw CancelFunction();
            }else{
                cout << "Barang yang anda pilih dari penyimpanan bukan makanan"<<endl;
            }
        }
            
        auto food = dynamic_pointer_cast<Consumable>(inventory.getItem(slot));
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
        while (true) {
            cout << "Pilih Nomor hewan yang ingin dipanen (untuk keluar ketik 0): ";
            cin >> choice;
            if (cin.fail() ||(choice != 0 && choice<0) || choice > (int) harvestOptions.size()) {
                cin.clear(); 
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                cout<<"Input tidak valid. Harap masukkan nomor yang benar."<<endl;
            }else if (choice == 0){
                throw CancelFunction(); 
            }
            else if (harvestOptions.find(choice) == harvestOptions.end()){
                cout << "Input tidak sesuai!";
            }else{
                break;
            }
        }      

        string selectedType = harvestOptions[choice];
        int numToHarvest;
        while (true) {
            cout << "Berapa petak yang ingin dipanen (untuk keluar ketik 0): ";
            cin >> numToHarvest;
            if (cin.fail()||(choice != 0 && choice<0) ) {
                cin.clear(); 
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                cout<<"Input tidak valid. Harap masukkan nomor yang benar."<<endl;
            }else if (choice == 0){
                throw CancelFunction(); 
            }else if (numToHarvest > readyToHarvest[selectedType]){
                cout << "Jumlah hewan yang ingin dipanen tidak cukup!"<<endl;
            }else{
                auto livestock = barn.getElement(selectedType);
                int requiredSpace = livestock->isOmnivore() ? 2 * numToHarvest : numToHarvest;
                if (requiredSpace > inventory.countEmpty()) {
                    cout << "Tidak cukup slot di penyimpanan!"<<endl;
                }else{
                    break;
                }
            }
        }  

        auto livestock = barn.getElement(selectedType);
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