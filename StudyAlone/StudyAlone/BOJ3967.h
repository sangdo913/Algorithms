//https://www.acmicpc.net/problem/3967
//BOJ3967 매직스타
//
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;

int nums[12];
int line[6][4] = {{0,2,5,7}, {0,3,6,10},{1,2,3,4},{7,8,9,10}, {1,5,8,11},{4,6,9,11}};
bool check[13];
bool first(int i);

bool findfill=true;

char map[5][10];

bool isvalid(){
    bool ch[13]= {};

    for(int i = 0; i < 12; i++){
        if(nums[i] && ch[nums[i]]) return false;
        ch[nums[i]] = true;
    }

    for(int i = 0; i < 6; i++){
        int sum = 0; 
        int fillNum = 0;
        for(int j = 0; j < 4; j++){
            sum += nums[line[i][j]];
            if(nums[line[i][j]]) fillNum++;
        }
        if(fillNum == 4 && sum != 26) return false;
    }
    return true;
}

bool dfs(int idx){
    bool findfill = true;
    while(findfill){
        findfill = false;
        if(!first(0)) return false;
    }

    if(!isvalid()) return false;


    if(idx == 12){
        return true;
    }

    if(nums[idx]) {
        bool res = dfs(idx+1); 
        if(res)
            return true;
        return false;
    }

    int restore[12];
    bool tch[13];
    memcpy(restore, nums,sizeof(nums));
    memcpy(tch, check, sizeof(tch));

    int i;
    for(i = 1; i <= 12; i++){
        if(check[i] == false){
            nums[idx] = i;
            check[i] = true;
            bool res = dfs(idx+1);
            if(res) return true;

            memcpy(nums, restore, sizeof(nums));
            memcpy(check, tch, sizeof(check));
        }
    }

    return false;
}  

bool first(int idx){
    if(idx == 6) return true;

    int cnt = 0;
    int* l = line[idx];
    int index0 = -1;
    int sum = 0;
    for(int i = 0; i < 4; i++){
        if(nums[l[i]]) cnt++; 
        if(nums[l[i]] == 0) index0 = l[i];
        sum += nums[l[i]];
    }

    if(cnt == 3){
		if (26 - sum > 12 || 26 - sum < 0) return false;
        findfill = true;
        nums[index0] = 26-sum;
        check[26-sum] = true;
        cnt = 4;
    }

    return first(idx+1);
}


int pos[12][2] = {{0,4},{1,1},{1,3},{1,5}, {1,7},{2,2},{2,6},{3,1},{3,3},{3,5}, {3,7},{4,4}};

int BOJ3967(){
    for(int i = 0; i < 5; i++) cin >> map[i];

    for(int i = 0; i < 12;i++){
        int cod[2] = {pos[i][0], pos[i][1]};
        nums[i] = map[cod[0]][cod[1]]- 'A' + 1;
        if(nums[i] <= 12) {
            check[nums[i]] = true;
        }
        else{
            nums[i] = 0;
        }
    }

    while(findfill) {
        findfill = false;
        first(0);
    }

    int i;
    for( i = 0; i < 12; i++) {
        if(nums[i] == 0) break;
    }
    dfs(i);
    for(int i = 0; i < 12; i++){
        map[pos[i][0]][pos[i][1]] = nums[i] + 'A'-1;
    }

    for(int i = 0; i < 5; i++) cout << map[i] << '\n';
    
    return 0;
}