//#define N 4
//
//typedef struct {
//	int strike;
//	int ball;
//} Result;
//
//bool num[11], cc[5];
//bool flag;
//int ret[5], tmp[5], ans[5];
//
//extern Result query(int guess[]);
//
//void go(int pos, int index) {
//	if (flag) return;
//	if (index == 4) {
//		int k = 0;
//		for (int i = 0; i < 10; i++) {
//			if (num[i]) {
//				ret[k++] = i;
//			}
//		}
//		Result res = query(ret);
//		if (res.ball + res.strike == 4) {
//			flag = 1;
//		}
//		return;
//	}
//	if (flag || pos > 9) return;
//
//	num[pos] = 1;
//	go(pos + 1, index + 1);
//	num[pos] = 0;
//	go(pos + 1, index);
//}
//
//void permut(int index) {
//	if (flag) return;
//	if (index == 4) {
//		Result res = query(tmp);
//		if (res.strike == 4) {
//			for (int i = 0; i < 4; i++) {
//				ans[i] = tmp[i];
//			}
//			flag = 1;
//		}
//		return;
//	}
//	for (int i = 0; i < 4; i++) {
//		if (!cc[i]) {
//			cc[i] = 1;
//			tmp[index] = ret[i];
//			permut(index + 1);
//			cc[i] = 0;
//			tmp[index] = 0;
//		}
//	}
//}
//
//void init() {
//	for (int i = 0; i < 4; i++) {
//		ret[i] = 0;
//		tmp[i] = 0;
//		cc[i] = 0;
//		ans[i] = 0;
//	}
//	for (int i = 0; i < 11; i++)
//		num[i] = 0;
//}
//
//void doUserImplementation(int guess[]) {
//	init();
//	flag = 0;
//	go(0, 0);
//	flag = 0;
//	permut(0);
//
//	for (int i = 0; i < 4; i++)
//		guess[i] = ans[i];
//}
