#include<iostream>

using namespace std;
int nums[5] = {10000,1000,100,10,1};
int main(){
    freopen("0Text.txt", "r", stdin);
    int tc;
    cin >> tc;
    while(tc--){
        int b;
        cin >> b;
        int spend = 0;
        for(int i = 0; i < 5; ++i){
            while(nums[i] <= b){
                int cost = (b/nums[i])*nums[i];
                spend+= cost;
                b -= cost;
                b += cost/10;
            }
        }
        cout << spend <<endl;
    }

    return 0;
}