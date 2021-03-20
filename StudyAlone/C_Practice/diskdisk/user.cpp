/*
score : 2468
*/
#define LEN 15
#define FILE 16
#define ui unsigned int
#define rint register int
#define Asize 5
extern void read_disk(int sector, char data[512]);
extern void write_disk(int sector, char data[512]);

void correcterror(int sector, char (*mem)[512]){
    int v[Asize] = {0x3f3f3f3f,0x3f3f3f3f,0x3f3f3f3f,0x3f3f3f3f,0x3f3f3f3f};
    int count[Asize] = {};
    for(rint i = 0; i < 512; ++i){
        count[0] = count[1] = count[2] = count[3] = count [4] = 0;
        int size = 0;
        for(rint j = 0; j < Asize; ++j) {
            rint k = 0;
            while(k < size && v[k] != mem[j][i]) ++k; 
            if(size == k){
                count[k] = 0;
                ++size;
            }
            v[k] = mem[j][i];
            count[k]++;
            if(count[k] == 3){
                v[0] = mem[j][i];
                break;
            }
            int val = v[k];
            rint cnt = count[k];
            while(k && count[k-1] < cnt ){
                count[k] = count[k-1];
                v[k] = v[k-1];
                --k;
            }
            count[k] = cnt;
            v[k] = val;
        }
        mem[0][i] = v[0];
    }
}
void read_file(char file_name[36], char data[4096], int pos, rint size) {
    rint slen = 0;
    char mem[Asize][512];
    while(file_name[slen]) ++slen;
    int key = 0;
    rint idx = 0;
    while(true) {
        for(rint i = 0; i < Asize; ++i) read_disk(key*Asize + i, mem[i]);
        correcterror(key, mem);
        for(rint i = 0; i < 8; ++i,idx++) {
            int i6 = i << 6;
            int len = ((ui)mem[0][i6] << 8) +  (ui)mem[0][(i6)+1];
            if(len != slen) continue;
            rint j = 0;
            while(file_name[j] && file_name[j] == mem[0][i6+2 + j])++j;
            if(file_name[j] == mem[0][i6+2+j]) {
                goto FIND;
            }
        }
        ++key;
    }
    FIND:
    for(rint i = 0; i < Asize; ++i){
        read_disk(LEN*Asize, mem[i]);
    }
    correcterror(LEN, mem);

    int fsize = ((int (*))mem)[idx];
	if (size > fsize) size = fsize;
	if (pos + size > fsize) pos = fsize - size;
    rint p = ((FILE<<9) + (idx<<16) + pos);
    rint sector = p>>9;
    int s= p%512;
    for(rint i = 0; i < size;sector++) {
        for(rint i = 0; i < Asize; ++i) read_disk(sector*Asize + i, mem[i]);
        correcterror(sector, mem);
        rint remain = size-i+s < 512 ? size-i+s : 512;
        for(rint j = s; j < remain; ++j, ++i){
            data[i] = mem[0][j];
        }
        s= 0;
    }
}

void write_file(char file_name[36], char data[4096], int pos, rint size) {
    rint key = 0;
    rint slen = 0;
    char temp[Asize][512];
    bool find = true;
    int len = 0;
    while(file_name[slen]) ++slen;
    while(true) {
        rint idx = key>>3;
        for(rint k = 0; k < Asize; ++k) {
            read_disk(idx*Asize + k, temp[k]);
        }
        correcterror(idx, temp);
        for(rint i = 0; i < 8; ++i, ++key) {
            int i6 = i<<6;
            len = ((unsigned int)temp[0][i6] << 8) + (unsigned int)temp[0][i6+1];
            if(!len) {
                find = false;
                goto LOOP_END;
            }
            if(slen != len) continue;
            rint j = 0;
            while(temp[0][i6+j+2] && temp[0][i6+j+2] == file_name[j]) ++j;
            if(temp[0][i6+j+2] == file_name[j]) {
                goto LOOP_END;
            }
        }
    }
    LOOP_END:
    if(!find) {
        rint s = (key%8)<<6;
        temp[0][s] = slen>>8;
        temp[0][s+1] = slen&0xff;
        for(rint i = 0; i < slen; ++i) {
            temp[0][s + i + 2] = file_name[i];
        }
        for(rint k = 0; k< Asize; ++k) {
            write_disk((key>>3)*Asize+k, temp[0]);
        }
    }

    for(rint i = 0; i < Asize; ++i) {
        read_disk(LEN*Asize + i, temp[i]);
    }
    correcterror(LEN, temp);
    bool changed = false;
    int(*fsize) = (int(*)) temp;
	if (pos > fsize[key]) pos = fsize[key];
	if (pos + size > 65536) size = 65536 - pos;
	if (pos + size > fsize[key])  {
        fsize[key] = pos + size;
        changed = true;
    }

    if(changed)
        for(rint k = 0; k < Asize; ++k){
            write_disk(LEN*Asize + k,temp[0]);
        }

    rint p = ((FILE<<9) + (key<<16) + pos);
    rint sector = p>>9;
    int s = p%512;
    for(rint i = 0; i < size; sector++) {
        for(rint i = 0; i < Asize; ++i) read_disk(sector*Asize + i, temp[i]);
        correcterror(sector, temp);
        rint remain = size- i+s < 512 ? size-i+s:512;

        for(rint j = s; j < remain; ++j,++i){
            temp[0][j] = data[i];
        }
        s = 0;
        for(rint i = 0; i < Asize; ++i) write_disk(sector*Asize+ i, temp[0]);
    }
}