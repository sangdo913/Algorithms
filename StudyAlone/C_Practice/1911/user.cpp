// #define rint register int
// /*
//     PASS
//     1921507.006470
    // 1926781.012490

//     main.cpp 를 읽고 문제를 해석하여 SCORE 를 최소화 하세요.
//     *전역 변수 사용 불가
// */
// int encode(char* src, char* paper, int papern) {
//     rint b = 0;
//     int conv[256];
//     for(int i = 'a'; i <= 'z'; ++i) conv[i] = i-'a'+1;
//     int mhash[1024] = {};
//     int chk[1024] = {};
//     int table[1024][7];
//     int len[1024] = {};
//     long long key[1024];
//     rint i =0;
//     rint idx = 0;
//     rint plen = 0;
//     while(i!= papern) {
//         plen++;
//         rint l = 0;
//         long long h = 0;
//         while(paper[i+l] && paper[i+l] != ' '){
//             h = ((h << 5) + conv[paper[i+l]]);
//             l++;
//         }
//         rint k = h%1024;
//         while(chk[k] && key[k] != h) k = ++k%1024;
//         if(!chk[k]) {
//             chk[k] = 1;
//             key[k] = h;
//             mhash[k] = idx;
//             len[idx] = l;
//             for(rint s = 0; s< l; ++s) {
//                 table[idx][s] = conv[paper[i+s]];
//             }
//             ++idx;
//          }
//          i+=l+1;
//     }
//     rint remain = 15;
//     rint read = plen;
//     for(int i = 0; i < idx; ++i){
//         remain = 3;
//         read = len[i];
//         while(remain--){
//             src[b/8] |= (read&1) << (b%8);
//             read>>=1;
//             ++b;
//         }
//         for(rint s = 0; s < len[i]; ++s){
//             remain = 5;
//             read = table[i][s];
//             while(remain--){
//                 src[b/8] |= (read&1) << (b%8);
//                 read>>=1;
//                 ++b;
//             }
//         }
//     }
//     b+=3;
//     remain = 15;
//     read = plen;
//     while(remain--) {
//         src[b/8] |= (read&1)<<(b%8);
//         read>>=1;
//         b++;
//     }
//     i= 0;
//     while(paper[i]) {
//         long long h = 0;
//         while(paper[i] && paper[i] != ' '){
//             h = ((h << 5) + conv[paper[i]]);
//             i++;
//         }
//         rint k = h%1024;
//         while(chk[k] && key[k] != h) k = ++k%1024;
//         remain = 10;
//         read = mhash[k];
//         while(remain--) {
//             src[b/8] |= (read&1)<<(b%8);
//             read>>=1;
//             b++;
//         }
//         if(!paper[i])break;
//         ++i;
//     }
//     return b/8+1;
// }
// void decode(char* dest, char* src, int s) {
//     int debug = 1;
//     rint b = 0;
//     rint remain = 0;
//     rint read, sh;
//     int table[1024][7];
//     int len[1024];
//     rint i = 0;
//     while(true){
//         remain = 3;
//         read = 0;
//         sh = 0;
//         while(remain--){
//             read |= (src[b/8]&1) << sh++;
//             src[b/8]>>=1;
//             b++;
//         }
//         if(!read) {
//             break;
//         }
//         len[i] = read;
//         for(rint s = 0; s < len[i]; ++s) {
//             remain = 5;
//             read = 0;
//             sh = 0;
//             while(remain--){
//                 read |= (src[b/8]&1) << sh++;
//                 src[b/8]>>=1;
//                 b++;
//             }
//             table[i][s] = read - 1 + 'a';
//         }
//         ++i;
//     }
//     remain = 15;
//     read = 0;
//     sh=0;
//     while(remain--){
//         read |= (src[b/8]&1) << sh++;
//         src[b/8]>>=1;
//         b++;
//     }
//     rint allen = read;
//     rint rlen = 0;
//     for(rint i = 0;  i< allen; ++i){
//         remain = 10;
//         read = 0;
//         sh=0;
//         while(remain--){
//             read |= (src[b/8]&1) << sh++;
//             src[b/8]>>=1;
//             b++;
//         }
//         for(rint s = 0; s < len[read]; ++s){
//             dest[rlen++] = table[read][s];
//         }
//         dest[rlen++] = ' ';
//     }
//     for(rint i = 0; i <s; ++i) src[i] = 0;
// }

/*
	main.cpp 를 읽고 문제를 해석하여 SCORE 를 최소화 하세요.
	*전역 변수 사용 불가
*/


#define MAX_TABLE 1024
#define MAX_WORD 1024
#define MAX_LEN 7

