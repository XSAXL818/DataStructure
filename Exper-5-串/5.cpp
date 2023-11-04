#include <stdio.h>
#include <stdlib.h>

typedef struct _Node{
	int id;
	int grade;
	struct _Node* next;
} LNode,*List;

void add( List list, int id, int grade ){
	while( list->next ){
		list = list->next;
	}
	LNode* node = (LNode*)malloc( sizeof( LNode ) );
	node->id = id;
	node->grade = grade;
	node->next = NULL;
	list->next = node;
}

void travel( List list ){
	printf("学生学号\t分数\n");
	while( list->next ){
		list = list->next;
		printf("%d\t%d\n",list->id,list->grade);
	}
	
}

int main(){
	
	LNode list;
	list.next = NULL;
	add( &list, 2111070050, 88 );
	add( &list, 2111070051, 98 );
	add( &list, 2111070052, 89 );
	add( &list, 2111070053, 99 );
	travel( &list );
	return 0;
}