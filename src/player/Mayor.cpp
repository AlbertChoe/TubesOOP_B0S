#include "../../header/Mayor.hpp"

void Mayor::addNewPlayer(vector<shared_ptr<Player>>& players){
    try
    {
        if (this->gulden<50)
        {
            throw NotEnoughAddPlayerException();
        }

        string jenis;
        string nama;

        bool valid=false;

        while (!valid)
        {
            cout<<"Masukkan jenis pemain: ";
            cin >> jenis;

            if (jenis=="peternak"||jenis=="harvest moon")
            {
                valid=true;
            }
        }

        if (jenis=="peternak")
        {
            auto newBreeder = make_shared<Breeder>("", 10, 10, 10, 10);
            while (true) {
                cout << "Masukkan nama pemain: ";
                cin >> nama;
                if (Utils::isNameInPlayers(players, nama)) {
                    cout << "Nama sudah diambil, pilih nama lain!" << endl;
                } else {
                    newBreeder->setName(nama);
                    break;
                };
            }
            Utils::addNewPlayer(players, newBreeder);
        } else if (jenis=="petani")
        {
            auto newFarmer = make_shared<Farmer>("", 10, 10, 10, 10);
            while (true) {
                cout << "Masukkan username untuk player Petani baru: ";
                cin >> nama;
                if (Utils::isNameInPlayers(players, nama)) {
                    cout << "Nama sudah diambil, pilih nama lain!" << endl;
                } else {
                    newFarmer->setName(nama);
                    break;
                };
            }
        Utils::addNewPlayer(players, newFarmer);
        }
        this->gulden-=50;
    }
    catch(const exception& e)
    {
        cerr << e.what() << '\n';
    }
}

void Mayor::collectTax(vector<shared_ptr<Player>>& players){
    cout<<"Cring cring cring..."<<endl<<"Pajak sudah dipungut!"<<endl<<endl;

    cout<<"Berikut adalah detil dari pemungutan pajak:"<<endl;
    int i = 1;
    int tot = 0;
    for (auto& player : players)
    {
        int tax = player->getTaxable();
        if (player->getType()==PlayerType::Farmer)
        {
            cout <<"   " <<i<<". " << player->getName() <<" - "<< "Petani"<<": "<<tax <<" gulden"<<endl;
        } else if (player->getType()==PlayerType::Breeder)
        {
            cout <<"   " <<i<<". " << player->getName() <<" - "<< "Peternak"<<": "<<tax <<" gulden"<<endl;
        }
        tot+=tax;
        i++;
    }

    cout<<endl<<"Negara mendapatkan pemasukan sebesar "<< tot <<" gulden."<<endl;
    cout<<"Gunakan dengan baik dan jangan dikorupsi ya!"<<endl;

}

void Mayor::buildBuilding(const BuildingConfig& recipe){
    cout<<"Resep bangunan yang ada adalah sebagai berikut."<<endl;
    cout<<"   1. SMALL_HOUSE (50 gulden, teak wood 1, sandal wood 1)"<<endl;
    cout<<"   2. MEDIUM_HOUSE (70 gulden, aloe wood 1, ironwood wood 1)"<<endl;
    cout<<"   3. LARGE_HOUSE (90 gulden, teak wood 2, aloe wood 1, ironwood wood 1)"<<endl;
    cout<<"   4. HOTEL (150 gulden, teak wood 3, aloe wood 4, ironwood wood 4, sandal wood 2)"<<endl;
    cout<<endl;

    string tipebangunan;

    bool valid=false;

    while (!valid)
    {
        cout<<"Bangunan yang ingin dibangun: ";
        cin >> tipebangunan;

        if (tipebangunan=="SMALL_HOUSE" || tipebangunan=="MEDIUM_HOUSE" || tipebangunan=="LARGE_HOUSE" || tipebangunan=="HOTEL")
        {
            valid=true;

            try
            {
                if (tipebangunan=="SMALL_HOUSE")
                {
                    /* code */
                } else if (tipebangunan=="MEDIUM_HOUSE")
                {
                    /* code */
                } else if (tipebangunan=="LARGE_HOUSE")
                {
                    /* code */
                } else if (tipebangunan=="HOTEL")
                {
                    /* code */
                }
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
        } else {
            cout<<"Kamu tidak punya resep bangunan tersebut!"<<endl<<endl;
            cout<<"Resep bangunan yang ada adalah sebagai berikut."<<endl;
            cout<<"   1. SMALL_HOUSE (50 gulden, teak wood 1, sandal wood 1)"<<endl;
            cout<<"   2. MEDIUM_HOUSE (70 gulden, aloe wood 1, ironwood wood 1)"<<endl;
            cout<<"   3. LARGE_HOUSE (90 gulden, teak wood 2, aloe wood 1, ironwood wood 1)"<<endl;
            cout<<"   4. HOTEL (150 gulden, teak wood 3, aloe wood 4, ironwood wood 4, sandal wood 2)"<<endl;
            cout<<endl;
        }
        
    }
    
}

int Mayor::getTaxable(){
    return 0;
}

PlayerType Mayor::getType() {
    return PlayerType::Mayor;
}