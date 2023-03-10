//
// Created by Siqing Zhang on 16/10/2022.
//

#include <vector>
#include <queue>
#include <string>
#include <stack>
#include <unordered_map>

using namespace std;

class Solution1 {
private:
    int rows, columns;
    static constexpr int dir[4][2] ={{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
public:
    int findPath(vector<vector<int>> matrix, vector<vector<int>> explore, int i, int j){
        if (explore[i][j]){
            return explore[i][j];
        }

        explore[i][j]++;
        for (int k = 0; k < 4; ++k) {
            int nextRow = dir[k][0]+i;
            int nextColumn = dir[k][1]+j;
            if (nextColumn>= 0 && nextColumn<columns && nextRow>=0 && nextRow<rows && matrix[nextRow][nextColumn]>matrix[i][j]) {
                explore[i][j] = max(explore[i][j], 1 + findPath(matrix,explore,nextRow,nextColumn));
            }
        }
        return explore[i][j];
    }

    int longestIncreasingPath(vector<vector<int>>& matrix) {
        rows = matrix.size();
        columns = matrix[0].size();
        // 初始化一个2d缓存列表
        vector<vector<int>> explore (rows, vector <int> (columns, 0));
        int maxPath = 1;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                maxPath = max(maxPath,findPath(matrix,explore,i,j));
            }
        }
        return maxPath;
    }
};

class Solution {
private:
    int rows, columns;
    static constexpr int dir[4][2] = {{-1, 0},
                                      {1,  0},
                                      {0,  -1},
                                      {0,  1}};
public:
    int findPath(vector<vector<int>> matrix, vector<vector<int>> explore, int i, int j) {

    }
};