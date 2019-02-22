#include<iostream>
#include<cstring>

using namespace std;

int node[101*4];
int lazy[101*4], n;
int line[2][101], idx;

#define MAX(x, y) ((x) > (y) ? (x) : (y))

void insert(int idx, int s, int e, int left, int right, int value){
    node[idx] =  MAX(node[idx], lazy[idx]);
    if(left != right) {
        lazy[idx*2] = MAX(lazy[idx*2], node[idx*2]);
        lazy[idx*2+1] = MAX(lazy[idx*2+1], node[idx*2+1]);
    }

    if(right < s || e < left) return;

    node[idx] = MAX(node[idx], value);

    if(left != right) {
        lazy[idx*2] = MAX(lazy[idx*2], node[idx]);
        lazy[idx*2+1] = MAX(lazy[idx*2+1], node[idx]);
    }

    if(s <= left && right <= e){ return; }

    int m = (left + right)/2;
    insert(idx*2, s,e, left, m, value);
    insert(idx*2+1, s, e, m+1, right, value);
}

int get(int idx, int s, int e, int left, int right){
    node[idx] =  MAX(node[idx], lazy[idx]);

    if(left != right) {
        lazy[idx*2] = MAX(lazy[idx*2], node[idx]);
        lazy[idx*2+1] = MAX(lazy[idx*2+1], node[idx]);
    }

    if(right < s || e < left){
        return -0x3f3f3f3f;
    }

    if(s <= left && right <= e){
        return node[idx];
    }

    int m = (left + right) /2;

    return MAX(get(idx*2, s,e, left, m), get(idx*2+1, s,e, m+1, right));
}

int l = -1000000000;
int r = 1000000000;
int Do(){
    ios_base::sync_with_stdio(0), cout.tie(0), cin.tie(0);

    cin >> n;
    while(n--){
        int a, b, c;
        cin >> a >> b  >> c;

        if(a == 1){
            insert(1, b,c, l, r, c);
            line[0][idx] = b;
            line[1][idx] = c;
        }

        else{
            int x1 = line[0][b], y1 = line[1][b], x2 = line[0][c], y2 = line[1][c];
            int to = get(1, x1,y1, l,r);
            if(x2 < to && to < y2);
        }
    }
    return 0;
}