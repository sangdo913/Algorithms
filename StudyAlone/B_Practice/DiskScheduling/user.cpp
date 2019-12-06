const int MAX = 100000;
#define RANGE 100
#define MAXLEVEL 10
#define rint register int

struct NODE{
    int track;
	int level;
	int isdel;
    NODE *p[MAXLEVEL], *n[MAXLEVEL];
}nodes[MAX];

unsigned long long myseed;
unsigned long long myrand(){
	return myseed = (((214013LL *myseed + 2531011)>>16) & 0x7fffffffffffL);
}

char blocks[10][100001];
NODE level;
int query;
int nid;
int tc;
int delid;
int headcur;
int dir;
int cnt[10];
void init(int track_size, int head){
	for(int i = 0; i < 10; ++i) cnt[i] =0;
	for(rint i = 0; i < MAXLEVEL; ++i) level.n[i] = level.p[i] = &level;
	level.track = -1;
	nid = 0;
	++tc;
	delid = 0;
	headcur= head;
	dir = 0;
	for(rint i = 0; i < 10; ++i) for(rint j = 0; j < 10000; ++j) blocks[i][j] = '-';

}

void request(int track){
	query++;
	NODE* cursor[MAXLEVEL];
	rint maxlevel = 0;
	cursor[MAXLEVEL-1] = &level;
	NODE& nn = nodes[nid++];
	nn.track = track;
	nn.level = 0;
	while(nn.level < MAXLEVEL && !(myrand()%4)) nn.level++;
	cnt[nn.level]++;
	for(rint i = 0; i <= nn.level; ++i){
		blocks[9-i][nid-1] = '@';
	}
	cursor[0] = &level;

	for(rint i = MAXLEVEL-1; i >= 0; --i){
		while(cursor[i]->n[i] != &level && cursor[i]->n[i]->track < track){
			cursor[i] = cursor[i]->n[i];
		}
		if(i) cursor[i-1] = cursor[i];
	}
	for(rint i = 0; i <= nn.level; ++i){
		nn.n[i] = cursor[i]->n[i];
		nn.p[i] = cursor[i];
		cursor[i]->n[i]->p[i] = &nn;
		cursor[i]->n[i] = &nn;
	}
}

int fcfs(){
	while(nodes[delid].isdel == tc) delid++;
	nodes[delid].isdel = tc;
	for(rint i = 0; i <= nodes[delid].level; ++i) nodes[delid].p[i]->n[i] = nodes[delid].n[i], nodes[delid].n[i]->p[i] = nodes[delid].p[i];
	headcur = nodes[delid].track;
	return nodes[delid++].track;
}

int sstf(){
	NODE *cursor = &level;
	rint nowlevel = MAXLEVEL-1;
	for(rint nowlevel = MAXLEVEL-1; nowlevel>=0; --nowlevel){
		while(cursor->n[nowlevel]!= &level&& cursor->n[nowlevel]->track < headcur) cursor= cursor->n[nowlevel];
		if(cursor->track == headcur) break;
	}

	NODE* r = cursor->n[0];
	rint ll, rr;
	ll = cursor == &level ? 0x3f3f3f3f : headcur-cursor->track;
	rr = r == &level ? 0x3f3f3f3f : r->track - headcur;
	cursor = ll > rr ? r : cursor;
	cursor->isdel = tc;

	for(rint i = 0; i <= cursor->level; ++i)
		cursor->n[i]->p[i] = cursor->p[i],
		cursor->p[i]->n[i] = cursor->n[i],
		cursor->isdel = tc;

	return headcur = cursor->track;
}

int look(){
	register NODE* cursor = &level;
	for(rint i = MAXLEVEL-1; i >= 0; --i){
		while(cursor->n[i] != &level && cursor->n[i]->track < headcur) cursor= cursor->n[i];
		if(cursor->track == headcur) break;
	}

	if(dir == 0){
		if(cursor == &level) cursor = cursor->n[0], dir = 1;
	}
	else{
		cursor = cursor->n[0];
		if(cursor == &level) cursor = cursor->p[0], dir = 0;
	}
	cursor->isdel = tc;
	for(rint i = 0; i <= cursor->level; ++i) cursor->n[i]->p[i] = cursor->p[i], cursor->p[i]->n[i] = cursor->n[i];

	return headcur = cursor->track;
}

int clook(){
	register NODE* cursor = &level;
	for(rint i = MAXLEVEL-1; i >= 0; --i){
		while(cursor->n[i] != &level && cursor->n[i]->track < headcur) cursor = cursor->n[i];
		if(cursor->track == headcur) break;
	}

	if(cursor == &level) cursor = cursor->p[0];
	cursor->isdel = tc;
	for(rint i = 0; i <= cursor->level; ++i) cursor->n[i]->p[i] = cursor->p[i], cursor->p[i]->n[i] = cursor->n[i];

	return headcur = cursor->track;
}