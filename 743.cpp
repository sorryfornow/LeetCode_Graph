#include <vector>
#include <queue>
#include <string>
#include <stack>
#include <unordered_map>
#include <algorithm>

using namespace std;



struct cmp{
    bool operator()(vector<int> a, vector<int> b){
        return a[2]>b[2];
    }
};

class Solution {
private:
    const int inf = INT16_MAX-1;
    // bool visitCheck(vector<int>& distance, int n){
    //     for(int i=1;i<n+1;++i){
    //         if (distance[i]==inf) return true;
    //     }
    //     return false;
    // }
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        // int& src = k;
        vector<int> dist(n+1,inf);
        // vector<vector<int>> edges(n+1,vector<int>(n+1,-1));
        // for (auto& arc:times){
        //     edges[arc[0]][arc[1]] = arc[2];
        // }
        dist[k]=0;
        unordered_map< int,vector<vector<int>> > edg;
        for (auto& arc:times){
            edg[arc[0]].emplace_back(arc);
        }
        priority_queue<vector<int>,vector<vector<int>>,cmp> pq;
        // Dijkstra implement hereby
        for (auto& pArc:edg[k]){
            pq.push(pArc);
        }

        while (!pq.empty()){
            auto edge = pq.top();
            pq.pop();
            // cout<<edge[0]<<edge[1]<<' '<<edge[2]<<endl;
            if (dist[edge[0]]+edge[2]< dist[edge[1]]){
                dist[edge[1]] = dist[edge[0]]+edge[2];
                if (dist[edge[1]] != inf){
                    for (auto& pArc:edg[edge[1]]){
                        pq.push(pArc);
                    }
                }
            }
        }

        // for(auto&e:dist){
        //     cout<<e;
        //     cout<<' ';
        // }
        // cout<<endl;

        int res = *max_element(begin(dist)+1,end(dist));
        return res==inf ? -1:res;
    }
};