<<<<<<< HEAD
#define SIZE 1048576
#define HASH 65537
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

#include<cstdio>
void test(unsigned int data[SIZE])
{
    int cnt[2048] = {0};
    short digit[2048] = {0}, temp[2048];
    unsigned short cdigit[2048];
    bool visit[HASH] = {0};
    int idx[HASH]= {};
    rint dlen = 0;

    for(rint i = 0; i < SIZE; ++i){
        unsigned short d1 = (data[i] >> 16)&0xffff;
        unsigned short d2 = data[i] & 0xffff;
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
    while(digit[zi] < 0) zi++;

    for(rint i = 0; i < 2048; ++i){
            cdigit[i] = (unsigned short)digit[(zi+i)%2048];   
    }
    for(rint i = 0; i < 1024; ++i){
        rint temp = cdigit[i];
        cdigit[i] = cdigit[2047-i];
        cdigit[2047-i] = temp;
    }
    for(rint i = 0; i < 2048; ++i){
        unsigned short d = cdigit[i];
        idx[d] = i;
    }

    for(rint i =0; i < SIZE; ++i){
        unsigned short d = (data[i] >> 16)&0xffff;
        cnt[idx[d]]++;
    }

    for(rint i = 1; i < 2048; ++i){
        cnt[i] += cnt[i-1];
    }
    
    for(rint i = 0; i < SIZE; ++i){
        unsigned short d = (data[i] >> 16)&0xffff;
        rint nnid = cnt[idx[d]]-1;
        while(nnid < i){
            if((unsigned short)(data[i] >> 16) < (unsigned short)(data[nnid] >> 16)){
                printf("noononono\n");
            }
            rint temp = data[i];
            data[i] = data[nnid];
            data[nnid] = temp;
            cnt[idx[d]]--;
            d = data[i] >> 16;
            nnid = cnt[idx[d]]-1;
        }
    }
    
    for(int i = 1; i < SIZE; ++i){
        if((unsigned short)(data[i-1]>>16) < (unsigned short)(data[i]>> 16)) 
            printf("nono\n");
    }
    short lbit[1024*4];
    
    for(rint i = 0; i < SIZE; ){
        rint len = 1;
        rusrt hbit = (data[i] >> 16)&0xffff;
        lbit[0] = (data[i] & 0xffff);
        while(i + len < SIZE && ((data[i+len]>>16)&0xffff) == hbit) lbit[len++] = (data[i+len]&0xffff);

        merge(lbit, 0, len-1);
        if(len > 2060){
            printf("exeed\n");
        }

        for(rint k = 0; k < len; ++k){
            data[i+k] = (data[i+k] & 0xffff0000) | (unsigned short)lbit[k];
        }
        i +=len;
    }
}
// #define SIZE 1048576
// #define HASH 65536
// #define ruint register unsigned int
// #define rint register int
// #define uint unsigned int

// extern void test_sort(short data[1024]);

// void merge(short data[1024*4], int s, int e){
//     if(s < e){
//         if (e - s + 1 <= 1024)
//         {
//             short q[1024] = {0};
//             rint zi = 0;
//             rint l = (e - s + 1);
//             for (rint i = 0; i < l; ++i)
//             {
//                 q[i] = data[s + i];
//             }
//             test_sort(q);

//             while (q[zi] < 0)
//                 zi++;
//             l -= zi;
//             e = 1023;
//             while (zi)
//                 data[s++] = q[--zi];
//             while (l--)
//                 data[s++] = q[e--];
//         }
//         else
//         {
//             rint m = (s + e) / 2;
//             if(m > e) m = e;
//             m = (m / 1024 + (m % 1024 > 0)) * 1024;
//             merge(data, s, m - 1);
//             merge(data, m, e);
//             short temp[1024 * 4];
//             rint l = s, r = m, k = s;
//             while (l <= m - 1 && r <= e)
//             {
//                 if ((unsigned short)data[l] < (unsigned short)data[r])
//                     temp[k++] = data[r++];
//                 else
//                     temp[k++] = data[l++];
//             }
//             while (l <= m - 1)
//                 temp[k++] = data[l++];
//             while (r <= e)
//                 temp[k++] = data[r++];
//             for (rint i = s; i <= e; ++i)
//                 data[i] = temp[i];
//         }
//     }
// }

// void test(unsigned int data[SIZE])
// {
//     int cnt[2048] = {0};
//     short digit[2048] = {0}, temp[2048];
//     unsigned short cdigit[2048];
//     bool visit[HASH] = {0};
//     int idx[HASH];
//     rint dlen = 0;

//     for(rint i = 0; i < SIZE; ++i){
//         unsigned short d1 = data[i] >> 16;
//         unsigned short d2 = data[i] & 0xffff;
//         if(!visit[d1]){
//             visit[d1] = true;
//             digit[dlen++] = (short)d1;
//         }
//         if(!visit[d2]){
//             visit[d2] = true;
//             digit[dlen++] = (short)d2;
//         }
//     }

//     test_sort(digit);
//     test_sort(digit+1024);
//     rint k = 0, d1 = 0, d2 = 1024;
//     while(d1 < 1024 && d2 < 2048) temp[k++] = digit[d1] > digit[d2] ? digit[d2++] : digit[d1++];
//     while(d1 < 1024) temp[k++] = digit[d1++];
//     while(d2<2048) temp[k++] = digit[d2++]; 
//     for(rint i = 0; i < 2048; ++i) digit[i] = temp[i];
//     rint zi = 0;
//     while(digit[zi] < 0) zi++;

//     for(rint i = 0; i < 2048; ++i){
//             cdigit[i] = (unsigned short)digit[(zi+i)%2048];   
//     }
//     for(rint i = 0; i < 1024; ++i){
//         rint temp = cdigit[i];
//         cdigit[i] = cdigit[2047-i];
//         cdigit[2047-i] = temp;
//     }
//     for(rint i = 0; i < 2048; ++i){
//         unsigned short d = cdigit[i];
//         idx[d] = i;
//     }

//     for(rint i =0; i < SIZE; ++i){
//         unsigned short d = data[i] >> 16;  
//         cnt[idx[d]]++;
//     }

//     for(rint i = 1; i < 2048; ++i){
//         cnt[i] += cnt[i-1];
//     }
    
//     for(rint i = 0; i < SIZE; ++i){
//         unsigned short d = data[i] >> 16;
//         rint nnid = cnt[idx[d]]-1;
//         while(nnid < i){
//             rint temp = data[i];
//             data[i] = data[nnid];
//             data[nnid] = temp;
//             cnt[idx[d]]--;
//             d = data[i] >> 16;
//             nnid = cnt[idx[d]]-1;
//         }
//     }

//     short lbit[1024*4];
//     for(rint i = 0; i < SIZE; ){
//         rint len = 1;
//         rint hbit = data[i] >> 16;
//         lbit[0] = (data[i] & 0xffff);
//         while(i + len < SIZE && (data[i+len]>>16) == hbit) lbit[len++] = (data[i+len]&0xffff);

//         merge(lbit, 0, len-1);

//         for(rint k = 0; k < len; ++k){
//             data[i+k] = (data[i+k] & 0xffff0000) + (unsigned short)lbit[k];
//         }
//         i +=len;
//     }
// }
=======
 #define SIZE 1048576
 #define HASH 65536
 #define ruint register unsigned int
 #define rint register int
 #define uint unsigned int
 #define rsrt register short
 #define rusrt register unsigned short
 
 extern void test_sort(short data[1024]);
 
 void merge(short data[1024 * 4], int s, int e) {
     if (s < e) {
         if (e - s + 1 <= 1024) {
             short q[1024] = { 0 };
             rint zi = 0;
             rint l = (e - s + 1);
             for (rint i = 0; i < l; ++i) {
                 q[i] = data[s + i];
             }
             test_sort(q);
 
             while (q[zi] < 0) zi++;
             l -= zi;
             e = 1023;
             while (zi) data[s++] = q[--zi];
             while (l--) data[s++] = q[e--];
         }
         else {
             rint m = (s + e) / 2;
             m = (m / 1024 + (m % 1024 > 0)) * 1024;
             if (e < m) m = e;
             merge(data, s, m - 1);
             merge(data, m, e);
             short temp[1024 * 4];
             rint l = s, r = m, k = s;
             while (l <= m - 1 && r <= e) {
                 if ((unsigned short)data[l] < (unsigned short)data[r]) temp[k++] = data[r++];
                 else temp[k++] = data[l++];
             }
             while (l <= m - 1) temp[k++] = data[l++];
             while (r <= e) temp[k++] = data[r++];
             for (rint i = s; i <= e; ++i) data[i] = temp[i];
         }
     }
 
 }
 
 void test(unsigned int data[SIZE])
 {
     int cnt[2048] = { 0 };
     short digit[2048] = { 0 }, temp[2048];
     unsigned short cdigit[2048];
     bool visit[HASH] = { 0 };
     int idx[HASH];
     rint dlen = 0;
 
     for (rint i = 0; i < SIZE; ++i) {
         rusrt d1 = data[i] >> 16;
         rusrt d2 = data[i] & 0xffff;
         if (!visit[d1]) {
             visit[d1] = true;
             digit[dlen++] = (short)d1;
         }
         if (!visit[d2]) {
             visit[d2] = true;
             digit[dlen++] = (short)d2;
         }
     }
 
     test_sort(digit);
     test_sort(digit + 1024);
     rint k = 0, d1 = 0, d2 = 1024;
     while (d1 < 1024 && d2 < 2048) temp[k++] = digit[d1] > digit[d2] ? digit[d2++] : digit[d1++];
     while (d1 < 1024) temp[k++] = digit[d1++];
     while (d2 < 2048) temp[k++] = digit[d2++];
     for (rint i = 0; i < 2048; ++i) digit[i] = temp[i];
     rint zi = 0;
     while (digit[zi] < 0) zi++;
 
     for (rint i = 0; i < 2048; ++i) {
         cdigit[i] = (unsigned short)digit[(zi + i) % 2048];
     }
     for (rint i = 0; i < 1024; ++i) {
         rint temp = cdigit[i];
         cdigit[i] = cdigit[2047 - i];
         cdigit[2047 - i] = temp;
     }
     for (rint i = 0; i < 2048; ++i) {
         rusrt d = cdigit[i];
         idx[d] = i;
     }
 
     for (rint i = 0; i < SIZE; ++i) {
         rusrt d = data[i] >> 16;
         cnt[idx[d]]++;
     }
 
     for (rint i = 1; i < 2048; ++i) {
         cnt[i] += cnt[i - 1];
     }
 
     for (rint i = 0; i < SIZE; ++i) {
         rusrt d = data[i] >> 16;
         rint nnid = cnt[idx[d]] - 1;
         while (nnid < i) {
             rint temp = data[i];
             data[i] = data[nnid];
             data[nnid] = temp;
             cnt[idx[d]]--;
             d = data[i] >> 16;
             nnid = cnt[idx[d]] - 1;
         }
     }
 
     short lbit[1024 * 4];
     for (rint i = 0; i < SIZE; ) {
         rint len = 1;
         rint hbit = data[i] >> 16;
         lbit[0] = (data[i] & 0xffff);
         while (i + len < SIZE && (data[i + len] >> 16) == hbit) lbit[len++] = (data[i + len] & 0xffff);
 
         merge(lbit, 0, len - 1);
 
         for (rint k = 0; k < len; ++k) {
             data[i + k] = (data[i + k] & 0xffff0000) + (unsigned short)lbit[k];
         }
         i += len;
     }
 }
>>>>>>> 1334a45bf6826b008bb656b57a561418b8523ba1
