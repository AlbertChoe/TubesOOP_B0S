#include "../../header/Grid.hpp"

template <typename T>
Grid<T>::Grid(int row, int col)
{
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
            if (grid[i][j] == nullptr)
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
    int col = stoi(location.substr(1)) - 1;
    grid[row][col] = item;
}
template <typename T>
void Grid<T>::remove(string location)
{
    int row, col;
    row = location[0] - 'A';
    int col = stoi(location.substr(1)) - 1;
    grid[row][col] = empty;
}
template <typename T>
void Grid<T>::remove(int row, int col)
{
    grid[row][col] = empty;
}
template <typename T>
T Grid<T>::get(string location)
{
    int row, col;
    row = location[0] - 'A';
    int col = stoi(location.substr(1)) - 1;
    return grid[row][col];
}

template <typename T>
bool Grid<T>::isValid(string location)
{
    if (location.size != 3)
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

template <typename T>
T Grid<T>::get(int row, int col)
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
            if (grid[i][j] == nullptr)
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
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (grid[i][j] != nullptr)
            {
                char r = i + 'A';
                cout << r << endl;
                cout << setfill('0') << setW(2) << j;
                cout << " : " << grid[i][j].getCode() << endl;
            }
        }
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

template <typename T>
bool Grid<T>::isEmpty()
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

template <typename T>
bool Grid<T>::isEmpty(string location)
{
    int row, col;
    row = location[0] - 'A';
    int col = stoi(location.substr(1)) - 1;
    if (grid[row][col] != nullptr)
    {
        return false;
    }
    return true;
}

template <typename T>
bool Grid<T>::isFull()
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