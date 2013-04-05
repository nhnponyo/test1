#include "def.h"

#if TEMPLATE_STRUCTURES

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct humanBeing {
	char	name[10];
	int		age;
	float	salary;
} humanBeing_t;

typedef struct list {
	char data;
	struct list *next;
} list_t;

//
// call by value로 두 사람의 정보를 입력받아서 두 사람의 아니, 급여, 이름이 같은지 검사하는 함수
//
int humansEqualByCallByValue(humanBeing_t person1, humanBeing_t person2)
{
	//
	// 채울 부분
	//
	// 두 사람의 age, 급여, 이름이 모두 같으면 1을 return
	// 하나라도 다르면 0을 return
	//

	return 1;
}

//
// call by reference로 두 사람의 정보를 입력받아서 두 사람의 아니, 급여, 이름이 같은지 검사하는 함수
//
int humansEqualByCallByReference(humanBeing_t *person1, humanBeing_t *person2)
{
	//
	// 채울 부분
	//
	// 두 사람의 age, 급여, 이름이 모두 같으면 1을 return
	// 하나라도 다르면 0을 return
	//

	return 1;
}


void testStructures(void)
{
	humanBeing_t	person1, person2;

	strcpy(person1.name, "kim");
	person1.age = 30;
	person1.salary = 200;

	strcpy(person2.name, "kim");
	person2.age = 30;
	person2.salary = 200;

	if(humansEqualByCallByValue(person1, person2)) {
		printf("두 사람은 이름, 나이, 급여가 같음\n");
	}
	else
		printf("두사람은 나이, 급여, 이름 중 하나가 다름\n");

	if(humansEqualByCallByReference(&person1, &person2)) {
		printf("두 사람은 이름, 나이, 급여가 같음\n");
	}
	else
		printf("두사람은 나이, 급여, 이름 중 하나가 다름\n");

}

void	testSelfReferentialStrucutures(void)
{
	list_t	item1, item2, item3;
	list_t	*tmpItem;

	item1.data = 'a';
	item2.data = 'b';
	item3.data = 'c';

	item1.next = &item2;
	item2.next = &item3;
	item3.next = NULL; 

	tmpItem = &item1;

	while(tmpItem) {
		printf("item: %c\n", tmpItem->data);
		tmpItem = tmpItem->next;
	}
}



#endif // TEMPLATE_STRUCTURES
