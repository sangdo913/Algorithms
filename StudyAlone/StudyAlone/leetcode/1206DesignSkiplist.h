#pragma once
#include<iostream>
#include<vector>
using namespace std;
struct NODE {
    int v;
    int level;
    NODE *n[10], *p[10];
}nodes[50000];
NODE levels;
long long myseed;
int myrand() {
    return myseed =(( ((214013LL * myseed + 2531011LL) >> 16)) & 0x7fffffff);
}
class Skiplist {
public:
    int nid;
    
    Skiplist() {
        nid = 0;
        for (int i = 0; i < 10; ++i) levels.n[i] = levels.p[i] = &levels, levels.v = 0x3f3f3f3f;
    }
    bool search(int target) {
        NODE* cur, *ed;
        cur = &levels;
        for (int i = 9; i >= 0; --i) {
            while (cur->v != target && cur->n[i]->v <= target) {
                cur = cur->n[i];
            }
            if (cur->v == target) return true;
        }
        return false;
    }
    void add(int num) {
        int level = 1;
        //int cnt = 100, rand;
        //while (cnt--) {
        //rand = myrand();
        //cout << "rand: " << rand << ' ' << rand%4 << endl;
        //}
        //rand = myrand();
        while (level < 10 && !(myrand() % 4)) level++;
        
        NODE* cur[10];
        cur[9] = &levels;
        for (int i = 9; i >= 0; --i) {
            while (cur[i]->n[i]->v < num) cur[i] = cur[i]->n[i];
            if (i) cur[i - 1] = cur[i];
        }
        NODE& nn = nodes[nid++];
        nn.level = level;
        nn.v = num;
        for (int i = 0; i < level; ++i) {
            nn.n[i] = cur[i]->n[i];
            nn.p[i] = cur[i];
            cur[i]->n[i]->p[i] = &nn;
            cur[i]->n[i] = &nn;
        }
    }
    bool erase(int num) {
        NODE* cur[10];
        cur[9] = &levels;
        for (int i = 9; i >= 0; --i) {
            while (cur[i]->v != num && cur[i]->n[i]->v <= num) cur[i] = cur[i]->n[i];
            if (cur[i]->v == num) {
                for (int j = 0; j < cur[i]->level; ++j) {
                    cur[i]->n[j]->p[j] = cur[i]->p[j];
                    cur[i]->p[j]->n[j] = cur[i]->n[j];
                }
                return true;
            }
            if (i) cur[i - 1] = cur[i];
        }
        return false;
    }
};

int main() {
    freopen("0Text.txt", "r", stdin);
    int n;
    int query;
    cin >> n;
    Skiplist sl;
    while (n--) {
        int num;
        cin >> query >> num;
        bool ans;
        bool res;
        switch (query) {
        case 0:
            sl.add(num); break;
        case 1: 
            res = sl.erase(num);
            cin >> ans;
            if (res != ans) cout << "wrong erase" << endl;
            break;
        case 2: 
            res = sl.search(num);
            cin >> ans;
            if (res != ans) cout << "wrong search" << endl;
            break;
        }
    }
}