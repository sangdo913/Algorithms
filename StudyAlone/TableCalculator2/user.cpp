#define MAXR		99
#define MAXC		26
#define rint register int
#define NONE 0x3f3f3f3f
enum CALC {ADD, SUB, MUL, DIV, MAX, MIN, SUM, CONST};

int p[MAXR][MAXC];
int fr[MAXR][MAXC];
int to[MAXR][MAXC];
int type[MAXR][MAXC];
int myvalue[MAXR][MAXC];
int changed[MAXR][MAXC];
bool first;
int ncol, nrow;

int st[3000];
int stsize;

void init(int C, int R) {
	ncol = C; 
	nrow = R;
	first = true;
	stsize = 0;

	for (rint i = 0; i < nrow; ++i) {
		for (rint j = 0; j < ncol; ++j) {
			myvalue[i][j] = 0;
			p[i][j] = -1;
			type[i][j] = CONST;
		}
	}
}

void set(int col, int row, char input[]) {
	int cid = ((--row ) << 5) + --col;

	rint np = cid;
	rint rr = row;
	rint cc = col;

	if (type[row][col] != CONST) {
		rint cr1 = fr[row][col] >> 5, cr2 = to[row][col] >>5;
		rint cc1 = fr[row][col] & 0b11111, cc2 = to[row][col] & 0b11111;
		rint dr = cr2 - cr1>0;
		rint dc = cc2 - cc1>0;

		if (type[row][col] < MAX) {
			p[cr1][cc1] = p[cr2][cc2] = -1;
		}
		else {
			while (cc1 != cc2 || cr1 != cr2) {
				p[cr1][cc1] = cid;
				cc1 += dc;
				cr1 += dr;
			}
			p[cr1][cc1] = cid;
		}
	}

	while (np != -1 && !changed[rr][cc]) {
		changed[rr][cc] = 1;
		st[stsize++] = np;
		np = p[rr][cc];
		rr = np >> 5;
		cc = np & 0b11111;
	}

	if ((input[0] <= '9' && input[0] >= '1') || input[0] == '-') {
		type[row][col] = CONST;
		rint rr = cid >> 5;
		rint cc = cid & 0b11111;
		bool isminus = false;
		if (input[0] == '-') {
			isminus = (input++)[0];
		}
		rint num = 0;
		while (*input) num *= 10, num += *input - '0', input++;
		
		myvalue[rr][cc] = num * (1 - 2 * isminus);
	}
	else {
		switch (input[2]) {
		case 'D': type[row][col] = ADD; break;
		case 'B': type[row][col] = SUB; break;
		case 'L': type[row][col] = MUL; break;
		case 'V': type[row][col] = DIV; break;
		case 'X': type[row][col] = MAX; break;
		case 'N': type[row][col] = MIN; break;
		case 'M': type[row][col] = SUM; break;
		}
		rint cr1, cc1, cr2, cc2;
		input += 4;

		cc1 = *(input++) - 'A';
		cr1 = 0;
		while (*input != ',') {
			cr1 *= 10, cr1 += *input - '0';
			input++;
		}

		cc2 = *(++input)++ - 'A';
		cr2 = 0;
		while (*input != ')') {
			cr2 *= 10, cr2 += *input - '0';
			input++;
		}
		--cr2;
		--cr1;
		rint cf = (cr1 << 5) + cc1;
		rint ct = (cr2 << 5) + cc2;
		fr[row][col] = cf;
		to[row][col] = ct;

		if (type[row][col] < MAX) {
			p[cr2][cc2] = p[cr1][cc1] = cid;
		}
		else {
			rint dr =(bool)(cr2 - cr1);
			rint dc = (bool)(cc2 - cc1);

			while (cc1 != cc2 || cr1 != cr2) {
				p[cr1][cc1] = cid;
				cc1 += dc;
				cr1 += dr;
			}
			p[cr1][cc1] = cid;
		}
	}
}

int calc(int r, int c) {
	if (!changed[r][c]) return myvalue[r][c];
	changed[r][c] = 0;
	if (type[r][c] == CONST) return myvalue[r][c];

	rint cr1, cr2, cc1, cc2, dr, dc, res;
	rint cnt;

	cr1 = fr[r][c] >> 5;
	cc1 = fr[r][c] & 0b11111;
	cr2 = to[r][c] >> 5;
	cc2 = to[r][c] & 0b11111;

	dr = cr2 - cr1 > 0;
	dc = cc2 - cc1 > 0;
	switch (type[r][c]) {
	case ADD: return myvalue[r][c] = calc(cr1, cc1) + calc(cr2, cc2);
	case SUB: return myvalue[r][c] = calc(cr1, cc1) - calc(cr2, cc2);
	case MUL: return myvalue[r][c] = calc(cr1, cc1) * calc(cr2, cc2);
	case DIV: return myvalue[r][c] = calc(cr1, cc1) / calc(cr2, cc2);
	case MAX:
		myvalue[r][c] = -0x3f3f3f3f;
		cnt = cr1 == cr2 ? cc2 - cc1 : cr2 - cr1;
		for (rint i = 0; i <= cnt; ++i) {
			res = calc(cr1, cc1);
			myvalue[r][c] = myvalue[r][c] > res ? myvalue[r][c] : res;
			cr1 += dr, cc1 += dc;
		}
		return myvalue[r][c];
	case MIN:
		myvalue[r][c] = 0x3f3f3f3f;
		cnt = cr1 == cr2 ? cc2 - cc1 : cr2 - cr1;
		for (rint i = 0; i <= cnt; ++i) {
			res = calc(cr1, cc1);
			myvalue[r][c] = myvalue[r][c] < res ? myvalue[r][c] : res;
			cr1 += dr, cc1 += dc;
		}
		return myvalue[r][c];
	case SUM:
		myvalue[r][c] = 0;
		cnt = cr1 == cr2 ? cc2 - cc1 : cr2 - cr1;
		for (rint i = 0; i <= cnt; ++i) {
			myvalue[r][c] += calc(cr1, cc1);
			cr1 += dr, cc1 += dc;
		}
		return myvalue[r][c];
	}
}

void update(int value[MAXR][MAXC]) {
	if (first) {
		for (rint i = 0; i < nrow; ++i) {
			for (rint j = 0; j < ncol; ++j) {
				value[i][j] = 0;
			}
		}
		first = false;
	}

	while (stsize) {
		--stsize;
		rint r = st[stsize] >> 5;
		rint c = st[stsize] & 0b11111;
		value[r][c] = calc(r, c);
	}
	stsize = 0;
}