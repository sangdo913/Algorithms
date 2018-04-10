#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include"LeakOfBackBird.h"

using namespace std;

int main()
{
	freopen("0Text.txt", "r", stdin);
	LeakOfBackBird();
	return 0;
}