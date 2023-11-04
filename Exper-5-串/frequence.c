#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define maxSize 100
typedef struct _Node{
	char c; 
	int num;	
} Node;

typedef struct{
	Node* arr;// 数组，每个元素保存字符及其出现的次数
	int num;// 保存字符的个数
} List;

typedef struct _LNode{
	int index;
	struct _LNode* next;
} LNode;

typedef struct{
	LNode* arr;

} SList;

void addElem( LNode* list, int index ){
	list->index = 1;
	while( list->next ){
		list = list->next;
	}
	LNode* node = (LNode*)malloc( sizeof( LNode ) );
	node->index = index;
	node->next = NULL;
	list->next = node;
}

SList* creatSList( List* list ){
	SList* slist = (SList*)malloc( sizeof( SList ) );
	slist->arr = ( LNode* )malloc( maxSize * sizeof( LNode ) );

	int i;
	for( i = 0; i< maxSize; i++ ){
		slist->arr[i].index = -1;
		slist->arr[i].next = NULL;
	}
	for( i = 0; i < list->num; i++ ){
		addElem( slist->arr+list->arr[i].num, i );
	}
	return slist;
}

List* creatList(void){
	List* list = (List*)malloc( sizeof(List) );
	list->num = 0;
	list->arr = (Node*)malloc( maxSize * sizeof(Node) );
	return list;
}


void add( List* list, char c){
	int i = 0;
	while( i < list->num ){
		if( list->arr[i].c == c ){// 字符已存在
			list->arr[i].num++;
			return ;
		}
		i++;
	}
	list->arr[i].c = c;
	list->arr[i].num = 1;
	list->num++;
}
void printSList( SList* slist, List* list ){
	int i = maxSize-1;
	int cnt = 0;
	LNode* start;
	while( i > 0  ){
	
		if( slist->arr[i].index == -1 ){
			
		} else {
			start = slist->arr + i;
			while( start->next ){
				start = start->next;
				int index = start->index;
				char c = list->arr[index].c;

				printf("%c-%d", c, i);
				cnt++;
				if( cnt == 4 ){
					printf("\n");
					cnt = 0;
				} else {
					printf(" ");
				}	
			}
		}
		
		i--;
	}
}


int main(){
	
	List* list= creatList();
	char str[10000];
	gets( str );
	int len = strlen( str );
	int i = 0;
	while( i < len ){
		add( list, str[i] );
		i++;
	}

	SList* slist = creatSList( list );
	printSList( slist, list );

	
	
	
	return 0;
}