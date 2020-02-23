#define SIZE 1048576
#define HASH 65536
#define ruint register unsigned int
#define rint register int
#define uint unsigned int
#define rusrt register unsigned short

extern void test_sort(short data[1024]);

void merge(short data[1024*4], int s, int e){
    if(s < e){
    if(e-s +1 <= 1024){
        short q[1024] = {0};
        rint zi = 0;
        rint l = (e-s+1);
        for(rint i = 0; i < l; ++i){
            q[i] = data[s+i];
        }
        test_sort(q);
        
        while(zi < l && q[zi] < 0) zi++;
        l -= zi;
        e = 1023;
        while(zi) data[s++] = q[--zi];
        while(l--) data[s++] = q[e--];
    }
    else{
        rint m = (s+e)/2;
        m = (m/1024 + (m%1024 > 0))*1024;
        if(e < m) m = e;
        merge(data, s, m-1);
        merge(data, m, e);
        short temp[1024*4]= {};
        rint l= s, r = m, k = s;
        while(l <= m-1 && r <= e){
            if((unsigned short)data[l] < (unsigned short)data[r]) temp[k++] = data[r++];
            else temp[k++] = data[l++];
        }
        while(l<=m-1) temp[k++] = data[l++];
        while(r <= e) temp[k++] = data[r++];
        for(rint i = s; i <= e; ++i) data[i] = temp[i];
    }
    }
}

void test(unsigned int data[SIZE])
{
    int cnt[2048] = {0};
    short digit[2048], temp[2048] = {};
    unsigned short cdigit[2048];
    bool visit[HASH] = {};
    int idx[HASH];
    rint dlen = 0;

    for(rint i = 0; i < SIZE; ++i){
        register unsigned short d1 = data[i] >> 16;
        register unsigned short d2 = data[i];
        if(!visit[d1]){
            visit[d1] = true;
            digit[dlen++] = (short)d1;
        }
        if(!visit[d2]){
            visit[d2] = true;
            digit[dlen++] = (short)d2;
        }
    }

    test_sort(digit);
    test_sort(digit+1024);
    rint k = 0, d1 = 0, d2 = 1024;
    while(d1 < 1024 && d2 < 2048) temp[k++] = digit[d1] > digit[d2] ? digit[d2++] : digit[d1++];
    while(d1 < 1024) temp[k++] = digit[d1++];
    while(d2<2048) temp[k++] = digit[d2++]; 
    for(rint i = 0; i < 2048; ++i) digit[i] = temp[i];
    rint zi = 0;
    while(zi < 2048 && digit[zi] < 0) zi++;

    for(rint i = 0; i < 2048; ++i){
            cdigit[i] = digit[(zi+i)%2048];   
    }
    for(rint i = 0; i < 1024; ++i){
        register unsigned short temp = cdigit[i];
        cdigit[i] = cdigit[2047-i];
        cdigit[2047-i] = temp;
    }
    
    for(rint i = 0; i < 2048; ++i){
        idx[cdigit[i]] = i;
    }

    for(rint i =0; i < SIZE; ++i){
        cnt[idx[data[i] >> 16]]++;
    }

    for(rint i = 1; i < 2048; ++i){
        cnt[i] += cnt[i-1];
    }
    
    for(rint i = 0; i < SIZE; ++i){
        register unsigned short d = (data[i] >> 16);
        rint nnid = cnt[idx[d]]-1;
        while(nnid < i){
            ruint temp = data[i];
            data[i] = data[nnid];
            data[nnid] = temp;
            cnt[idx[d]]--;
            d = data[i] >> 16;
            nnid = cnt[idx[d]]-1;
        }
    }
    
    short lbit[1024*4];
    
    for(rint i = 0; i < SIZE; ){
        rint len = 1;
        rusrt hbit = data[i] >> 16;
        lbit[0] = (data[i] & 0xffff);
        while(i + len < SIZE && ((data[i+len]>>16)) == hbit) lbit[len] = (data[i+len]), len++;

        merge(lbit, 0, len-1);

        for(rint k = 0; k < len; ++k){
            data[i+k] = (data[i+k] & 0xffff0000) | (unsigned short)lbit[k];
        }
        
        i +=len;
    }
}