#define R register
#define MAX(x,y) ((x) > (y) ? (x) : (y))
#define MIN(x,y) ((x) > (y) ? (y) : (x))

int tc;
int chk[1001][1001];
int cellChk[10000];
int undoType;
typedef enum CMD{NONE, MERGE, SPLIT, UNDO};
struct CELL{
    int sr,sc,er,ec;
    int cid;
    CELL *p, *n;
}cells[10000];
CELL h;
int ncell;

void init(int r, int c)
{
    h.p = h.n = &h;
    ncell = 0;
    tc+=10000;
    undoType = NONE;
}

void getRect(int r, int c, int rect[])
{
    for(R CELL* cc = h.n;cc != &h ; cc = cc->n) {
        if(cc->sr <= r && r <= cc->er && cc->sc <= c && c <= cc->ec) {
            rect[0] = cc->sr;
            rect[1] = cc->sc;
            rect[2] = cc->er;
            rect[3] = cc->ec;
            return;
        } 
    }
    rect[0] = r;
    rect[1] = c;
    rect[2] = r;
    rect[3] = c;
}

int newInfo[10000];
int infolen;
int stored;
int mergeCells(int cnt, int rs[], int cs[], int rect[])
{
    tc++;
    R int msr = 0x3f3f3f3f;
    R int mer = -1;
    R int msc = 0x3f3f3f3f;
    R int mec = -1;
    R int mergeCnt = 0;
    int r,c;
    int id[15];
    int ilen = 0;
    for(R int k = 0; k < cnt; ++k){
        int sr,sc,er,ec;
        r = rs[k], c= cs[k];
        R CELL* cc;
        for(cc = h.n; cc != &h; cc = cc->n) {
            if(cc->sr <= r && r <= cc->er && cc->sc <= c && c <= cc->ec) {
                if(cellChk[cc->cid] == tc) return 0;
                cellChk[cc->cid] = tc;
                mergeCnt += (cc->er+1-cc->sr)*(cc->ec+1-cc->sc);
                er = cc->er;
                sr = cc->sr;
                sc = cc->sc;
                ec = cc->ec;
                id[ilen++] = cc->cid;
                break;
            }
        }
        if(cc == &h) {
            if(chk[r][c] == tc) return 0;
            sr = er = r;
            sc = ec = c;
            chk[r][c] = tc;
            mergeCnt++;
        }
        msr = MIN(sr, msr);
        mer = MAX(mer, er);
        msc = MIN(sc, msc);
        mec = MAX(ec, mec);
    }
    if(mergeCnt != (mer+1-msr)*(mec+1-msc)) return 0;
    CELL& cell = cells[ncell];
    stored = ncell;
    cell.cid = ncell++;
    cell.n = &h;
    cell.p = h.p;
    h.p->n = &cell;
    h.p = &cell;
    undoType = MERGE;

    for(R int i = 0; i < ilen; ++i){
        newInfo[i] = id[i];
        CELL &c = cells[id[i]];
        c.n->p = c.p;
        c.p->n = c.n;
    }
    infolen = ilen;
    cell.sr = rect[0] = msr;
    cell.sc= rect[1] = msc;
    cell.er = rect[2] = mer;
    cell.ec = rect[3] = mec;
	return 1;
}

int splitCell(int r, int c, int rect[])
{
    R CELL* i= 0;
    for(i = h.n; i != &h; i = i->n){
        if(i->sr <= r && r <= i->er && i->sc <= c && c <= i->ec) break;
    }
    if(i == &h) return 0;
    infolen = 0;
    stored = i->cid;
    i->p->n = i->n;
    i->n->p = i->p;

    rect[0] = i->sr;
    rect[1] = i->sc;
    rect[2] = i->er;
    rect[3] = i->ec;
    undoType = SPLIT;
	return 1;
}

void undo()
{
    if(undoType == NONE) return;
    if(undoType == MERGE){
        CELL& c = cells[stored];
        c.p->n = c.n;
        c.n->p = c.p;
        for(R int i = 0; i < infolen; ++i) {
            CELL& nc = cells[newInfo[i]];
            nc.n = &h;
            nc.p = h.p;
            h.p->n = &nc;
            h.p = &nc;
        }
        undoType = SPLIT;
    }
    else{
        CELL& c = cells[stored];
        c.n = &h;
        c.p = h.p;
        h.p->n = &c;
        h.p = &c;
        for(R int i = 0; i < infolen; ++i){
            CELL&dc = cells[newInfo[i]];
            dc.n->p = dc.p;
            dc.p->n = dc.n;
        }
        undoType = MERGE;
    }
}

int checkRectangle(int r1, int c1, int r2, int c2)
{
    for(R CELL* cur = h.n; cur != &h; cur = cur->n){
        int sr = MAX(cur->sr, r1);
        int er = MIN(cur->er, r2);
        int sc = MAX(cur->sc, c1);
        int ec = MIN(cur->ec, c2);
        if(er < sr || ec < sc) continue;
        int s1 = (er+1-sr)*(ec+1-sc);
        if(s1 && s1 !=(cur->er+1-cur->sr) *(cur->ec+1-cur->sc)) return 1;
    }
	return 0;
}
