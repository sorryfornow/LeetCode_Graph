//
// Created by Siqing Zhang on 2022/8/19.
//
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> out(numCourses);
        int indexOut = 0;
        vector<vector<int>> edges(numCourses);
        vector<int> inDegree(numCourses);
        for (const vector<int>& pre: prerequisites) {
            edges[pre[1]].push_back(pre[0]);
            inDegree[pre[0]]++;
        }

        queue<int> Q;
        for (int i = 0; i < numCourses; ++i) {
            if (inDegree[i] == 0) {
                Q.push(i);
            }
        }

        int visited = 0;
        while (!Q.empty()) {
            visited++;
            int u = Q.front();

            out[indexOut] = u;
            indexOut++;

            Q.pop();
            for (int v: edges[u]) {
                inDegree[v]--;
                if (inDegree[v] == 0) {
                    Q.push(v);
                }
            }
        }
        if (visited != numCourses) {
            out.clear();
        }
        //return out;
        return visited == numCourses;
    }
};

