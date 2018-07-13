#include<cstdio>
#include<cstring>

int maxH, n, k, tc;
int visit[10][10] = {0};
int maxes[5][2];    // 가장 높은 봉우리들 저장
int maxLen, map[10][10];    //maxLen : 높은 봉우리들 개수, map : 지형 정보
int dr[4] = {-1,0,1,0}; // 위, 아래, 왼쪽, 오른쪽
int dc[4] = {0,1,0,-1};

int max(int i1, int i2){
    return i1 > i2 ? i1 : i2;
}

//해당 행, 열에서 가장 긴 길이 반환
int len(int r, int c, bool dig){

    //여기 들어 왔으면 일단 길이 1 확보
    int res = 1;
    
    visit[r][c] = tc;
    
    //위, 아래, 왼쪽, 오른쪽
    for(int d = 0; d < 4; d++){
        int nextR = r + dr[d];
        int nextC = c + dc[d];

        //이미 뚫은 곳, 맵 밖
        if(visit[nextR][nextC] == tc) continue;
        if(map[nextR][nextC] == -1) continue;

        if(map[nextR][nextC] < map[r][c]){
            res = max(res, len(nextR, nextC, dig) + 1);
        }
    
        //높은 봉우리인 경우 깎기
        //높이는 무조건 지금에서 1 낮게 깎는게 유리
        else if(dig && map[nextR][nextC] - k < map[r][c]){
            int temp = map[nextR][nextC];
            map[nextR][nextC] =  map[r][c] - 1;

            res = max(res, len(nextR, nextC, false) + 1);

            map[nextR][nextC] = temp;
        }
    }
    
    visit[r][c] = 0;

    return res;
}

int Hike(){
    int t;

    scanf("%d\n", &t);

    for(tc = 1; tc <= t; tc++){
        memset(map, -1, sizeof(map));

        maxLen = 0;
        maxH = 0;

        scanf("%d %d\n", &n, &k);

        int res = 0;

        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){

                scanf("%d \n", &map[i][j]);

                //가장 높은 봉우리 높이 저장
                //가장 높은 봉우리들 저장
                if(map[i][j] > maxH) {
                    maxLen = 1;
                    maxH = map[i][j];
                    maxes[0][0] = i;
                    maxes[0][1] = j;
                }

                //높은 봉우리가 여러개인 경우
                else if(map[i][j] == maxH){
                    maxes[maxLen][0] = i;
                    maxes[maxLen++][1] = j;
                }
            }
        }

        //높은 봉우리들에서 가장 긴 경로 구하기
        for(int i = 0; i < maxLen; i++){
            res = max(res, len(maxes[i][0], maxes[i][1], true));
        }

        printf("#%d %d\n", tc, res);
    }
    return 0;
    
}