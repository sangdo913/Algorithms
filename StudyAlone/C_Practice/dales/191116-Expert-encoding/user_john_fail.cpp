#include <stdio.h>
// src: 3B 씩 저장. 3b: 길이, 21b: 합 -> 순서를 알수업어
int encode(char* src, char* paper, int papern)
{	
	int char2code[26] = { 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, // m 
		610, 987, 1597, 2584, 4181, 6765, 10946, 17711, 28657, 46368, 75025, 121393, 196418};
	
	int sum = 0;
	int s = 0;
	int l = 0;

	for (register int i = 0; i < papern; i++)
	{
		if (paper[i] == ' ') {
			// record 
			src[s] |= l << 5;

			src[s++] |= ((sum >> 16) & 0xff );
			src[s++] |= ((sum >> 8) & 0xff);
			src[s++] |= (sum & 0xff);
			sum = l = 0;
			continue;
		}
		sum += char2code[paper[i] - 'a'];
		l++;
	}
	return s;
}

void code2char(int sum, int length, char *seg) {

}

void decode(char* dest, char* src, int s)
{
	int l = 0, sum = 0;
	for (register int i = 0; i < s; i = i + 3)
	{
		l = src[i] >> 5;
		sum = ((src[i] & 0x1f) << 16) | (src[i + 1] << 8) | (src[i + 2]);
	}
	char seg[7];
	code2char(sum, l, seg);

}





//int p[26] = { 0 };
//p[0] = 1;
//p[1] = 2;
//p[2] = 3;
//
//for (int i = 3; i < 26; i++)
//{
//	p[i] = p[i - 1] + p[i - 3];
//	printf("%d, ", p[i]);
//
//}