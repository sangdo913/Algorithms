#include<iostream>
using namespace std;

#define rint register int
#define rll register long long
struct group{
    int gid;
    int uid[10];
    int usize;
    long long name;
}G[10];

int gsize;
struct user{
    int gid;
    int uid;
    long long name;
}users[20];

struct MFILE{
    long long name;
    int id;
    MFILE* next;
} files[10000];
int fsize;
struct EXT{
    long long name;
    int id;
    EXT * next;
}extension[10000];
struct DIRECTORY{
    long long name;
    int uid;
    int permission;
    DIRECTORY *next;
    DIRECTORY *child;
    MFILE *fnext;
    EXT *enext;
}directory[10000];
int dsize;

DIRECTORY root;

int esize;
int usize;
int conv[256];
void init()
{
    int cnt = 1;
    for(rint i = 'a'; i <= 'z'; ++i){
        conv[i] = cnt++;
    }
    conv['.'] = cnt++;
    conv['*'] = 0;

    usize = 1;
    gsize = 1;
    fsize = dsize = 0;
    const char*name = "admin";
    long long lname = 0;
    rint size= 0;
    while(name[size]){
        lname = (lname << 5) + conv[name[size++]];
    }
    users[0].name = G[0].name = lname;
    
    root.next = 0;
    root.enext = 0, root.fnext = 0;
    root.name = conv['/'];
    root.permission = 2;
    root.uid = 0;
    root.child = 0;
    root.next = 0;
}

void createUser(char userName[], char groupName[])
{
    rll lname = 0;
    rll gname = 0;
    while(*userName){
        lname = (lname <<5) + conv[*(userName++)];
    }
    user &u = users[usize];
    u.uid = usize++;
    u.name = lname;

    while(*groupName){
        gname = (gname<<5) + conv[*(groupName++)];
    }

    int gid =0;
    for(; gid < gsize; ++gid) 
        if(G[gid].name == gname){
            u.gid = gid;
            return;
        }
    G[gsize].gid = gsize;;
    G[gsize].name = gname;
    u.gid = gsize++;
}

DIRECTORY* findpath(DIRECTORY* dir, int group, int user, char path[]){
    path++;
    if(*path == 0) return dir;
    rll dname = 0;
    while(*path && *path != '/'){
        dname = (dname << 5) + conv[*(path++)];
    }
    DIRECTORY *cur = dir->child;
    while(cur){
        switch(cur->permission){
            case 0: 
            if(cur->uid != user) {
                if(cur->name == dname) return 0;
                else goto NEXT1;
            }
            break;
            case 1: 
            if(users[cur->uid].gid != group) {
                if(cur->name == dname) return 0;
                else goto NEXT1;
            }
            break;
        }
        if(cur->name == dname){
            return findpath(cur, group, user, path);
        }
        NEXT1:
        cur = cur->next;
    }
    return 0;
}
int createDirectory(char userName[], char path[], char directoryName[], int permission)
{
    rll uname = 0;
    while(*userName){
        uname = (uname<<5) + conv[*(userName++)];
    }
    int uid;
    for(uid = 0; uid < usize; ++uid) {
        if(users[uid].name == uname) break;
    }
    DIRECTORY* dir = findpath(&root, users[uid].gid, uid, path);
    if(dir == 0) return 0;

    rll dname = 0;

    while(*directoryName){
        dname = (dname << 5) + conv[*(directoryName++)];
    }
    DIRECTORY &d = directory[dsize++];
    d.enext = 0;
    d.fnext = 0;
    d.name = dname;
    d.permission = permission;
    d.uid = uid;
    d.next = dir->child;
    d.child = 0;

    dir->child = &d;
    
    return 1;
}


int createFile(char userName[], char path[], char fileName[], char fileExt[])
{
    rll uname = 0;
    while(*userName){
        uname = (uname << 5) + conv[*(userName++)];
    }
    int uid = 0;
    for(uid = 0; uid < usize; ++uid){
        if(users[uid].name == uname) break;
    }
    DIRECTORY* dir = findpath(&root, users[uid].gid, uid, path);
    if(dir ==0) return 0;
    rll fname = 0, ename = 0;
    while(*fileName){
        fname = (fname << 5) + conv[*(fileName++)];
    }
    while(*fileExt){
        ename = (ename<<5) + conv[*(fileExt++)];
    }

    MFILE& f = files[fsize];
    EXT& e = extension[fsize++];
    f.next = dir->fnext;
    e.next = dir->enext;

    dir->fnext = &f;
    dir->enext = &e;
    
    f.name = fname; e.name = ename;
    return 1;
}

int findpattern(DIRECTORY* dir, int uid, int gid, long long pattern[], long long fname, long long ename, int depth, int now){
    int res = 0;
    
    if(depth == now){
        MFILE * fcur = dir->fnext;
        EXT *ecur = dir->enext;
        while(fcur){
            if((!fname || fcur->name == fname) && (!ename || ecur->name == ename)){
                res++;
            }
            fcur= fcur->next;
            ecur= ecur->next;
        }
    }
    else{
        DIRECTORY* cur = dir->child;
        while(cur){
            if(cur->permission == 0 && cur->uid != uid) goto NEXT;
            if(cur->permission == 1 && users[cur->uid].gid != gid) goto NEXT;
            if(pattern[now] && pattern[now] != cur->name) goto NEXT;
            res += findpattern(cur, uid, gid, pattern, fname, ename, depth, now+1);

            NEXT:
            cur = cur->next;
        }
    }

    return res;
}
int find(char userName[], char pattern[])
{
    long long path[50];
    int psize = 0;
    rll fname = 0;
    rll ename = 0;
    rll pname = 0;

    while(1){
        pattern++;
        pname = 0;
        while(*pattern!='/' && *pattern!='.'){
            pname = (pname << 5) + conv[(*(pattern++))];
        }
        if(*pattern == '.') break;
        path[psize++] = pname;
    }
    fname = pname;
    pattern++;
    while(*pattern){
        ename = (ename << 5) + conv[*(pattern++)];
    }
    
    rll uname = 0;
    while(*userName){
        uname = (uname<<5) + conv[*(userName++)];
    }
    rint uid = 0;
    for(;uid < usize; ++uid){
        if(users[uid].name == uname) break;
    }
    
    return findpattern(&root, uid, users[uid].gid, path, fname, ename, psize, 0);
}
