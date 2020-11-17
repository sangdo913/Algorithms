#include<cstdio>

#define WAY1 0
#define WAY2 1

int my[201];
int *res;
extern int check(int in[200]);

#if WAY1
int fenwix[201];

void update(int i) {
	while (i <= 200) {
		fenwix[i]++;
		i += i & -i;
	}
}

int getsum(int i) {
	int ret = 0;
	while (i) {
		ret += fenwix[i];
		i -= i & -i;
	}
	return ret;
}

void mergeFind(int s, int e, int num ){
	if (s < e) {
		int m = (s + e) / 2;
		int l = getsum(m + 1) - getsum(s);
		int r = getsum(e+1)- getsum(m+1);
		
		if (l == m - s + 1) {
			mergeFind(m + 1, e, num);
			return;
		}

		else if (r == e - m) {
			mergeFind(s, m, num);
			return;
		}

		for (int i = s; i <= m; ++i) {
			my[i] = 0;
		}
		
		int res = check(my);
		if ((res>>8) == 1) {
			mergeFind(m + 1, e, num);
		}
		else {
			for (int i = s; i <= m; ++i) my[i] = num; 
			mergeFind(s, m, num);
		}
		
	}
	else if (s == e) {
		res[s] = num;
		update(s+1);
	}
}

int MODE = 2;
int stack[200];
int top;
void func(int in[200]) {
	res = in;
	top = 0;

	for (int i = 1; i <= 200; ++i) fenwix[i] = 0;

	switch (MODE) {
	case 1:
		for (int i = 1; i <= 256; ++i) {
			for (int j = 0; j < 200; ++j) my[j] = i;
			int r = check(my);
			if (r %256== 200) {
				mergeFind(0, 199, i);
			}
		}
		break;
	case 2:
		for (int i = 1; i <= 256; i += 7) {
			for (int i = 0; i < 200; ++i) my[i] = 0;
			int t = 1;
			int idx = 0;
			for (int a = 0; a < 7; ++a) {
				for (int id = 0; id < t; ++id) {
					my[idx++] = i+a;
				}
				t <<= 1;
			}
			int a = 0;
			int res = check(my) % 256;
			while (res) {
				if (res & 1) {
					stack[top++] = i + a;
				}
				a++; res >>= 1;
			}
		}

		for (int i = 0; i < 200; ++i) {
			for (int j = 0; j < 200; ++j) my[j] = stack[i];
			mergeFind(0, 199, stack[i]);
		}
		break;

	}
}

#else
int cnum;
int idxtree[201];
void update(int i) {
	while (i <= 200){
		idxtree[i] ++;
		i += i & -i;
	}
}

int getsum(int i) {
	int ret = 0;
	while (i) {
		ret += idxtree[i];
		i -= i & -i;
	}
	return ret;
}
int qq;
int end[200];
int fcnt[3];

void pbs(int n1, int n2, int s1, int e1, int s2, int e2) {
	if (s1 == e1) {
		res[s1] = n1;
		if (end[s1] != qq) {
			end[s1] = qq;
			update(s1 + 1);
		}
	}
	if (s2 == e2) {
		res[s2] = n2;
		if (end[s2] != qq) {
			end[s2] = qq;
			update(s2 + 1);
		}
	}

	if (s1 < e1 || s2 < e2) {
		int m1 = (s1 + e1) / 2;
		int m2 = (s2 + e2) / 2;

		int num1 = getsum(m1 + 1) - getsum(s1);
		int num2 = getsum(e1 + 1) - getsum(m1 + 1);
		int num3 = getsum(m2 + 1) - getsum(s2);
		int num4 = getsum(e2 + 1) - getsum(m2 + 1);

		if (s1 < e1 &&num1 == m1 - s1 + 1) {
			pbs(n1, n2, m1 + 1, e1, s2, e2);
			return;
		}
		else if (s1 <  e1 &&num2 == e1 - m1) {
			pbs(n1, n2, s1, m1, s2, e2);
			return;
		}

		else if (s2 <e2 &&num3 == m2 - s2 + 1) {
			pbs(n1, n2, s1, e1, m2 + 1, e2);
			return;
		}
		else if (s2 < e2 &&num4 == e2 - m2) {
			pbs(n1, n2, s1, e1, s2, m2);
			return;
		}

		if (s1 < e1) for (int i = s1; i <= m1; ++i)  my[i] = n1; 
		if (s2 < e2) for (int i = m2 + 1; i <= e2; ++i) my[i] = n2;
		
		int ret = check(my);
		ret >>= 8;
		if (ret == 1) {
			for (int i = s2; i <= e2; ++i) my[i] = 0;
			if(s1 < e1) for (int i = s1; i <= m1; ++i) my[i] = n1;
			ret = check(my)>>8;
			if (ret == 1) {
				for (int i = s1; i <= m1; ++i) my[i] = 0;
				pbs(n1, n2, s1, m1, s2, m2);
			}
			else {
				pbs(n1, n2, m1 + 1, e1, m2 + 1, e2);
			}
		}
		else if (!ret) {
			for (int i = m1 + 1; i <= e1; ++i) my[i] = 0;
			for (int i = s2; i <= m2; ++i) my[i] = 0;
			pbs(n1, n2, m1 + 1, e1, s2, m2);
		}
		else {
			for (int i = s1; i <= m1; ++i) my[i] = 0;
			for (int i = m2 + 1; i <= e2; ++i) my[i] = 0;
			pbs(n1, n2, s1, m1, m2 + 1, e2);
		}

	}
}

int sta[200];
int top;
int MODE = 1;

void func(int in[200]) {
	top = 0;
	res = in;
	qq++;
	cnum = 0;
	for (int i = 0; i < 200; ++i) my[i] = 0, idxtree[i] = 0;
	idxtree[200] = 0;

	switch (MODE) {
	case 1:
		for (int st = 1; st <= 255; st += 7) {
			int n = 1;
			int idx = 0;
			for (int i = 0; i < 7; ++i) {
				for (int j = 0; j < n; ++j) {
					my[idx++] = st + i;
				}
				n <<= 1;
			}
			int res = check(my);
			res %= 256;
			idx = 0;
			while (res) {
				if (res & 1) {
					sta[top++] = st + idx;
				}
				idx++, res >>= 1;
			}
		}
		break;
	case 2: 
		for (int n = 1; n <= 256; ++n) {
			for (int i = 0; i < 200; ++i)my[i] = n;
			int ret = check(my) % 256;
			if (ret == 200) sta[top++] = n;
		}
		break;
	}

	for (int i = 0; i < 100; ++i) {
		for (int i = 0; i < 200; ++i) my[i] = 0;
		int a = sta[--top];
		int b = sta[--top];
		pbs(a, b, 0, 199, 0, 199);
	}
}

#endif