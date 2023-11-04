#include <stdio.h>
#include <stdlib.h>

#define ERROR 0
#define OK 1
#define Status int
#define MaxSize 100

// 链表--头插--带头结点
typedef struct _LNode{
	int data;
	struct _LNode* next;
} LNode,*List;
// 索引表单个元素
typedef struct{
	int maxValue;// 链表中最大值
	List list;// 存储的元素
} Elem;
// 索引表
typedef struct{
	Elem* index;// 索引
	int length;// 长度
} IndexList;


//****************链表*********************
int insert( List list, int data );// 插入
int dele( List list, int data );// 删除
void destory( List list );// 摧毁
LNode* findValue( List list, int data );// 查找
//****************链表*********************
// 创建一个索引表
IndexList* creatIndex(void);
// 向索引表中插入一个数
int insertValue( IndexList* iList, int key );
// 找到数在索引表应在分块的下标---二分查找
int binSearch( IndexList* iList, int key );
// 删除
int deleValue( IndexList* iList, int key );
// 查找
int find( IndexList* iList, int key );
int main(){
	
	
	IndexList* list = creatIndex();
	int i,num,select;
	int dic = 1;
	while( 1 ){
		dic = 1;
		printf("块：      ");
		for( i = 0; i < list->length; i++ ){
			printf("%d\t",list->index[i].maxValue);
		}
		printf("\n");
		LNode* n1,*n2,*n3,*n4,*n5;
		n1 = list->index[0].list->next;
		n2 = list->index[1].list->next;
		n3 = list->index[2].list->next;
		n4 = list->index[3].list->next;
		n5 = list->index[4].list->next;
		while( n1 || n2 || n3 || n4 || n5 ){
			if( dic ){
				printf("块内元素: ");
				dic = 0;
			} else {
				printf("          ");
			}
			
			if( n1 ){
				printf("%d\t",n1->data);
				n1 = n1->next;
			} else {
				printf("\t");
			}
			if( n2 ){
				printf("%d\t",n2->data);
				n2 = n2->next;
			} else {
				printf("\t");
			}
			if( n3 ){
				printf("%d\t",n3->data);
				n3 = n3->next;
			} else {
				printf("\t");
			}
			if( n4 ){
				printf("%d\t",n4->data);
				n4 = n4->next;
			} else {
				printf("\t");
			}
			if( n5 ){
				printf("%d\t",n5->data);
				n5 = n5->next;
			} else {
				printf("\t");
			}
			printf("\n");
		}
		printf("\n请选择功能：1.查找\t2.插入\t3.删除\n");
		scanf("%d",&select);
		switch( select ){
			case 1:
				printf("请输入要查找的值:\n");
				scanf("%d",&num);
				if( find( list, num ) ){
					printf("存在!\n");
				} else {
					printf("不存在!\n");
				}
				break;
			case 2:
				printf("请输入要插入的值:\n");
				scanf("%d",&num);
				insertValue( list, num );
				break;
			case 3:
				printf("请输入要删除的值:\n");
				scanf("%d",&num);
				deleValue( list, num );
				break;
		}
	}
	
	printf("%d\n",find( list, 56 ));
	return 0;
}
//****************链表*********************
int insert( List list, int data ){// 插入
	LNode* node = (LNode*)malloc( sizeof(LNode) );
	node->data = data;
	node->next = list->next;
	list->next = node;
	return 1;
}
int dele( List list, int data ){// 删除

	if( list->next == NULL ){
		return 0;
	}

	LNode* start = list;
	while( start->next ){
		if( start->next->data == data ){
			LNode* t = start->next;
			start->next = t->next;
			free( t );
			return 1;
		}
		start = start->next;
	}

	return 0;
}
void destory( List list ){// 摧毁

	LNode* start = list;
	while( list ){
		start = list;
		list = list->next;
		free( start );
	}
}

LNode* findValue( List list, int data ){// 查找
	LNode* start = list->next;
	while( start ){
		if( start->data == data ){
			return start;
		}
		start = start->next;
	}
	return NULL;
}
//****************链表*********************

// 创建一个索引表
IndexList* creatIndex(void){
	IndexList* indexList = (IndexList*)malloc(sizeof(IndexList));
	indexList->index = (Elem*)malloc( 5*sizeof(Elem) );
	indexList->length = 5;
	int i,cnt = 0;
	for( i = 60; i <= 100; i += 10 ){
		LNode* node = (LNode*)malloc(sizeof(LNode));
		node->next = NULL;
		indexList->index[cnt].list = node;
		indexList->index[cnt++].maxValue = i;
	}
	int arr[] = { 60, 56, 59, 63, 69, 73, 75, 79, 89, 94, 95, 88, 78, 82 };
	int len = sizeof(arr)/sizeof(arr[0]);
	for( i = 0; i < len; i++ ){
		insertValue( indexList, arr[i] );
	}
	return indexList;
}
// 向索引表中插入一个数
int insertValue( IndexList* indexList, int key ){
	int i = binSearch( indexList, key );
	if( i == - 1 ){// 不存在块中
		return 0;
	}
	insert( indexList->index[i].list, key );
	return 1;
}
// 找到数在索引表应在分块的下标---二分查找
int binSearch( IndexList* indexList, int key ){
	
	if( key > indexList->index[indexList->length-1].maxValue ){
		return -1;
	}
	
	int low = 0,high = indexList->length-1;
	int mid;
	Elem* arr = indexList->index;
	do{
		mid = ( low + high ) / 2;
		if( key > arr[mid].maxValue ){
			low = mid + 1;
		} else if( key < arr[mid].maxValue ){
			high = mid - 1;//           0     1    2     3      4
		} else {//                     60    70    80    90    100  
			return mid;//    65                    2
		}//								0	
	}while( low <= high );//                  1
	//                                 high  low
	return low;// data在low所指定的块内
	
}
// 删除
int deleValue( IndexList* indexList, int key ){
	if( key > indexList->index[indexList->length-1].maxValue ){
		return 0;
	}
	int i = binSearch( indexList, key );
	if( i == -1 ){
		return 0;
	}
	if( dele( indexList->index[i].list, key ) ){
		return 1;
	}
	return 0;
}
// 查找
int find( IndexList* indexList, int key ){
	int i = binSearch( indexList, key);
	if( i == -1 ){
		return 0;
	}
	if( findValue( indexList->index[i].list, key ) ){
		return 1;
	}
	return 0;
}