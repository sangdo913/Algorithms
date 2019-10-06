#define HSIZE 2017

struct LINE {
	char str[16];
	int len;
	LINE() :len(0), str{ 0 } {}
}*lines;

int llen, clen;
int _lsize, _csize;

struct COMMIT {
	int p;
	int idx;
	bool isdelete;
	int line;
	char str[21];
}*commits;

struct BRANCH {
	int cid;
	char str[16];
	int lines[1025];
	int llen;
}branches[1001];
int blen;

int myhash[HSIZE];
BRANCH* now;
int cnow;

int mystrcpy(const char *f, char *t) {
	int res = 0;
	while (*f) *(t++) = *(f++), res++;
	*t = 0;
	return res;
}

int mystrcmp(const char *a, const char *b) {
	while (*a && *a == *b) ++a, ++b;
	return *a - *b;
}

unsigned int gethash(const char *str) {
	unsigned int ret = 0;
	while (*str) {
		ret = (ret + (*str << 5) + 5381) % HSIZE;
		str++;
	}
	return ret;
}
void Init() {
	for (register int i = 0; i < HSIZE; ++i) myhash[i] = 0;

	if (_csize) delete[](commits);
	if (_lsize) delete[](lines);
	commits = new COMMIT[10];
	_csize = 10;
	clen = 1;
	
	lines = new LINE[10];
	_lsize = 10;
	llen = 1;

	myhash[gethash("Master")] = 1;
	mystrcpy("Master", branches[1].str);
	blen = 2;
	now = branches + 1;
	branches[1].llen = 0;
}

COMMIT* commitalloc() {
	if (clen == _csize) {
		COMMIT* c = new COMMIT[_csize * 2];
		for (register int i = 0; i < _csize; ++i) {
			c[i].p = commits[i].p;
			c[i].idx = commits[i].idx;
			c[i].isdelete = commits[i].isdelete;
			c[i].line = commits[i].line;
			mystrcpy(commits[i].str, c[i].str);
		}
		delete[](commits);
		commits = c;
		_csize *= 2;
	}

	return commits + clen++;
}

LINE* linealloc() {
	if (llen == _lsize) {
		LINE* l = new LINE[_lsize * 2];
		for (register int i = 0; i < _lsize; ++i) {
			l[i].len = mystrcpy(lines[i].str, l[i].str);
		}
		delete[](lines);
		lines = l;
		_lsize <<= 1;
	}
	return lines+llen++;
}

void insert(int line[1025], int llen, int v, int p) {
	while (llen != p) {
		line[llen] = line[llen - 1];
		--llen;
	}
	line[p] = v;
}
void del(int line[1025], int p, int llen) {
	for (; p < llen; ++p) {
		line[p] = line[p + 1];
	}
	line[llen] = 0;
}

int getDocument(int cnow, int docu[1025]) {
	int len = now->llen;
	for (int i = 0; i < now->llen; ++i) docu[i] = now->lines[i];

	if (cnow != now->cid) {
		int c = now->cid;
		while (c != cnow) {
			if (commits[c].isdelete) {
				insert(docu, len++, commits[c].line, commits[c].idx);
			}
			else {
				if (lines[commits[c].line].len) {
					docu[commits[c].idx] = commits[c].line;
				}
				else del(docu, commits[c].idx, --len);
			}

			c = commits[c].p;
		}
	}
	return len;
}

void Branch(const char *str) {
	unsigned int h = gethash(str);

	while (myhash[h]) h = ++h%HSIZE;
	myhash[h] = blen;

	BRANCH &nb = branches[blen++];

	nb.llen = getDocument(cnow, nb.lines);
	nb.cid = cnow;


	mystrcpy(str, nb.str);
	now = &nb;
};

void Commit(int line_idx, int operation, const char *str, char* commit_message) {
	COMMIT *nc = commitalloc();
	if (line_idx >= now->llen) {
		for (int i = now->llen; i <= line_idx; ++i)
			now->lines[i] = 0;
		now->llen = line_idx+1;
	}
	nc->p = cnow;
	cnow = clen-1;
	nc->idx = line_idx;
	nc->line = now->lines[line_idx];
	nc->isdelete = false;

	now->cid = clen-1;

	mystrcpy(commit_message, nc->str);

	LINE *line = linealloc();
	int lid = llen - 1;

	switch (operation) {
	case 1:
		lines[lid].len = mystrcpy(str, lines[lid].str);
		now->lines[line_idx] = lid;
		break;
	case 0:
		lines[lid].len = mystrcpy(lines[nc->line].str, lines[lid].str);
		lines[lid].len += mystrcpy(str, lines[lid].str + lines[lid].len);
		now->lines[line_idx] = lid;
		break;
	case 2:
		del(now->lines, line_idx, --now->llen);
		nc->isdelete = true;
		break;
	}
}

void Checkout(const char *str, int commit_idx, char *msg) {
	unsigned int h = gethash(str);
	while (mystrcmp(str, branches[myhash[h]].str)) h = ++h%HSIZE;
	now = branches + myhash[h];
	cnow = now->cid;

	while (commit_idx--) cnow = commits[cnow].p;

	mystrcpy(commits[cnow].str, msg);
}

int GetDocument(char str[][15]) {
	int document[1025];
	int len = getDocument(cnow, document);

	for (int i = 0; i < len; ++i) {
		mystrcpy(lines[document[i]].str, str[i]);
	}

	return len;
}