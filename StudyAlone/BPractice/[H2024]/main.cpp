#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include"user.cpp"

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
#define MALE   0
#define FEMALE 1

#define INIT         0
#define ADDMEMBER    1
#define GETDISTANCE  2
#define COUNTMEMBER  3

#define COUPLE  0
#define PARENT  1
#define CHILD   2

#define NAME_LEN_MAX 19

////////////////////////////////////////////////////////////////////////////////

extern void init(char initialMemberName[], int initialMemberSex);
extern bool addMember(char newMemberName[], int newMemberSex, int relationship, char existingMemberName[]);
extern int  getDistance(char nameA[], char nameB[]);
extern int  countMember(char name[], int dist);

////////////////////////////////////////////////////////////////////////////////

static int score = 0;

static void cmd_init()
{
	char initialMemberName[NAME_LEN_MAX + 1];
	int initialMemberSex;

	scanf("%s %d", initialMemberName, &initialMemberSex);
	
	init(initialMemberName, initialMemberSex);
}

static void cmd_addMember()
{
	char newMemberName[NAME_LEN_MAX + 1];
	int newMemberSex;
	int relationship;
	char existingMemberName[NAME_LEN_MAX + 1];

	scanf("%s %d %d %s", newMemberName, &newMemberSex, &relationship, existingMemberName);
	
	bool userAns = addMember(newMemberName, newMemberSex, relationship, existingMemberName);
    // printf("%s %s %s g:%d r:%d, ans: %d\n", __func__, newMemberName, existingMemberName, newMemberSex, relationship,userAns);

	int ans;
	scanf("%d", &ans);
	bool ansbool = ans == 1 ? true : false;
	
	if (ansbool != userAns)
	{
		score = 0;
	}
}

static void cmd_getDistance()
{
	char nameA[NAME_LEN_MAX + 1];
	char nameB[NAME_LEN_MAX + 1];

	scanf("%s %s", nameA, nameB);
	
	int userAns = getDistance(nameA, nameB);

	int ans;
	scanf("%d", &ans);
	
	if (ans != userAns)
	{
		score = 0;
	}
}

static void cmd_countMember()
{
	char name[NAME_LEN_MAX + 1];
	int dist;

	scanf("%s %d", name, &dist);
	
	int userAns = countMember(name, dist);

	int ans;
	scanf("%d", &ans);
	
	if (ans != userAns)
	{
		score = 0;
		printf("%s %d\n", name,dist);
		printf("diff:%d\n", ans-userAns);
	}
}

int main()
{

	freopen("0Text.txt", "r", stdin);

	int T, scoreIdx;
	scanf("%d %d", &T, &scoreIdx);
	
	for (int TC = 1; TC <= T; TC++)
	{
		score = scoreIdx;
		
		int cmdL;
		scanf("%d", &cmdL);
		
		for (int cmdIdx = 0; cmdIdx < cmdL; ++cmdIdx)
		{
			int c_num;
			scanf("%d", &c_num);
            // printf("%d\n", cmdIdx);
			
			switch (c_num)
			{
			case INIT: 
				cmd_init(); 
				break;
				
			case ADDMEMBER: 
				cmd_addMember();  
				break;
				
			case GETDISTANCE: 
				cmd_getDistance();  
				break;
				
			case COUNTMEMBER: 
				cmd_countMember();  
				break;
				
			default: 
				break;
			}
		}
		
		printf("#%d %d\n", TC, score == scoreIdx ? scoreIdx : 0);
	}
	return 0;
}
