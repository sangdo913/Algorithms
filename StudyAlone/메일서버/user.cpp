#define USER 1000
#define MAILSIZE 300
#define SENDQ 10000
#define WORDS 10

#define rint register int
int mailnum[USER];

struct SUBJECTMAIL {
	int uid;
	int mid;
	SUBJECTMAIL *prev, *next;
	SUBJECTMAIL *p, *n;
}snodes[50 * SENDQ];

int sid;
int query;
int myn;
#define HASHSIZE 30017
#define TSIZE 30017
long long texts[TSIZE];
int tsize[TSIZE][USER];

SUBJECTMAIL shash[HASHSIZE];
int myatoi[128];
int k;
SUBJECTMAIL mque[USER];

int tids[HASHSIZE][10];
int mids[HASHSIZE][10];
int ntid[HASHSIZE];
int nrid[HASHSIZE];
bool ismade;
void init(int N, int K)
{
	rint cnt;
	if (!ismade) {
		ismade = true;
		cnt = 1;
		for (rint i = 'a'; i <= 'z'; ++i) myatoi[i] = cnt++;
	}
	for (rint i = 0; i < myn; ++i) {
		register SUBJECTMAIL* dn = mque[i].n;
		while (dn != &mque[i]) {
			rint mid = dn->mid;
			for (rint j = 0; j < ntid[mid]; ++j) --tsize[tids[mid][j]][i];
			dn = dn->n;
		}
		mailnum[i] = 0;
	}

	myn = N;
	k = K;
	sid = 0;
	cnt = N;
	for (rint i = 0; i < cnt; ++i) {
		mque[i].p = mque[i].n = mque + i;
	}

	cnt = TSIZE;
	for (rint i = 0; i < cnt; ++i) {
		texts[i] = -1;
	}
	cnt = HASHSIZE;
	for (rint j = 0; j < cnt; ++j)shash[j].prev = shash[j].next = &shash[j], shash[j].mid = -1;
}
int sendcheck[TSIZE];
int idx[WORDS];
int temp[WORDS];

void sendMail(char subject[], int uID, int cnt, int rIDs[])
{
	++query;

	rint len = cnt;
	register char *s = subject; 
	register long long conv;
	rint convsub = 0;
	rint words = 0;
	rint  tlen = 0;
	rint key;
	rint rid;
	register SUBJECTMAIL *dn;
	for(rint i = 0; s[i]; i+=(bool)s[i]) {
		conv = 0;
		while (s[i] != ' ' && s[i]) {
			convsub = ((convsub << 5) + s[i]) % HASHSIZE;
			conv = (conv <<= 5) + myatoi[s[i++]];
		}

		key = conv % TSIZE;
		while (texts[key] != -1 && texts[key] != conv) key = (++key) % TSIZE;

		if (sendcheck[key] != query) {
			sendcheck[key] = query;
			temp[tlen++] = key;
		}

		idx[words++] = key;
		texts[key] = conv;
	}

	while (shash[convsub].mid != -1) {
		if (nrid[convsub] != words) goto FAIL;
		for (rint i = 0; i < words; ++i) {
			if (idx[i] != mids[convsub][i]) {
				goto FAIL;
			}
		}
		break;

		FAIL:
		convsub = ++convsub % HASHSIZE;
	}
	if (shash[convsub].mid == -1) {
		shash[convsub].mid = convsub;
		nrid[convsub] = words;
		for (rint i = 0; i < words; ++i) {
			mids[convsub][i] = idx[i];
		}
		ntid[convsub] = tlen;
		for (rint i = 0; i < tlen; ++i) {
			tids[convsub][i] = temp[i];
		}
	}
	

	for (rint i = 0; i < len; ++i) {
		rid = rIDs[i];
		if (mailnum[rid] == k) {
			dn = mque[rid].n;
			rint dmid = dn->mid;

			for (rint j = 0; j < ntid[dmid]; ++j) {
				--tsize[tids[dmid][j]][rid];
			}
			dn->prev->next = dn->next;
			dn->next->prev = dn->prev;
			dn->p->n = dn->n;
			dn->n->p = dn->p;
			mailnum[rid]--;
		}

		mailnum[rid]++;
		register SUBJECTMAIL &nn = snodes[sid++];

		nn.uid = rid;
		nn.prev = shash[convsub].prev;
		nn.next = &shash[convsub];
		nn.mid = convsub;

		shash[convsub].prev->next = &nn;
		shash[convsub].prev = &nn;

		nn.p = mque[rid].p;
		nn.n = &mque[rid];

		mque[rid].p->n = &nn;
		mque[rid].p = &nn;
		for (rint j = 0; j < tlen; ++j) {
			++tsize[temp[j]][rid];
		}
	}
}

int getCount(int uID)
{
	return mailnum[uID];
}

int deleteMail(int uID, char subject[])
{
	rint cnt = 0, key;
	register long long conv;
	register char* c = subject;
	rint convsub = 0;
	for(rint i = 0; c[i]; i += (bool)c[i]) {
		conv = 0;
		while (c[i] != ' ' && c[i]) {
			convsub = ((convsub << 5) + c[i]) % HASHSIZE;
			conv = (conv << 5) + myatoi[c[i++]];
		}
		key = conv % TSIZE;
		while (texts[key] != -1 && texts[key] != conv) key = ++key % TSIZE;
		if (texts[key] == -1) return 0;
		idx[cnt++] = key;
	}
	while (shash[convsub].mid != -1) {
		if (nrid[convsub] != cnt) goto FAIL2;
		for (rint i = 0; i < cnt; ++i) {
			if (mids[convsub][i] != idx[i]) goto FAIL2;
		}
		break;
		FAIL2:
		convsub = ++convsub%HASHSIZE;
	}
	if (shash[convsub].mid == -1) return 0;

	rint res = 0;
	register SUBJECTMAIL *cursor = shash[convsub].next;
	register SUBJECTMAIL *dn;

	while (cursor != &shash[convsub]) {
		if (cursor->uid == uID) {
			dn = cursor;
			cursor = cursor->prev;

			dn->prev->next = dn->next;
			dn->next->prev = dn->prev;
			dn->p->n = dn->n;
			dn->n->p = dn->p;
			++res;
		}

		cursor = cursor->next;
	}
	mailnum[uID] -= res;
	for (rint i = 0; i < ntid[convsub]; ++i) {
		tsize[tids[convsub][i]][uID] -= res;
	}
	return res;
}

int searchMail(int uID, char text[])
{
	register long long conv = 0;
	register char * t = text;
	for(rint i = 0; t[i]; ++i) {
		conv = ((conv << 5) + myatoi[t[i]]);
	}
	rint key = conv % TSIZE;
	while (texts[key] != -1 && texts[key] != conv) key = ++key % TSIZE;
	if (key == -1) return 0;
	return tsize[key][uID];
}