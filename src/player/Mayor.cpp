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
            cout << "Masukkan jenis pemain (Ketik 0 untuk membatalkan): ";
            cin >> jenis;

            try
            {
                if (jenis=="0")
                {
                    return;
                }

                if (jenis == "peternak" || jenis == "petani")
                {
                    valid = true;
                } else {
                    throw FarmerBreederInvalidInput();
                }
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
        }

        if (jenis == "peternak")
        {
            auto newBreeder = make_shared<Breeder>("",0,50, gameConfig.getInventoryRow(), gameConfig.getInventoryCol(), gameConfig.getBarnRow(), gameConfig.getBarnCol());
            while (true)
            {
                cout << "Masukkan username untuk player Peternak baru (Ketik 0 untuk keluar): ";
                cin >> nama;
                if (nama=="0")
                {
                    return;
                }

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
            auto newFarmer = make_shared<Farmer>("",0,50, gameConfig.getInventoryRow(), gameConfig.getInventoryCol(), gameConfig.getFieldRow(), gameConfig.getFieldCol());
            while (true)
            {
                cout << "Masukkan username untuk player Petani baru (Ketik 0 untuk keluar): ";
                cin >> nama;
                if (nama=="0")
                {
                    return;
                }

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
        cout<<endl<<"Pemain baru ditambahkan!"<<endl<<"Selamat datang “"<<nama<<"” di kota ini!"<<endl;
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
        player->setGulden(player->getGulden()-tax);
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

    this->setGulden(this->getGulden()+tot);

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

            map<string, int> material = databuilding.getMaterial();


            int firstprint=true;
            for (auto &pairmaterial : material)
            {
                if (!firstprint)
                {
                    cout<<", "<<pairmaterial.first<<" "<<pairmaterial.second;
                } else {
                    firstprint=false;
                    cout<<pairmaterial.first<<" "<<pairmaterial.second;
                }
            }

            cout<<")"<<endl;
            
            idx++;
        }

        cout <<endl<< "Nama bangunan yang ingin dibangun: ";
        cin >> tipebangunan;

        try
        {
            Building foundbuilding = recipe.getConfig(tipebangunan);
            valid = true;

            map<string, int> material = recipe.getConfig(tipebangunan).getMaterial();
            bool accepted = true;
            for (auto &pair : material)
            {
                pair.second -= inventory.getItemCountByName(pair.first);
                if (inventory.getItemCountByName(pair.first) < pair.second)
                {
                    accepted = false;
                }
            }

            if (accepted)
            {
                auto newBuilding = make_shared<Building>(foundbuilding);
                map<string, int> materialdelete = recipe.getConfig(tipebangunan).getMaterial();
                for (auto &pair : materialdelete)
                {
                    inventory.removeItemByCountName(pair.first,pair.second);
                }
                inventory=inventory+newBuilding;
                cout << tipebangunan << " berhasil dibangun dan telah menjadi hak milik walikota!" << endl;
            }
            else
            {
                bool printfirst = false;
                cout << "Kamu tidak punya sumber daya yang cukup! Masih memerlukan ";

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

shared_ptr<Player> Mayor::normalizeClone(int _gulden, int _weight) {
    auto clone = make_shared<Mayor>(*this);
    if (clone->weight >= _weight) {
        clone->weight = _weight;
    }
    if (clone->gulden >= _gulden) {
        clone->gulden = _gulden;
    }
    return clone;
}