/*
RESULT : 9790
TOTAL CALL COUNT : 227649
AVERAGE CALL COUNT : 1025

1. 한번에 2개
2. 찾은건 fenwix
*/
#define rint register int

int fenwix[201];
unsigned char arr[300] = {};
unsigned char Q[200]= {};
unsigned char *k;
int check(unsigned char* key);

void pbs(int a, int b, int l1, int r1, int l2, int r2) {
    if(l1 + 1 == r1){
        k[l1] = a;
        rint idx = l1+1;
        while(idx <=200) {
            fenwix[idx]++;
            idx += idx&-idx;
        }
        Q[l1] = 0;
        r1 = l1;
    }
    if(l2 + 1 == r2) {
        rint idx = l2 + 1;
        k[l2] = b;
        while(idx <=200) {
            fenwix[idx]++;
            idx += idx&-idx;
        }
        Q[l2] = 0;
        r2 = l2;
    }
    if(l1 >= r1 && l2 >= r2) return;
    rint m1 = (l1 + r1)/2;
    rint left = l1, right = m1;
    rint num1 = 0,num2 = 0;
    rint num11 = 0, num22 = 0;
    while(left) {
        num1 -= fenwix[left];
        left -= left&-left;
    }

    while(right) {
        num1 += fenwix[right];
        right -= right & -right;
    }

    rint m2 = (l2 + r2)/2;
    left = l2, right = m2;

    while(left) {
        num2 -= fenwix[left];
        left -= left&-left;
    }
    while(right) {
        num2 += fenwix[right];
        right -= right&-right;
    }
    left = m1, right = r1;
    num11 = 0, num22 = 0;
    bool finda = 0,findaa = 0, findb = 0, findbb = 0;

    while(left) {
        num11 -= fenwix[left];
        left -= left&-left;
    }

    while(right) {
        num11 += fenwix[right];
        right -= right&-right;
    }
    finda = num11 == (r1 - m1);
    left = m2, right  = r2;
    while(left) {
        num22 -= fenwix[left];
        left -= left&-left;
    }
    while(right) {
        num22 += fenwix[right];
        right -= right&-right;
    }
    findb = num22 == (r2-m2);
    if(m1 - l1 == num1) {
        findaa = 1;
    }
    if(m2 - l2 == num2) {
        findbb = 1;
    }
    
    int des = (!finda && !findaa) + (!findb && !findbb);
    if(finda) r1 = m1; 
    if(findaa) l1 = m1;
    if(findb) r2 = m2;
    if(findbb) l2 = m2;
    if((finda || findaa) && (findb || findbb)) {
        pbs(a,b,l1,r1,l2,r2);
        return;
    }
    for(int i = l1; i < r1; ++i) Q[i] = 0;
    for(int i = l2; i < r2; ++i) Q[i] = 0;
    if(!finda && !findaa) {
        for(rint i = l1; i < m1; ++i) Q[i] = a;
    }
    if(!findb && !findbb) {
        for(rint i = m2; i < r2; ++i) Q[i] = b;
    }
    int res = check(Q);
    if(res /512 == des){
        if(finda || findaa) pbs(a,b,l1,r1, m2,r2);
        else if(findb || findbb) pbs(a,b,l1,m1,l2,r2);
        else{ pbs(a,b,l1,m1, m2,r2); }
    }
    else{
        if(finda || findaa){
            pbs(a,b, l1,r1, l2,m2);
        }
        else if(findb || findbb) pbs(a,b,m1,r1, l2,r2);
        else{ 
            if(res/512 == 0){
                pbs(a,b,m1,r1, l2,m2);
            }
            else {
                for(rint i = m2; i < r2; ++i)Q[i] = 0; 
                res = check(Q);
                if(res/512) pbs(a, b, l1, m1, l2, m2);
                else pbs(a,b, m1, r1, m2,r2);
            }
        }
    }
}

void test(unsigned char* key) {
    k = key;
    for(int i = 0; i <= 200; ++i) fenwix[i] = 0;
    for(rint i = 0; i < 200; ++i) Q[i] = 0;
    rint qlen = 0;
    rint nums = 1;
    rint asize = 0;
    while(asize < 200) {
        rint l = 0;
        rint s = nums;
        for(rint j = 1; j < 128; j<<=1) {
            for(rint k = 0; k < j; ++k) Q[l++] = nums;
            nums++;
        }
        
        rint b = check(Q);
        b%=512;
        while(b) {
            if(b&1) {
                arr[asize++] = s;
            }
            s++;
            b>>=1;
        }
    }
    asize = 200;
    for(int i = 0; i < 200; i+=2) {
        pbs(arr[i], arr[i+1], 0, 200, 0,200);
    }
}