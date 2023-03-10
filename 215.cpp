//
// Created by Siqing Zhang on 15/10/2022.
//
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, greater<int>> PQ; //最小堆
        for (const auto &num: nums) {
            if (PQ.size() < k) {
                PQ.push(num);
                // 没满
            } else if (PQ.top() < num) {
                PQ.pop();
                PQ.push(num);

                // 遍历后续时 如果num比PQ顶端最小的元素大，顶端弹出
            }
        }
        return PQ.top();
    }
};