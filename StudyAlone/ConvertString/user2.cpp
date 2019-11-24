#define MAX_WORD_LIST 50000
#define DIV 3500

char *str;
int nn;

struct NODE {
	int i;
	NODE *prev, *next;
}nodes[MAX_WORD_LIST];

NODE myhash[27][27][27][MAX_WORD_LIST/DIV+1];
int conv[256];

#define C(x) (conv[x])

void init(int n, char Word[])
{
	nn = n;
	str = Word;

	int cnt = 0;
	for (register int i = 'a'; i <= 'z'; ++i) conv[i] = cnt++;
	int len = n/ DIV;

	for (register int i = 0; i < cnt; ++i) {
		for (register int j = 0; j < cnt; ++j) {
			for (register int k = 0; k < cnt;++k ) {
				for (register int l = 0; l <= len; ++l) myhash[i][j][k][l].i = l, myhash[i][j][k][l].prev = myhash[i][j][k][l].next = myhash[i][j][k] + l;
			}
		}
	}
	for (register int i = 0; i <= n - 3; ++i) {
		NODE &h = myhash[C(Word[i])][C(Word[i + 1])][C(Word[i + 2])][i/DIV];
		nodes[i].i = i;
		nodes[i].prev = h.prev;
		nodes[i].next = &h;

		h.prev->next = nodes + i;
		h.prev = nodes + i;
	}
}

void insert(NODE* a, NODE* b) {
	NODE* ed = a;
	a = a->next;

	while (a != ed && a->i < b->i) {
		a = a->next;
	}

	b->next = a;
	b->prev = a->prev;

	a->prev = a->prev->next = b;
}

void del(NODE* a) {
	a->next->prev = a->prev;
	a->prev->next = a->next;
}

int Replace(char str1[], char str2[])
{
	NODE *cursor ,*ed, *dn;
	int ret = 0;
	int len = nn / DIV;
	int mini = -1;

	for (register int id = 0; id <= len; ++id) {
		ed = &myhash[C(str1[0])][C(str1[1])][C(str1[2])][id];
		cursor = ed->next;

		while (cursor!=ed) {
			int i = cursor->i;

			if (i < mini) {
				cursor = cursor->next;
				continue;
			}
			mini = i+3;

			while(cursor != ed && cursor->i < mini) cursor = cursor->next;

			ret++;

			str[i] = str2[0], str[i + 1] = str2[1], str[i + 2] = str2[2];
			
			for (register int ii = i - 2 < 0 ? 0 : i - 2; ii + 2 < nn && ii <= i + 2; ++ii) {
				dn = nodes + ii;
				del(dn);
				insert(&myhash[C(str[ii])][C(str[ii+1])][C(str[ii+2])][ii / DIV], dn);
			}
		}
	}

	return ret;
}

void GetStr(char Result[])
{
	for (register int i = 0; i < nn; ++i) Result[i] = str[i];
}
