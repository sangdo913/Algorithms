// #define rint register int
// extern bool check_map(unsigned char map[4096][4096]);

// unsigned char allpuzzle[4096][4096];
// int canboard[256];
// int tc;

// int sx[4] = {0,0,255, 0};
// int sy[4] = {0,255,0,0};
// int dx[2][4] = {{1,0,-1,0},{0,-1,0,1}};
// int dy[2][4] = {{0,1,0,1},{1,0,1,0}};
// int iserase[256];
// int echk[256];
// int info[4][256][256];
// int diff[4][256][256];
// int temp[256];
// int puzzleinfo[4][256][256];
// int adj[4][256][256];
// int adjlen[4][256];


// void mergesort(int pid, int d, int s, int e){
//     if(s >= e-1){
//         return;
//     }
//     rint m = (s+e)/2;
//     mergesort(pid,d,s,m);
//     mergesort(pid,d,m,e);
//     rint l = s, r = m, k = l;
//     while(l < m && r < e){
//         int id1 = info[d][pid][l];
//         int id2 = info[d][pid][r];
//         if(diff[d][pid][id1] > diff[d][pid][id2]) temp[k++] = id1, l++;
//         else temp[k++] = id2, r++;
//     }
//     while(l < m){ temp[k++] = info[d][pid][l++]; }
//     while(r < e) temp[k++] = info[d][pid][r++];
//     for(rint i= s; i < e; ++i) info[d][pid][i] = temp[i];
// }

// int mypuzzle[16][16];
// int putted[256];
// bool makepuzzle(unsigned char map[4096][4096], int i, int j){
//     if(i == 16){
//         for(int i = 0; i < 16; ++i){
//             for(int j = 0; j < 16; ++j){
//                 int r = mypuzzle[i][j]/16;
//                 int c = mypuzzle[i][j]%16;
//                 rint x = r*256, y = c*256;
//                 rint a = i*256, b= j*256;
//                 for(rint ii = 0; ii < 256; ++ii){
//                     for(rint jj = 0; jj < 256; ++jj){
//                         allpuzzle[a + ii][b + jj] = map[x+ii][y+jj];
//                     }
//                 }
//             }
//         }
//         if(check_map(allpuzzle)) {
//             for(rint i = 0; i < 4096; ++i){
//                 for(rint j = 0; j < 4096; ++j){
//                     map[i][j] = allpuzzle[i][j];
//                 }
//             }
//             return true;
//         }
//         return false;
//     }
//     int ni = i, nj =j+1;
//     if(nj == 16) ni++, nj = 0;
//     int d = 0;
//     if(!i) d |= (1<<0);
//     if(j == 15) d |= (1<< 1);
//     if(i == 15) d |= (1<< 2);
//     if(!j) d |= (1<<3);
//     if(i == 0 && j == 0) {
//         for(int id = 0; id < 256; ++id){
//             if(canboard[id] >= 0x9) {
//                 mypuzzle[i][j] = id;
//                 putted[id] = 1;
//                 bool ret = makepuzzle(map, ni,nj);
//                 putted[id] = 0;
//                 if(ret) return true;
//             }
//         }
//         return false;
//     }
//     bool ret = false;
//     if(j) {
//         for(rint k = 0; k < adjlen[1][mypuzzle[i][j-1]]; ++k){
//             int nxt = info[1][mypuzzle[i][j-1]][k];
//             if(canboard[nxt] >= d && !putted[nxt] && (!i || adj[2][mypuzzle[i-1][j]][nxt] == tc)) {
//                 putted[nxt] = 1;
//                 mypuzzle[i][j] = nxt;
//                 ret = makepuzzle(map, ni,nj);
//                 putted[nxt] = 0;
//                 if(ret) return true;
//             }
//         }
//     }
//     else if(i){
//         for(rint k = 0; k < adjlen[2][mypuzzle[i-1][j]]; ++k){
//             int nxt = info[2][mypuzzle[i-1][j]][k];
//             if(canboard[nxt] >= d && !putted[nxt]){
//                 putted[nxt] =1;
//                 mypuzzle[i][j] = nxt;
//                 ret = makepuzzle(map,ni,nj);
//                 putted[nxt] = 0;
//                 if(ret) return true;
//             }
//         }
//     }
//     return false;
// }

