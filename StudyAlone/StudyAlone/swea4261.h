#include<iostream>

using namespace std;

char avail[10][5] = {"","", "abc","def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
char s[1000001];
char in[1000001];

int strlen(char s[]){
    int res = 0;
    while(*s) s++, res++;
    return res;
}


int Do(){
    cin.sync_with_stdio(false), cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    for(int tc = 1;  tc <= T; tc++){
        int n;
        cin >> in >> n;
        int insize = strlen(in);
        int ret = 0;

        while(n--){
            cin >> s;
            int  ssize = strlen(s);
            if(ssize != insize){
                continue;
            }
            bool ok = true;
            for(int i = 0; i < ssize; i++){
                int num = in[i] - '0';
                bool isin = false;

                for(int j = 0; avail[num][j]; j++){
                    if(avail[num][j] == s[i]) {
                        isin = true; 
                        break;
                    }
                }
                if(!isin) {
                    ok = false; break;
                }
            }
            ret += ok;
        }
        cout << '#' << tc << ' ' << ret<< '\n';
    }
    return 0;
}