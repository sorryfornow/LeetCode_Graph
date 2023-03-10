//
// Created by Siqing Zhang on 14/10/2022.
//

/* The knows API is defined for you.
      bool knows(int a, int b); */

#include <vector>
#include <queue>
#include <string>
#include <unordered_map>

using namespace std;


// Forward declaration of the knows API.
bool knows(int a, int b);

class Solution {
public:
    int findCelebrity(int n) {
        // 两两比较
        int lastOne = 0;
        for (int i = 1; i < n; ++i) {
            if (knows(lastOne, i)) {
                lastOne = i;
            }
        }
        //
        for (int i = 0; i<n; ++i){
            if (lastOne == i){
                continue;
            }
            if(knows(lastOne, i) || !knows(i, lastOne)){
                return -1;
            }
        }
        return lastOne;
    }
};

