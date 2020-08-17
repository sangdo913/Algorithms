#define MAX_N				20000
#define MAX_M				128
#define MAX_BLOCKCOUNT		1250
#define MAX_DATALENGTH		5120000
#define FRAMESIZE			256
#define rint int

struct huffman
{
	int symbol, codeword, codewordLength;
};
typedef int FRAME[FRAMESIZE];

int blocks[MAX_N/16][16][256];
int n,m;
int nid;

unsigned char hofinfo[1<<21][22];
unsigned char chk[1<<21][22];
int query;

void Init(int N, int *size, unsigned char *data, int M, struct huffman *code)
{
    n = N, m = M;
    query++;
    
    for(rint i = 0; i < M; ++i){
        chk[code[i].codeword][code[i].codewordLength] = query;
        hofinfo[code[i].codeword][code[i].codewordLength] = code[i].symbol;
    }
    for(rint i = 0; i < N/16; ++i){
        rint cur = 0;
        rint b = 0;
        rint flen = 0;
        rint sz = size[i]*8;
        for(rint read = 0; read< sz; ++read){
            b = (b<<1) + ((data[read/8] >> (7-(read%8)))&1);
            cur++;
            if(chk[b][cur] == query){
                blocks[i][flen/256][flen%256] = hofinfo[b][cur];
                flen++;
                if(flen == 256*16) {
                    break;
                }
                b = 0; cur = 0;
            }
        }
        for(rint f = 1; f < 16; ++f){
            for(rint p = 0; p < 256; p++){
                blocks[i][f][p] = blocks[i][f][p] + blocks[i][f-1][p]-128;
            }
        }
        data += size[i];
    }
}

void Goto(int frame)
{
    nid = frame;
}

int Tick(unsigned char *screen)
{
    if(nid == n) nid = n-1;
    rint b = nid/16;
    rint f = nid%16;
    for(rint i = 0; i < 256; ++i){
        screen[i] = blocks[b][f][i];
    }
	return nid++;
}