#include<cstdio>

bool nfirst;
int memo[5][5][5][5][5];
int count[6];
const int conv[5] = {1,5,25,125,625};
int charconv[256];
#define F(A,i,j) charconv[A[i][j][0]]
#define S(A,i,j) charconv[A[i][j][1]]
#define SCORE(A,T,i) memo[T(A,i,0)][T(A,i,1)][T(A,i,2)][T(A,i,3)][T(A,i,4)]

int test( char *A[1000000][5],  char *B[1000000][5]){
    if(!nfirst) {
        nfirst = true;
        for(int i = '1'; i <= '5'; ++i){
            charconv[i] = i-'1';
        }
        for(int i = 0; i < 5; ++i){
            for(int j = 0; j < 5; ++j){
                for(int k = 0; k < 5; ++k){
                    for(int l = 0; l < 5; ++l){
                        for(int m = 0; m < 5; ++m){
                            count[0] = count[1] = count[2] = count[3] = count[4] = 0;
                            int cnt2 = 0;
                            int maxsame = 0;
                            count[i]++; count[j]++; count[k]++; count[l]++; count[m]++;
                            for(int i = 0; i < 5; ++i){
                                cnt2 += count[i] == 2;
                                maxsame = count[i] < maxsame ? maxsame : count[i];
                            }
                            int rank = -1;
                            switch(maxsame){
                                case 5: rank = 6; break;
                                case 1: rank = 5; break;
                                case 2: 
                                    if(cnt2 == 1){
                                        rank =4 ;
                                    }
                                    else rank = 3;
                                    break;
                                case 3: rank = 2; break;
                                case 4: rank = 1; break;
                            }
                            int &dp = memo[i][j][k][l][m];
                            dp = rank*100000;
                            int n;
                            switch(rank){
                                case 1:
                                for(n = 0; n < 5; ++n){
                                    if(count[n] == 1){
                                        dp -= n;
                                        break;
                                    }
                                }
                                break;
                                case 2:
                                for(n = 0; n < 5; ++n){
                                    if(count[n] != 3){
                                        dp += count[n]*conv[n];
                                    }
                                }
                                break;
                                case 3:
                                case 4:
                                for(n = 0; n < 5; ++n){
                                    dp += count[n]*conv[n];
                                }
                                break;
                            }
                        }
                    }
                }
            }
        }
        
    }
    int ret = 0;
    for(int i = 0; i < 1000000; ++i){
        ret += SCORE(A,F,i) != SCORE(B,F,i) || SCORE(A,S,i) != SCORE(B,S,i)|| (SCORE(A,S,i) == 500000 &&SCORE(A,F,i) == 500000);
    }
    return ret;
}