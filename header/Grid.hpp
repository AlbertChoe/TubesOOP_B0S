#ifndef GRID_HPP
#define GRID_HPP

#include <vector>
#include <iostream>
#include <memory>
#include <iomanip>
#include <map>
#include "Exception.hpp"
using namespace std;

template <typename T>
class Grid
{
private:
    T empty;
    vector<vector<T>> grid;

public:
    Grid(int row, int col)
    {
        grid.resize(row, vector<T>(col));
    }

    void add(T item)
    {
        int row = grid.size();
        int col = grid[0].size();

        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                if (grid[i][j] == nullptr)
                {
                    grid[i][j] = item;
                    return;
                }
            }
        }
        // throw some error??
    }

    void add(T item, string location)
    {
        int row, col;
        row = location[0] - 'A';
        col = stoi(location.substr(1)) - 1;
        grid[row][col] = item;
    }

    void remove(string location)
    {
        int row, col;
        row = location[0] - 'A';
        col = stoi(location.substr(1)) - 1;
        grid[row][col] = empty;
    }

    void remove(int row, int col)
    {
        grid[row][col] = empty;
    }

    T get(string location)
    {
        int row, col;
        row = location[0] - 'A';
        col = stoi(location.substr(1)) - 1;
        return grid[row][col];
    }

    bool isValid(string location)
    {
        if (location.size() != 3)
        {
            int row = location[0] - 'A';
            if (row < 0 || row > 26)
            {
                throw InvalidRow();
            }
            int col = stoi(location.substr(1)) - 1;
            if (col < 0)
            {
                throw InvalidCol();
            }
            if (row >= grid.size() || col >= grid[0].size())
            {
                throw InvalidIndex();
            }
            return true;
        }
        else
        {
            throw InvalidCode();
        }
    }

    T get(int row, int col)
    {
        return grid[row][col];
    }

    int countEmpty()
    {
        int res = 0;
        int row = grid.size();
        int col = grid[0].size();
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                if (grid[i][j] == nullptr)
                {
                    res++;
                }
            }
        }
        return res;
    }

    void print(string title)
    {
        int row = grid.size();
        int col = grid[0].size();
        cout << title << endl;
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                cout << "+-----+";
            }

            cout << endl;
            for (int j = 0; j < 10; j++)
            {
                cout << "| " << grid[i][j] << " |";
            }
            cout << endl;

            for (int j = 0; j < 10; j++)
            {
                cout << "+-----+";
            }
            cout << endl;
        }
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                if (grid[i][j] != nullptr)
                {
                    char r = i + 'A';
                    cout << r << endl;
                    cout << setfill('0') << setw(2) << j;
                    cout << " : " << grid[i][j].name << endl;
                }
            }
        }
    }

    void printElementType()
    {
        int row = grid.size();
        int col = grid[0].size();
        map<string, string> mp;
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                map[grid[i][j].code] = grid[i][j].name;
            }
        }

        while (it != mp.end())
        {
            cout << it->first << ": "
                 << it->second << endl;
            ++it;
        }
    }

    int getCol()
    {
        return this->grid[0].size();
    }

    int getRow()
    {
        return this->grid.size();
    }

    bool isEmpty()
    {
        int row = grid.size();
        int col = grid[0].size();
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                if (grid[i][j] != nullptr)
                {
                    return false;
                }
            }
        }
        return true;
    }

    bool isEmpty(string location)
    {
        int row, col;
        row = location[0] - 'A';
        col = stoi(location.substr(1)) - 1;
        if (grid[row][col] != nullptr)
        {
            return false;
        }
        return true;
    }

    bool isFull()
    {
        int row = grid.size();
        int col = grid[0].size();
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                if (grid[i][j] == nullptr)
                {
                    return false;
                }
            }
        }
        return true;
    }
};

#endif