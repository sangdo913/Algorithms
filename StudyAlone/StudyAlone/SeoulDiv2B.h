#pragma once
#include<iostream>

using namespace std;
const char nums[10][5][4] =
{
	//0
	{
		{
			"###"
},
		{
			"#.#"
},
		{
			"#.#"
},
		{
			"#.#"
},
		{
			"###"
}

},
//2
{
		{
		"###"
},
		{
			"..#"
},
		{
			"###"
},
		{
			"#.."
},
		{
			"###"
}

},
//3
{
	"###",
	"..#",
	"###",
	"..#",
	"###"

},
//4
{
	"#.#",
	"#.#",
	"###",
	"..#",
	"..#"
	
},
//5
	{
		"###",
		"#..",
		"###",
		"..#",
		"###"

},
//6
	{
		"###",
		"#..",
		"###",
		"#.#",
		"###"
},
//7
	{
		"###",
		"..#",
		"..#",
		"..#",
		"..#",
},
//8
	{
		"###",
		"#.#",
		"###",
		"#.#",
		"###",

},
//9
	{
		"###",
		"#.#",
		"###",
		"..#",
		"###",

},
//1
			{
				"#","#","#","#","#"
			}
};
char str[5][100000];

int SeoulDiv2B() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < n / 5; j++) {
			cin >> str[i][j];
		}
	}
	char num[100000];
	int rlen = 0;
	for (int j = 0; j < n / 5; j++)
	{
		if (str[0][j] == '#') {
			int d;
			for (d = 0; d < 10; d++) {
				
				int len = d == 9 ? 1 : 3;
				bool correct = true;
				for (int i = 0; i < 5; i++) {
					for (int c = 0; c < len; c++) {
						if (str[i][c + j] != nums[d][i][c]) {
							correct = false; break;
						}
					}
					if (correct == false) break;
				}
				if (correct) {
					d++;
					switch (d) {
					case 1:d = 0; break;
					case 10: d = 1; break;
					}
					num[rlen++] = d + '0';

					j += len;
					break;
				}
			}
		}
	}
	
	num[rlen] = 0;
	cout << num;
	return 0;
}
