#include<cstdio>
#define LEN_NUMBER 128
#define LEN_OPERANDS 128
#define LEN_RESULT 260

/*
36 진수 곱셈
숫자는 '0', '1', ... '9', 'A', ..., 'Z' 로 36 진수로 이루어진다.
인덱스 0 에는 일의 자리, 1에는 십의 자리의 순으로 인덱스 127에는 128번째 자리가 저장돼 있다.
res 에 op1 과 op2 의 곱셈의 결과를 저장해라
*/

long long muls0[64];
long long muls1[64];

int conv[128];
bool ismade;
long long llres[64];
char myitoa[36];

int ires[LEN_RESULT + 1];
long long table[128][128][128];

void multiply(char res[LEN_RESULT], char op1[LEN_OPERANDS], char op2[LEN_OPERANDS]) {
	if (!ismade) {
		int cnt = 0;
		for (register int i = '0'; i <= '9'; ++i) {
			conv[i] = cnt++;
		}
		for (register int i = 'A'; i <= 'Z'; ++i) conv[i] = cnt++;
		ismade = true;

		for (register int i = 0; i < 10; ++i) myitoa[i] = '0' + i;
		for (register int i = 10; i < 36; ++i) myitoa[i] = 'A' + i-10;

		for (register int i = 0; i < 36; ++i) {
			for (register int j = 0; j < 36; ++j) {
				for (register int k = 0; k < 36; ++k) {
					register int a = i < 10 ? i + '0' : i + 'A' - 10;
					register int b = j < 10 ? j + '0' : j + 'A' - 10;
					register int c = k < 10 ? k + '0' : k + 'A' - 10;

					table[a][b][c] = 36LL*36*k + 36L*j + i;
					table[a][b][0] = 36LL*36*36*36*j + 36LL*36*36*i;
				}
			}
		}
	}

	for (register int i = 0; i < 125; i += 5) {
		muls0[i / 5] = table[op1[i]][op1[i + 1]][op1[i + 2]] + table[op1[i + 3]][op1[i + 4]][0];
	}
	muls0[25] = table[op1[125]][op1[126]][op1[127]];

	for (register int i = 0; i < 125; i += 5) {
		muls1[i / 5] = table[op2[i]][op2[i + 1]][op2[i + 2]] + table[op2[i + 3]][op2[i + 4]][0];
	}
	muls1[25] = table[op2[125]][op2[126]][op2[127]];
 
	for (register int i = 0; i < 26; ++i) {
		for (register int j = 0; j < 26; ++j) {
			llres[i + j] += muls0[i] * muls1[j];
		}
	}
	for (register int i = 0; i < 52; ++i) {
		register int si = i * 5;
		res[si] = myitoa[llres[i] %  36];
		llres[i] /= 36;
		res[si+1] = myitoa[llres[i] %  36];
		llres[i] /= 36;
		res[si+2] = myitoa[llres[i] %  36];
		llres[i] /= 36;
		res[si+3] = myitoa[llres[i] %  36];
		llres[i] /= 36;
		res[si+4] = myitoa[llres[i] %  36];
		llres[i] /= 36;
		llres[i + 1] += llres[i];
		llres[i] = 0;
	}

///////////////
	char res2[LEN_RESULT+1];
	register int carry = 0;
	for (register int i = 0; i < LEN_RESULT; ++i) res2[i] = '0', ires[i] = 0;
	for (register int i = 0; i < LEN_OPERANDS; ++i) { for (register int j = 0; j < LEN_OPERANDS; ++j) ires[i + j] += conv[op1[i]] * conv[op2[j]]; }

	for (register int i = 0; i < LEN_RESULT; ++i) {
		res2[i] = myitoa[(carry + ires[i]) % 36];
		carry = (carry + ires[i]) / 36;
	}
	//////////////
	res2[LEN_RESULT] = 0; 
//	printf("%s\n%s\n\n", res, res2);
	for(register int i = 0; i < LEN_NUMBER; ++i) if(res[i] != res2[i])
	int debug = 1;
}
