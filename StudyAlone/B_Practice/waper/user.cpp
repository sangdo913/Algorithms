struct Rect
{
	unsigned int width;		// First dimension
	unsigned int height;	// Second dimension
};

typedef unsigned char ui;
typedef unsigned int uii;
ui** goodimage;
int mm, nn;

#define NODENUM 1000000
#define HASHLEN 107
struct NODE{
    uii hash[2];
    int r, c;
   NODE *prev[2], *next[2];
}nodes[NODENUM];

NODE hash[HASHLEN];
int nid;

void init(unsigned int m, unsigned int n)
{
    nid = 0;
    mm = m;
    nn = n;
    for( int i = 0; i < HASHLEN; ++i) for( int d = 0; d < 2; ++d) hash[i].prev[d] = hash[i].next[d] = hash + i;

}

void setChipImage(unsigned char **chipImage)
{
    goodimage = chipImage;
     uii key[2];

    for( int i = 0; i<= nn-mm; ++i) {
            key[0] = ((uii)chipImage[i][0] << 8) + (uii)chipImage[i+1][0]; 
            key[1] = ((uii)chipImage[i+mm-2][mm-2] <<8) + (uii)chipImage[i+mm-1][mm-2];

            for( int j = 0; j <= nn-mm; ++j) {
                        key[0] = (key[0] << 16) + ((uii)chipImage[i][j+1] << 8) + chipImage[i+1][j+1];
                        key[1] = (key[1] << 16) + ((uii)chipImage[i+mm-2][mm-1+j] << 8) + chipImage[i+mm-1][mm-1+j];
                        NODE &nn = nodes[nid++];
                        nn.r = i, nn.c = j;

                        for( int d = 0; d < 2; ++d){
                            nn.next[d] = &hash[key[d]%HASHLEN];
                            nn.prev[d] = hash[key[d]%HASHLEN].prev[d];
                            nn.hash[d] = key[d];

                            hash[key[d]%HASHLEN].prev[d]->next[d] = &nn;
                            hash[key[d]%HASHLEN].prev[d] = &nn;
                        }
            }
    }
}
#define MAX(x,y) ((x) > (y) ? (x) : (y))
#define MIN(x,y) ((x) < (y) ? (x) : (y))

Rect check( ui **sampleImage, int r, int c){
    int ux= 0x3f3f3f3f, ly = 0x3f3f3f3f, dx = -1, ry= -1;
    for( int i = 0; i < mm; ++i){
        for( int j = 0;j < mm; ++j){
            if(goodimage[i+r][c+j] != sampleImage[i][j]){
                ux = MIN(ux, i);
                ly = MIN(ly, j);
                dx = MAX(dx, i);
                ry = MAX(ry, j);
            }
        }
    }
    if(dx == -1) return {0,0};
    if(dx - ux > 3 || ry - ly > 3) return {100,100}; 
    return {dx-ux+1, ry - ly+1};
}

Rect checkSampleImage( unsigned char **sampleImage)
{
     uii key[2];
     Rect res;

    key[0] = ((uii)sampleImage[0][0] <<24) + ((uii)sampleImage[1][0] <<16) +((uii)sampleImage[0][1] << 8) + sampleImage[1][1];
    key[1] = ((uii)sampleImage[mm-2][mm-2] << 24) + ((uii)sampleImage[mm-1][mm-2] <<16) + ((uii)sampleImage[mm-2][mm-1] << 8) + sampleImage[mm-1][mm-1];


    NODE* cursor;
    for(int d = 0; d < 2; ++d){
        cursor = hash[key[d]%HASHLEN].next[d];

        while(cursor != &hash[key[d]%HASHLEN]){
            if(cursor->hash[d] == key[d]){
                res = check(sampleImage, cursor->r, cursor->c);
                if(res.height == 100) {
                    cursor = cursor->next[d];
                    continue;
                }

                else return res;
            }
            cursor= cursor->next[d];
        }
    }

	return {102, 100};
}