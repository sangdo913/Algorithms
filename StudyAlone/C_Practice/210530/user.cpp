#include<iostream>
#include<algorithm>
#define R register
using namespace std;

extern double msqrt(double x) ;
inline double ppow(double a) {
   return a * a;
}

static unsigned long long mseed = 5;
static long long mmrand() {
   return (long long)((mseed = (mseed * 25214903917ULL + 11ULL)) >> 16);
}

double len[100000];
int temp[100000];
int indices[100000];

void merge(int indices[100000], int s, int e) {
    R int l = s, m = (s+e)/2, r = m, k = s;
    while(l < m && r < e) {
        temp[k++] = len[indices[l]] < len[indices[r]] ? indices[l++] : indices[r++];
    }
    while(l < m) temp[k++] = indices[l++];
    while(r < e) temp[k++] = indices[r++];
    for(R int i = s ; i < e;++i) indices[i] = temp[i]; 
}

void mergeSort(int indices[100000], int s, int e) {
    if(s+1 >= e) return;
    int m = (s+e)/2;
    mergeSort(indices, s,m);
    mergeSort(indices, m,e);
    merge(indices, s,e);
}

void test(double coord[100000][3], int result[3]) {
    for(R int i = 0; i < 100000; ++i) {
        len[i] = coord[i][0]*coord[i][0] + coord[i][1]*coord[i][1] + coord[i][2] * coord[i][2];
        indices[i] = i;
    }
    mergeSort(indices, 0, 100000);
    // for(R int i = 0; i < 100000; ++i) f << len[indices[i]] << endl;
    R int r[3];
    R int cnt = 1200;
    double res = 1e15;
    while(cnt--) {
        r[0] = indices[mmrand()%3000 + 40000]; 
        r[1] =indices[mmrand()%80 + 99900]; 
        r[2] = indices[mmrand()%20 + 99980];
        double loss = 0;

        for(R int i = 0; i < 100000; i++) {
            double mmin = 1e15;
            for (R int j = 0; j < 3; ++j) {
                double dist = ppow(coord[i][0] - coord[r[j]][0]) + \
                    ppow(coord[i][1] - coord[r[j]][1]) + \
                    ppow(coord[i][2] - coord[r[j]][2]);

                if (dist < mmin) { mmin = dist; }
            }
            loss += msqrt(mmin);
        }
        if(res > loss) {
            res = loss;
            result[0] = r[0];
            result[1] = r[1];
            result[2] = r[2];
        }
    }
}

void uest(double coord[100000][3], int result[3]){
    R int i,j;
     int r[3];
    double res = 1e15;
    R int rr;
    for( j = 95000; j < 100000; ++j) {
        double loss = 0.0;
        indices[j];
        for(i = 95000; i < 100000; ++i){
            double dist = ppow(coord[indices[i]][0] - coord[rr][0]) + \
                ppow(coord[indices[i]][1] - coord[rr][1]) + \
                ppow(coord[indices[i]][2] - coord[rr][2]);

            loss += msqrt(dist);
        }
        if(res > loss) {
            res = loss;
            r[2] = rr;
        }
    }
    res = 1e15;
    rr = r[2];
    R int cnt = 1000;
    while(cnt--) {
        r[0] = indices[mmrand()%85000]; 
        r[1] = indices[mmrand()%10000 + 85000]; 
        r[2] = rr;
        double loss = 0;

        for(R int i = 0; i < 100000; i++) {
            double mmin = 1e15;
            for (R int j = 0; j < 3; ++j) {
                double dist = ppow(coord[i][0] - coord[r[j]][0]) + \
                    ppow(coord[i][1] - coord[r[j]][1]) + \
                    ppow(coord[i][2] - coord[r[j]][2]);

                if (dist < mmin) { mmin = dist; }
            }
            loss += msqrt(mmin);
        }
        if(res > loss) {
            res = loss;
            result[0] = r[0];
            result[1] = r[1];
            result[2] = r[2];
        }
    }
}