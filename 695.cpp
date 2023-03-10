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
    static constexpr int dir[4][2] = {{0,1}, {1,0}, {0,-1},{-1,0}};
public:

    int dfs (vector<vector<int>>& grid, int r, int c, int& area){

        grid[r][c] = 0;
        area++;
        for (auto& [i,j]:dir) {
            int nextR = r+i;
            int nextC = c+j;
            if(nextR<rows && nextR>0 && nextC<columns && nextC>0 && grid[nextR][nextC]){
                area += dfs(grid,nextR,nextC,area);
            }
        }
        return area;
    }

    int maxAreaOfIsland(vector<vector<int>>& grid) {
        rows = grid.size();
        columns = grid[0].size();
        int maxArea = 0;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                if (grid[i][j]){
                    int area =0;
                    max(maxArea,dfs(grid,i,j,area));
                }
            }
        }
        return maxArea;
    }
};