#include <vector>
#include <queue>
#include <string>
#include <stack>
#include <unordered_map>

using namespace std;

class UnionFindSet{
public:
    vector<int> roots;
    //vector<int> rank;
    UnionFindSet(int n){
        //this->rank = vector<int>(n,1);
        this->roots = vector<int>(n);
        for (int i = 0; i < n; ++i) {
            this->roots[i] = i;
        }
    }
    
    int findRoot(int x){
        if(this->roots[x] == x){
            return x;
        } else{
            this->roots[x] = findRoot(this->roots[x]);
        }
        return this->roots[x];
    }

    void Union(int u, int v){
        int uRoot = findRoot(u);
        int vRoot = findRoot(v);
        if (uRoot != vRoot){
            this->roots[vRoot] = uRoot;
        }
    }

    bool sameRoot(int u, int v){
        int uRoot = findRoot(u);
        int vRoot = findRoot(v);
        if (uRoot != vRoot){
            return false;
        }
        return true;
    }
};

class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        UnionFindSet ufs(edges.size()+1);
        for(auto& edge:edges){
            if(!ufs.sameRoot(edge[0],edge[1])){
                ufs.Union(edge[0],edge[1]);
            } else{
                return edge;
            }
        }
        return edges[0];
    }
};

