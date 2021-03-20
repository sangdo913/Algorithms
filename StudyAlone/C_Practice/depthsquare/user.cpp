#define SIZE 100
#define rint register int

#define getv(i, j) ((i < 0 || j < 0 || i >= SIZE || j >= SIZE) ? 0 : image[i][j])

int pos[2][SIZE*SIZE];
int plen[2];

int recog(int image[SIZE][SIZE]) {
    rint ret= 0;
    plen[0] = plen[1]=0;
    for(rint i = -1; i <= SIZE; ++i) {
        for(rint j = -1; j <= SIZE; ++j){
              rint v = getv(i,j) - getv(i,j+1) - (getv(i+1,j) - getv(i+1,j+1));
              if(v > 0&& i < SIZE - 10 && j < SIZE - 10) {
                  pos[0][plen[0]++] = ((i+1)<<16)+j+1;
              }
              v = getv(i,j) - getv(i,j-1) - (getv(i-1,j) - getv(i-1,j-1));
              if(v>0 && i >= 10 && j >= 10) {
                  pos[1][plen[1]++] = ((i-1)<< 16) + j -1;
              }
        }
    }
    for(rint l1 = 0; l1 < plen[0]; ++l1){
        for(rint l2 = 0; l2 < plen[1]; ++l2){
            rint lux = pos[0][l1] >> 16;
            rint luy = pos[0][l1] & 0xffff;
            rint rdx = pos[1][l2] >> 16;
            rint rdy = pos[1][l2] & 0xffff;
            if(rdx - lux < 9 || rdy - luy < 9) continue;

            rint v1 = getv(lux-1,luy-1) - getv(lux-1,luy) - (getv(lux,luy-1) - getv(lux,luy));
            rint v2 = getv(rdx+1,luy-1) - getv(rdx+1,luy) - (getv(rdx,luy-1) - getv(rdx,luy));
            rint v3 = getv(lux-1, rdy+1) - getv(lux-1,rdy) - (getv(lux, rdy+1) - getv(lux, rdy));
            rint v4 = getv(rdx+1, rdy+1) - getv(rdx+1,rdy) - (getv(rdx, rdy+1) - getv(rdx, rdy));
            if(v2 >0 &&  v3 > 0 ){
                ret += ((rdx - lux) == (rdy - luy));
            }
        }
    }

	return ret;   
}