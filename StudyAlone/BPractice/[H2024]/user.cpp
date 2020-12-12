#define MAXSIZE 200000
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
int trie[MAXSIZE][26];
int gender[MAXSIZE];
int nodeid[MAXSIZE];
int tid;
int nsize;

//parent, name[2], childs[200], clen
struct NODE{
    int parent[2];
    int name[2];
    int childs[200];
    int clen = 0;
} nodes[201];
int conv[256];

int dist[201][201];
int counter[201][201];

void init(char initialMemberName[], int initialMemberSex)
{
    for(rint i = 0; i < tid; ++i) {
        for(rint j = 0; j < 26; ++j) trie[i][j] = 0;
    }
    for(rint i = 1; i < nsize; ++i) {
        nodes[i].name[0] = nodes[i].name[1] = 0;
        nodes[i].clen = 0;
        nodes[i].parent[0] = nodes[i].parent[1] = 0;
        for(rint j = 0; j < nsize; ++j) counter[i][j] = 0;
    }
    tid = 1;
    nsize = 1;
    rint cnt = 0;
    for(rint i = 'a'; i <= 'z'; ++i) conv[i] = cnt++;
    int t = 0;

    while(*initialMemberName){
        trie[t][conv[*initialMemberName]] = tid++;
        t = trie[t][conv[*initialMemberName++]];
    }
    nodes[nsize].name[initialMemberSex] = t;
    gender[t] = initialMemberSex;
    nodeid[t] = nsize++;
    counter[1][0] = 1;
    dist[1][1] = 0;
}

bool addMember(char newMemberName[], int newMemberSex, int relationship, char existingMemberName[])
{
    rint node;
    rint nid = 0;
    while(*newMemberName){
        if(!trie[nid][conv[*newMemberName]]){
            trie[nid][conv[*newMemberName]] = tid++;
        }
        nid = trie[nid][conv[*newMemberName++]];
    }
    gender[nid] = newMemberSex;

    rint nid2 = 0;
    while(*existingMemberName) {
        nid2 = trie[nid2][conv[*existingMemberName++]];
    }
    rint exist = nodeid[nid2];
    rint g = gender[nid2];
    switch(relationship){
        case WIFE:
        node = nodeid[nid2];
        break;
        case PARENT:
        if(nodes[exist].parent[g] == 0){
            node = nsize++;
            nodes[node].clen = 1;
            nodes[node].childs[0] = nodeid[nid2];

            nodes[exist].parent[g] = node;
        }
        else{
            node = nodes[exist].parent[g];
        }
        break;
        case CHILD:
            node = nsize++;
            nodes[node].parent[newMemberSex] = exist;

            nodes[exist].childs[nodes[exist].clen++] = node;
        break;
    }
    if(nodes[node].name[newMemberSex]){
        return false;
    }

    nodeid[nid] = node;
    nodes[node].name[newMemberSex] = nid;
    
    if(!nodes[node].name[newMemberSex^1]){
        for(rint i = 1; i < nsize-1; ++i){
            dist[i][node] = dist[node][i] = dist[exist][i] + 1;
            counter[node][dist[node][i]]+= !!nodes[i].name[0] + !!nodes[i].name[1];
            counter[i][dist[node][i]]++;
        }
        counter[node][0]=1;
    }
    else{
        for(rint i = 1; i < nsize; ++i){
            counter[i][dist[node][i]]++;
        }
    }
	return true;
}

int getDistance(char nameA[], char nameB[])
{
    rint nA = 0;
    while(*nameA){
       nA = trie[nA][conv[*nameA++]]; 
    }
    nA = nodeid[nA];

    rint nB = 0;
    while(*nameB){
        nB = trie[nB][conv[*nameB++]];
    }
    nB = nodeid[nB];
    
	return dist[nA][nB];
}

int countMember(char nameA[], int dist)
{
    rint id = 0;
    while(*nameA){
        id = trie[id][conv[*nameA++]];
    }
    id = nodeid[id];
    
	return counter[id][dist]-!dist;
}