#include<iostream>
#include<queue>
#include<functional>

using namespace std;

int nums[1001], n;
priority_queue<int, vector<int>, greater<int>> pq[1000];

int Do(){
    cin >> n;
    int cnt = 0;
    for(int i = 0; i < n; i++){
        int in; 
        cin >> in;
        nums[in]++;
        pq[0].push(in);
    }

    int now;
    while(pq[cnt].size()){
        now = 0;
        while(pq[cnt].size()){
            int nn = pq[cnt].top(); pq[cnt].pop();

            if(nums[nn] == 0) continue;
            if(now > nn) {
                pq[cnt+1].push(nn);
                continue;
            }

            nums[nn]--;
            now++;
        }
        cnt++;
    }
    cout << cnt;

    return 0;
}