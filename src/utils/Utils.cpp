#include "../../header/Utils.hpp"

void Utils::addNewPlayer(vector<shared_ptr<Player>>& players, shared_ptr<Player> newPlayer) {
    auto it = players.begin();
    while (it != players.end() && (*it)->getName() < newPlayer->getName()) {
        it++;
    }
    players.insert(it, newPlayer);
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