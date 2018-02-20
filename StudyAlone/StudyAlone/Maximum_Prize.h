#pragma once
#include<iostream>

using namespace std;
struct Prize_Data;
struct Prize_Node;
struct Prize_Queue;
struct Prize_Data
{
	char str[6];
	int size;
	int value;
	int count;
	Prize_Data();
};
Prize_Data::Prize_Data()
{
	str[0] = '\0';
	size = 0;
	value = 0;
	count = 0;
}
struct Prize_Node
{
	typedef Prize_Node Node;
	typedef Prize_Data Data;
	Node* prev;
	Node* next;
	Data data;
};

struct Prize_Queue
{
	typedef Prize_Node::Data Data;
	typedef Prize_Node Node;
	Node* head;
	Node* tail;
	int size;
	bool empty();
	void push(Data data);
	bool pop(Data &data);
	Prize_Queue();
	~Prize_Queue();
};

bool Prize_Queue::empty()
{
	return size == 0;
}

void Prize_Queue::push(Data data)
{
	Node* newNode = new Node();
	newNode->data = data;

	newNode->next = head->next;
	newNode->prev = head;

	newNode->next->prev = newNode;
	head->next = newNode;
	size++;
}


bool Prize_Queue::pop(Data &data)
{
	if (empty()) return false;
	size--;
	Node* rNode = tail->prev;
	data = rNode->data;
	tail->prev = rNode->prev;
	rNode->prev->next = tail;
	delete(rNode);
	return true;
}

Prize_Queue::Prize_Queue() :head(new Node()), tail(new Node()), size(0)
{
	head->next = tail;
	tail->prev = head;
}
Prize_Queue::~Prize_Queue()
{
	Node* rNode;
	while (head)
	{
		rNode = head;
		head = head->next;
		delete(rNode);
	}
}

int Prize_max_Num = -1;

int Prize_Get_Size(char*str)
{
	int size = 0;
	while (*str)
	{
		size++;
		str++;
	}
	return size;
}

int Prize_Str_To_Int(char* str,int size)
{
	int result = 0;
	for (int i = 0; i < size; i++)
	{
		result *= 10;
		result += str[i] - '0';
	}
	return result;
}
void Prize_Int_To_Str(char* str,int num,int size)
{
	str[size] = '\0';
	for (int n = size; n--;)
	{
		str[n] = num % 10 + '0';
		num /= 10;
	}
}
int Prize_Get_Int_Size(int num)
{
	int size = 0;
	while (num)
	{
		size++;
		num /= 10;
	}
	return size;
}
void Prize_Swap(char* str, int index1, int index2)
{
	char temp = str[index1];
	str[index1] = str[index2];
	str[index2] = temp;
}
bool Prize_memoi[11][1000000];
void Prize_Get_Max_Prize(int num, int count, int size,int max_Count) 
{
	if (Prize_memoi[count][num]) return;
	if (max_Count==count)
	{
		Prize_max_Num = Prize_max_Num < num ? num : Prize_max_Num;
		return;
	}
	int next_Num;
	Prize_memoi[count][num] = true;
	char str[7];
	Prize_Int_To_Str(str, num, size);
	for (int i = 0; i < size; i++)
	{
		for (int j = i + 1; j < size; j++)
		{
			Prize_Swap(str, i, j);
			next_Num = Prize_Str_To_Int(str, size);
			Prize_Get_Max_Prize(next_Num, count + 1, size, max_Count);
			Prize_Swap(str, i, j);
		}
	}
}

int Maximum_Prize()
{
	char str[7];
	int size;
	int T, count, num;
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{
		cin >> num >> count;
		size = Prize_Get_Int_Size(num);
		int arr_Size = 1;
		for (int i = 0; i < size; i++)
		{
			arr_Size *= 10;
		}
		for (int cnt = 0; cnt < count; cnt++)
			for (int i = 0; i < arr_Size; i++)
				Prize_memoi[cnt][i] = false;
		Prize_max_Num = -1;

		Prize_Get_Max_Prize(num, 0, size, count);
		cout << '#' << tc << ' ' << Prize_max_Num << endl;
	}

	return 0;
}