#include "../../header/Breeder.hpp"
#include "../../header/Exception.hpp"
#include <stdexcept>
#include <limits>
#include <vector>
#include <map>
#include <cmath>

void Breeder::addLivestock()
{
    try
    {
        if (inventory.isEmpty())
        {
            throw EmptyInventoryException();
        }
        if (barn.isFull())
        {
            throw BarnFullException();
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
        while (true)
        {
            try
            {
                cout << "Pilih petak tanah yang akan ditinggali (untuk keluar ketik 'KELUAR'): ";
                cin >> barnLocation;
                if (barnLocation == "KELUAR")
                {
                    throw CancelFunction();
                }
                else if (barn.isEmpty(barnLocation))
                {
                    break;
                }
                else
                {
                    cout << "Petak tanah yang anda pilih sudah penuh" << endl;
                }
            }
            catch (const CancelFunction &e)
            {
                cout << e.what() << endl;
                return;
            }
            catch (const exception &e)
            {
                cout << e.what() << endl;
            }
        }
        if (auto herb = dynamic_pointer_cast<Herbivore>(selectedAnimal)) {
            barn.addLivestock(herb, barnLocation);
        } else if (auto carn = dynamic_pointer_cast<Carnivore>(selectedAnimal)) {
            barn.addLivestock(carn, barnLocation);
        } else if (auto omni = dynamic_pointer_cast<Omnivore>(selectedAnimal)) {
            barn.addLivestock(omni, barnLocation);
        } else {
            throw InvalidTypeException();
        }
        inventory.removeItem(selectedLocation);
        cout << "Dengan hati-hati, kamu meletakkan seekor " << selectedAnimal->getName() << " di kandang." << endl;
        cout << selectedAnimal->getName() << " telah menjadi peliharaanmu sekarang!" << endl;
    }
    catch (const exception &e)
    {
        cout << e.what() << endl;
    }
}

void Breeder::feedLivestock()
{
    try
    {
        if (barn.isEmpty())
        {
            throw NothingToFeedException();
        }

        barn.display();
        string location;
        cout << "Pilih petak kandang: ";
        cin >> location;
        if (barn.getElement(location)->getType() == "HERBIVORE") {
            auto herb = dynamic_pointer_cast<Herbivore>(barn.getElement(location));
            if (!herb) {
                cout << "Casting ke Herbivore gagal, objek bukan Herbivore!\n";
            }
        }
        auto livestock = dynamic_pointer_cast<Livestock>(barn.getElement(location));
        if (livestock == nullptr)
        {
            throw EmptySlotInputException();
        }
        if (!livestock)
        {
            throw InvalidTypeException();
        }
        cout << "Kamu memilih " << livestock->getName() << " untuk diberi makan.\n";
        displayInventory();
        string slot;
        while (true)
        {
            try
            {
                cout << "Pilih pangan yang akan diberikan (untuk keluar ketik 'KELUAR'): ";
                cin >> slot;
                if (slot == "KELUAR")
                {
                    throw CancelFunction();
                    break;
                }
                auto food = dynamic_pointer_cast<Consumable>(inventory.getItem(slot));
                if (food)
                {
                    if (livestock->getType() == "HERBIVORE") {
                        auto herb = dynamic_pointer_cast<Herbivore>(livestock);
                        if (!herb) {
                            cout << "Casting ke Herbivore gagal, objek bukan Herbivore!\n";
                            continue;
                        }
                        livestock->eat(*food);
                        cout << livestock->getName() << " berhasil diberi makan dan beratnya menjadi " << livestock->getCurrentWeight() << endl;
                        inventory.removeItem(slot);
                        break;
                    } else if (livestock->getType() == "CARNIVORE") {
                        dynamic_pointer_cast<Carnivore>(livestock)->eat(*food);
                        cout << livestock->getName() << " berhasil diberi makan dan beratnya menjadi " << livestock->getCurrentWeight() << endl;
                        inventory.removeItem(slot);
                        break;
                    } else if (livestock->getType() == "OMNIVORE") {
                        dynamic_pointer_cast<Omnivore>(livestock)->eat(*food);
                        cout << livestock->getName() << " berhasil diberi makan dan beratnya menjadi " << livestock->getCurrentWeight() << endl;
                        inventory.removeItem(slot);
                        break;
                    }
                }
                else
                {
                    cout << "Barang yang anda pilih dari penyimpanan bukan makanan" << endl;
                }
            }
            catch (const CancelFunction &e)
            {
                cout << e.what() << endl;
                return;
            }
            catch (const exception &e)
            {
                cout << e.what() << endl;
            }
        }
    }
    catch (const exception &e)
    {
        cout << e.what() << endl;
    }
}

void Breeder::displayBarn()
{
    barn.display();
}
void Breeder::harvestLivestock()
{
    try
    {
        displayBarn();

        auto readyToHarvest = barn.countReadyToHarvest();
        if (readyToHarvest.empty())
        {
            throw HarvestNotReadyException();
        }

        int count = 1;
        map<int, pair<string, string>> harvestOptions;
        cout << "Pilih hewan siap panen yang kamu miliki: " << endl;
        for (const auto &pair : readyToHarvest)
        {
            cout << count << ". " << pair.first << " (" << pair.second.first << " petak siap panen)" << endl;
            harvestOptions[count].first = pair.first;
            harvestOptions[count].second = pair.second.second;
            count++;
        }

        int choice;
        while (true)
        {
            cout << "Pilih Nomor hewan yang ingin dipanen (untuk keluar ketik 0): ";
            cin >> choice;
            if (cin.fail() || (choice != 0 && choice < 0) || choice > (int)harvestOptions.size())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Input tidak valid. Harap masukkan nomor yang benar." << endl;
            }
            else if (choice == 0)
            {
                throw CancelFunction();
            }
            else if (harvestOptions.find(choice) == harvestOptions.end())
            {
                cout << "Input tidak sesuai!";
            }
            else
            {
                break;
            }
        }

        string selectedType = harvestOptions[choice].first;
        string selectedLocType = harvestOptions[choice].second;
        int numToHarvest;
        while (true)
        {
            try
            {
                cout << "Berapa petak yang ingin dipanen (untuk keluar ketik 0): ";
                cin >> numToHarvest;
                if (cin.fail() || (numToHarvest != 0 && numToHarvest < 0))
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Input tidak valid. Harap masukkan nomor yang benar." << endl;
                }
                else if (numToHarvest == 0)
                {
                    throw CancelFunction();
                }
                else if (numToHarvest > readyToHarvest[selectedType].first)
                {
                    cout << "Jumlah hewan yang ingin dipanen tidak cukup!" << endl;
                }
                else
                {
                    auto livestock = barn.getElement(selectedLocType);
                    int requiredSpace = livestock->isOmnivore() ? 2 * numToHarvest : numToHarvest;
                    if (requiredSpace > inventory.countEmpty())
                    {
                        throw InventoryFullException();
                        return;
                    }
                    else
                    {
                        break;
                    }
                }
            }
            catch (const CancelFunction &e)
            {
                cout << e.what() << endl;
                return;
            }
            catch (const InventoryFullException &e)
            {
                cout << e.what() << endl;
                return;
            }
            catch (const exception &e)
            {
                cout << e.what() << endl;
            }
        }

        auto livestock = barn.getElement(selectedLocType);
        map<string, vector<string>> harvestedLocations;
        while (numToHarvest > 0)
        {
            string location;
            cout << "Pilih lokasi petak yang akan dipanen : ";
            cin >> location;
            auto livestock = barn.getElement(location);
            if (livestock && livestock->getCode() == selectedType && livestock->isReadyToHarvest())
            {
                vector<Consumable> harvestResult = livestock->getHarvestResult();
                for (const Consumable &item : harvestResult)
                {
                    auto itemPtr = std::make_shared<Consumable>(item);
                    inventory=inventory+itemPtr;
                }
                barn.remove(location);
                harvestedLocations[selectedType].push_back(location);
                numToHarvest--;
            }
            else
            {
                cout << "Petak " << location << " tidak valid atau tidak siap dipanen." << endl;
            }
        }

        cout << "Berhasil memanen:" << endl;
        for (const auto &pair : harvestedLocations)
        {
            cout << pair.second.size() << " petak hewan " << pair.first << " pada petak ";
            for (size_t i = 0; i < pair.second.size(); ++i)
            {
                cout << pair.second[i];
                if (i < pair.second.size() - 1)
                {
                    cout << ", ";
                }
            }
            cout << " telah dipanen!" << endl;
        }
    }
    catch (const exception &e)
    {
        cout << e.what() << endl;
    }
}

