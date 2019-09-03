#define PLEN 1001
#define POSTMAX 100000
#define MAXTIME 1001

struct POST{
    int timestamp;
    int pid;
    int uid;
    int like;
}posts[POSTMAX];

struct PEOPLE{
    int follow[PLEN];
}people[PLEN];

int ts;
int tc;

bool comp(POST p1, POST p2){
    if(ts - p1.timestamp <= 1000 && ts - p2.timestamp <= 1000){
        if(p1.like == p2.like) return p1.timestamp > p2.timestamp;
        return p1.like > p2.like;
    }
    else if(ts -p1.timestamp > 1000 && ts - p2.timestamp > 1000){
        return p1.timestamp > p2.timestamp;
    }
    else{
        return ts-p1.timestamp <= 1000;
    }
}

int allposts[MAXTIME][1000];
int plen[MAXTIME];

void init(int N)
{
    ++tc;
    for(int i = 0; i < MAXTIME; ++i) plen[i] = 0;
    for(int i = 1; i <=N; ++i) people[i].follow[i] = tc;
}

int temp[100000];

void mergeSort(int*arr,int s, int e){
    int l = s, m = (s+e)/2, r = m+1;
    int k = l;
    while(l<=m && r <= e) temp[k++] = comp(posts[arr[l]],posts[arr[r]]) ? arr[l++] : arr[r++];
    while(l<=m) temp[k++] = arr[l++];
    while(r<=e) temp[k++] = arr[r++];
    for(int i = s; i <=e; ++i) arr[i] = temp[i];
}

void merge(int *arr, int s, int e){
    if(s<e){
        int m = (s+e)/2;
        merge(arr,s,m);
        merge(arr,m+1,e);
        mergeSort(arr,s,e);
    }
}

void follow(int uID1, int uID2, int timestamp)
{
    people[uID1].follow[uID2] = tc;
}

void makePost(int uID, int pID, int timestamp)
{
    posts[pID].timestamp = timestamp;
    posts[pID].like = 0;
    posts[pID].pid = pID;
    posts[pID].uid = uID;

    allposts[timestamp/1000][plen[timestamp/1000]++] = pID;
}

void like(int pID, int timestamp)
{
    posts[pID].like++;
}

int show[10000];
void getFeed(int uID, int timestamp, int pIDList[])
{
    ts = timestamp;
    
    int rlen = 0;
    for(int i = timestamp/1000; i>=0 && !(timestamp/1000 - i > 1 && rlen > 10); --i){
        for(int j = 0; j < plen[i]; ++j){
            int pid = allposts[i][j];
            if(people[uID].follow[posts[pid].uid] == tc){
                show[rlen++] = pid;
            }
        }
    }
    merge(show, 0, rlen-1);

    for(int i = 0; i < (rlen < 10 ? rlen : 10); ++i) pIDList[i] = show[i];
    for(int i = rlen; i < 10; ++i) pIDList[i] = 0; 
}