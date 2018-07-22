#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;

bool visit[102][102];
int max(int i1, int i2){
    return i1 > i2 ? i1 : i2;
}
struct COD{
    int x, y;
};

int dr[4] = {-1,0,1,0};
int dc[4] = {0,1,0,-1};
// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
vector<int> solution(int m, int n, vector<vector<int>> picture) {
    int number_of_area = 0;
    int max_size_of_one_area = 0;
    memset(visit, 0, sizeof(visit));

    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
         queue<COD> que;
        if(picture[i][j] == 0) continue;
            if(visit[i][j] )continue;
            number_of_area++;
            visit[i][j] = true;
            int diffi = picture[i][j];
            que.push({j,i});
            int temp = 0;
            while(que.size()){
                COD now = que.front();
                que.pop();
                temp++;

                for(int d = 0; d < 4; d++){
                    COD next;
                    next.x = now.x + dc[d];
                    next.y = now.y + dr[d];
                    
                    if(next.x >= 0 && next.x < n && next.y >= 0 && next.y <m){
                        if(picture[next.y][next.x] != diffi) continue;
                        if(visit[next.y][next.x]) continue;
                        visit[next.y][next.x] = true;
                        que.push(next);
                    }
                }
            }
            
            max_size_of_one_area = max(temp, max_size_of_one_area);
        }
    }


    vector<int> answer(2);
    answer[0] = number_of_area;
    answer[1] = max_size_of_one_area;
    return answer;
}