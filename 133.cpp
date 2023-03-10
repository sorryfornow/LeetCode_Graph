#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};


class Solution {
public:
    Node* cloneGraph(Node* node) {
        typedef Node* ND;
        if (node == nullptr) {
            return node;
        }

        // initialization
        unordered_map<ND,ND> visited;
        queue<ND> Q;
        Q.push(node);
        visited[node] = new Node(node->val);

        while (!Q.empty()) {
            ND cur = Q.front();
            Q.pop();

            for (ND& adjN: cur->neighbors) {
                if (visited.find(adjN) == visited.end()) {
                    // not been visited
                    visited[adjN] = new Node(adjN->val);
                    Q.push(adjN);
                }
                visited[cur]->neighbors.emplace_back(visited[adjN]);
            }
        }
        return visited[node];
    }
};

