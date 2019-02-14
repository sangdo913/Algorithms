#include<iostream>
#include<algorithm>
#include<map>

using namespace std;
map<int, int> mp;

struct FLOOR{
    int l, r, h;
}floor[5000];

int water[5000];

int Do(){
    int n, x1, y1, x2, y2;
    cin >> n;
    n>>=1;
    floor[0].h = 0;

    for(int i = 0; i < n; i++){
        cin >> x1 >> y1 >> x2 >> y2;
        
        floor[i].h = y1;
        floor[i +1].h = y2;

        floor[i].r = x1;
        floor[i+1].l = x2;
    }
    int k;
    cin >> k;

    for(int i =1 ; i < n; i++){
        int key = floor[i].l*40001 + floor[i].r;
        mp.insert({key,i});
    }

    for(int i = 0; i< k; i++){
        cin >> x1 >> y1 >> x2 >> y2;
        int key = x1*40001 + x2;

        int idx = mp[key];
        water[idx] = water[idx] > y1 ? water[idx] : y1;

        for(int i1 = idx -1; i1 > 0; --i1){
            y1 = y1 > floor[i1].h ? floor[i1].h: y1;
            water[i1] = water[i1] > y1 ? water[i1] : y1;
        }

        y1 = y2;
        for(int i1 = idx+1; i1 < n; ++i1){
            y1 = y1 > floor[i1].h ? floor[i1].h : y1;
            water[i1] = water[i1] > y1 ? water[i1] : y1;
        }
    }

    int res = 0;
    for(int i = 1; i < n; i++){
        res += (floor[i].h - water[i])*(floor[i].r - floor[i].l);
    }
    cout << res;
    return 0;
}