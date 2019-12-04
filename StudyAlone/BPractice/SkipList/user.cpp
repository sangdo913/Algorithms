#define RANGELIST

#if defined(RANGELIST)
#define MAXSIZE 200000
#define RANGE 100
#define rint register int
struct NODE{
    int val;
    NODE *n, *p;
}nodes[MAXSIZE];
int nid;

NODE rangelist[MAXSIZE/RANGE+1];
int cnt[MAXSIZE/RANGE+1];

void init(){
    for(rint i = 0; i < nid;++i){
        nodes[i].p = nodes[i].n = &nodes[i];
    }
    for(rint i = 0; i < MAXSIZE/RANGE+1; ++i){
        cnt[i] = 0;
        rangelist[i].p = rangelist[i].n = rangelist + i;
    }
    nid = 0;
}

void insert(int idx, int value){
   register NODE& nn = nodes[nid++];
   rint row = 0;
   rint myidx =0;
   while(cnt[row] + myidx < idx) myidx+=cnt[row++];
   rint mycnt = idx - myidx;
   register NODE* cursor = rangelist[row].n;
   while(mycnt--){
    cursor = cursor->n;
   }

   nn.val = value;
   nn.n = cursor;
   nn.p = cursor->p;
   cursor->p->n = &nn;
   cursor->p = &nn;

   cnt[row]++;
   while (cnt[row] > RANGE)
   {
       cnt[row]--;
       register NODE *cn = rangelist[row].p;
       cn->p->n = cn->n;
       cn->n->p = cn->p;
       row++;
       cnt[row]++;
       cn->n = rangelist[row].n;
       cn->p = &rangelist[row];
       rangelist[row].n->p = cn;
       rangelist[row].n = cn;
   }
}

void erase(int from, int to){
    int size = to-from+1;
    rint pos = 0;
    rint nowcnt = 0;
    while(nowcnt +cnt[pos] <= from) nowcnt += cnt[pos], ++pos;
    rint col = from - nowcnt;
    register NODE* cursor = rangelist[pos].n;
    while(col--) cursor = cursor->n;
    register NODE* end = &rangelist[pos];
    rint delnum = 0;
    while(size != delnum){
        if(cursor == end){
            ++pos;
            end = &rangelist[pos];
            cursor = end->n;
        }
        delnum++;
        cursor->n->p = cursor->p;
        cursor->p->n = cursor->n;
        cursor = cursor->n;
        cnt[pos]--;
    }
}

int get(int idx){
    rint pos = 0;
    rint nowcnt = 0;
    while(nowcnt + cnt[pos] <= idx) nowcnt+= cnt[pos++];
    register NODE* cursor = rangelist[pos].n;
    rint col = idx - nowcnt;
    while(col--) cursor = cursor->n;
    return cursor->val;
}

#else
#define MAXSIZE 100000
struct NODE{
    int v;
    NODE *p, *n;
} nodes[MAXSIZE];

NODE mylist;
int nid;

void insert(int idx, int value){
    int cnt = idx;
    NODE* cursor = mylist.n;    
    while(idx--){
        cursor = cursor->n;
    }

    NODE& nn = nodes[nid++];
    nn.v = value;

    nn.n = cursor;
    nn.p = cursor->p;
    cursor->p->n = &nn;
    cursor->p = &nn;
}

void init(){
  mylist.p = mylist.n = &mylist;
  nid = 0;
}

void erase(int from, int to){
    NODE* f = mylist.n;
    NODE* t = mylist.n;
    while(from--) f = f->n;
    while(to--) t = t->n;

    f->p->n = t->n;
    t->n->p = f->p;
}

int get(int idx){
    NODE* cursor = mylist.n;
    while(idx--) cursor = cursor->n;
    return cursor->v;
}

void allprint(){

}

#endif

//makecode
/*
#include<cstdio>
#include<iostream>
#include<fstream>

using namespace std;

enum COMM { ADD, DELETE, GET };

extern void insert(int, int);
extern void init();
extern void erase(int from, int to);
extern int get(int idx);
extern void allprint();

unsigned long long seed;
unsigned long long myrand() {
	return (seed = (214013LL * seed + 2531011LL));
}

int main()
{
	ofstream my("Text.txt");
	seed = myrand();
	int T = 20, score;
	my << T << endl;
	for (int tc = 1; tc <= T; ++tc) {
		int size = 0;
		score = 100;
		init();
		int cnt = 100000;
		int score = 100;
		 my << cnt << endl;
		for (int i = 0; i < cnt; ++i) {
			int comm, idx, val;
			int from, to;
			int res;
			comm = myrand() % 100;
			if (comm < 2)
				comm = DELETE;
			else if (comm < 8)
				comm = GET;
			else
				comm = ADD;
			if (size < 10000)
				comm = ADD;
			
			my << comm << ' ';

			switch (comm) {
			case ADD:
				if (size)
					idx = myrand() % size;
				else
					idx = 0;
				val = myrand() % 2000000000;
				insert(idx, val);
				my << idx << ' ' << val << endl;
				size++;
				break;

			case DELETE:
				from = myrand() % size;
				to = 0;
				if (size / 100)
					to = myrand() % (size / 100);
				if (from + to >= size)
					to = size - 1;
				else
					to = from + to;

				erase(from, to);
				my << from << ' ' << to << endl;
				size -= to - from + 1;
				break;
			case GET:
				idx = myrand() % size;
				res = get(idx);
				 my << idx << ' ' << res << endl;
				break;
			}
		}
	}
	 printf("total score : %d\n", score);
	return 0;
}
*/