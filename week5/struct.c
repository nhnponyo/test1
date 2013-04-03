#include <stdio.h>

struct human;
struct human
{
	int id;
	char name[64];
	//struct human lover;
	struct human *lover;
};

int main()
{
	struct human stlk = {1,"sinzzang",NULL};
	struct human naru = {2,"narci", &naru};
	struct human *lover1;
	struct human *lover2;
	char* l2name;
	stlk.lover = &naru;
	lover1 = stlk.lover;
	lover2 = lover1->lover;
	l2name = lover2->name;

	printf("%s\n", l2name);
}
