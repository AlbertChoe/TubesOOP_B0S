#ifndef GRID_HPP
#define GRID_HPP

#include <vector>
#include <iostream>
using namespace std;

template <typename T>
class Grid
{
private:
    T empty;
    vector<vector<T>> grid;

public:
    Grid();
    void add(T item);
    void add(T item, string location);
    void remove(string location);
    void remove(int row, int col);
    void print(string title);
    int countEmpty();
    int getRow();
    int getCol();
    T *get(string location);
    T *get(int row, int col);
};

#endif