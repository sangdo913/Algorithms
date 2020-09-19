#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<queue>

using namespace std;

class Solution {
public:
    string largestMultipleOfThree(vector<int>& digits) {
        priority_queue<int> pq[3];
        int allsum = 0;
        for(int i = 0; i < digits.size(); ++i) {
            int num = digits[i];
            allsum+=num;
            pq[num%3].push(-num);
        }
        int r = allsum%3;
        string res;
        switch(r){
            case 1:
                if(pq[1].size() > 0) {
                    pq[1].pop();
                }
                else if(pq[2].size() > 1){
                    pq[2].pop(); pq[2].pop();
                }
                else return "";
                break;
            case 2:
                if(pq[2].size() > 0){
                    pq[2].pop();
                }
                else if(pq[1].size() > 1){
                    pq[1].pop(); pq[1].pop();
                }
                break;
        }
        for(int i = 0; i < 3; ++i) {
            while(pq[i].size()){
                res += -pq[i].top() + '0';
                pq[i].pop();
            }
        }
        sort(res.begin(), res.end());
        reverse(res.begin(), res.end());
        while(res.size() > 1 && res[0] == '0') res.pop_back();
        return res;
    }
};