void addChar(char* src, int& idx, int& extra, int value, int len)
{
	while (1) {
		if (len == 0) break;
		if (extra >= len) {
			src[idx] >>= (extra - len);
			src[idx] |= value;
            extra = extra-len;
			len = 0;
			src[idx] <<= extra;
		}
		else {
			int bitDiff = len - extra;
			src[idx] |= (value >> bitDiff);
			value %= (1 << bitDiff);
			len -= extra;
			extra = 0;
		}
		if (extra == 0) {
			idx++;
			extra = 8;
		}
	}
}

//>> 문자열을 압축하여 저장
//len : 넣어야 되는 코드의 bit의 길이
//value : 넣는 값
//idx : 넣는 배열의 index
//extra : 넣는 배열의 index에 남은 bit

int returnValue(char* src, int& idx, int& extra, int len) {
	int value = 0;
	while (1) {
		if (len == 0)break;
		if (extra <= len) {
			value <<= extra;
			for (int i = 0; i < extra; ++i) {
				if (src[idx] & (1 << i))
					value |= (1 << i);
			}
			src[idx] = 0;
			len -= extra;
			extra = 0;
		}
		else {
			value <<= len;
			int bitDiff = extra - len;
			for (int i = 0; i < len; ++i) {
				if (src[idx] & (1 << (extra - i - 1)))
					value |= (1 << (len - i - 1));
			}
			src[idx] %= (1 << bitDiff);
			extra -= len;
			len = 0;
		}
		if (extra == 0) {
			idx++;
			extra = 8;
		}
	}
    return value;
}

//압축된 문자열을 반환
//len : 반환해야 되는 코드의 bit의 길이
//idx : 반환해야 되는 배열의 index
//extra : 반환해야 되는 배열의 index에 남은 bit

int _strcmp(char* a, char* b, int idx) {
	for (int i = 0; i < idx; ++i) {
		if (a[i] != b[i]) {
			return 1;
		}
	}
	return 0;
}

unsigned long getHash(char* dummy, int index) {
	unsigned long hashVal = 0;

    for(register int i = 0; i < index; ++i) {
        hashVal = (hashVal <<5) + dummy[i] - 'a'+1; 
    }

	return hashVal;
}

int encode(char* src, char* paper, int len) {
	char Word[MAX_WORD][MAX_LEN] = { 0, };
	char WordLen[MAX_WORD] = { 0, };
    int chk[MAX_WORD] = {};
	char dummyWord[MAX_LEN] = { 0, };
	char* currWord = paper;
	int idx = 0;
	for (int i = 0; i < len; ++i) {
		if (currWord[i] == ' ') {
			unsigned long hashValue = getHash(dummyWord, idx)%MAX_TABLE;

			while (1) {
				if (WordLen[hashValue] == 0) {
					WordLen[hashValue] = idx;
					for (int y = 0; y < idx; ++y) {
						Word[hashValue][y] = dummyWord[y];
					}
				}
				if (idx == WordLen[hashValue] && _strcmp(Word[hashValue], dummyWord, idx) == 0) break;
				hashValue++;
				hashValue %= MAX_TABLE;
			}
			idx = 0;
		}
		else {
			dummyWord[idx++] = currWord[i];
		}
	}
	int pos = 0;
	int currPos = 8;
	for (int i = 0; i < MAX_WORD; ++i) {
		int length = WordLen[i];
		addChar(src, pos, currPos, length, 3);
		for (int y = 0; y < length; ++y) {
			addChar(src, pos, currPos, Word[i][y] - 'a', 5);
		}
	}
	for (int i = 0; i < len; ++i) {
		if (currWord[i] == ' ') {
			unsigned long hashValue = getHash(dummyWord, idx)%MAX_WORD;
			while (1) {
				if (idx == WordLen[hashValue] && _strcmp(Word[hashValue], dummyWord, idx) == 0) break;
				hashValue++;
				hashValue %= MAX_TABLE;
			}
			addChar(src, pos, currPos, hashValue, 10);
			idx = 0;
		}
		else {
			dummyWord[idx++] = currWord[i];
		}
	}
	return pos + 1;
}

void decode(char* dest, char* src, int s) {
	char Word[MAX_WORD][MAX_LEN] = { 0, };
	char WordLen[MAX_WORD] = { 0, };
	int pos = 0;
	int currPos = 8;
	for (int i = 0; i < MAX_TABLE; ++i) {
		int len = returnValue(src, pos, currPos, 3);
		if (len) {
			WordLen[i] = len;
			for (int y = 0; y < len; ++y) {
				char alpha = returnValue(src, pos, currPos, 5);
				alpha += 'a';
				Word[i][y] = alpha;
			}
		}
	}
	int idx = 0;
	while (1) {
		int hashIdx = returnValue(src, pos, currPos, 10);
		if (pos >= s) break;
		for (int i = 0; i < WordLen[hashIdx]; ++i) {
			dest[idx++] = Word[hashIdx][i];
		}
		dest[idx++] = ' ';
	}
}