#include<cstdio>
#define SIZE 6000000

int box[100][100][100];
int n, m, h;

struct COD{
    int z, x, y;
};

COD que[SIZE];
int fr,re;
int dx[6] = {-1,1,0,0,0,0};
int dy[6] = {0,0,1,-1,0,0};
int dz[6] = {0,0,0,0,1,-1};

bool isout(int x,int y, int z){
    return x < 0 || y < 0 || z < 0 || x >= n || y >= m || z >= h;
}

int ain(){
    scanf("%d%d%d\n", &m, &n, &h);
    int delicous = 0;
    int des = 0;

    for(int i = 0; i < h; ++i) for(int j = 0; j < n; ++j) for(int k = 0; k < m; ++k) {
        scanf("%d ", &box[i][j][k]);
        if(box[i][j][k] == 1) que[re++] = {i,j,k}, ++delicous;
        des += box[i][j][k] != -1;
    } 
    
    int day = 0;
    int cnt = re- fr;

    while(cnt&& des != delicous){
        day++;
        while(cnt--){
            COD c = que[fr++%SIZE], next;
            for(int d = 0; d < 6; ++d){
                next.x = c.x+dx[d];
                next.y = c.y+dy[d];
                next.z = c.z + dz[d];
                if(!isout(next.x,next.y,next.z) && !box[next.z][next.x][next.y]) que[re++%SIZE] = next, delicous++, box[next.z][next.x][next.y] = 1;
            }
        }
        cnt = (SIZE + re%SIZE - fr%SIZE)%SIZE;
    }

    printf("%d\n", des == delicous ? day : -1);
    
    

    return 0;
}