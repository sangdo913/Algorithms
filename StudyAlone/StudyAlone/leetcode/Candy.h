#include<iostream>
#include<queue>
#include<algorithm>
#include<vector>
#include<tuple>

using namespace std;

class Solution {
public:
    int candy(vector<int>& ratings) {
        if(!ratings.size()) return 0;
        ratings.push_back(0x7fffffff);
        vector<int> mystack;
        vector<int> candies(ratings.size(), 1);

        int totalcandy = 0;
        if(ratings[0] > ratings[1]) mystack.push_back(0);
        else totalcandy = 1;

        for(int i = 1; i < ratings.size()-1; ++i){
            if(ratings[i-1] < ratings[i]){
                if(ratings[i] <= ratings[i+1]) candies[i] = candies[i-1] + 1, totalcandy += candies[i];
                else mystack.push_back(i);
            }
            else if(ratings[i] > ratings[i+1]){
                mystack.push_back(i);
            }
            else{
                totalcandy++;
                while(mystack.size()){
                    int id = mystack.back();
                    mystack.pop_back();
                    int left = id && ratings[id-1] < ratings[id] ? candies[id-1]+1 : 1;
                    int right = candies[id+1] + 1;
                    candies[id] = left> right ? left : right;
                    totalcandy+= candies[id];
                }
            }
        }
        
        return totalcandy;
    }
};

int main(){
    freopen("0Text.txt", "r", stdin);
    int n;
    vector<int> input;
    cin >> n;
    for(int i = 0; i < n; ++i) {
        int in;
        cin >> in;
        input.push_back(in);
    }

    
   cout << Solution().candy(input);
   return 0;
}