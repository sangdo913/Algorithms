#include<iostream>
#include<queue>
#include<algorithm>

using namespace std;

int n, m;
int axs, axb, ays, ayb, bxs,bxb, bys,byb;
pair<int, int> points[4];
int ABS(int i){return i > 0 ? i : -i;}
int MIN(int i1, int i2){
    return i1 < i2? i1 : i2;
}
int MAX(int i1, int i2){
    return i1 < i2 ? i2 : i1;
}
int distance(pair<int, int> st, pair<int, int> dt){
    return ABS(st.first - dt.first ) + ABS(st.second - dt.second);
}

bool cross(int a , int b, int c, int d){
    bool res = false;
    res |= (a == b && c == a) || (a == b && d == a);
    res |= (c == d && c == a) || (c == d && c == b);
    
    return (a < c && d < b) || (c < a && b < d) || res;
}

int plDist(int s1, int b1, int s2, int b2, int flag){
    int res = 0x3f3f3f3f;
    if((s1 < s2 && b2 < b1) ||((s2 == b2)&&((s1 == s2) || (b1 == s2)))){
        if(s1 > 0) res = MIN(res, 2+ ABS(s2-s1)+ABS(b2-s1));
        if(b1 < flag) res = MIN(res, 2+ ABS(b1-b2)+ABS(b1-s2));
    }
    else if ((s2 < s1 &&b1 < b2) || ((s1 == b1) && ((s2 == s1) || (s1 == b2))) ){
        if(s2 > 0){
            res = MIN(res, 2 + ABS(s1-s2) + ABS(b1-s2));
        }
        if(b2 < flag){
            res = MIN(res, 2 + ABS(b2-s1) + ABS(b2 - b1));
        }
    }
    return res;
}
int BOJ5022(){
    cin >> n >> m;
    
    for(int i = 0; i < 4; i++){
        cin >> points[i].first >> points[i].second;
    }
    
    axs = MIN(points[0].first, points[1].first);
    axb = points[0].first + points[1].first - axs;

    ays = MIN(points[0].second, points[1].second);
    ayb = points[0].second + points[1].second -ays;

    bxs = MIN(points[2].first, points[3].first);
    bxb = points[2].first + points[3].first - bxs;

    bys = MIN(points[2].second, points[3].second);
    byb = points[2].second + points[3].second - bys;

    int dist[2] ={distance(points[0], points[1]), distance(points[2], points[3])};

    bool isCross = cross(axs,axb, bxs, bxb) && cross(ays, ayb, bys, byb);
    if(!isCross){
        cout << dist[0] + dist[1];
    }
    else{
        int pl = 0x3f3f3f3f;
        pl = MIN(pl,plDist(axs, axb, bxs, bxb, n));
        pl = MIN(plDist(ays, ayb, bys, byb, m),pl);
        if(pl == 0x3f3f3f3f) cout << "IMPOSSIBLE";
        else cout << dist[0] + dist[1] + pl;
    }
    
    return 0;
}