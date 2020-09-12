#include <string>
#include<algorithm>
#include <vector>
#include<set>
#include<iostream>
#include<queue>
#include<map>
using namespace std;

vector<string> solution(vector<string> orders, vector<int> course) {
map<string,int> mp[11];
    vector<string> answer;
    priority_queue<pair<int, string>> pq[11];
    for(int i = 0; i < orders.size(); ++i){
        for(int b = 1; b < (1<<orders[i].size()); ++b){
            sort(orders[i].begin(), orders[i].end());
            int bb = b;
            int cnt = 0;
            string str;
            int bnum= 0;
            while(bb) {
                if(bb & 1) {
                    str.push_back(orders[i][cnt]);
                    bnum++;
                }
                cnt++;
                bb>>=1;
            }
            if(bnum > 1 ) mp[bnum][str]++;
        }
    }
    int mmax= 2;
    for(int i = 0; i < course.size(); ++i) {
        for(auto it : mp[course[i]]){
            if(it.second < mmax ) continue;
            
            pq[course[i]].push({it.second, it.first});
        }
    }
    for(int i = 0; i < course.size(); ++i){
        if(pq[course[i]].size() == 0) continue;
        auto t = pq[course[i]].top();
        pq[course[i]].pop();
        int num = t.first;
        answer.push_back(t.second);
        while(pq[course[i]].size()){
            t = pq[course[i]].top();
            pq[course[i]].pop();
            if(t.first != num) break;
            answer.push_back(t.second);
        }
    }
    sort(answer.begin(), answer.end());
    return answer;
}