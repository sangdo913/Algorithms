#define MAXR		99
#define MAXC		26
#define LEN         100

int visit[MAXR][MAXC];
int dp[MAXR][MAXC];
int tc;
int row,col;
int operater[MAXR][MAXC];
int dir[MAXR][MAXC];
int from[MAXR][MAXC], to[MAXR][MAXC];

void init(int C, int R) {
    row = R, col = C;

    for(int i = 0; i < row; ++i) for(int j = 0; j < col; ++j){
        dp[i][j] = operater[i][j] = 0;
    }
}
enum ftype {NONE,ADD, SUB, MUL, DIV, MAX, MIN, SUM, SIZE, CONST};
const char name[SIZE][4] = {"", "ADD", "SUB", "MUL", "DIV", "MAX", "MIN", "SUM"};

bool neqall(const char *s1, const char *s2){
    while(*s1 && *s1 == *s2) s1++, s2++;
    return *s1- *s2;
}
int myatoi(const char *s){
    int ret = 0;
    while(*s){
        ret*=10;
        ret += *s++-'0';
    }
    return ret;
}

int dr[2] = {1,0};
int dc[2] = {0,1};

void set(int col, int row, char input[]) {
    --col, --row;
    int cursor = 0;
    if('A'<=input[0] && input[0] <= 'Z'){
        char fname[4] = {input[0], input[1], input[2], 0};
        int d;
        for(d = 1; d < SIZE; ++d)if(!neqall(fname, name[d])) break;

        operater[row][col] = d;
        int cursur = 4;
        int c1 = input[4] - 'A';
        cursor = 5;
        int r1 = 0;
        while('0' <= input[cursor] && input[cursor] <= '9'){
            r1*= 10;
            r1+= input[cursor++] - '0';
        }
        cursor++;

        from[row][col] = (--r1<<5) + c1;
        int c2 = input[cursor++] - 'A';
        int r2 = 0;
        while('0' <= input[cursor] && input[cursor] <= '9'){
            r2*= 10;
            r2+= input[cursor++]-'0';
        }
        to[row][col] = (--r2<<5)+c2;
        dir[row][col] = r1 == r2;
    }
    else{
        operater[row][col] = CONST;
        bool minus = input[0] == '-';
        
        dp[row][col] = myatoi(input+ minus);
        dp[row][col] *= (1-2*minus);
    }
}

int getValue(int r, int c){
    if(!operater[r][c]) return 0;
    if(operater[r][c] == CONST) return dp[r][c] = dp[r][c];
    if(visit[r][c] == tc) return dp[r][c];
    visit[r][c] = tc;
    dp[r][c] = 0;

    int fr = from[r][c] >>5;
    int fc = from[r][c] & 0b11111;
    int tr = to[r][c] >>5;
    int tc = to[r][c] & 0b11111;

    switch(operater[r][c]){
        case ADD: return dp[r][c] = getValue(fr,fc) + getValue(tr,tc);
        case SUB: return dp[r][c] = getValue(fr,fc) - getValue(tr,tc);
        case MUL: return dp[r][c] = getValue(fr,fc) * getValue(tr,tc);
        case DIV: return dp[r][c] = getValue(fr, fc) / getValue(tr,tc);
        case MAX: 
        dp[r][c] = getValue(tr,tc);
        while(fr != tr || fc != tc){
            dp[r][c]  = dp[r][c] > getValue(fr,fc) ? dp[r][c] : getValue(fr,fc);
            fr += dr[dir[r][c]], fc += dc[dir[r][c]];
        }

        return dp[r][c];
        case MIN:
        dp[r][c] = getValue(tr,tc);
        while(fr != tr || fc != tc){
            dp[r][c] = dp[r][c] > getValue(fr,fc) ? getValue(fr,fc) : dp[r][c];
            fr += dr[dir[r][c]], fc += dc[dir[r][c]];
        }
        return dp[r][c];

        case SUM:
        dp[r][c] = getValue(tr,tc);
        while(fr != tr || fc != tc){
            dp[r][c] += getValue(fr,fc); 
            fr+= dr[dir[r][c]], fc += dc[dir[r][c]];
        }
        return dp[r][c];
    }
    return -1;
}

void update(int value[MAXR][MAXC]) {
    ++tc;
    for(int i = 0; i < row; ++i)for(int j = 0; j < col; ++j){
        value[i][j] = getValue(i,j);
    } 
}