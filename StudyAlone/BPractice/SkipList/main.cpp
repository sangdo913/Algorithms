#include<cstdio>
#include"user.cpp"
#include<time.h>

using namespace std;

enum COMM {ADD, DELETE, GET};

extern void insert(int, int);
extern void init();
extern void erase(int from, int to);
extern int get(int idx);

int main() {
    clock_t st = clock();
    freopen("0Text.txt", "r", stdin);
    int T, score;
    scanf("%d", &T);
    for (int tc = 1; tc <= T; ++tc) {
        score = 100;
        init();
        int cnt;
        scanf("%d", &cnt);
        int score = 100;
        for (int i = 0; i < cnt; ++i) {
            int comm, idx, val;
            int from, to;
            int res;
            
            scanf("%d", &comm);
            switch (comm) {
            case ADD:
                scanf("%d %d", &idx, &val);
                insert(idx, val);
                break;

            case DELETE:
                scanf("%d %d", &from, &to);
                erase(from, to);
                break;
            case GET:
                scanf("%d", &idx);
                res = get(idx);

                int ans;
                scanf("%d", &ans);
                if(res != ans) 
                     score = 0;
                break;
            }
        }
    }
    printf("%d\n", clock() - st);
    printf("total score : %d\n", score);
    return 0;
}