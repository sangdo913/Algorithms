#include<iostream>

using namespace std;

int maxscore = -1;
struct NODE{
    int idx;
    int score;
    bool mark;
    NODE* next[2];
    int nlen;
    bool isgoal;
    bool isblue;
}nodes[33];
int nums[10];
NODE* mypos[4];

NODE* canmove(NODE* st, int num){
    int nid = st- nodes;
    NODE* ret = 0;
    if(nid == 5 || nid == 10 || nid == 15){
        num--;
        st = st->next[1];
    }
    while(num--){
       st= st->next[0]; 
       if(st->isgoal) return st;
    }
    if(st->mark) return 0;
    return st;
}

int move(int l){
    if(l == 10){
        return 0;
    }
    int max = 0;
    for(int i = 0; i < 4; ++i){
        if(mypos[i] == &nodes[32]) continue;
        NODE* ret = canmove(mypos[i], nums[l]);
        NODE* store;
        if(ret){
            mypos[i]->mark = false;
            store = mypos[i];
            mypos[i] = ret;
            ret->mark = true;
            int res = move(l+1) +ret->score;
            ret->mark = false;
            mypos[i] = store;
            mypos[i]->mark = true;
            max = max < res ? res : max;
        }
    }
    return max;
}

int main(){
    freopen("0Text.txt", "r", stdin);
    int score = 0;
    int nid = 0;
    for(int i = 0; i < 20; ++i){
        nodes[nid].score = score;
        score+=2;
        nodes[nid].next[nodes[nid].nlen++] = &nodes[nid+1];
        nid++;
    }
    nodes[20].score = 40;
    nodes[20].next[0] = &nodes[32];
    nodes[32].isgoal = true;
    nodes[5].isblue = nodes[10].isblue = nodes[15].isblue = true;
    score = 25;
    for(int i = 21; i < 23; ++i){
        nodes[i].next[0] = &nodes[i+1];
        nodes[i].score = score;
        score +=5;
    }
    nodes[23].score = 35;
    nodes[23].next[0] = &nodes[20];
    nodes[5].next[1] = &nodes[24];
    score = 13;
    for(int i = 24; i < 26; ++i){
        nodes[i].next[0] = &nodes[i+1];
        nodes[i].score = score;
        score+=3;
    }
    nodes[26].score = 19;
    nodes[26].next[0] = &nodes[21];
    score = 28;
    nodes[15].next[1] = &nodes[27];
    for(int i = 27; i < 29; ++i){
        nodes[i].next[0] = &nodes[i+1];
        nodes[i].score = score--;
    }
    nodes[29].score = score;
    nodes[29].next[0] = &nodes[21];
    nodes[10].next[1] = &nodes[30];
    nodes[30].next[0] = &nodes[31];
    nodes[30].score = 22;
    nodes[31].score = 24;
    nodes[31].next[0] = &nodes[21];
    mypos[0] = mypos[1] = mypos[2] = mypos[3] = &nodes[0];
    for(int i = 0; i < 10; ++i) cin >> nums[i];
    
    return !(cout << move(0));
}