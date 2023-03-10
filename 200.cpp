//
// Created by Siqing Zhang on 17/10/2022.
//
#include <vector>
#include <queue>
#include <string>
#include <stack>
#include <unordered_map>

using namespace std;

class Solution {
private:
    int rows;
    int columns;
public:
    void dfs(vector<vector<char>>& grid, int r, int c){
        grid[r][c] = '0';
        if (r - 1 >= 0 && grid[r-1][c] == '1') {
            dfs(grid, r - 1, c);
        }
        if (r + 1 < rows && grid[r+1][c] == '1'){
            dfs(grid, r + 1, c);
        }
        if (c - 1 >= 0 && grid[r][c-1] == '1') {
            dfs(grid, r, c - 1);
        }
        if (c + 1 < columns && grid[r][c+1] == '1'){
            dfs(grid, r, c + 1);
        }
    }
    int numIslands(vector<vector<char>>& grid) {
        rows = grid.size();
        columns = grid[0].size();
        int islands = 0;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                if (grid[i][j] == '1') {
                    islands++;
                    dfs(grid, i, j);
                }
            }
        }
        return islands;
    }
};