#define MAX_PICTURE_SIZE 1000
#define MAX_PIECE_SIZE 100
#define MAXN 1500
#define rint register int
#define HASHSIZE 10007
enum DIR {UP = 0, RIGHT, DOWN, LEFT};

extern bool setPicture(int id, int x, int y);

struct INFO{
    int mid;
    unsigned int key;
    int d;
    INFO *prev, *next;
}nodes[8*MAXN];

INFO myhash[2][HASHSIZE];

int nid;
int myqueue[1500];
int myused[1500];
int pos[1500][2];
int tc;

void mergePictures(int N, int M, int K, char pictures[MAXN][MAX_PIECE_SIZE][MAX_PIECE_SIZE]) {
    tc++;
    nid = 0;
    for(rint i = 0; i < HASHSIZE; ++i) {
        myhash[0][i].prev = myhash[0][i].next = &myhash[0][i];
        myhash[1][i].prev = myhash[1][i].next = &myhash[1][i];
    }
    myused[0] = tc;

    for(rint i = 1; i < N; ++i){
        //DOWN
        register unsigned int key = (pictures[i][0][0] << 28) + (pictures[i][0][1] << 24) + (pictures[i][0][2] << 20) + (pictures [i][0][3] << 16)
        + (pictures[i][1][0] << 12) + (pictures[i][1][1] << 8) + (pictures[i][1][2] << 4) + pictures[i][1][3];
        
        //RIGHT
        register unsigned int key2 = (pictures[i][0][0] << 28) + (pictures[i][1][0] << 24) + (pictures[i][2][0] << 20) + (pictures[i][3][0] << 16)
        + (pictures[i][0][1] << 12) + (pictures[i][1][1] << 8) + (pictures[i][2][1] << 4) + pictures[i][3][1];

        //LEFT
        register unsigned int key3 = (pictures[i][0][M-2] << 28) + (pictures[i][1][M-2] << 24) + (pictures[i][2][M-2] << 20) + (pictures[i][3][M-2] << 16)
        + (pictures[i][0][M-1] << 12) + (pictures[i][1][M-1] << 8) + (pictures[i][2][M-1] << 4) + pictures[i][3][M-1];

        //UP
        register unsigned int key4 = (pictures[i][M-2][0] << 28) + (pictures[i][M-2][1] << 24) + (pictures[i][M-2][2] << 20) + (pictures [i][M-2][3] << 16)
        + (pictures[i][M-1][0] << 12) + (pictures[i][M-1][1] << 8) + (pictures[i][M-1][2] << 4) + pictures[i][M-1][3];

        INFO &n1 = nodes[nid++];
        INFO &n2 = nodes[nid++];
        INFO &n3 = nodes[nid++];
        INFO &n4 = nodes[nid++];
        n1.key = key;
        n1.mid = i;
        n1.d = DOWN;

        n2.key = key2;
        n2.mid = i;
        n2.d = RIGHT;

        n3.key = key3;
        n3.mid = i;
        n3.d = LEFT;

        n4.key = key4;
        n4.mid = i;
        n4.d = UP;

        INFO *head = &myhash[0][key % HASHSIZE];
        n1.prev = head->prev;
        n1.next = head;

        head->prev->next = &n1;
        head->prev = &n1;

        head = &myhash[1][key2 % HASHSIZE];
        n2.prev = head->prev;
        n2.next = head;

        head->prev->next = &n2;
        head->prev = &n2;

        head = &myhash[1][key3 % HASHSIZE];
        n3.prev = head->prev;
        n3.next = head;

        head->prev->next = &n3;
        head->prev = &n3;

        head = &myhash[0][key4 % HASHSIZE];
        n4.prev = head->prev;
        n4.next = head;

        head->prev->next = &n4;
        head->prev = &n4;
    }
    register int fr, re;
    fr = re = 0;
    myqueue[re++] = 0;

    while(fr != re){
        rint now = myqueue[fr++];
        register unsigned int key = (pictures[now][0][0] << 12) + (pictures[now][0][1] << 8) + (pictures[now][0][2] << 4) + pictures [now][0][3];
        register unsigned int key2 = (pictures[now][0][0] << 12) + (pictures[now][1][0] << 8) + (pictures[now][2][0] << 4) + pictures[now][3][0];

        for(rint j = 1; j < M; ++j){
            key = (key << 16) + (pictures[now][j][0] << 12) + (pictures[now][j][1] << 8) + (pictures[now][j][2] << 4) + pictures[now][j][3];
            register INFO *cur = myhash[0][key%HASHSIZE].next;
            while(cur != &myhash[0][key%HASHSIZE]){
                rint id = cur->mid;
                if(myused[id] == tc) goto NEXT;
                if(cur->key != key) goto NEXT;
                rint nextY ;
                if(cur->d == DOWN) nextY = pos[now][1] + j-1;
                else nextY = pos[now][1] + j-M+1;

                if(setPicture(id, pos[now][0], nextY)){
                    myused[id] = tc;
                    pos[id][0] = pos[now][0];
                    pos[id][1] = nextY;
                    myqueue[re++] = id;
                }
                NEXT:
                cur= cur->next;
            }
        }

        for(rint j = 1; j < M; ++j){
            key2 = (key2<<16) + (pictures[now][0][j] << 12) + (pictures[now][1][j] << 8) + (pictures[now][2][j] << 4) + pictures[now][3][j];
            INFO * cur = myhash[1][key2%HASHSIZE].next;
            while(cur != &myhash[1][key2%HASHSIZE]){
                rint id = cur->mid;
                if(myused[id] == tc) goto NEXT2;
                if(cur->key != key2) goto NEXT2;
                rint nX;
                if(cur->d == RIGHT) nX = pos[now][0] + j-1;
                else nX = pos[now][0] + j -M+1;

                if(setPicture(id, nX, pos[now][1])){
                    myused[id] = tc;
                    pos[id][0] = nX;
                    pos[id][1] = pos[now][1];
                    myqueue[re++] = id;
                
                }
                NEXT2:
                cur= cur->next;
            }
        }
    }
}