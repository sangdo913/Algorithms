#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>

using namespace std;

struct mcmp{
    bool operator()(const vector<int> &v1, const vector<int> &v2){
        return v1[1] < v2[1];
    }
};
class Solution {
public:
    int scheduleCourse(vector<vector<int>>& courses) {
        sort(courses.begin(), courses.end(),mcmp());
        int res = 0;
        priority_queue<int> pq;
        int mytime = 0;
        for(int i = 0; i < courses.size(); ++i){
            if(mytime + courses[i][0] <= courses[i][1]){
                mytime+=courses[i][0];
                pq.push(courses[i][0]);
            }
            else {
                if(!pq.empty() && pq.top() > courses[i][0]){
                    mytime += courses[i][0] - pq.top();
                    pq.pop();
                    pq.push(courses[i][0]);
                }
            }
        }
        return pq.size();
    }
};