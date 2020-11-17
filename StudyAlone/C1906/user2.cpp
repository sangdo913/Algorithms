int temp[200];
int candidate[200];
int clen = 0;
int fenwix[201];
int *arr;

void mymerge(int s1, int e1, int s2, int e2, int n1, int n2){
    if(s1 == e1+1){

    }
    for(int i = 0; i < 200; ++i) temp[i] = 0;
    int m1 = (s1+e1)/2, m2 = (s2+e2)/2;
    for(int i = s1; i < m1; ++i) {
        temp[i] = n1;
    }
    for(int i = m2; i < e2; ++i){
        temp[i] = n2;
    }
    int res = check(temp);
    if(res >> 8) == 2){

    }
    else if(res >>8) == 0){
        
    }
    else{

    }
}
void func(int in[200]){
    arr = in;
    int n = 1;
    for(int i = 127; i < 200; ++i) temp[i] = 0;
    while(clen != 200){
        int cnt = 0;
        for(int i = 0; i < 7; ++i){
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
}