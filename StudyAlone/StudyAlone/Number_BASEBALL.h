#pragma once
typedef int BASE[4];

typedef struct {
	int strike;
	int ball;
} Result;
extern Result query(int guess[]);

// 리스트를 사용해 가능한 모든 4자리의 수를 구한다.
class List
{
public:
	int value[4];
	List* prev;
	List* next;
	List()
	{
		prev = next = 0;
		for (int i = 0; i < 4; i++) value[i] = 0;
	}
	List(const int value[4])
	{
		prev = next = 0;
		for (int i = 0; i < 4; i++) this->value[i] = value[i];
	}
};

List *first;
List *last;
void User_Swap(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}
int cnt = 0;
//10P4를 이용해 만들 수 있는 4자리 숫자를 모두 만든다.
void init(int n, int r, int length, int arr[10])
{
	if (r == 0)
	{
		List * temp = new List();
		for (int i = 0; i < 4; i++)
		{
			temp->value[i] = arr[i];
		}

		last->next = temp;
		temp->prev = last;
		last = temp;

		return;
	}

	for (int i = length; i < n; i++)
	{
		User_Swap(arr[length], arr[i]);
		init(n, r - 1, length + 1, arr);
		User_Swap(arr[length], arr[i]);
	}
}

//비교하는 수와 기존 수의 스트라이크가 몇 개인지 비교한다.
int StrikeCheck(int guess[4], int nums[4])
{
	int result = 0;
	for (int i = 0; i < 4; i++) result = guess[i] == nums[i] ? ++result : result;
	return result;
}

//비교하는 수와 기존 수의 볼 개수가 몇 개 인지 비교한다.
int BallCheck(int guess[4], int num[4])
{
	int result = 0;
	int digits[10] = { 0,0,0,0,0,0,0,0,0,0 };
	for (int i = 0; i < 4; i++)
	{
		digits[guess[i]]++;
	}
	for (int i = 0; i < 4; i++)
	{
		result = digits[num[i]] > 0 ? ++result : result;
	}
	return result;
}

//만들 수 있는 모든 경우의 수에서 만들어 질 수 없는 수를 뺸다.
void User_Check(Result result, int guess[4])
{
	List* now = first->next;
	while (now != 0)
	{
		//스트라이크 개수와 볼 개수를 합쳤는데 비교하는 수의 볼 수가 그것보다 많다면 만들어 질 수 없다.
		// 마찬가지로 검사해서 나온 스트라이크 개수보다 비교하는 것에서 스트라이크가 더 많이나온다면 만들 수 없다.
		if (BallCheck(guess, now->value) > result.strike + result.ball || StrikeCheck(guess, now->value) > result.strike)
		{
			if (now == first)
			{
				first = first->next;
				delete(now);
				now = first;
				continue;
			}

			else if (now == last)
			{
				last = last->prev;
				delete(now);
				last->next = 0;
				now = 0;
			}
			else {
				List* next = now->next;
				now->prev->next = now->next;
				now->next->prev = now->prev;
				delete(now);
				now = next;
			}
		}

		else
		{
			now = now->next;
		}
	}
	List *next = first->next;
	delete(first);
	first = next;
}

void doUserImplementation(int guess[])
{
	//처음과 끝 초기화
	first = new List();
	last = first;

	int flag[10] = { 0,1,2,3,4,5,6,7,8,9 };
	//모든 수를 리스트로 만듦.
	init(10, 4, 0, flag);
	//처음 노드는 쓰레기이므로 버린다.
	List* del = first;
	first = first->next;
	delete(del);

	for (int i = 0; i < 4; i++)
	{
		guess[i] = first->value[i];
	}
	Result result;

	//원하는 수를 찾는다.
	while (true)
	{
		result = query(guess);
		if (result.strike == 4) break;

		User_Check(result, guess);
		for (int i = 0; i < 4; i++)
		{
			guess[i] = first->value[i];
		}
	}

	//남은 리스트 삭제
	while (true)
	{
		List* temp = first->next;
		delete(first);
		if (!temp) break;
		first = temp;
	}
}