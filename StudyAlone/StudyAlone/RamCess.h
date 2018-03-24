#pragma once
#include<iostream>

using namespace std;

/*

Practice는 표준 입출력을 사용합니다.
파일 입출력을 사용하지 않음에 주의하세요.
In Practice, You should use the statndard input/output
in order to receive a score properly.
Do not use file input and output. Please be very careful.

*/

#include <stdio.h>

int T;
int N;
int M;
char I[1000001];
int Answer;
int A[1000001];
int B[500001];

// Iterate version
int f_c(int a, int b, int n)
{
	int i, c;
	c = 0;
	for (i = n; i >= 0; i--) {
		if (i == 0) { c++; c = (c%M); break; }
		if (i == 1 && ((a == 0 && b == 2) || (a == 2 && b == 0))) { c++; c = (c%M); break; }
		if (a == 1 && b == 0 && I[N - i + 1] == 'L') { a = 2; b = 0; continue; }
		if (a == 1 && b == 0 && I[N - i + 1] == 'P') {
			c += B[(i - 1) / 2];
			c = (c%M);
			a = 0; b = 1;
			continue;
		}
		if (a == 0 && b == 1 && I[N - i + 1] == 'L') { a = 1, b = 0; continue; }
		if (a == 0 && b == 1 && I[N - i + 1] == 'P') {
			c += A[i - 1];
			c = (c%M);
			a = 0; b = 2;
			continue;
		}
		if (a == 0 && b == 2 && I[N - i + 2] == 'L') { a = 2; b = 0; i--; continue; }
		if (a == 0 && b == 2 && I[N - i + 2] == 'P') {
			c += B[(i - 2) / 2];
			c = (c%M);
			a = 0; b = 2; i--;
			continue;
		}
		if (a == 2 && b == 0 && I[N - i + 2] == 'L') { a = 2; b = 0; i--; continue; }
		if (a == 2 && b == 0 && I[N - i + 2] == 'P') {
			c += B[(i - 2) / 2];
			c = (c%M);
			a = 0;
			b = 2;
			i--;
			continue;
		}
	}
	return c;
}

// Recursive version
int f_b(int a, int b, int n)
{
	if (n == 0) return 1;
	if (n == 1 && ((a == 0 && b == 2) || (a == 2 && b == 0))) return 1;
	if (a == 1 && b == 0 && I[N - n + 1] == 'L') return f_b(2, 0, n - 1);
	if (a == 1 && b == 0 && I[N - n + 1] == 'P') return (B[(n - 1) / 2] + f_b(0, 1, n - 1)) % M;
	if (a == 0 && b == 1 && I[N - n + 1] == 'L') return f_b(1, 0, n - 1);
	if (a == 0 && b == 1 && I[N - n + 1] == 'P') return (A[n - 1] + f_b(0, 2, n - 1)) % M;
	if (a == 0 && b == 2 && I[N - n + 2] == 'L') return f_b(2, 0, n - 2);
	if (a == 0 && b == 2 && I[N - n + 2] == 'P') return (B[(n - 2) / 2] + f_b(0, 2, n - 2)) % M;
	if (a == 2 && b == 0 && I[N - n + 2] == 'L') return f_b(2, 0, n - 2);
	if (a == 2 && b == 0 && I[N - n + 2] == 'P') return (B[(n - 2) / 2] + f_b(0, 2, n - 2)) % M;
}

void f_a()
{
	int i;
	A[0] = 1;
	A[1] = 2 % M;
	B[0] = 1;
	B[1] = 2 % M;

	// 2^x % M
	for (i = 2; i <= N / 2; i++)
		B[i] = (B[i - 1] * 2) % M;

	for (i = 2; i <= N; i++) {
		A[i] = (A[i - 1] + B[(i - 1) / 2]) % M;
	}

	if (I[1] == 'L') Answer = f_c(1, 0, N - 1);
	else if (I[1] == 'P') {
		Answer = (A[N - 1] + f_c(0, 1, N - 1)) % M;
	}
}

