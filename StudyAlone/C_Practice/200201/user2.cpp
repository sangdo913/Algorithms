#include<cstdio>
#define SIZE 1048576
#define rint register int

void test_sort(short data[1024]);
void mymerge(int *data, int size, short *buf){
    if(size < 2) return;
    if(size < 1024){
        for(rint i = 0; i < size; ++i){
            buf[i] = data[i];
        }
        test_sort(buf);
        rint l = 0;
        while(l < 1024 && buf[l] < 0) ++l;
        rint sz = size-l;
        rint i  =0;
        while(l){
           data[i++] = (unsigned short)buf[--l]; 
           buf[l] = 0;
        }
        l = 1024;
        while(sz--) {
            data[i++] = buf[--l];
            buf[l] = 0;
        }
        return;
    }
    rint m = size/2;
    mymerge(data, m, buf);
    mymerge(data+m, size-m, buf);
    rint s = 0, e = m, k = 0;
    while(s < m && e < size){
        buf[k++] = (data[s] < data[e] ? data[e++] : data[s++]);
    }
    while(s < m) buf[k++] = data[s++];
    while(e < size) buf[k++] = data[e++];
    for(rint i = 0; i < k; ++i){
        data[i] = (unsigned short)buf[i];
        buf[i] = 0;
    }
}

void test(unsigned int data[SIZE]) {
    int check[1<<16] = {};
    int count[2050] = {};
    int origin[2050] = {};
    int count2[2050] = {};
    rint id = 1;
    for (rint i = 0; i < SIZE; ++i) {
        register unsigned int v = data[i] >> 16;
        if(!check[v]) {
            origin[id] = v;
            check[v] = id++;
        }
        rint idx = check[v];
        ++count[idx];
    }
    short buf[1024*4] = {};
    mymerge(origin + 1,id-1, buf);

    for(rint i = 1; i< id; ++i) {
        count2[i] = count[check[origin[i]]];
        check[origin[i]] = i;
    }

    for(rint i = 1; i < id; ++i){
        count2[i] += count2[i-1];
    }

    for(rint i = SIZE-1; i>=0; --i){
        rint v = data[i] >> 16;
        rint idx = check[v];
        while(count2[idx]-1 >= i) {
            register unsigned int temp = data[i];
            rint sid = --count2[idx];
            data[i] = data[sid];
            data[sid] = temp;
            idx = check[data[i] >> 16];
        }
    }
    
    rint cur = 0;
    
    while(cur != SIZE){
        rint l = 0;
        rint prev = data[cur]>>16;
        while(cur != SIZE && prev == (int)(data[cur]>>16)){
            check[l++] = data[cur]&0xffff; 
            ++cur;
        }
        mymerge(check, l, buf);
        for(rint i = 0; i < l; ++i){
            data[cur-l+i] = (data[cur-l+i] &0xffff0000) + check[i];
        }
    }
}