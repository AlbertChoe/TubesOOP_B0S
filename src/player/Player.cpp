#include "../../header/Player.hpp"

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
            shared_ptr<Item> search=this->inventory.getItem(input);

            if (search->getID()==0 && search->getCode()=="" )
            {
                throw EmptySlotInputException();
            } else if (search->getType()!="PRODUCT_ANIMAL" ||search->getType()!="PRODUCT_FOOD_PLANT")
            {
                throw InvalidSlotInputException();
            }
            
            shared_ptr<Consumable> consumable = dynamic_pointer_cast<Consumable>(search);
            if (consumable)
            {
                int addedWeight = consumable->getAddedWeight();
                this->weight+=addedWeight;
                cout << "Dengan lahapnya, kamu memakan hidangan itu"<<endl;
                cout<<"Alhasil, berat badan kamu naik menjadi "<<this->weight<<endl;

                valid=true;
            } else {
                throw InvalidSlotInputException();
            }
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

string Player::getName(){
    return this->name;
}

vector<string> parseAndTrimInput(const string& input) {
    vector<string> tokens;
    string token;
    for (char ch : input) {
        if (ch == ',') {
            if (!token.empty()) {
                size_t first = token.find_first_not_of(' ');
                size_t last = token.find_last_not_of(' ');
                if (first != string::npos && last != string::npos) {
                    tokens.push_back(token.substr(first, last - first + 1));
                } else {
                    tokens.push_back("");
                }
            } else {
                tokens.push_back(token);
            }
            token.clear();
        } else {
            token += ch;
        }
    }

    if (!token.empty()) {
        size_t first = token.find_first_not_of(' ');
        size_t last = token.find_last_not_of(' ');
        if (first != string::npos && last != string::npos) {
            tokens.push_back(token.substr(first, last - first + 1));
        } else {
            tokens.push_back("");
        }
    }
    return tokens;
}

int Player::getGulden() {
    return this->gulden;
}

int Player::getWeight() {
    return this->weight;
}

void Player::setName(string _name) {
    this->name = _name;
}

void Player::setGulden(int gulden) {
    this->gulden = gulden;
}

Inventory& Player::getRefInventory() {
    return this->inventory;
}