#include "../../header/Mayor.hpp"

void Mayor::addNewPlayer(vector<shared_ptr<Player>> &players, int &currentPlayerIndex, GameConfig gameConfig)
{
    try
    {
        if (this->gulden < 50)
        {
            throw NotEnoughAddPlayerException();
        }

        string jenis;
        string nama;

        bool valid = false;

        while (!valid)
        {
            cout << "Masukkan jenis pemain: ";
            cin >> jenis;

            if (jenis == "peternak" || jenis == "petani")
            {
                valid = true;
            }
        }

        if (jenis == "peternak")
        {
            auto newBreeder = make_shared<Breeder>("", gameConfig.getInventoryRow(), gameConfig.getInventoryCol(), gameConfig.getBarnRow(), gameConfig.getBarnCol());
            while (true)
            {
                cout << "Masukkan nama pemain: ";
                cin >> nama;
                if (Utils::isNameInPlayers(players, nama))
                {
                    cout << "Nama sudah diambil, pilih nama lain!" << endl;
                }
                else
                {
                    newBreeder->setName(nama);
                    break;
                };
            }
            Utils::addNewPlayer(players, currentPlayerIndex, newBreeder);
        }
        else if (jenis == "petani")
        {
            auto newFarmer = make_shared<Farmer>("", gameConfig.getInventoryRow(), gameConfig.getInventoryCol(), gameConfig.getFieldRow(), gameConfig.getFieldCol());
            while (true)
            {
                cout << "Masukkan username untuk player Petani baru: ";
                cin >> nama;
                if (Utils::isNameInPlayers(players, nama))
                {
                    cout << "Nama sudah diambil, pilih nama lain!" << endl;
                }
                else
                {
                    newFarmer->setName(nama);
                    break;
                };
            }
            Utils::addNewPlayer(players, currentPlayerIndex, newFarmer);
        }
        this->gulden -= 50;
        cout<<endl<<"Pemain baru ditambahkan!"<<endl<<"Selamat datang “harvest moon” di kota ini!"<<endl;
    }
    catch (const exception &e)
    {
        cerr << e.what() << '\n';
    }
}

void Mayor::collectTax(vector<shared_ptr<Player>> &players)
{
    cout << "Cring cring cring..." << endl
         << "Pajak sudah dipungut!" << endl
         << endl;

    cout << "Berikut adalah detil dari pemungutan pajak:" << endl;
    int i = 1;
    int tot = 0;
    for (auto &player : players)
    {
        int tax = player->getTaxable();
        if (player->getType() == PlayerType::Farmer)
        {
            cout << "   " << i << ". " << player->getName() << " - "
                 << "Petani"
                 << ": " << tax << " gulden" << endl;
        }
        else if (player->getType() == PlayerType::Breeder)
        {
            cout << "   " << i << ". " << player->getName() << " - "
                 << "Peternak"
                 << ": " << tax << " gulden" << endl;
        }
        tot += tax;
        i++;
    }

    cout << endl
         << "Negara mendapatkan pemasukan sebesar " << tot << " gulden." << endl;
    cout << "Gunakan dengan baik dan jangan dikorupsi ya!" << endl;
}

void Mayor::buildBuilding(BuildingConfig recipe)
{

    bool valid = false;

    while (!valid)
    {
        string tipebangunan;

        // cout << "Resep bangunan yang ada adalah sebagai berikut." << endl;
        // cout << "   1. SMALL_HOUSE (50 gulden, teak wood 1, sandal wood 1)" << endl;
        // cout << "   2. MEDIUM_HOUSE (70 gulden, aloe wood 1, ironwood wood 1)" << endl;
        // cout << "   3. LARGE_HOUSE (90 gulden, teak wood 2, aloe wood 1, ironwood wood 1)" << endl;
        // cout << "   4. HOTEL (150 gulden, teak wood 3, aloe wood 4, ironwood wood 4, sandal wood 2)" << endl;
        // cout << endl;
        
        auto data = recipe.getConfigMap();
        int idx=0;
        for (auto &pair : data){
            cout<<"   "<<idx+1<<". "<<pair.first<<" (";
            Building databuilding = recipe.getConfig(pair.first);
            cout<<databuilding.getPrice()<<" gulden";

            map<string, int> material = databuilding.getMaterial();

            for (auto &pairmaterial : material)
            {
                cout<<", "<<pairmaterial.first<<" "<<pairmaterial.second;
            }

            cout<<")"<<endl;
            
            idx++;
        }

        cout <<endl<< "Bangunan yang ingin dibangun: ";
        cin >> tipebangunan;

        try
        {
            Building foundbuilding = recipe.getConfig(tipebangunan);
            valid = true;
            int kuranggulden = 0;

            if (this->getGulden() < foundbuilding.getPrice())
            {
                kuranggulden = foundbuilding.getPrice() - this->getGulden();
            }

            map<string, int> material = recipe.getConfig(tipebangunan).getMaterial();
            bool accepted = true;
            for (auto &pair : material)
            {
                if (inventory.getItemCountByName(pair.first) < pair.second)
                {
                    pair.second -= inventory.getItemCountByName(pair.first);
                    accepted = false;
                }
            }

            if (accepted)
            {
                gulden -= foundbuilding.getPrice();
                auto newBuilding = make_shared<Building>(foundbuilding);
                inventory.addItem(newBuilding);
                // for (auto &pair : material)
                // {
                //     for (int i = 0; i < pair.second; i++)
                //     {
                        
                //     }
                    
                //     pair.second -= inventory.getItemCountByName(pair.first);
                //     accepted = false;
                // }
                //TODO : hapus item bangunan
                cout << tipebangunan << " berhasil dibangun dan telah menjadi hak milik walikota!" << endl;
            }
            else
            {
                bool printfirst = false;
                cout << "Kamu tidak punya sumber daya yang cukup! Masih memerlukan ";
                if (kuranggulden > 0)
                {
                    printfirst = true;
                    cout << kuranggulden << " gulden";
                }

                for (auto &pair : material)
                {
                    if (pair.second > 0)
                    {
                        if (printfirst)
                        {
                            cout << ", " << pair.second << " " << pair.first;
                        }
                        else
                        {
                            printfirst = true;
                            cout << pair.second << " " << pair.first;
                        }
                    }
                }
                cout << "!" << endl;
            }
        }
        catch (const exception &e)
        {
            cout << "Kamu tidak punya resep bangunan tersebut!" << endl;
        }
    }
}

int Mayor::getTaxable()
{
    return 0;
}

PlayerType Mayor::getType()
{
    return PlayerType::Mayor;
}