// void recover(unsigned char map[4096][4096])
// {
//     tc++;
//     for(rint i = 0; i < 16; ++i) {
//         for(rint j = 0; j < 16; ++j){
//             int id = i*16+j;
//             canboard[id] = 0;
//             for(rint d = 0; d < 4; ++d){
//                 int x = i*256 + sx[d], y = j*256 + sy[d];
//                 for(rint cnt = 16; cnt; --cnt) {
//                     rint x2 = x, y2 = y;
//                     for(rint cnt = 256; cnt; --cnt) {
//                         if(map[x2][y2]){
//                             goto END;
//                         }
//                         x2 += dy[0][d], y2 += dy[1][d];
//                     }
//                     x+= dx[0][d]; y += dx[1][d];
//                 }
//                 canboard[id] |= 1 << d;
//                 END:
//                 continue;
//             }
//             for(rint d = 0; d < 4; ++d){
//                 for(rint k = 0; k < 256; ++k) puzzleinfo[d][id][k] = 0;
//                 int x = i*256 + sx[d], y = j*256 + sy[d];
//                 for(rint ii = 0; ii < 5; ++ii){
//                     for(rint k = 0; k < 256; ++k) temp[k] = 0;
//                     tc++;
//                     rint elen = 0;
//                     rint x2 = x, y2 = y;
//                     rint prev = -1;
//                     int cont= 0;
//                     for(rint jj = 0; jj < 256; ++jj) {
//                         if(map[x2][y2] && prev == (int)map[x2][y2]) cont++;
//                         else if(map[x2][y2]) cont = 0, prev = map[x2][y2];
//                         if(cont > 10) {
//                             if(echk[map[x2][y2]] != tc){
//                                 iserase[elen++] = map[x2][y2];
//                                 echk[map[x2][y2]] = tc;
//                             }
//                         }
//                         temp[map[x2][y2]]++;
//                         x2 += dy[0][d], y2 += dy[1][d];
//                     }
//                     for(rint l = 0; l < elen; ++l){
//                             temp[iserase[l]] = 1;
//                     }
//                     for(rint k = 0; k < 256; ++k) puzzleinfo[d][id][k] += temp[k];
//                     x+= dx[0][d]; y += dx[1][d];
//                 }
//             }
//         }
//     }
//     tc++;
//     for(rint d = 0; d < 4; ++d) {
//         for(rint i = 0; i < 256; ++i) adjlen[d][i] = 0;
//     }

//     for(rint i = 0; i < 256; ++i){
//         for(rint j = i+1; j< 256; ++j){
//             for(rint d = 0; d < 4; ++d){
//                 rint d2 = (d+2)%4;
//                 diff[d2][j][i] = 0;
//                 diff[d][i][j] = 0;
//                 for(rint jj = 1; jj < 256; ++jj) {
//                     rint di = puzzleinfo[d][i][jj] > puzzleinfo[d2][j][jj] ? puzzleinfo[d2][j][jj] : puzzleinfo[d][i][jj];
//                     diff[d][i][j] += di;
//                     di = puzzleinfo[d][i][jj] - puzzleinfo[d2][j][jj];
//                     if(di > 5 || di < -5){
//                         diff[d][i][j]-=5;
//                     }
//                     // di = puzzleinfo[d][i][jj] -  puzzleinfo[d2][j][jj];
//                     // di = di < 0 ? di : -di;
//                     // diff[d][i][j] += di;
//                 }
//                 info[d][i][adjlen[d][i]++] = j;
//                 info[d2][j][adjlen[d2][j]++] = i;
//                 diff[d2][j][i] = diff[d][i][j];
//             }
//         }
//     }
//     for(rint d = 0; d < 4; ++d){
//         for(rint i = 0; i < 256; ++i){
//             mergesort(i,d,0,adjlen[d][i]);
//             for(rint j = 0; j < 10; ++j){
//                 adj[d][i][info[d][i][j]] = tc;
//                 adjlen[d][i] = 2;
//             }
//         }
//     }

//     if(0){
//         int id = 206;
//         int rr= id/16;
//         int cc = id%16;
//         for(int i = 255; i>252; --i){
//             for(int j = 0; j < 256; ++j){
//                 printf("%3d ", map[i + rr*256][j + cc*256]);
//             }
//             printf("\n");
//         }
//         printf("==\n\n");
//         id = 111;
//         rr= id/16;
//         cc = id%16;
//         for(int i = 0; i< 3; ++i){
//             for(int j = 0; j < 256; ++j){
//                 printf("%3d ", map[i + rr*256][j + cc*256]);
//             }
//             printf("\n");
//         }
//         printf("==\n");
//         // printpuzzle(76,1);
//         // printpuzzle(15,3);
//         // printpuzzle(108,3);

//         int dx[4] = {-1,0,1,0};
//         int dy[4] = {0,1,0,-1};
//         for(int d = 1; d < 3; ++d){
//             for(int i = 0; i < 16; ++i){
//                 for(int j = 0; j < 16; ++j){
//                     int ni = i +dx[d];
//                     int nj = j +dy[d];
//                     if(ni < 0 || nj < 0 || ni == 16 || nj == 16) {
//                         continue;
//                     }
//                     int now = convpuzzle[i][j];
//                     int n = convpuzzle[ni][nj];
//                     bool canfind = false;
//                     if(adj[d][now][n] != tc){
//                         printf("wrong\n");
//                     }
//                     for(int b = 0; b < 255; ++b){
//                         if(info[d][now][b] == n){
//                             canfind= true;
//                             printf("(%d %d), diff:%d %d %d pos %d\n", i,j,diff[d][now][n],now, n,b);
//                             break;
//                             int debug=1;
//                         }
//                     }
//                     if(!canfind){
//                         printf("??\n");

//                     }

//                 }
//                 printf("\n");
//             }
//             printf("==\n");
//         }
//     }


//     makepuzzle(map, 0,0);
// }