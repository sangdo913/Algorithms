#define DIVP 10000
#define DIVS 500
struct ITEM
{
	int version;	// 1 ~ 10
	int price;	// 100000 ~ 1999999
	int cores;	// 1 ~ 8
	double size; // 1.0 ~ 5.0
};

struct RANGE_INT
{
	int from;
	int to;
};

struct RANGE_DBL {
	double from;
	double to;
};

static const int MAX_ITEM = 1000000;


struct NODE {
	int version;
	int price;
	int cores;
	double size;

	NODE* next, *prev;
}nodes[MAX_ITEM];
NODE head[11][200][9][101];

int inum;

void init() {
	// 초기화 함수
	inum = 0;
	for (register int i = 1; i <= 10; ++i)
		for (register int j = 10; j < 200; ++j) {
			for (register int k = 1; k <= 8; ++k) {
				for (register int l = 20; l <= 100; ++l) {
					head[i][j][k][l].prev = head[i][j][k][l].next = head[i][j][k] + l;
				}
			}
		}

	int dib = 1;
}

void produce(const ITEM& item) {
	// 재고에 item 을 저장한다.
	NODE &nn = nodes[inum++];
	nn.version = item.version;
	nn.price = item.price;
	nn.cores = item.cores;
	nn.size = item.size;

	NODE& h = head[nn.version][nn.price / DIVP][nn.cores][(int)(nn.size*10000) / DIVS];
	nn.prev = h.prev;
	nn.next = &h;
	
	h.prev->next = &nn;
	h.prev = &nn;
}

#define isin(a,b,c) (((a)<=(b)) &&((b)<=(c)))

int search(RANGE_INT version, RANGE_INT price, RANGE_INT cores, RANGE_DBL size) {
	// 재고에서 범위에 해당하는 아이템의 수를 반환한다.

	NODE * ed;
	NODE* cursor;

	register int from[4] = { version.from, price.from / DIVP, cores.from, (int)(size.from * 10000) / DIVS }, to[4] = { version.to, price.to / DIVP, cores.to, (int)(size.to * 10000) / DIVS };

	int ret = 0;

	for (register int i = from[0]; i <= to[0]; ++i) {
		for (register int j = from[1]; j <= to [1]; ++j) {
			for (register int k = from[2]; k <= to[2]; ++k) {
				for (register int l = from[3]; l <= to[3]; ++l) {
					cursor = head[i][j][k][l].next;
					ed = cursor->prev;
					while (cursor != ed) {
						ret += isin(version.from, cursor->version, version.to) && 
							isin(price.from, cursor->price, price.to) && 
							(isin(cores.from, cursor->cores, cores.to)) && 
							(isin(size.from, cursor->size, size.to));
						
						cursor = cursor->next;
					}
				}
			}
		}
	}

	return ret;
}
