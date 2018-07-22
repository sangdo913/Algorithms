#include <vector>
#include<queue>
#include<cstring>
using namespace std;

int MOD = 20170805;
struct WAY{
    int nums[2];

    void clear(){
        nums[0] = nums[1] = 0;
    }
};

bool visit[500][500];

WAY map[500][500];
int dr[4] = {-1,1,0,0};
int dc[4] = {0, 0, -1, 1};
int direct[2][2] = {{0,1},{2,3}};
int direct2[4] = {0,0,1,1};
struct COD{
    int x, y;
};
// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
int solution(int m, int n, vector<vector<int> > city_map) {
    int answer = 0;
    
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++)
            map[i][j].clear();
    }
    
    queue<COD> que;
    memset(visit,false,sizeof(visit));
    visit[0][0] = true;

    map[0][0].nums[0] = 1;
    map[0][0].nums[1] = 0;
    COD c = {0,0};
    que.push(c);
    while(que.size()){
        COD now = que.front();
        que.pop(); 

        if(now.x == n - 1 && now.y == m - 1) {
            answer = map[now.y][now.x].nums[0] + map[now.y][now.x].nums[1];
            break;
            }

        COD next;

        switch(city_map[now.y][now.x]){
            case 0:
            for(int d = 0; d < 4; d++){
                next.y = now.y + dr[d];
                next.x = now.x + dc[d];
                if(next.y < 0 || next.y >= m || next.x < 0 || next.y >= n) continue;
                
                map[next.y][next.x].nums[direct2[d]] = map[now.y][now.x].nums[0] + map[now.y][now.x].nums[1];
                map[next.y][next.x].nums[direct2[d]] %= MOD;

                if(visit[next.y][next.x]) continue;
                visit[next.y][next.x] = true;
                que.push(next);
            }
            break;

            case 2:
            for(int d = 0; d < 4; d++){
                next.y = now.y + dr[d];
                next.x = now.x + dc[d];

                if(next.y < 0 || next.y >= m || next.x < 0 || next.y >= n) continue;
                map[next.y][next.x].nums[direct2[d]] = map[now.y][now.x].nums[direct2[d]] ;
                map[next.y][next.x].nums[direct2[d]] %= MOD;        

                if(visit[next.y][next.x]) continue;
                visit[next.y][next.x] = true;
                que.push(next);
            }
            break;
        }

    }
    
    
    return answer;
}