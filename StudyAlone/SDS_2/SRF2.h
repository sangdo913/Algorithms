#pragma once
#include<iostream>
#include<string>

using namespace std;

char nums[46] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ $%*+-./:";
int cflag[9];

string bits;
string res;
int snum;

void conv(const string& in) {
	for (int i = 0; i < in.size(); i++) {
		int num = in[i];
		if (in[i] >= 'A') num += 10-'A';

		string bit;
		for (int i = 0; i < 4; i++) {
			bit.push_back(num % 2 + '0');
			num >>= 1;
		}
		bit = string(bit.rbegin(), bit.rend());
		bits += bit;
	}
}

void pl(int num, int cnt) {
	string pl;
	for(int i = 0; i < cnt; i++){
		pl += num % 10 + '0';
		num /= 10;
	}

	pl = string(pl.rbegin(), pl.rend());
	res += pl;
}

void ascii(char num) {
	int nums[2] = { num & 0b11110000, num & 0b1111 };
	nums[0] >>= 4;
	if (nums[0] > 9) nums[0] += -10 + 'A';
	else nums[0] += '0';
	if (nums[1] > 9) nums[1] += -10 + 'A';
	else nums[1] += '0';
	res += '\\';
	res += nums[0];
	res += nums[1];
}

void apl(char c) {
	if (c < ' ' || c > 0x7e) ascii(c);
	else {
		if (c == '\\') res += "\\\\";
		else if(c == '#') {
			res += "\\#";
		}
		else {
			res += c;
		}
	}
}

void kanji(int num) {
	int nums[4] = {};
	nums[0] = num & 0b1111000000000000;
	nums[0] >>= 12;
	nums[1] = num & 0b111100000000;
	nums[1] >>= 8;
	nums[2] = num & 0b11110000;
	nums[2] >>= 4;
	nums[3] = num & 0b1111;
	res += '#';
	for (int i = 0; i < 4; i++) {
		if (nums[i] > 9) nums[i] += -10 + 'A';
		else nums[i] += '0';

		res += nums[i];
	}
}

int passing(int cursor) {
	int mode = 0;;

	for (int i = 0; i < 4; i++, cursor++) {
		if (cursor == bits.size()) return -1;
		mode <<= 1;
		mode += bits[cursor] - '0';
	}

	if (mode == 0) return -1;

	int cnt = cflag[mode];
	int len = 0;
	for (int i = 0; i < cnt; i++,cursor++) {
		if (cursor == bits.size()) return -1;
		len <<= 1;
		len += bits[cursor] - '0';
	}

	int remain=0, fbit = 0;
	int num;
	string str;

	switch (mode) {
	case 1:
		remain = len % 3;
		if (remain == 1) fbit = 4;
		else if (remain == 2) fbit = 7;

		for (int i = 0; i < len / 3; i++) {
			num = 0;
			for (int j = 0; j < 10; j++, cursor++) {
				num <<= 1;
				num += (bits[cursor] - '0');
			}
			pl(num,3);
			snum+=3;
		}


		num = 0;

		if(fbit){
			for (int i = 0; i < fbit; i++, cursor++) {
				num <<= 1;
				num += (bits[cursor] - '0');
			}
			pl(num, remain);
			snum+= remain;
		}
		break;
	case 2:
		remain = len % 2;
		if (remain == 1) fbit = 6;

		for (int cnt = 0; cnt < len / 2; cnt++) {
			num = 0;
			for (int i = 0; i < 11; i++, cursor++) {
				num <<= 1; num += bits[cursor]-'0';
			}

			int c[2] = { num / 45, num % 45 };
			res += nums[c[0]];
			snum++;
			res += nums[c[1]];
			snum++;
		}

		if (fbit) {
			num = 0;
			for (int i = 0; i < 6; i++, cursor++) {
				num <<= 1;
				num += bits[cursor] - '0';
			}
			res += nums[num];
			snum++;
		}
		break;
	case 4:
		for (int i = 0; i < len; i++) {
			num = 0;
			for (int j = 0; j < 8; j++, cursor++) {
				num <<= 1; num += bits[cursor] - '0';
			}
			apl(num);
			snum++;
		}
		break;
	case 8:
		for (int i = 0; i < len; i++) {
			num = 0;
			for (int i = 0; i < 13; i++, cursor++) {
				num <<= 1;
				num += bits[cursor] - '0';
			}
			kanji(num);
			snum++;
		}
		break;
	case 0:
		return -1;
		break;
	default:
		return -1;
	}

	return cursor;
}

int DO() {
	int tc;
	cin >> tc;
	cflag[1] = 10;
	cflag[2] = 9;
	cflag[4] = 8;
	cflag[8] = 8;
	cflag[0] = 0;

	for (int t = 1; t <= tc; t++) {
		string in;
		snum = 0;
		res.clear();
		bits.clear();
		cin >> in;

		conv(in);
		int cursor = 0;

		while (cursor != -1 && cursor < bits.size()) {
			cursor = passing(cursor);
		}
		
		cout << "Case #" << t << '\n';
		cout << snum << ' ' << res << endl;
	}

	return 0;
}
