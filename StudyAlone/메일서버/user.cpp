//kinssang 님 코드를 보고 작성했습니다.
#define USER 1000
#define SENDQ 10000
#define WORDS 10
#define TSIZE 5000000
#define HASHSIZE 100017
#define THASH 100017
#define rint register int
int mailnum[USER];

struct SUBJECTMAIL {
	int uid;
	int mid;
}snodes[50 * SENDQ];

struct TMAIL {
	int id;
	int mid;
	TMAIL *next;
}tnodes[10 * SENDQ];

int tc;
SUBJECTMAIL shash[HASHSIZE];
int myatoi[128];
int k;

int mQ[USER][SENDQ];
int mdeleted[50 * SENDQ];
int from[USER];
int to[USER];
long long mids[SENDQ][10];
int nrid[SENDQ];
int smcheck[HASHSIZE];

TMAIL thash[THASH];
TMAIL* tlist[SENDQ];
long long texts[SENDQ];
int tcheck[THASH];
int tid;
int sid;
int tsize;
bool ismade;
int msize;
long long idx[WORDS];
int idxcheck[SENDQ];
int keys[WORDS];
int query;

void init(int N, int K)
{
	if (!ismade) {
		rint cnt;

		ismade = true;
		cnt = 1;
		for (rint i = 'a'; i <= 'z'; ++i) myatoi[i] = cnt++;
	}
	for (rint i = 0; i < N; ++i) {
		mailnum[i] = 0;
		from[i] = to[i] = 0;
	}
	for(rint j = 0 ; j < N;++j)

	++tc;
	tid = tsize = sid = msize = 0;
	k = K;
}

void sendMail(char subject[], int uID, int cnt, int rIDs[])
{
	++query;
	rint len = cnt;
	register char *s = subject;
	register long long conv;
	rint convsub = 0;
	rint words = 0;
	rint textsize = 0;
	rint rid;
	rint klen = 0;
	for (rint i = 0; s[i]; i += (bool)s[i]) {
		conv = 0;
		while (s[i] != ' ' && s[i]) {
			convsub = ((convsub << 5) + s[i]) % HASHSIZE;
			conv = (conv <<= 5) + myatoi[s[i++]];
		}
		rint key = conv % THASH;
		while (tcheck[key] == tc && texts[thash[key].id] != conv) { key = ++key % THASH; }

		if (tcheck[key] != tc) {
			thash[key].id = tsize;
			texts[thash[key].id] = conv;
			tcheck[key] = tc;
			tlist[tsize++] = 0;
		}
		rint id = thash[key].id;
		if (idxcheck[id] != query) {
			idxcheck[id] = query;
			keys[klen++] = id;
		}
		
		idx[words++] = conv;
	}
	rint mid;

	while (smcheck[convsub] == tc) {
		mid = shash[convsub].mid;
		if (nrid[mid] != words) goto FAIL;
		for (rint i = 0; i < words; ++i) {
			if (idx[i] != mids[mid][i]) {
				goto FAIL;
			}
		}
		break;

	FAIL:
		convsub = ++convsub % HASHSIZE;
	}
	if (smcheck[convsub] != tc) {
		smcheck[convsub] = tc;
		mid = shash[convsub].mid = msize;
		nrid[mid] = words;
		for (rint i = 0; i < words; ++i) {
			mids[mid][i] = idx[i];
		}
		for (rint i = 0; i < klen; ++i) {
			rint id = keys[i];
			register TMAIL &nn = tnodes[tid++];
			nn.id = id;
			nn.mid = msize;
			nn.next = tlist[id];
			tlist[id] = &nn;
		}
		++msize;
	}

	for (rint i = 0; i < len; ++i) {
		rid = rIDs[i];
		while (mdeleted[mQ[rid][from[rid]]] == tc) ++from[rid];

		if (mailnum[rid] == k) {
			rint snid = mQ[rid][from[rid]++];
			mdeleted[snid] = tc;
			mailnum[rid]--;
		}

		mailnum[rid]++;
		register SUBJECTMAIL &nn = snodes[sid];
		mQ[rid][to[rid]++] = sid++;
		nn.uid = rid;
		nn.mid = mid;
	}
}

int getCount(int uID)
{
	return mailnum[uID];
}

int deleteMail(int uID, char subject[])
{
	rint cnt = 0;
	register long long conv;
	register char* c = subject;
	rint convsub = 0;
	for (rint i = 0; c[i]; i += (bool)c[i]) {
		conv = 0;
		while (c[i] != ' ' && c[i]) {
			convsub = ((convsub << 5) + c[i]) % HASHSIZE;
			conv = (conv << 5) + myatoi[c[i++]];
		}
		idx[cnt++] = conv;
	}
	rint mid;
	while (smcheck[convsub] == tc) {
		mid = shash[convsub].mid;
		if (nrid[mid] != cnt) goto FAIL2;
		for (rint i = 0; i < cnt; ++i) {
			if (mids[mid][i] != idx[i]) goto FAIL2;
		}
		break;
	FAIL2:
		convsub = ++convsub%HASHSIZE;
	}
	if (smcheck[convsub] != tc) return 0;

	rint res = 0;

	for (rint i = from[uID]; i < to[uID]; ++i) {
		rint sid = mQ[uID][i];
		if (mdeleted[sid] == tc) continue;
		rint nowMid = snodes[sid].mid;

		if (mid == nowMid) {
			mdeleted[sid] = tc;
			++res;
		}
	}
	mailnum[uID] -= res;
	return res;
}

int searchMail(int uID, char text[])
{
	register long long conv = 0;
	register char * t = text;
	for (rint i = 0; t[i]; ++i) {
		conv = ((conv << 5) + myatoi[t[i]]);
	}
	rint key = conv % THASH;
	while (tcheck[key] == tc && texts[thash[key].id] != conv) key = ++key % THASH;

	rint res = 0;
	if (tcheck[key] != tc) return 0;
	register TMAIL* tm = tlist[thash[key].id];
	while (tm) {
		for (rint i = from[uID]; i < to[uID]; ++i) {
			rint sid = mQ[uID][i];
			if (mdeleted[sid] == tc) continue;
			if (snodes[sid].mid == tm->mid) ++res;
		}
		tm = tm->next;
	}
	return res;
}