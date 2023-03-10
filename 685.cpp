#include <vector>
#include <queue>
#include <string>
#include <stack>
#include <unordered_map>

using namespace std;


class UnionFindSet{
public:
    vector<int> roots;
    int markFrom = 0;
    int markTo = 0;
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
        } 
        return findRoot(this->roots[x]);
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

    bool conflictProbe(int u, int v){
        int uRoot = findRoot(u);
        int vRoot = findRoot(v);
        if (vRoot != v){
            return false;
        }
        return true;
    }
    
};

class Solution {
public:
    vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
        UnionFindSet ufs(edges.size()+1);
        for(auto& edge:edges){
            if(ufs.sameRoot(edge[0],edge[1])){
                return edge;
            } else if (!ufs.conflictProbe(edge[0],edge[1])){
                ufs.markFrom = edge[0];
                ufs.markTo = edge[1];
            }
            else{
                ufs.Union(edge[0],edge[1]);
            }
        }
        
        return edges[edges.size()-1];
    }
};