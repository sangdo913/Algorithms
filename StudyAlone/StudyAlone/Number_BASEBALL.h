#pragma once
typedef int BASE[4];

typedef struct {
	int strike;
	int ball;
} Result;
extern Result query(int guess[]);

// ����Ʈ�� ����� ������ ��� 4�ڸ��� ���� ���Ѵ�.
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
//10P4�� �̿��� ���� �� �ִ� 4�ڸ� ���ڸ� ��� �����.
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

//���ϴ� ���� ���� ���� ��Ʈ����ũ�� �� ������ ���Ѵ�.
int StrikeCheck(int guess[4], int nums[4])
{
	int result = 0;
	for (int i = 0; i < 4; i++) result = guess[i] == nums[i] ? ++result : result;
	return result;
}

//���ϴ� ���� ���� ���� �� ������ �� �� ���� ���Ѵ�.
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

//���� �� �ִ� ��� ����� ������ ����� �� �� ���� ���� �A��.
void User_Check(Result result, int guess[4])
{
	List* now = first->next;
	while (now != 0)
	{
		//��Ʈ����ũ ������ �� ������ ���ƴµ� ���ϴ� ���� �� ���� �װͺ��� ���ٸ� ����� �� �� ����.
		// ���������� �˻��ؼ� ���� ��Ʈ����ũ �������� ���ϴ� �Ϳ��� ��Ʈ����ũ�� �� ���̳��´ٸ� ���� �� ����.
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
	//ó���� �� �ʱ�ȭ
	first = new List();
	last = first;

	int flag[10] = { 0,1,2,3,4,5,6,7,8,9 };
	//��� ���� ����Ʈ�� ����.
	init(10, 4, 0, flag);
	//ó�� ���� �������̹Ƿ� ������.
	List* del = first;
	first = first->next;
	delete(del);

	for (int i = 0; i < 4; i++)
	{
		guess[i] = first->value[i];
	}
	Result result;

	//���ϴ� ���� ã�´�.
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

	//���� ����Ʈ ����
	while (true)
	{
		List* temp = first->next;
		delete(first);
		if (!temp) break;
		first = temp;
	}
}