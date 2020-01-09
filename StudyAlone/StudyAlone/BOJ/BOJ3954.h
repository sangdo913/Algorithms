#include<iostream>
using namespace std;
unsigned char arr[100000];
unsigned char str[5000];
unsigned char comm[5000];
int p;
int sp;
int asize, csize, ssize;
int jump[100000];
int st[100000];


int main(){
    freopen("0Text.txt", "r", stdin);
    int cnt;
    cin >> cnt;
    while(cnt--){
        int top = 0;
        int fcnt = 0;
        p = sp = 0;
        cin >> asize >> csize >> ssize;
        for(int i = 0; i < asize; ++i) arr[i] = 0;;
        for(int i = 0; i < csize; ++i) jump[i] = -1;
        cin >> comm;
        cin >> str;
        int cp = 0;
        int x = 1;
        while(cp != csize){
            switch(comm[cp]){
                case '-':
                arr[p]--;
                break;
                case '+': arr[p]++; break;
                case '<': p = (--p + asize) %asize; break;
                case '>': p = ++p %asize; break;
                case '[':
                if(arr[p]){
                    st[top++] = cp;
                }
                else{
                    int mycnt = 1;
                    cp++;
                    while(mycnt){
                        if(comm[cp] == ']') mycnt--;
                        else if(comm[cp] == '[') mycnt++;
                        cp++;
                    }
                    cp--;
                }
                break;
                case ']':
                if(fcnt >= 50000000){
                    cp  = st[0];
                    cp++;
                    top = 1;
                    while(top){
                        if(comm[cp] == '[') top++;
                        if(comm[cp] == ']') --top;
                        cp++;
                    }
                    cout << "Loops " << st[0] << ' ' << cp-1 << endl;
                    goto LOOPEND;
                }
                if(arr[p]){
                    cp = st[top-1];
                }
                else top--;
                break;
                case ',':
                if(ssize == sp) arr[p] = 255;
                else arr[p] = str[sp++];
                break;
            }
            fcnt++;
            cp++;
        }
        cout << "Terminates" << endl;
        LOOPEND:
        x=1;
    }
    return 0;
}