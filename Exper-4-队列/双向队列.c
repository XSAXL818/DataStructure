#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define ERROR 0
#define OK 1
#define Status int
#define ElemType int

//  双向队列: 允许两端都可以进行入队和出队操作的队列
//  front 指向对头  rear 指向队尾后一个位置
//  front == rear  空队列  (front + 1) % maxSize == rear 队列满
typedef struct{
	ElemType* data;
	int front;
	int rear;
	int maxSize;
} DeQueue;
// 创建一个队列
DeQueue* creatDeQueue( int maxSize );
// 摧毁一个队列
Status destoryDeQueue( DeQueue* que );
// 向对头添加元素
Status addByFront( DeQueue* que, ElemType e );
// 向队尾添加元素
Status addByRear( DeQueue* que, ElemType e );
// 从队头开始访问已有元素
void printDeQueue( DeQueue* que );
// 队头删除元素,并返回
Status deByFront( DeQueue* que, ElemType* e );
// 队尾删除元素,并返回
Status deByRear( DeQueue* que, ElemType* e );
// 获取队列长度
int getDeLength( DeQueue* que );
// 清空队列
Status clearDeQueue( DeQueue* que );
// 得到队头
Status getHead( DeQueue* que, ElemType* e );
// 得到队尾
Status getTail( DeQueue* que, ElemType* e );
// 判断队列是否为空
Status isEmpty( DeQueue* que );
// 界面化
// 菜单
int view( DeQueue* que );
int main(){
	// 创建双向队列
	DeQueue* que = creatDeQueue( 7 );
	// 用于数据的输入与输出
	ElemType e;
	// 进入操作界面
	while( 1 ){
		int select = view(que);
//	1.插入队头	2.插入队尾	3.删除队头	4.删除队尾
//	4.获取队头	5.获取队尾  6.清空队列
		switch( select ){
			case 1:
				printf("请输入要插入的数据：\n");
				scanf("%d",&e);
				if( addByFront( que, e ) ){
					printf("-----插入成功-----\n");
				} else {
					printf("-----插入失败-----\n");
				}
				break;
			case 2:
				printf("请输入要插入的数据：\n");
				scanf("%d",&e);
				if( addByRear( que, e ) ){
					printf("-----插入成功-----\n");
				} else {
					printf("-----插入失败-----\n");
				}
				break;
			case 3:
				if( deByFront( que, &e ) ){
					printf("\n-----%d已删除-----\n",e);
				} else {
					printf("-----删除失败-----\n");
				}
				break;
			case 4:
				if( deByRear( que, &e ) ){
					printf("\n-----%d已删除-----\n",e);
				} else {
					printf("-----删除失败-----\n");
				}
				break;
			case 5:
				if( getHead( que, &e ) ){
					printf("-----队头为%d-----\n",e);
				} else {
					printf("-----查询失败-----\n");
				}
				break;
			case 6:
				if( getTail( que, &e ) ){
//					printf("front=%d rear=%d\n",que->front,que->rear);
					printf("-----队尾为%d-----\n",e);
				} else {
					printf("-----查询失败-----\n");
				}
				break;
			case 7:
				clearDeQueue( que );
				break;
		}
		if( select == 8 ){
			break;
		}
	}


	return 0;
}

