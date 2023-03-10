#include <vector>
#include <iostream>
using namespace std;

class Solution {
private:
    static constexpr int dirs[4][2]={{0,1},{1,0},{-1,0},{0,-1}};
    int row,col;
    int rDest,cDest;
    void dfs(vector<vector<int>>& maze, vector<vector<int>>& visited,int r, int c, int curStep){
        // cout<< r << c << endl;
        if (rDest == r && cDest == c){
            return;
        }
        // visited[r][c] = curStep;
        for(int i=0;i<4;++i){
            int rNext = r;
            int cNext = c;
            int dist =0;
            while(rNext+dirs[i][0]>=0 && rNext+dirs[i][0]<row && cNext+dirs[i][1]>=0 && cNext+dirs[i][1]<col){
                if (maze[rNext+dirs[i][0]][cNext+dirs[i][1]]){
                    break;
                }
                rNext+=dirs[i][0];
                cNext+=dirs[i][1];
                ++dist;
            }
            if (visited[rNext][cNext]<0 || curStep+dist < visited[rNext][cNext]){
                visited[rNext][cNext] = curStep+dist;
                dfs(maze,visited,rNext,cNext,curStep+dist);
            }
        }
    }
public:
    int shortestDistance(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
        this->row = maze.size();
        this->col = maze[0].size();
        this->rDest = destination[0];
        this->cDest = destination[1];
        vector<vector<int>> visited(row,vector<int>(col,-1));
        dfs(maze,visited,start[0],start[1], 0);
        return visited[rDest][cDest];
    }
};
