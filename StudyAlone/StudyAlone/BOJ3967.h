#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;

int nums[12];
int line[6][4] = {{0,2,5,7}, {0,3,6,10},{1,2,3,4},{7,8,9,10}, {1,5,8,11},{4,6,9,10}};
bool check[13];
void first(int i);
int indexs[6];
int nnum[6];
int icnt = 6;

bool findfill=true;
int fNum = 0;

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
    if(!isvalid()) return false;
    bool findfill = true;

    while(findfill){
        findfill = false;
        first(0);
    }

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


void first(int i){
    if(i == 6) return;

    int cnt = 0;
    int* l = line[i];
    int index0 = -1;
    int sum = 0;
    for(int i = 0; i < 4; i++){
        if(nums[l[i]]) cnt++; 
        if(nums[l[i]] == 0) index0 = l[i];
        sum += nums[l[i]];
    }

    if(cnt == 3){
        findfill = true;
        nums[index0] = 26-sum;
        check[26-sum] = true;
        cnt = 4;
        fNum++;
    }

    nnum[i] = cnt;
    first(i+1);
}


int pos[12][2] = {{0,4},{1,1},{1,3},{1,5}, {1,7},{2,2},{2,6},{3,1},{3,3},{3,5}, {3,7},{4,4}};

int BOJ3967(){
    for(int i = 0; i < 5; i++) cin >> map[i];

    for(int i = 0; i < 12;i++){
        int cod[2] = {pos[i][0], pos[i][1]};
        nums[i] = map[cod[0]][cod[1]]- 'A' + 1;
        if(nums[i] <= 12) {
            check[nums[i]] = true;
            fNum++;
        }
        else{
            nums[i] = 0;
        }
    }

    for(int i = 0; i < 6; i++) indexs[i] = i;

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
        map[pos[i][0]][pos[i][1]] = nums[i];
    }

    for(int i = 0; i < 5; i++) cout << map[i];
    
    return 0;
}