#include<iostream>
#include<queue>
#include<string>
#include<algorithm>


using namespace std;

struct info{
    string s;
    int remain;
};
int main(){
    freopen("0Text.txt", "r", stdin);

    int n, m;
    string d;
    int T;
    cin >> T;
    int visit[10001];

    for(int tc = 1; tc <= T; ++tc) {
        queue<info> Q;
        cin >> d >> n >> m;

        int i = 0;
        sort(d.begin(), d.end());
        while(d[i]){
            string str;
            str.push_back(d[i]);
            Q.push({str,d[i]-'0'});
            ++i;
        }
        while(!Q.empty()){
            info now = Q.front();
            info next;
            int num = atoi(now.s.c_str());
            if(num < n + m){
                if(now.s[0] != '0'){
                    for (int i = 0; i < d.size(); ++i)
                    {
                        next.s = now.s + d[i];
                        next.remain = (now.remain * 10 + d[i] - '0') % n;
                        Q.push(next);
                    }
                }
                Q.pop();
            }
            else {
                break;
            }
        }
        
        while(!Q.empty()){
            info now = Q.front(); Q.pop();
            info next;
            if(now.remain == m){
                printf("%s\n", now.s.c_str());
                goto LOOPEND;
            }
            else{
                if(now.s[0] != '0'){
                    for (int i = 0; i < d.size(); ++i)
                    {
                        next.s = now.s + d[i];
                        next.remain = (now.remain * 10 + d[i] - '0') % n;
                        if (visit[next.remain] != tc)
                        {
                            visit[next.remain] = tc;
                            Q.push(next);
                        }
                    }
                }
            }
        }
        printf("IMPOSSIBLE\n");
        LOOPEND:
        int x=1;
    }
    return 0;
}