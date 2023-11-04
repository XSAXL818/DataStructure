#include <stdio.h>
#include <stdlib.h>
// 目前所知：用于解决没有指针的编程语言,实现具有链式结构的线性表
// next == -1 表示该元素为尾元素 next == 0 表示该元素无值 
// 元素序号不是所在下标，为链接的第n个
typedef struct{
	int data;
	int next;
} *SLinkList,Node;
// 创建一个静态链表
SLinkList creatSLinkList( int maxSize );
// 向静态链表中添加元素,成功返回其所在下标
int addElem( SLinkList list, int data, int maxSize );
// 找到静态链表中的第一个元素
int getIndexOfEmpty( SLinkList list,int maxSize );
// 按下标依次遍历
void printList( SLinkList list );
// 删除指定序号的元素,删除成功元素返回1，否则返回0
int deleteElemAtIndex( SLinkList list, int index );
// 删除指定数值的元素,删除成功元素返回1，否则返回0
int deleteElemAtNum( SLinkList list, int dest );

int main(){
	int maxSize = 20;
	int i;
	SLinkList list = creatSLinkList( maxSize );
//	int index = getIndexOfEmpty( list, maxSize );
	addElem( list, 1, maxSize );
	addElem( list, 4, maxSize );
	addElem( list, 3, maxSize );
	addElem( list, 8, maxSize );
	deleteElemAtIndex( list, 4 );
	addElem( list, 10, maxSize );
	deleteElemAtIndex( list, 8 );
	addElem( list, 11, maxSize );
	deleteElemAtIndex( list, 1 );
	addElem( list, 8, maxSize );

	deleteElemAtNum( list, 5 );
	
	addElem( list, 7, maxSize );
	printList( list );
	for( i = 0; i < maxSize; i++ ){
		printf("%d ",list[i].data);
	}
	printf("\n");
	for( i = 0; i < maxSize; i++ ){
		printf("%d ",list[i].next);
	}
	printf("\n");
	return 0;
}
// 创建一个静态链表
SLinkList creatSLinkList( int maxSize ){
	SLinkList list = (Node*)malloc( maxSize * sizeof(Node) );
	list[0].next = -1;
	int i;
	for( i = 1 ; i < maxSize; i++ ){
		list[i].next = 0;
	}
	return list;
}
// 向静态链表中添加元素,成功返回其所在下标,失败返回-1
int addElem( SLinkList list, int data, int maxSize ){
	int index = getIndexOfEmpty( list, maxSize );
	if( index == -1 ){
		return -1;
	} else if( index == 0 ){
		list[0].next = 1;
		list[1].data = data;
		list[1].next = -1;
	} else {
		// 找到尾元素
		int start = list[0].next;
		while( list[start].next != -1 ){
			start = list[start].next;	
		}
		list[start].next = index;
		list[index].data = data;
		list[index].next = -1;
	}
	return index;
}
// 找到静态链表中的第一个元素,找到返回该元素下标,满了返回-1，无元素返回0
int getIndexOfEmpty( SLinkList list, int maxSize ){
	if( list[0].next == -1 ){
		return 0;
	}
	int i;
	for( i = 1; i < maxSize; i++ ){
		if( list[i].next == 0 ){
			return i;
		}
	}
	return -1;
}
// 按下标依次遍历
void printList( SLinkList list ){
	int start = list[0].next;
	while( start > 0 ){
		printf("%d ",list[start].data);
		start = list[start].next;
	}
	printf("\n");
}
// 删除指定序号的元素,删除成功元素返回1，否则返回0
int deleteElemAtIndex( SLinkList list, int index ){
	int i = 1;
	int start = 0;
	while( i < index ){
		if( list[start].next == -1 ){
			return 0;
		}
		start++;
		i++;
	}
	int di = list[start].next;
	list[start].next = list[di].next;
	list[di].next = 0;
	return 1;
}
// 删除指定数值的元素,删除成功元素返回1，否则返回0
int deleteElemAtNum( SLinkList list, int dest ){
	int start = 0;
	while( list[start].next > 0 ){
		if( list[list[start].next].data == dest ){
			int di = list[start].next;
			list[start].next = list[di].next;
			list[di].next = 0;
			return 1;
		}
		start = list[start].next;
	}
	return 0;
}

