#include "header/Grid.hpp"

template <typename T>
Grid<T>::Grid()
{
    int row, col;
    grid.resize(row, vector<T>(col));
}

template <typename T>
void Grid<T>::add(T item)
{
    int row = grid.size();
    int col = grid[0].size();
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (grid[i][j].is_empty)
            {
                grid[i][j] = item;
                return;
            }
        }
    }
    // throw some error??
}
template <typename T>
void Grid<T>::add(T item, string location)
{
    int row, col;
    row = location[0] - 'A';
    col = 0;
    for (int i = 1; i < location.size(); i++)
    {
        col *= 10;
        col += location[i] - '0';
    }
    grid[row][col] = item;
}
template <typename T>
void Grid<T>::remove(string location)
{
    int row, col;
    row = location[0] - 'A';
    col = 0;
    for (int i = 1; i < location.size(); i++)
    {
        col *= 10;
        col += location[i] - '0';
    }
    grid[row][col] = empty;
}
template <typename T>
void Grid<T>::remove(int row, int col)
{
    grid[row][col] = empty;
}
template <typename T>
T *Grid<T>::get(string location)
{
    int row, col;
    row = location[0] - 'A';
    col = 0;
    for (int i = 1; i < location.size(); i++)
    {
        col *= 10;
        col += location[i] - '0';
    }
    return grid[row][col];
}

template <typename T>
T *Grid<T>::get(int row, int col)
{
    return grid[row][col];
}

template <typename T>
int Grid<T>::countEmpty()
{
    int res = 0;
    int row = grid.size();
    int col = grid[0].size();
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (grid[i][j].is_empty)
            {
                res++;
            }
        }
    }
    return res;
}

template <typename T>
void Grid<T>::print(string title)
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
}

template <typename T>
int Grid<T>::getCol()
{
    return this->grid[0].size();
}
template <typename T>
int Grid<T>::getRow()
{
    return this->grid.size();
}
