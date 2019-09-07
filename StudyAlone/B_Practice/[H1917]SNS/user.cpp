#define MAX_USER      1000
#define MAX_TAG       5000
#define MAX_MSG       100
#define HASH          20007

int follow[MAX_USER][MAX_USER];
int flen[MAX_USER];
int message[MAX_USER][MAX_MSG];
int mlen[MAX_USER];

struct MES{
    int time;
    int uid;
    int mid;
}msg[1000001];

struct SNS{
    int sid;
    char tag[10];
    SNS *prev, *next;
}sns[10*MAX_MSG*MAX_USER];
int sid;

SNS hash[HASH];

#define CONVTIME(a,b) ((a[b] - '0')*10 + (a[b+1]-'0')) 

inline int gethash(register char *s){
    register int ret = 0;
    while(*s){
        ret = ((ret <<5) +5381+ *s) %HASH;
        s++;
    }
    return ret;
}

inline int mstrcmp(register const char *a, register const char *b)
{
    register int i;
    for (i = 0; a[i] != '\0'; ++i) if (a[i] != b[i]) return a[i] - b[i];
    return a[i] - b[i];
}

inline void mmstrcpy(register char *dest, register const char *src)
{
    int i = 0;
    while (src[i] != '\0') { dest[i] = src[i]; i++; }
    dest[i] = src[i];
}

void init()
{
    sid = 0;
    for(register int i = 0; i < MAX_USER; ++i) follow[i][0] = i,flen[i] =1 , mlen [i] = 0;
    for(register int i = 0; i < HASH; ++i) hash[i].prev = hash[i].next = hash+i;
}

void createMessage(int msgID, int userID, register char msgData[])
{
    int h = CONVTIME(msgData,0)*3600 + CONVTIME(msgData, 3)*60 + CONVTIME(msgData, 6);
    int len = 0;
    int key;
    msgData += 9;

    while(*msgData){
        register SNS& s = sns[sid++];
        s.sid = msgID;

        msgData++;
        len = 0;
        while(*msgData && *msgData != ' '){
            s.tag[len++] = *msgData++;
        }
        s.tag[len] = 0;

        key = gethash(s.tag);

        s.next = hash + key;
        s.prev = hash[key].prev;

        hash[key].prev->next = &s;
        hash[key].prev = &s;

        msgData += *msgData == ' ';
    }

    msg[msgID].time = h;
    msg[msgID].uid = userID;
    msg[msgID].mid = msgID;

    message[userID][mlen[userID]++] = msgID; 
}

void followUser(int userID1, int userID2)
{
    follow[userID1][flen[userID1]++] = userID2;
}

inline bool cmp(int i1, int i2){
    if(msg[i1].time == msg[i2].time){
        return msg[i1].uid < msg[i2].uid;
    }
    return msg[i1].time > msg[i2].time;
}

int res[6];

inline void insert(int &rsize, int idx){
        res[rsize] = idx;
        register int j = rsize;
        while(j && cmp(res[j], res[j-1])){ res[j-1]^=res[j] ^= res[j-1] ^= res[j]; --j;}
        rsize += rsize < 5;
}

int searchByHashtag(char tagName[], int retIDs[])
{
    int key = gethash(++tagName);
    int rsize = 0;

    register SNS *cursur = hash[key].next;

    while(cursur != hash + key){
        if(mstrcmp(tagName, cursur->tag) == 0){
            insert(rsize, cursur->sid);
        }
        cursur = cursur->next;
    }
    for(int i  =0 ; i < rsize;++i) retIDs[i] = res[i];
	return rsize;
}

int getMessages(int userID, int retIDs[])
{
    int rsize = 0, uid, msgID;

    for(register int i = 0; i < flen[userID]; i++){
        uid = follow[userID][i];
        for(register int j = 0; j < mlen[uid]; ++j){
            msgID = message[uid][j];
            insert(rsize, msgID);
        }
    }
    for(int i = 0; i < rsize; ++i) retIDs[i] = res[i];
	return rsize;
}