int SeongHwan(void)
{
	int test_case;
	/*
	The freopen function below opens input.txt file in read only mode, and afterward,
	the program will read from input.txt file instead of standard(keyboard) input.
	To test your program, you may save input data in input.txt file,
	and use freopen function to read from the file when using scanf function.
	You may remove the comment symbols(//) in the below statement and use it.
	But before submission, you must remove the freopen function or rewrite comment symbols(//).
	*/
	//freopen("input.txt", "r", stdin);

	/*
	If you remove the statement below, your program's output may not be rocorded
	when your program is terminated after the time limit.
	For safety, please use setbuf(stdout, NULL); statement.
	*/
	setbuf(stdout, NULL);

	scanf("%d ", &T);

	for (test_case = 1; test_case <= T; test_case++)
	{
		int i;
		scanf("%d", &N);
		scanf("%d", &M);
		scanf("%s", &I[1]);

		/////////////////////////////////////////////////////////////////////////////////////////////
		/*
		Implement your algorithm here.
		The answer to the case will be stored in variable Answer.
		*/
		/////////////////////////////////////////////////////////////////////////////////////////////
		f_a();

		printf("#%d %d\n", test_case, Answer);

		// Print the answer to standard output(screen).
	}

	return 0;//Your program should return 0 on normal termination.
}

///////////////2
#include <iostream>
#include <cmath>
#include <string>
#include <fstream>

using namespace std;
int m = 10000000;
int RamCess_arr[1000001][2];
//  P 1, L 0 : PLPLPLPL  길이당 1개
//  L 1, P 0 : LPLPLPLP  길이당 1개
//[0] :  2,  0
//[1] :  1,  1

int modPow(int n)
{
	int ret = 1;
	for (int i = 0; i<n; i++)
	{
		ret = (ret * 2) % m;
	}

	return ret;
}


void fillRamCess_array()
{
	RamCess_arr[1][0] = 0;
	RamCess_arr[1][1] = 0;


	for (int i = 2; i <= 1000000; i++)
	{

		if (i % 2 == 1)
			RamCess_arr[i][0] = RamCess_arr[i][1] = RamCess_arr[i - 1][0];
		else
		{

			int j1 = i / 2;
			RamCess_arr[i][0] = (RamCess_arr[i - 1][0] * 2 + 1) % m;

			RamCess_arr[i][1] = RamCess_arr[i - 1][0];
		}
	}                                                                                                          

}


int calcIndex(int n, char* str)
{
	int ret = 1;
	int L = 0, P = 0;


	if (str[0] == 'P')
	{
		ret = (ret + RamCess_arr[n][0] + RamCess_arr[n][1] + 1) % m;
		P++;
	}
	else
	{
		L++;
	}

	for (int i = 1; str[i] != 0; i++)
	{
		if (str[i] == 'P')
		{
			if (L == 1 && P == 0)
			{
				ret = (ret + RamCess_arr[n - i][1] + 1) % m;
			}
			else if (P == 1 && L == 0)
			{
				ret = (ret + RamCess_arr[n - i][0] + RamCess_arr[n - i][1] + 1) % m;
			}
			else if (L == 1)
			{
				ret = (ret + RamCess_arr[n - i][1] + 1) % m;
			}



			P++;
			L--;

			if (L<0)
				L = 0;
		}
		else
		{

			P--;
			L++;

			if (P<0)
				P = 0;
		}
	}

	return ret;
}


int main23()
{


	ios_base::sync_with_stdio(false);


	int t;


	cin >> t;





	for (int test_case = 1; test_case <= t; test_case++)
	{
		int n;

		char str[1000001];


		cin >> n >> m;
		cin.ignore();
		//getline(cin,str);
		cin >> str;


		fillRamCess_array();

		int r = calcIndex(n, str);
		cout << "#" << test_case << " " << r%m << endl;
	}

	return 0;

}