#include <stdio.h>
#include <stdlib.h>

typedef struct _Node{
	int data;
	struct _Node *next;
} *LinkList,Node;

// 初始化列表
int InitList( LinkList list );
// 尾插法
int add1( LinkList list, int data );
// 头插法
int add( LinkList list, int data );

int main(){
	
	LinkList list;
	InitList( list );	
	while( 1 ){	
		printf("输入999退出\n");
		int num;
		scanf("%d",&num);
		if( num == 999 ){
			break;
		}
		
		add1( list, num );
	}
	LinkList start = list->next;
	while( start ){
	//	LinkList start = list->next;
		printf("%d ",start->data);
		start = start->next;	
	}

	return 0;
}


// 初始化列表
int InitList( LinkList list ){
	if( list == NULL ){
		return 0;
	}
	list->next = NULL;
	return 1;
}
// 头插法O(1)
int add( LinkList list, int data ){
	if( list == NULL ){
		return 0;
	}
	Node* p = (Node*)malloc( sizeof(Node) );
	p->data = data;
	p->next = list->next;
	list->next = p;

	return 1;	
}
// 尾插法 时间复杂度O(N)
int add1( LinkList list, int data ){
	if( list == NULL ){
		return 0;
	}
	
	while( list->next ){
		list = list->next;
	}
	Node* node = (Node*)malloc( sizeof( Node ) );
	node->data = data;
	node->next = NULL;
	list->next = node;
	
	return 1;	
}


