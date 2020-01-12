#include<vector>
#include<iostream>
#include<map>
#include<algorithm>
#include<functional>


using namespace std;

#define pii pair<int, int>

vector<vector<int>> *v;
bool cmp(const pii &a, const pii &b){
    int coda, codb;

    coda = (*v)[a.first][a.second == -1];
    codb = (*v)[b.first][b.second == -1];
    return coda < codb;
}

class Solution {
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        vector<pair<int, int>> vec;
        for(int i = 0; i < buildings.size(); ++i){
            vec.push_back({i, 1});
            vec.push_back({i, -1});
        }
        sort(vec.begin(), vec.end(), cmp);
        map<int, int, greater<int>> heights;

        vector<vector<int>> res;
        heights[0] = 1;
        for(int i = 0; i < vec.size(); ++i){
            int prev = vec[i].first;
            while(prev == vec[i].first){
                heights[vec[i].first] += vec[i].second;
                if(heights[vec[i].first] == 0)  heights.erase({vec[i].first});
                ++i;
                if(i == vec.size()) break;
            }
            res.push_back({prev, heights.begin()->first});
        }
        return res;
    }
};

int main(){
    
    return 0;
}