#include<vector>

using namespace std;

class Solution {
public:
    bool isSelfCrossing(vector<int>& x) {
        int n = x.size();
        bool blocked = false;
        int len = -1;
        
        for(int i = 2; i < n; ++i){
            if(blocked){
                if(len!=-1){
                    if(x[i] >= len) {
                        return true;
                    }
                    len = -1;
                }
                else{
                   if(x[i] >= x[i-2]) {
                        return true; 
                   }
                }
            }
            if(x[i] <= x[i-2] && !blocked) {
                blocked = true;
                int before4 = i < 4 ? 0 : x[i-4];
                int before3 = i < 3 ? 0 : x[i-3];
                if(x[i] >= x[i-2]- before4){
                   len = x[i-1] - before3;
                }
            }
        }
        return false;
    }
};