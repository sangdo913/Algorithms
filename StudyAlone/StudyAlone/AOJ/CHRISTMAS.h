#include<stdio.h>
long long presum[100001];

int ain(){
    int tc;
    int n,k ;
    scanf("%d", &tc);

    while(tc--){
        cin >> n >> k;
        line.clear();

        long long r1 = 0;
        for(int i = 0; i < k; ++i) vec[i].clear();
        vec[0].push_back(0);
        for(int i = 1; i <= n; ++i) {
            int in;
            cin >> in;
            presum[i] = presum[i-1]+in; 
            vec[presum[i]%k].push_back(i);
        }
        for(int i = 0; i < k; ++i){
             r1 = (r1 + ((long long)vec[i].size()*((long long)vec[i].size()-1)/2LL))%20091101;
        }

        for(int i = 0; i < k; ++i){
            for(int j = 0; j < (int)vec[i].size()-1; ++j){
                line.push_back({vec[i][j]+1, vec[i][j+1]});
            }
        }
        sort(line.begin(), line.end(), cmp);
        int lineed = 0;
        int r2 = 0;
        for(int i = 0; i < line.size(); ++i){
            if(lineed >= line[i].s) continue;
            r2++;
            lineed = line[i].e;
        }
        cout << r1 << ' ' << r2 << '\n';
    }
    return 0;
}