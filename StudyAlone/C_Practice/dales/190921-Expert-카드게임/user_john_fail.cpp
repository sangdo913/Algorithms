#define CHAR_TO_INT(x) x =='1'?1 : x == '2'?2 :x == '3'? 3:x == '4'?4:5

inline int get_prior(int ret, int current_prior) {
	if (ret >= 5) {
		return 6;
	}
	if (ret == 4) {
		return 1; // 1순위
	}
	if (ret == 3) {
		return 2; // 2순위
	}
	if (ret == 2) {
		if (current_prior == 2)
			return 2;
		if (current_prior == 4)
			return 3; // 3순위
		return 4; // 4순위
	}
	return 0; // 아직모름
}

int test(char* A[1000000][5], char* B[1000000][5])
{
	register int i, j, k;
	int count = 0;
	int ret, gp;

	int count_1 = 0, count_2 = 0, count_3 = 0, count_5 = 0;
	int a_10, b_10, a_1, b_1;
	int prior_a_10;
	int prior_b_10;
	int prior_a_1;
	int prior_b_1;

	for (i = 0; i < 1000000; i++)
	{

		int heap_a_10[6] = { 0 };
		int heap_b_10[6] = { 0 };
		int heap_a_1[6] = { 0 };
		int heap_b_1[6] = { 0 };

		prior_a_10 = 5;
		prior_b_10 = 5;
		prior_a_1 = 5;
		prior_b_1 = 5;

		for (j = 0; j < 5; j++)
		{
			// 10 push
			// A
			a_10 = CHAR_TO_INT(A[i][j][0]);
			ret = ++(heap_a_10[CHAR_TO_INT(A[i][j][0])]);

			gp = get_prior(ret, prior_a_10);
			if (gp != 0) prior_a_10 = gp; 

			// B
			b_10 = CHAR_TO_INT(B[i][j][0]);
			ret = ++(heap_b_10[b_10]);

			gp = get_prior(ret, prior_b_10);
			if (gp != 0) prior_b_10 = gp;


			// 1 push
			a_1 = CHAR_TO_INT(A[i][j][1]);
			ret = ++(heap_a_1[a_1]);
			gp = get_prior(ret, prior_a_1);
			if (gp != 0) prior_a_1 = gp;

			b_1 = CHAR_TO_INT(B[i][j][1]);
			ret = ++(heap_b_1[b_1]);
			gp = get_prior(ret, prior_b_1);
			if (gp != 0) prior_b_1 = gp;

			// 3장떄
			if (j == 2) {
				if ((prior_a_10 == 2 && (heap_b_10[a_10] > 0))
					|| (prior_b_10 == 2 && (heap_a_10[b_10] > 0))
					|| (prior_a_1 == 2 && (heap_b_1[a_1] > 0))
					|| (prior_b_1 == 2 && (heap_a_1[b_1] > 0))) {
					count++;
					break;
				}
			}

			// 4장때
			if (j == 3) {
				if ((prior_a_10 == 1 && (heap_b_10[a_10] > 0))
					|| (prior_b_10 == 1 && (heap_a_10[b_10] > 0))
					|| (prior_a_1 == 1 && (heap_b_1[a_1] > 0))
					|| (prior_b_1 == 1 && (heap_a_1[b_1] > 0))) {
					count++;
					break;
				}
				// 1순위 vs 3순위 이하
				if ((prior_a_10 == 1 && prior_b_10 > 2) || (prior_b_10 == 1 && prior_a_10 > 2)) {
					count++;
					break;
				}
				if ((prior_a_1 == 1 && prior_b_1 > 2) || (prior_b_1 == 1 && prior_a_1 > 2)) {
					count++;
					break;
				}

				// 2,3순위 vs 5순위 이하
				if ((prior_a_10 <= 3 && prior_b_10 > 4) || (prior_b_10 <= 3 && prior_a_10 > 4)) {
					count++;
					break;
				}
				if ((prior_a_1 <= 3 && prior_b_1 > 4) || (prior_b_1 <= 3 && prior_a_1 > 4)) {
					count++;
					break;
				}
			}

		}
		// 10 비교
		if (j < 5)
			continue;

		if (prior_a_10 != prior_b_10) {
			count++; 
			continue;
		}
		if (prior_a_1 != prior_b_1) {
			count++;
			continue;
		}

		// 1 vs 1
		if ((prior_a_10 == 1 && prior_b_10 == 1) || (prior_a_1 == 1 && prior_b_1 == 1)) {
			if (prior_a_10 == 1 && prior_b_10 == 1) {
				int a, b;
				for (j = 1; j < 6; j++)
				{
					if (heap_a_10[j] == 1) a = j;
					if (heap_b_10[j] == 1) b = j;
				}
				if (a != b) {
					count++;
					continue;
				}
			}
			if (prior_a_1 == 1 && prior_b_1 == 1) {
				int a, b;
				for (j = 1; j < 6; j++)
				{
					if (heap_a_1[j] == 1) a = j;
					if (heap_b_1[j] == 1) b = j;
				}
				if (a != b) {
					count++;
					continue;
				}
			}
		}
		else if ((prior_a_10 == 2 && prior_b_10 == 2) || (prior_a_1 == 2 && prior_b_1 == 2)) {
			if (prior_a_10 == 2 && prior_b_10 == 2) {
				int a1=0, a2=0, b1=0, b2=0;
				for (j = 1; j < 6; j++)
				{
					if (heap_a_10[j] == 1) a1==0?a1=j:a2=j;
					if (heap_b_10[j] == 1) b1==0?b1=j:b2=j;
				}
				if (a1*a2 != b1*b2) {
					count++;
					continue;
				}
			}
			if (prior_a_1 == 2 && prior_b_1 == 2) {
				int a1 = 0, a2 = 0, b1 = 0, b2 = 0;
				for (j = 1; j < 6; j++)
				{
					if (heap_a_1[j] == 1) a1 == 0 ? a1 = j : a2 = j;
					if (heap_b_1[j] == 1) b1 == 0 ? b1 = j : b2 = j;
				}
				if (a1*a2 != b1*b2) {
					count++;
					continue;
				}
			}
		}
			
		

		else if (((prior_a_10 == 3 && prior_b_10 == 3) || (prior_a_10 == 4 && prior_b_10 == 4)) || ((prior_a_1 == 3 && prior_b_1 == 3) || (prior_a_1 == 4 && prior_b_1 == 4))) {
			if ((prior_a_10 == 3 && prior_b_10 == 3) || (prior_a_10 == 4 && prior_b_10 == 4)) {
				for (j = 1; j < 6; j++)
				{
					if (heap_a_10[j] != heap_b_10[j]) {
						count++;
						break;
					}
				}
				if (j < 6) continue;
			}

			if ((prior_a_1 == 3 && prior_b_1 == 3) || (prior_a_1 == 4 && prior_b_1 == 4)) {
				for (j = 1; j < 6; j++)
				{
					if (heap_a_1[j] != heap_b_1[j]) {
						count++;
						break;
					}
				}
				if (j < 6) continue;
			}
		}

		else if ((prior_a_10 == 5 && prior_b_10 == 5) && (prior_a_1 == 5 && prior_b_1 == 5)) {
			for (j = 1; j < 6; j++) {
				for (k = j + 1; k < 6; k++) {
					int t, p;
					if (heap_a_10[j] < heap_a_10[k]) {
						t = heap_a_10[j];
						heap_a_10[j] = heap_a_10[k];
						heap_a_10[k] = t;

						t = heap_a_1[j];
						heap_a_1[j] = heap_a_1[k];
						heap_a_1[k] = t;
					}
					if (heap_b_10[j] < heap_b_10[k]) {
						t = heap_b_10[j];
						heap_b_10[j] = heap_b_10[k];
						heap_b_10[k] = t;

						t = heap_b_1[j];
						heap_b_1[j] = heap_b_1[k];
						heap_b_1[k] = t;
					}
				}
			}
			for (j = 1; j < 6; j++) {
				if (heap_b_1[j] != heap_a_1[j]) {
					count++;
					break;
				}
				if (j < 6) continue;
			}

		}

		// 1비교


	}

	return count;
}