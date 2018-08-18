#include<cstdio>
#include<cstring>

int A[2][1001];
int B[1001], n, m;

int SWExpertAcademy3347(){
    int t;
    scanf("%d\n", &t);

    for(int tc = 1; tc <=  t; tc++){
        scanf("%d %d", &n, &m);
        memset(A, 0, sizeof(A));

        for(int i = 1; i <= n; i++){
            scanf("%d \n", &A[0][i]);
        }
        for(int i = 1; i <= m; i++){
            scanf("%d \n", &B[i]);
        }

        for(int i = 1; i <= m; i++) {
            for(int j = 1; j <= n; j++){
                if(A[0][j] <= B[i]) {
                    A[1][j]++;
                    break;
                }
            }
        }

        int res[2] = {-1,0};
        for(int i = 1; i <= n; i++){
           if(A[1][i] > res[0]) {
                res[0] = A[1][i];
                res[1] = i;
           }
        }
        printf("#%d %d\n", tc, res[1]);
    }
    return 0;
}