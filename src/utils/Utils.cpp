#include "../../header/Utils.hpp"

void Utils::addNewPlayer(vector<shared_ptr<Player>>& players, int& currentPlayerIndex, shared_ptr<Player> newPlayer) {
    auto it = players.begin();
    int idx = 0;
    while (it != players.end() && stringToLower((*it)->getName()) < stringToLower(newPlayer->getName())) {
        it++;
        idx++;
    }
    players.insert(it, newPlayer);
    if (idx <= currentPlayerIndex) {
        currentPlayerIndex++;
    }
}

string Utils::stringToLower(string str) {
    for (char& c : str) {
        if (c >= 'A' && c <= 'Z') {
            c += 'a' - 'A';
        }
    }
    return str;
}

bool Utils::isNameInPlayers(const vector<shared_ptr<Player>>& players, string name) {
    for (const auto& player : players) {
        if (Utils::stringToLower(player->getName()) == Utils::stringToLower(name)) {
            return true;
        }
    }
    return false;
}

string Utils::intToString(int number) {
    if (number == 0) return "0"; 
    std::string result = "";
    while (number > 0) {
        char digit = '0' + (number % 10);
        result = digit + result;
        number /= 10;
    }

    return result;
}