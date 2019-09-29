struct Rect
{
	unsigned int width;		// First dimension
	unsigned int height;	// Second dimension
};

typedef unsigned char ui;
typedef unsigned int uii;
ui** goodimage;
int mm, nn;

void init(unsigned int m, unsigned int n)
{
    mm = m;
    nn = n;
}

void setChipImage(unsigned char **chipImage)
{
    goodimage = chipImage;
}

#define MAX(x,y) ((x) > (y) ? (x) : (y))
#define MIN(x,y) ((x) < (y) ? (x) : (y))

Rect check( ui **sampleImage, int r, int c){
    int ux= 0x3f3f3f3f, ly = 0x3f3f3f3f, dx = -1, ry= -1;
    for(register int i = 0; i < mm; ++i){
        for(register int j = 0;j < mm; ++j){
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

Rect checkSampleImage( unsigned char **sampleImage){
     register uii key[2];
     register uii mykey[2];
     Rect res;

    key[0] = ((uii)sampleImage[0][0] <<24) + ((uii)sampleImage[1][0] <<16) +((uii)sampleImage[0][1] << 8) + sampleImage[1][1];
    key[1] = ((uii)sampleImage[mm-2][mm-2] << 24) + ((uii)sampleImage[mm-1][mm-2] <<16) + ((uii)sampleImage[mm-2][mm-1] << 8) + sampleImage[mm-1][mm-1];

    for(register int i = 0; i<= nn-mm; ++i) {
            mykey[0] = ((uii)goodimage[i][0] << 8) + (uii)goodimage[i+1][0]; 
            mykey[1] = ((uii)goodimage[i+mm-2][mm-2] <<8) + (uii)goodimage[i+mm-1][mm-2];

            for(register int j = 0; j <= nn-mm; ++j) {
                    mykey[0] = (mykey[0] << 16) + ((uii)goodimage[i][j+1] << 8) + goodimage[i+1][j+1];
                    mykey[1] = (mykey[1] << 16) + ((uii)goodimage[i+mm-2][mm-1+j] << 8) + goodimage[i+mm-1][mm-1+j];

                    for(register int d = 0; d < 2; ++d){
                        if(mykey[d] == key[d]){
                            res = check(sampleImage, i,j);
                            if(res.height != 100) return res;
                        }

                    }
            }
    }

	return {102, 100};
}