#include<vector>

using namespace std;

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int vote;
        int numVote = 0;
        for (auto &num : nums) {
            if (numVote == 0) {
                vote = num;
                numVote = 0;
            }
            if (vote == num) {
                ++numVote;
            } else {
                --numVote;
            }
        }
        return vote;
    }
};