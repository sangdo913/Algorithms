#define MAX_USER      1000
#define MAX_TAG       5000
#define MAX_MSG       100
#define HASH          10017

int message[MAX_USER][6];
int mlen[MAX_USER];

struct MES {
	int time;
	int uid;
	int mid;
}msg[1000001];

long long hash[HASH];
int hlist[HASH][6];
int hsize[HASH];

int followed[1000][1000];
int fsize[1000];

#define CONVTIME(a,b) ((a[b] - '0')*10 + (a[b+1]-'0')) 

inline bool cmp(int i1, int i2) {
	if (msg[i1].time == msg[i2].time) {
		return msg[i1].uid < msg[i2].uid;
	}
	return msg[i1].time > msg[i2].time;
}

inline void insert(int* res, int &rsize, int idx) {
	res[rsize] = idx;
	register int j = rsize;
	int temp;
	while (j && cmp(res[j], res[j-1])) { 
		temp = res[j], res[j] = res[j - 1], res[j - 1] = temp, --j;
	}
	rsize += rsize < 5;
}

void init()
{
	for (register int i = 0; i < MAX_USER; ++i) {
		fsize[i] = 1, followed[i][0] = i;
		mlen[i] = 0;
	}
	for (register int i = 0; i < HASH; ++i) hsize[i] = hash[i] = 0;
}

void createMessage(int msgID, int userID, register char msgData[])
{
	int h = CONVTIME(msgData, 0) * 3600 + CONVTIME(msgData, 3) * 60 + CONVTIME(msgData, 6);
	long long key;
    int idx;
	msgData += 9;

	msg[msgID].time = h;
	msg[msgID].uid = userID;
	msg[msgID].mid = msgID;

	while (*msgData) {
        key = 0;
		msgData++;

		while (*msgData && *msgData != ' ') {
			key <<= 8;
			key += *(msgData++);
		}

        idx = key%HASH;

        while(hash[idx] && hash[idx] != key) idx = (idx+1)%HASH; 
        hash[idx] = key;

        insert(hlist[idx], hsize[idx], msgID);

		msgData += *msgData == ' ';
	}

	insert(message[userID], mlen[userID], msgID);
}

void followUser(int userID1, int userID2)
{
    followed[userID1][fsize[userID1]++] = userID2;
}


int searchByHashtag(char tagName[], int retIDs[])
{
	long long v = 0;

	while (*++tagName) {
		v <<= 8;
		v += *tagName;
	}
	int key = v % HASH;
	int rsize = 0;

    while(hash[key] && hash[key] != v) key = (key+1)%HASH;

	for (register int i = 0; i < hsize[key]; ++i) retIDs[i] = hlist[key][i];
	return hsize[key];
}

int getMessages(int userID, int retIDs[])
{
    int res[6];
	int cnt= 0;
    int uid, mid;

    for(register int i = 0; i < fsize[userID]; ++i){
       uid = followed[userID][i];

       for(register int j = 0; j < mlen[uid]; ++j){
           mid = message[uid][j];
           insert(res, cnt, mid);
       } 
    }

    for(register int i = 0; i < cnt; ++i) retIDs[i] = res[i];

	return cnt;
}