// 创建一个队列
DeQueue* creatDeQueue( int maxSize ){
	if( maxSize < 1 ){
		return NULL;
	}
	DeQueue* queue = (DeQueue*)malloc( sizeof(DeQueue) );
	if( queue == NULL ){
		return NULL;
	}
	queue->data = (ElemType*)malloc( maxSize * sizeof(ElemType) );
	if( queue->data == NULL ){
		return NULL;
	}
	queue->maxSize = maxSize;
	// 初始化队列为空
	queue->front = 0;
	queue->rear = 0;
	return queue;
}
// 摧毁一个队列
Status destoryDeQueue( DeQueue* que ){
	if( que == NULL ){
		return ERROR;
	}
	while( --que->maxSize ){
		free( que->data + que->maxSize );
	}
	free( que );
	return OK;
}
// 向对头添加元素
Status addByFront( DeQueue* que, ElemType e ){
	if( que == NULL ){
		return ERROR;
	}
	// 判断是否队列已满：对头前一个位置是否为队尾
	if( que->front - 1 >= 0 ){
		if( que->front-1 == que->rear ){
			return ERROR;
		} else {
			// front前移一位
			que->front--;
		}
	} else {
		if( (que->front - 1 + que->maxSize) == que->rear ){
			return ERROR;
		} else {
			// front前移一位
			que->front = que->front - 1 + que->maxSize;
		}
	}
	// 向队头加入新元素
	que->data[que->front] = e;
	return OK;
}
// 向队尾添加元素
Status addByRear( DeQueue* que, ElemType e ){
	if( que == NULL ){
		return ERROR;
	}
	// 判断是否队列已满
	if( (que->rear + 1) % que->maxSize == que->front ){
		return ERROR;
	}
	que->data[que->rear] = e;
	que->rear = (que->rear + 1) % que->maxSize;
	return OK;
}
// 从左到右访问已有元素
void printDeQueue( DeQueue* que ){
	int i;
	for( i = que->front; i != que->rear; i = (i + 1)%que->maxSize ){
		printf("%d ",que->data[i]);
	}
	printf("\n");
}
// 队头删除元素
Status deByFront( DeQueue* que, ElemType* e ){
	if( que == NULL ){
		return ERROR;
	}
	// 判空
	if( que->front == que->rear ){
		return ERROR;
	}
	// 删除后，队头向后移一位
	*e = que->data[que->front];
	que->front = (que->front + 1) % que->maxSize;
	return  OK;
}
// 队尾删除元素
Status deByRear( DeQueue* que, ElemType* e ){
	if( que == NULL ){
		return ERROR;
	}
	// 判空
	if( que->front == que->rear ){
		return ERROR;
	}
	// 删除:队尾向前移一位
	if( que->rear - 1 >= 0 ){
		que->rear--;
	} else {
		que->rear = que->rear - 1 + que->maxSize;
	}
	*e = que->data[que->rear];
	return OK;
}
// 获取队列长度
int getDeLength( DeQueue* que ){
	assert( que != NULL );
	
	if( que->rear >= que->front ){
		// 元素在中间
		return que->rear - que->front;
	} else {
		// 元素在两端
		return que->rear - que->front + que->maxSize;
	}
	
}
// 清空队列
Status clearDeQueue( DeQueue* que ){
	if( que == NULL ){
		return ERROR;
	}
	que->front = que->rear = 0;
	return OK;
}
// 得到队头
Status getHead( DeQueue* que, ElemType* e ){
	if( que == NULL || e == NULL ){
		return ERROR;
	}
	if( que->front == que->rear ){
		return ERROR;
	}
	*e = que->data[que->front];
	return OK;
}
// 得到队尾
Status getTail( DeQueue* que, ElemType* e ){
	if( que == NULL || e == NULL ){
		return ERROR;
	}
	if( que->front == que->rear ){
		return ERROR;
	}
	if( que->rear == 0 ){
		*e = que->data[que->maxSize-1];
	} else {
		*e = que->data[que->rear-1];
	}
	return OK;
}
// 判断队列是否为空
Status isEmpty( DeQueue* que ){
	assert( que != NULL );
	if( que->front == que->rear ){
		return OK;
	} else {
		return ERROR;
	}
}

// 菜单
int view( DeQueue* que ){
	printf("\n********************\n");
	if( !isEmpty( que ) ){
		printf("总共有%d个数据\n",getDeLength( que ));
		printDeQueue( que );
	} else {
		printf("当前无数据\n");	
	}
	printf("********************\n\n");
	printf("请选择以下功能:\n");
	printf("1.插入队头\t2.插入队尾\t3.删除队头\t4.删除队尾\n");
	printf("5.获取队头\t6.获取队尾\t7.清空队列\t8.退出\n");
	int select;
	scanf("%d",&select);
	return select;
}


