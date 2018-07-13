#include<cstdio>
#include<cstring>

int maxH, n, k, tc;
int visit[10][10] = {0};
int maxes[5][2];    // ���� ���� ���츮�� ����
int maxLen, map[10][10];    //maxLen : ���� ���츮�� ����, map : ���� ����
int dr[4] = {-1,0,1,0}; // ��, �Ʒ�, ����, ������
int dc[4] = {0,1,0,-1};

int max(int i1, int i2){
    return i1 > i2 ? i1 : i2;
}

//�ش� ��, ������ ���� �� ���� ��ȯ
int len(int r, int c, bool dig){

    //���� ��� ������ �ϴ� ���� 1 Ȯ��
    int res = 1;
    
    visit[r][c] = tc;
    
    //��, �Ʒ�, ����, ������
    for(int d = 0; d < 4; d++){
        int nextR = r + dr[d];
        int nextC = c + dc[d];

        //�̹� ���� ��, �� ��
        if(visit[nextR][nextC] == tc) continue;
        if(map[nextR][nextC] == -1) continue;

        if(map[nextR][nextC] < map[r][c]){
            res = max(res, len(nextR, nextC, dig) + 1);
        }
    
        //���� ���츮�� ��� ���
        //���̴� ������ ���ݿ��� 1 ���� ��°� ����
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

                //���� ���� ���츮 ���� ����
                //���� ���� ���츮�� ����
                if(map[i][j] > maxH) {
                    maxLen = 1;
                    maxH = map[i][j];
                    maxes[0][0] = i;
                    maxes[0][1] = j;
                }

                //���� ���츮�� �������� ���
                else if(map[i][j] == maxH){
                    maxes[maxLen][0] = i;
                    maxes[maxLen++][1] = j;
                }
            }
        }

        //���� ���츮�鿡�� ���� �� ��� ���ϱ�
        for(int i = 0; i < maxLen; i++){
            res = max(res, len(maxes[i][0], maxes[i][1], true));
        }

        printf("#%d %d\n", tc, res);
    }
    return 0;
    
}