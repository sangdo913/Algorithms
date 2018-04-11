#include<iostream>
#include<cstring>
#include<cstdio>

using namespace std;

struct CubingInfo
{
    char cube[6][3][3];
    typedef struct Cod{int r,c,direct,face;} cod;
    typedef enum {U = 0, D = 1, F = 2, B = 3, L = 4, R = 5} face;
    typedef enum{ w = 0, y = 1, r = 2, o = 3, g = 4, b = 5} color;
    typedef enum{UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3} direct;
    typedef enum {COD = 1} rotateType;
    typedef enum {ROW = 0 , COL = 1, DIRECT = 2} cordType;
    typedef enum {FACE = 0, COLOR = 1} type;
    typedef enum { oper = 0, buho = 1} cal;
    const int dr[4] = {-1,1,0,0};
    const int dc[4] = {0,0,-1,1};
    typedef char line[3];
    const int faceRotate[8] = {0,1,2,5,8,7,6,3};
    //up , down, front, back, left, right
    const int rotate[6][4] = {{B,R,F,L},{F,R,B,L},{U,R,D,L},{U,L,D,R},{U,F,D,B},{U,B,D,F}
    };
    const int rotateFace[6][4][3] = {
                                        {{0,0,RIGHT},{0,0,RIGHT},{0,0,RIGHT},{0,0,RIGHT}},{{2,0,RIGHT},{2,0,RIGHT},{2,0,RIGHT},{2,0,RIGHT}},
                                        {{2,0,RIGHT},{0,0,DOWN},{0,2,LEFT},{2,2,UP}}, {{0,2,LEFT},{0,0,DOWN},{2,0,RIGHT},{2,2,UP}},
                                        {{0,0,DOWN},{0,0,DOWN},{0,0,DOWN},{2,2,UP}}, {{2,2,UP},{0,0,DOWN},{2,2,UP},{2,2,UP}}
                                    };
    
    char conv[2]['Z' + 1];
    char comm[2][1000];
    int n, k;
    
    cod getFace(int op,int order)
    {
        cod res;
        res.face = rotate[op][order];
        res.r = rotateFace[op][order][ROW];
        res.c = rotateFace[op][order][COL];
        res.direct = rotateFace[op][order][DIRECT];

        return res;
    }


    void Rotate(int op, int bu)
    {
        char temp[3];
        cod tempPos;
        tempPos = getFace(op,0);

        for(int i = 0; i < 3; i ++)
        {
            temp[i] = cube[tempPos.face][tempPos.r + i*dr[tempPos.direct]][tempPos.c + i*dc[tempPos.direct]];
        }

        for(int i = 0; i < 3; i++)
        {
            cod now; cod next;
            now = getFace(op,(i*bu+4)%4);
            next = getFace(op,((i+1)*bu+4)%4);

            for(int j = 0 ; j < 3; j++)
            {
                cube[now.face][now.r][now.c] = cube[next.face][next.r][next.c];
                next.r += dr[next.direct];
                next.c += dc[next.direct];

                now.r += dr[now.direct];
                now.c += dc[now.direct];
            }

        }

        cod st = getFace(op,(4-bu)%4);

        for(int i = 0; i < 3; i++)
        {
            cube[st.face][st.r][st.c] = temp[i];
            st.r += dr[st.direct];
            st.c += dc[st.direct];
        }

        char store = cube[op][0][0];
        char store2 = cube[op][0][1];
        for(int i = 0 ; i < 6; i+=2)
        {
            int num = faceRotate[(8+i*bu)%8];
            int next = faceRotate[(8+ (i+2)*bu)%8];
            int num2 = faceRotate[(9+i*bu)%8];
            int next2 = faceRotate[(9+(i+2)*bu)%8];
            cube[op][num/3][num%3] = cube[op][next/3][next%3];
            cube[op][(num2)/3][(num2)%3] = cube[op][(next2)/3][(next2)%3];
        }
        int num = faceRotate[(8-2*bu)%8];
        int num2 = faceRotate[(9-2*bu)%8];
        cube[op][num/3][num%3] = store;
        cube[op][(num2)/3][(num2)%3] = store2;
        return ;
    }

    void init()
    {
        for(int i = 0; i < 6; i++)
        {
            for(int j = 0 ; j < 3; j++)
            {
                for(int k = 0; k < 3; k++)
                {
                    cube[i][j][k] = conv[COLOR][i];
                }
            }
        }
        scanf("%d\n",&n);
        for(int i = 0; i < n; i++)
        {
            scanf("%c%c \n", &comm[oper][i], &comm[buho][i]);
            Rotate(conv[0][comm[oper][i]],conv[0][comm[buho][i]]);
        }
    }

    void print()
    {
        for(int i = 0; i < 3; i++)
        {
            for(int j = 0 ; j < 3; j++)
            {
                printf("%c", cube[U][i][j]);
            }
            printf("\n");
        }
    }
}info;

int Cubing()
{
    typedef enum {U = 0, D = 1, F = 2, B = 3, L = 4, R = 5} face;
    typedef enum{ w = 0, y = 1, r = 2, o = 3, g = 4, b = 5} color;
 
    info.conv[1][w] = 'w';
    info.conv[1][y] = 'y';
    info.conv[1][r] = 'r';
    info.conv[1][o] = 'o';
    info.conv[1][g] = 'g';
    info.conv[1][b] = 'b';

    info.conv[0]['U'] = U;
    info.conv[0]['F'] = F;
    info.conv[0]['D'] = D;
    info.conv[0]['B'] = B;
    info.conv[0]['L'] = L;
    info.conv[0]['R'] = R; 
    info.conv[0]['+'] = -1;
    info.conv[0]['-'] = 1;
    
    int t;
    scanf("%d\n",&t);
    while(t--)
    {
        info.init();
        info.print();
    }
    return 0;
}