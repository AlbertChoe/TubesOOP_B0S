#ifndef GRID_HPP
#define GRID_HPP

#include <vector>
#include <iostream>
using namespace std;

template<typename T>
class Grid {
private:
    vector<vector<T>> grid;
public:
    void add(T item, string location);
    void remove(string location);
    void print(string title);
};

#endif