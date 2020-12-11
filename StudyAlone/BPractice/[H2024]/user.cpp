#define HSIZE 1000007
#define MAXSIZE 100000
#define ull unsigned long long 
#define rull register ull
#define rint register int

typedef enum RELATIONSHIP {
    WIFE = 0,
    PARENT = 1,
    CHILD = 2
};
typedef enum GENDER{
    MALE = 0,
    FEMALE=1
};
int chk[HSIZE];
int tc;
unsigned long long name[HSIZE][2];
int gender[HSIZE];
int nodeid[HSIZE];
int mhash[HSIZE];
int query;
int qchk[MAXSIZE];

//parent, name[2], childs[200], clen
struct NODE{
    int parent[2];
    int name[2];
    int childs[200];
    int clen = 0;
} nodes[MAXSIZE];
int conv[256];
int Q[200];

int nid;
int hid;

void init(char initialMemberName[], int initialMemberSex)
{
    ++tc;
    nid = 1;
    hid = 1;
    register unsigned long long name[2] = {};
    rint cnt = 1;
    for(rint i = 'a'; i <= 'z'; ++i) conv[i] = cnt++;
    while(*initialMemberName){
        name[0] = (name[0] << 5) + (name[1]  >> 58);
        name[1] = (name[1] << 5) + conv[*initialMemberName++];
    }
    rint k = name[1] % HSIZE;
    while(chk[k] == tc && (::name[k][0] != name[0] || ::name[k][1] != name[1])) k = ++k%HSIZE;
    if(chk[k] != tc){
        chk[k] = tc;
        gender[k] = initialMemberSex;
        nodeid[k] = nid; 
        mhash[k] = hid;
        nodes[nid].name[0] = nodes[nid].name[1] = 0;
        nodes[nid].name[initialMemberSex] = hid;
        nodes[nid].clen = 0;
        nodes[nid].parent[0] = nodes[nid].parent[1] = 0;
        ::name[k][0] = name[0];
        ::name[k][1] = name[1];
        nid++;
        hid++;
    }
}

bool addMember(char newMemberName[], int newMemberSex, int relationship, char existingMemberName[])
{
    rull name[2] = {};
    while(*newMemberName){
        name[0] = (name[0] << 5) + (name[1]  >> 58);
        name[1] = (name[1] << 5) + conv[*newMemberName++];
    }
    rint k = name[1]%HSIZE;
    while(chk[k] == tc && (::name[k][0] != name[0] || ::name[k][1] != name[1])) k = ++k%HSIZE;
    if(chk[k] != tc){
        chk[k] = tc;
        mhash[k] = hid;
        hid++;
        ::name[k][0] = name[0];
        ::name[k][1] = name[1];
    }
    gender[k] = newMemberSex;

    name[0] = name[1] = 0;
    while(*existingMemberName){
        name[0] = (name[0] << 5) + (name[1]  >> 58);
        name[1] = (name[1] << 5) + conv[*existingMemberName++];
    }
    rint k2 = name[1]%HSIZE;
    while(chk[k2] == tc && (::name[k2][0] != name[0] || ::name[k2][1] != name[1])) k2 = ++k2%HSIZE;

    rint node;
    rint g1 = gender[k];
    rint g2 = gender[k2];
    switch(relationship){
        case WIFE:
        node = nodeid[k2];
        break;
        case PARENT:
        if(nodes[nodeid[k2]].parent[g2] == 0){
            node = nid;
            nodes[nid].parent[0] = nodes[nid].parent[1] = 0;
            nodes[nid].name[0] = nodes[nid].name[1] = 0;
            nodes[nid].clen = 1;
            nodes[nid].childs[0] = nodeid[k2];

            nodes[nodeid[k2]].parent[g2] = nid++;
        }
        else{
            node = nodes[nodeid[k2]].parent[g2];
        }
        break;
        case CHILD:
            nodes[nid].parent[0] = nodes[nid].parent[1] = 0;
            nodes[nid].parent[g1] = nodeid[k2];
            nodes[nid].name[0] = nodes[nid].name[1] = 0;
            nodes[nid].clen = 0;

            nodes[nodeid[k2]].childs[nodes[nodeid[k2]].clen++] = nid;
            node = nid++;
        break;
    }
    if(nodes[node].name[newMemberSex]){
        return false;
    }

    nodeid[k] = node;
    nodes[node].name[newMemberSex] = mhash[k];
    
	return true;
}

int getDistance(char nameA[], char nameB[])
{
    rull name[2] = {};
    query++;
    while(*nameA){
        name[0] = (name[0] << 5) + (name[1]  >> 58);
        name[1] = (name[1] << 5) + conv[*nameA++];
    }
    rint k = name[1]%HSIZE;
    while(chk[k] == tc && (::name[k][0] != name[0] || ::name[k][1] != name[1])) k = ++k%HSIZE;
    rint n1 = ::mhash[k];
    rint nA = nodeid[k];
    name[0] = name[1]  =0;
    while(*nameB){
        name[0] = (name[0] << 5) + (name[1]  >> 58);
        name[1] = (name[1] << 5) + conv[*nameB++];
    }

    k = name[1]%HSIZE;
    while(chk[k] == tc && (::name[k][0] != name[0] || ::name[k][1] != name[1])) k = ++k%HSIZE;
    rint nB = nodeid[k];
    rint f, r;
    f = r=  0;
    Q[r++] = nA;
    qchk[nA] = query;
    rint dist = 0;
    while(f !=r){
        rint cnt = r - f;
        while(cnt--){
            int now = Q[f++];
            for(rint i = 0; i < 2; ++i){
                rint p = nodes[now].parent[i];
                if(now == nB) return dist;
                if(p && qchk[p] != query){
                    qchk[p] = query;
                    Q[r++] = p;
                }
            }
            for(rint i  =0; i < nodes[now].clen; ++i){
                rint nxt = nodes[now].childs[i];
                if(qchk[nxt] == query) continue;
                qchk[nxt] = query;
                Q[r++] = nxt;
            }
        }
        dist++;
    }
    
	return -1;
}

int countMember(char nameA[], int dist)
{
    rull name[2] = {};
    query++;
    while(*nameA){
        name[0] = (name[0] << 5) + (name[1]  >> 58);
        name[1] = (name[1] << 5) + conv[*nameA++];
    }
    rint k = name[1]%HSIZE;
    while(chk[k] == tc && (::name[k][0] != name[0] || ::name[k][1] != name[1])) k = ++k%HSIZE;
    rint id = nodeid[k];
    rint f = 0, r = 0;
    Q[r++] = id;
    qchk[id] = query;
    rint res = -!dist;
    while(dist--){
        rint cnt = r-f;
        while(cnt--){
            rint now = Q[f++];
            for(rint i = 0 ; i < 2; ++i){
                int p = nodes[now].parent[i];
                if(p && qchk[p] != query){
                    qchk[p] = query;
                    Q[r++] = p;
                }
            }
            for(rint i = 0; i < nodes[now].clen; ++i){
                rint nxt = nodes[now].childs[i];
                if(qchk[nxt] == query) continue;
                qchk[nxt] = query;
                Q[r++] = nxt;
            }
        }
    }
    for(rint i = f; i < r; ++i){
        rint id = Q[i];
        res += !!nodes[id].name[0] + !!nodes[id].name[1];
    }
    
	return res;
}