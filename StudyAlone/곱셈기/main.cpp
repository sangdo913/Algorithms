#include <cstdio>

#define LEN_NUMBER 128
#define LEN_OPERANDS 128
#define LEN_RESULT 260

unsigned int seed = 18043000UL;
static int pseudo_rand(void)
{
	seed = seed * 214013 + 2531011;
	return (seed >> 16) & 0x7FFF;
}

static char operand1[LEN_OPERANDS];
static char operand2[LEN_OPERANDS];
static char result[LEN_RESULT];

extern void multiply(char res[LEN_RESULT], char op1[LEN_OPERANDS], char op2[LEN_OPERANDS]);

static int get_digit() {
	char c = pseudo_rand() % 36;
	c += (c < 10) ? 48 : 55;
	return c;
}
static void make_number(char* operand) {
	for (register int i = 0; i < LEN_NUMBER; i++)
		operand[i] = get_digit();
}

static void sum(char answer[LEN_RESULT], char operand[LEN_RESULT]) {
	char carry = 0;
	for (register int i = 0; i < LEN_RESULT; i++) {
		operand[i] -= (operand[i] < 65) ? 48 : 55;
		answer[i] -= (answer[i] < 65) ? 48 : 55;
		answer[i] += operand[i] + carry;
		carry = answer[i] / 36;
		answer[i] = answer[i] % 36;
		answer[i] += (answer[i] < 10) ? 48 : 55;
	}

}

char answer[LEN_RESULT + 1];

int main() {
	answer[LEN_RESULT] = '\0';
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		for (register int i = 0; i < LEN_RESULT; i++) answer[i] = '0';
		for (register int i = 0; i < 10000; i++) {
			make_number(operand1);
			make_number(operand2);
			multiply(result, operand1, operand2);
			sum(answer, result);
		}
		printf("#%d: %s\n", t, answer);
	}
	return 0;
}
