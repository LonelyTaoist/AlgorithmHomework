#include <iostream>
#include <vector>
#include <unordered_set>
#include <random>
#include <ctime>

using namespace std;

int m = 0;

//取一个不同于周围的填涂数字
int diff_m(vector<vector<int>>& method, int x, int y)
{
    unordered_set<int> same;
    for (int i = x - 1; i < x + 3; ++i)
    {
        for (int j = y - 1; j < y + 3; ++j)
        {
            if (i >= 0 && i < method.size() && j >= 0 && j < method[0].size())
            {
                same.insert(method[i][j]);
            }
        }
    }
    int ans;
    do
    {
        ans = rand() % 10;
    } while (same.find(ans) != same.end());
    return ans;
    
}

void DFS(vector<vector<int>>& method, int row_begin, int row_end, int col_begin, int col_end, int x, int y)
{
    if (row_end - row_begin == 2)
    {
        int tmp_x = row_begin, tmp_y = col_begin;
        m = diff_m(method, tmp_x, tmp_y);
        while (tmp_x < row_end)
        {
            if (tmp_x != x || tmp_y != y)
            {
                method[tmp_x][tmp_y] = m;
            }
            ++tmp_y;
            if (tmp_y == col_end)
            {
                ++tmp_x;
                tmp_y = col_begin;
            }
        }
        return;
    }
    int middle_row = (row_begin + row_end) / 2;
    int middle_col = (col_begin + col_end) / 2;
    if (x < middle_row&& y < middle_col)
    {
        DFS(method, row_begin, middle_row, col_begin, middle_col, x, y);
        DFS(method, row_begin, middle_row, middle_col, col_end, middle_row - 1, middle_col);
        DFS(method, middle_row, row_end, col_begin, middle_col, middle_row, middle_col - 1);
        DFS(method, middle_row, row_end, middle_col, col_end, middle_row, middle_col);
        m = diff_m(method, middle_row - 1, middle_col - 1);
        method[middle_row - 1][middle_col] = m;
        method[middle_row][middle_col - 1] = m;
        method[middle_row][middle_col] = m;
    }
    else if (x < middle_row&& y >= middle_col)
    {
        DFS(method, row_begin, middle_row, col_begin, middle_col, middle_row - 1, middle_col - 1);
        DFS(method, row_begin, middle_row, middle_col, col_end, x, y);
        DFS(method, middle_row, row_end, col_begin, middle_col, middle_row, middle_col - 1);
        DFS(method, middle_row, row_end, middle_col, col_end, middle_row, middle_col);
        m = diff_m(method, middle_row - 1, middle_col - 1);
        method[middle_row - 1][middle_col - 1] = m;
        method[middle_row][middle_col - 1] = m;
        method[middle_row][middle_col] = m;
    }
    else if (x >= middle_row&& y < middle_col)
    {
        DFS(method, row_begin, middle_row, col_begin, middle_col, middle_row - 1, middle_col - 1);
        DFS(method, row_begin, middle_row, middle_col, col_end, middle_row - 1, middle_col);
        DFS(method, middle_row, row_end, col_begin, middle_col, x, y);
        DFS(method, middle_row, row_end, middle_col, col_end, middle_row, middle_col);
        m = diff_m(method, middle_row - 1, middle_col - 1);
        method[middle_row - 1][middle_col - 1] = m;
        method[middle_row - 1][middle_col] = m;
        method[middle_row][middle_col] = m;
    }
    else if (x >= middle_row&& y >= middle_col)
    {
        DFS(method, row_begin, middle_row, col_begin, middle_col, middle_row - 1, middle_col - 1);
        DFS(method, row_begin, middle_row, middle_col, col_end, middle_row - 1, middle_col);
        DFS(method, middle_row, row_end, col_begin, middle_col, middle_row, middle_col - 1);
        DFS(method, middle_row, row_end, middle_col, col_end, x, y);
        m = diff_m(method, middle_row - 1, middle_col - 1);
        method[middle_row - 1][middle_col - 1] = m;
        method[middle_row - 1][middle_col] = m;
        method[middle_row][middle_col - 1] = m;
    }
}

int main()
{
    srand(time(0));
    int length = 0, x= 0, y = 0;
    cout << "请输入正方形地板的边长(2的幂)以及不铺地板的空格位置(行列)：";
    cin >> length >> x >> y;
    vector<vector<int>> method(length, vector<int>(length, -1));
    DFS(method, 0, length, 0, length, x, y);
    for (auto i : method)
    {
        for (auto j : i)
        {
            if (j == -1)
            {
                cout << "  ";
            }
            else 
            {
                cout << j << ' ';
            }
        }
        cout << endl;
    }
    return 0;
}