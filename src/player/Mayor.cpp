#include "../../header/Mayor.hpp"

void Mayor::addNewPlayer(vector<Player>& players){
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
        
        cout<<"Masukkan nama pemain: ";
        cin >> nama;

        if (jenis=="petani")
        {
            players.push_back(new Farmer(nama));
        } else if (jenis=="peternak")
        {
            players.push_back(new Breeder(nama));
        }
        
        this->gulden-=50;

    }
    catch(const exception& e)
    {
        cerr << e.what() << '\n';
    }
    
}

// void Mayor::collectTax(vector<Player>& players){
//     cout<<"Cring cring cring..."<<endl<<"Pajak sudah dipungut!"<<endl<<endl;

//     cout<<"Berikut adalah detil dari pemungutan pajak:"<<endl;

// }

// void Mayor::buildBuilding(const BuildingConfig& recipe){
//     cout<<"Resep bangunan yang ada adalah sebagai berikut."<<endl;
//     cout<<"   1. SMALL_HOUSE (50 gulden, teak wood 1, sandal wood 1)"<<endl;
//     cout<<"   2. MEDIUM_HOUSE (70 gulden, aloe wood 1, ironwood wood 1)"<<endl;
//     cout<<"   3. LARGE_HOUSE (90 gulden, teak wood 2, aloe wood 1, ironwood wood 1)"<<endl;
//     cout<<"   4. HOTEL (150 gulden, teak wood 3, aloe wood 4, ironwood wood 4, sandal wood 2)"<<endl;
//     cout<<endl;

//     string tipebangunan;

//     bool valid=false;

//     while (!valid)
//     {
//         cout<<"Bangunan yang ingin dibangun: ";
//         cin >> tipebangunan;

//         if (this->inventory.getItem())
//         {
//             /* code */
//         }
        
//     }
    
// }

int Mayor::getTaxable(){
    return 0;
}

PlayerType Mayor::getType() {
    return PlayerType::Mayor;
}