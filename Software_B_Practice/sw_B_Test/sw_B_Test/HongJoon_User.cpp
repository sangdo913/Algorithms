#define _ARRSIZE 'Z'-'A'+1

int char_conv(char a)
{
	if (a >= 'a' && a <= 'z')
	{
		return a - 'a';
	}

	else return a - 'A';
}

typedef struct __chars
{
	__chars *values[_ARRSIZE];
	int nums;
	void init()
	{
		nums = 0;
		for (int i = _ARRSIZE; i--;)
		{
			values[i] = 0;
		}
	}
	void del()
	{
		for (int i = _ARRSIZE; i--;)
		{
			if (values[i]) values[i]->del();
		}
		delete(this);
	}
	void insert(char* str, int str_size)
	{
		nums++;
		if (str_size != 1)
		{
			if (!values[char_conv(str[1])])
			{
				__chars *temp = new __chars();
				values[char_conv(str[1])] = temp;
				values[char_conv(str[1])]->init();
			}
			values[char_conv(str[1])]->insert(&str[1], str_size - 1);
		}
	}

	int query(int buf_size, char*buf)
	{
		if (buf_size == 1) return nums;
		int result = 0;
		if (values[char_conv(buf[1])])
		{
			result = values[char_conv(buf[1])]->query(buf_size - 1, &buf[1]);
		}
		return result;
	}
}chars;

typedef struct __TRIE
{
	chars *containers[_ARRSIZE];
	void init()
	{
		for (int i = _ARRSIZE; i--;)
		{
			if (containers[i]) containers[i]->del();
			containers[i] = 0;
		}
	}

	void insert(char* str, int str_size)
	{
		if (!containers[char_conv(str[0])])
		{
			containers[char_conv(str[0])] = new chars();
			containers[char_conv(str[0])]->init();
		}
		containers[char_conv(str[0])]->insert(str, str_size);
	}
	int query(int buf_size, char* buf)
	{
		int result = 0;
		if (containers[char_conv(buf[0])]) result = containers[char_conv(buf[0])]->query(buf_size, buf);
		return result;
	}

	~__TRIE()
	{
		for (int i = _ARRSIZE; i--;)
		{
			if (containers[i]) containers[i]->del();
			containers[i] = 0;
		}
	}
}Trie;


Trie trie;
void init(void)
{
	trie.init();
}

void insert(int buffer_size, char *buf)
{
	trie.insert(buf, buffer_size);
}

int query(int buffer_size, char *buf)
{
	return trie.query(buffer_size, buf);
}
