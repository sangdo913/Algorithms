#include<queue>
#include<vector>
using namespace std;

class Solution {
public:
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
        if(startFuel >= target) return 0;
        int s = 0;
        int n = stations.size();
        priority_queue<int> pq;
        int res = 0;
        
        while(startFuel < target){
            while(s < n && stations[s][0] <= startFuel) pq.push(stations[s++][1]);
            if(pq.empty()) return -1;
            res++;
            startFuel += pq.top(); pq.pop();
        }
        
        return res;
   }
};