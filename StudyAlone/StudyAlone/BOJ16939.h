#include<iostream>

using namespace std;

int rot[6][4][2]{
    { {3,4}, {17,19}, {10,9}, {16,14} },
    { {1,3},{5,7},{9,11},{24,22} },
    { {4,2}, {21,23}, {12,10}, {8,6} },
    { {2,1}, {13,15}, {11,12}, {20,18} },
    { {11,12}, {18,17}, {6,5}, {14,13} },
    { {7,8}, {19,20}, {23,24}, {15,16} }
};

int origin[25];

void rr(int i){
    int temp[2] = {rot[i][0][0], rot[i][0][1]};
    temp[0] = origin[temp[0]];
    temp[1] = origin[temp[1]];

    for(int d = 0; d < 3; d++){
        int to[2] = {rot[i][d][0], rot[i][d][1]};
        int from[2] = {rot[i][d+1][0], rot[i][d+1][1]};

        origin[to[0]] = origin[from[0]];
        origin[to[1]] = origin[from[1]];
    }

    origin[rot[i][3][0]] = temp[0];
    origin[rot[i][3][1]] = temp[1];
}

bool check(){
    for(int i = 0; i < 6; i++){
        for(int j = 1; j < 4; j++){
            if(origin[i*4+1] != origin[i*4+ j+1]) return false;
        }
    }
    return true;
}
    
int Do(){
    for(int i = 1; i <= 24; i++){
        cin >> origin[i];
    }

    for(int i = 0; i < 6; i++){
        rr(i);
        if(check()) return !(cout << 1);
        
        rr(i);
        rr(i);
        if(check()) return !(cout << 1);
        rr(i);
    }
    cout << 0;
    return 0;
}