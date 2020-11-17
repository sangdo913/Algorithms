extern int check(int arr[200]);
int temp[200];
int candidate[200];
int clen = 0;
int fenwix[201];
int *arr;

void mymerge(int s1, int e1, int s2, int e2, int n1, int n2){
    int b, n;
    bool find1 = false, find2 = false;
    if(s1 == e1-1){ 
        b = s1+1;
        while(b <= 200) {
            fenwix[b]++;
            b += b & -b;
        }
        arr[s1] = n1;e1 = s1;
    }
    if(s2 == e2-1){ 
        b = s2 + 1;
        while(b <= 200) {
            fenwix[b]++;
            b += b & -b;
        }
        arr[s2] = n2;e2 = s2;
    }
    if(s1 == e1&& s2 == e2) return;
    int m1 = (s1+e1)/2, m2 = (s2+e2)/2;
    int f1, t1, f2, t2;
    n = m1-s1;
    b = m1;
    while(b) {
        n-= fenwix[b];
        b -= b&-b;
    }
    b = s1;
    while(b) {
        n+= fenwix[b];
        b-= b&-b;
    }
    if(!n) {
        find1 = true; 
        f1 = m1;
        t1 = e1;
    }
    else{
        n = e1 - m1;
        b = e1;
        while(b) {
            n-= fenwix[b];
            b -= b&-b;
        }
        b = m1;
        while(b) {
            n+= fenwix[b];
            b-= b&-b;
        }
        if(!n) {
            find1 = true;
            f1 = s1;
            t1 = m1;
        }
    }

    n = e2-m2;
    b = e2;
    while(b){
        n-= fenwix[b];
        b -= b&-b;
    }
    b = m2;
    while(b) {
        n+= fenwix[b];
        b-= b&-b;
    }
    if(!n){
        find2 =true;
        f2 = s2, t2 = m2;
    }
    else {
        n = m2-s2;
        b = m2;
        while(b){
            n-= fenwix[b];
            b -= b&-b;
        }
        b = s2;
        while(b) {
            n+= fenwix[b];
            b-= b&-b;
        }
        if(!n) {
            find2 = true;
            f2 = m2, t2 = e2;
        }
    }
    int res;
    if(find1 && find2){
        mymerge(f1,t1, f2,t2,n1,n2);
        return;
    }
    else if (!find1 && !find2) {
        for(int i = s1; i < m1; ++i) temp[i] = n1;
        for(int i = m2; i < e2; ++i) temp[i] = n2;
        res = check(temp);
        if((res >> 8) == 2){
            for(int i = s1; i < m1; ++i) temp[i] = 0;
            for(int i = m2; i < e2; ++i) temp[i] = 0;
            mymerge(s1,m1, m2,e2, n1,n2);
        }
        else if((res >>8) == 0) {
            for(int i = s1; i < m1; ++i) temp[i] = 0;
            for(int i = m2; i < e2; ++i) temp[i] = 0;
            mymerge(m1,e1, s2,m2, n1,n2);
        }
        else{
            for(int i = m2; i < e2; ++i) temp[i] = 0;
            res = check(temp);
            for(int i = s1; i <m1; ++i) temp[i] = 0;
            if(res >>8){
                mymerge(s1,m1,s2,m2,n1,n2);
            }
            else {
                mymerge(m1,e1,m2,e2,n1,n2);
            }
        }
        return;
    }
    if(find1) {
        for(int i = s2; i < m2; ++i){ temp[i] = n2; }
        res = check(temp);
        for(int i = s2; i < m2; ++i){ temp[i] = 0; }
        if(res >>8){
            mymerge(f1,t1,s2,m2, n1,n2);
        }
        else{
            mymerge(f1,t1,m2,e2,n1,n2);
        }
    }
    else {
        for(int i = s1; i < m1; ++i){ temp[i] = n1; }
        res = check(temp);
        for(int i = s1; i < m1; ++i){ temp[i] = 0; }
        if(res >>8){
            mymerge(s1,m1,f2,t2, n1,n2);
        }
        else{
            mymerge(m1,e1, f2,t2,n1,n2);
        }
    }
}
void func(int in[200]){
    arr = in;
    clen = 0;
    int n = 1;
    for(int i = 1; i <= 200; ++i) fenwix[i] = 0;
    for(int i = 127; i < 200; ++i) temp[i] = 0;
    while(clen != 200){
        int cnt = 0;
        for(int i = 0; i < 7; ++i) {
            int count = 1<<i;
            while(count--){
                temp[cnt++] = n;
            }
            ++n;
        }
        int res = check(temp);
        int nn = n;
        for(int i = 6; i >= 0; --i) {
            --nn;
            if(res & (1<<i)) candidate[clen++] = nn;
        }
    }
    for(int i = 0; i < 200; ++i) temp[i] = 0;
    for(int i = 0; i < 100; ++i){
        mymerge(0,200, 0,200, candidate[i*2], candidate[i*2+1]);
    }
}