int Breeder::getTaxable()
{
    int netWealth = 0;

    // Menghitung nilai dari hewan yang ada di peternakan dan inventory
    int barnWealth = barn.countWealth();
    int inventoryWealth = inventory.countWealth();
    netWealth += barnWealth + inventoryWealth;

    netWealth += gulden;

    int KKP = netWealth - 11;

    double tax = 0;
    if (KKP > 0)
    {
        if (KKP <= 6)
        {
            tax = 0.05 * KKP;
        }
        else if (KKP <= 25)
        {
            tax = 0.15 * KKP;
        }
        else if (KKP <= 50)
        {
            tax = 0.25 * KKP;
        }
        else if (KKP <= 500)
        {
            tax = 0.30 * KKP;
        }
        else
        {
            tax = 0.35 * KKP;
        }
    }
    int roundedTax = round(tax);

    // Jika uang tidak cukup untuk membayar pajak, gunakan uang yang dimiliki saat ini
    tax = min(roundedTax, gulden);

    return tax;
}

PlayerType Breeder::getType()
{
    return PlayerType::Breeder;
}

Barn &Breeder::getRefBarn()
{
    return this->barn;
}

shared_ptr<Player> Breeder::normalizeClone(int _gulden, int _weight) {
    auto clone = make_shared<Breeder>(*this);
    if (clone->weight >= _weight) {
        clone->weight = _weight;
    }
    if (clone->gulden >= _gulden) {
        clone->gulden = _gulden;
    }
    return clone;
}