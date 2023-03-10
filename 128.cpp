//
// Created by Siqing Zhang on 14/10/2022.
//
#include <vector>
#include <queue>
#include <string>
#include <stack>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        // 去重
        unordered_set<int> num_set;
        for (const int& num : nums) {
            num_set.insert(num);
        }

        int largest = 0;
        // 遍历 去重的set
        for (const int& num : num_set) {
            // 对每个数字i来说 i-1 不在set里 证明当前数字是头，继续寻找尾巴 head 1-2-3-4 tail
            if (num_set.count(num - 1) == 0) {
                int curNum = num;
                int curLarge = 1;

                while (num_set.count(curNum + 1)) {
                    curNum += 1;
                    curLarge += 1;
                }
                // 从头到尾

                largest = max(largest, curLarge);
            }
        }

        return largest;
    }
};


