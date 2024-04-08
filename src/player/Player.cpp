#include "header/Player.hpp"

Player::Player(string name){
    this->name=name;
    this->weight=40;
    this->gulden=50;
}

void Player::eat(){
    this->displayInventory();
    bool valid=false;

    while (!valid)
    {
        string input;
        cout << "Slot: ";
        cin >> input;

        cout<<endl;

        try
        {
            Item search=this->inventory.getItem(input);

            if (search.getID()==0 && search.getCode()=="" )
            {
                throw EmptySlotInputException();
            } else if (search.getType()!="PRODUCT_ANIMAL" ||search.getType()!="PRODUCT_FOOD_PLANT")
            {
                throw InvalidSlotInputException();
            }
            
            int addedWeight = search.getAddedWeight();
            this->weight+=addedWeight;
            cout << "Dengan lahapnya, kamu memakan hidangan itu"<<endl;
            cout<<"Alhasil, berat badan kamu naik menjadi "<<this->weight<<endl;

            valid=true;
            
        }
        catch(const exception& e)
        {
            cerr << e.what() << '\n';
        }
    }
}

void Player::displayInventory(){
    this->inventory.display();
}

// void Player::buy(Store& store){
    
//     cout<<"Uang anda: "<<this->gulden;
//     // cout<<"Slot penyimpanan tersedia: "<<this->inventory.sakd

//     try
//     {
        
//     }
//     catch(const exception& e)
//     {
//         cerr << e.what() << '\n';
//     }
    
// }

// void Player::sell(Store& store){
//     cout<<"Berikut merupakan penyimpanan Anda"<<endl;
//     this->displayInventory();
//     bool valid=false;

//     while (!valid)
//     {
//         string input;
//         int tempgulden=0;
//         cout<<"Silahkan pilih petak yang ingin Anda jual!"<<endl;
//         cout << "Petak: ";
//         cin >> input;

//         int count = 1;
//         for (char c : input) {
//             if (c == ',') {
//                 ++count;
//             }
//         }

//         string* parsedInput = new string[count];

//         cout<<endl;

//         try
//         {
//             Item search=this->inventory.getItem(input);

//             if (search.getID()==0 && search.getCode()=="" )
//             {
//                 throw EmptySlotSellException();
//             }

//             tempgulden+=this->inventory.getItem(input).getPrice();
//             this->gulden+=tempgulden;
            
//             this->inventory.removeItem(input);

//             cout<<endl<<"Barang Anda berhasil dijual! Uang Anda bertambah"<<tempgulden<<"gulden!"<<endl;

//             valid=true;
            
//         }
//         catch(const exception& e)
//         {
//             cerr << e.what() << '\n';
//         }
//     }
// }

int Player::getTaxable(){
    return this->gulden;
}
