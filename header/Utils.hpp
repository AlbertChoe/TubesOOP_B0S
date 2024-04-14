#ifndef UTILS_HPP
#define UTILS_HPP
#include "Player.hpp"
#include <memory>
#include <vector>
using namespace std;

class Utils {
public:
    static void addNewPlayer(vector<shared_ptr<Player>>& players, int& currentPlayerIndex, shared_ptr<Player> newPlayer);
    static bool isNameInPlayers(const vector<shared_ptr<Player>>& players, string name);
    static string stringToLower(string str);
    static string intToString(int number);
};

#endif