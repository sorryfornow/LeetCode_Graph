#include <vector>
#include <iostream>
using namespace std;

class Solution {
private:
    static constexpr int dirs[4][2]={{0,1},{1,0},{-1,0},{0,-1}};
    int row,col;
    int rDest,cDest;
    bool dfs(vector<vector<int>>& maze, vector<vector<bool>>& visited,int r, int c){
        //cout<< r << c << endl;
        if (rDest == r && cDest == c){
            return true;
        }
        visited[r][c] = true;
        for(int i=0;i<4;++i){
            int rNext = r;
            int cNext = c;
            while(rNext+dirs[i][0]>=0 && rNext+dirs[i][0]<row && cNext+dirs[i][1]>=0 && cNext+dirs[i][1]<col){
                if (maze[rNext+dirs[i][0]][cNext+dirs[i][1]]){
                    break;
                }
                rNext+=dirs[i][0];
                cNext+=dirs[i][1];
            }
            if (!visited[rNext][cNext] && dfs(maze,visited,rNext,cNext)){
                return true;
            }
        }
        return false;
    }
public:
    bool hasPath(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
        this->row = maze.size();
        this->col = maze[0].size();
        this->rDest = destination[0];
        this->cDest = destination[1];
        vector<vector<bool>> visited(row,vector<bool>(col,false));
        return dfs(maze,visited,start[0],start[1]);
    }
};
