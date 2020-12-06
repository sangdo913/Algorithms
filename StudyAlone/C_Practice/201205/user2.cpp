void culture(int n, int a, int b);
int covid_check(int n);
void clear(int n);
const int MAX_SIZE = 50000000;
#define RANGE 1000

void test(){
    int s = 0, e = MAX_SIZE;

    int l =0, r;
    int c = MAX_SIZE;
    while(s< e) {
        l = s;
        r = l + RANGE > MAX_SIZE ? MAX_SIZE : l + RANGE;
        c++;
        for(int i = l; i < r; ++i) culture(c,c,i);
        if(!covid_check(c)){
            s = r; 
            continue;
        }

        while(l < r){
            int m = l+r>>1;
            c++;
            for(int i = l; i <= m; ++i){
                culture(c,c,i);
            }
            if(!covid_check(c)){
                l = m+1;
            }
            else{
                r = m;
            }
        }
        clear(l); 
        s = l;
    }
}