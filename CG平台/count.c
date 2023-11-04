#include <stdio.h>
#include <stdlib.h>

typedef struct{
	int cnt;
	int number;
} Node;

typedef struct{
	Node* data;
	int length;
} List;

void addElem( List* list, int number ){
	int i;
	// 遍历列表，找寻是否已存在该数字
	for( i=0; i < list->length; i++ ){
		if( number == list->data[i].number ){
			list->data[i].cnt++;
			break;
		}
	}
	// 该数字第一次出现
	if( i == list->length ){
		list->data[i].number = number;
		list->data[i].cnt = 1;
		list->length++;
	}
}

int main(){
	// 读取数字,列表初始化
	int n;
	scanf("%d",&n);
	List list;
	list.length = 0;
	list.data = (Node*)malloc( n*sizeof(Node) );
	int t;
	while( n ){
		scanf("%d",&t);
		addElem( &list, t );
		n--;
	}
	int index = 0;
	for( t=0; t < list.length; t++ ){ 
		if( list.data[t].cnt > n ){
			// 保存最大出现次数
			n = list.data[t].cnt;
			// 保存出现次数最多数的下标
			index = t;
		}
	}
	printf("%d",list.data[index].number);
	return 0;
}