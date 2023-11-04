#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define ElemType Info 
#define Status int
#define OK 1
#define ERROR 0
// 队列-实现一个简易订单系统-使用顺序存储
//   0            1     2    3        4       // 此时队列满,(4+1) % 5 == 0  
//  对头(人1)    人2   人3  人4     队尾(无人)
// 人员信息：排队号-时间
typedef struct{
	int number;// 票号
	char* ttime;// 购票时间
} Info;
// 队列 
// 队列空：front == rear
// 队列满：存在一个空位,便于判断队列是否满了，已满即front下标后移一位等于rear
typedef struct{
	int maxSize;// 队列最大长度
	int rear;// 队尾-最后一个人的下标的后一位
	int front;// 对头-第一个人的下标,
	ElemType* info;// 数据域
} Queue;
// 创建一个队列：参数为初始化队列的最大长度
Queue* creatQueue( int maxSize );
// 摧毁队列
Status destoryQueue( Queue* queue );
// 判断队列是否为空
Status isEmpty( Queue* queue );
// 向队尾插入元素
Status enQueue( Queue* queue, char* ttime, int number );
// 清空队列
Status clearQueue( Queue* queue );
// 访问单个数据域
void visit( ElemType* elem );
// 访问队列
void printQueue( Queue* queue );
// 返回队头元素
ElemType* getHead( Queue* queue );
// 返回队列元素个数
int getLength( Queue* queue );
// 删除队头元素,并返回
ElemType* deQueue( Queue* queue );

//  界面化设计
// 菜单
int view( Queue* queue );

int main(){
	// 时间，队列申明
	time_t curtime;
	Queue* queue = creatQueue( 5 );
	char* ttime1;
	ElemType* e;
	// 进入操作界面
	while( 1 ){
		int select = view(queue);
	//1.创建新订单     2.出单    3.获取第一个订单信息    4.清空所有订单
		switch( select ){
			case 1:
				time( &curtime );
				ttime1 = (char*)malloc( 30*sizeof(char) );
				strcpy( ttime1, ctime(&curtime) );
				if( enQueue( queue, ttime1, queue->rear ) ){
					printf("-----新订单已创建-----\n");
				} else {
					printf("-----创建失败-----\n");
				}
				break;
			case 2:
				getchar();
				e = deQueue( queue );
				if( e != NULL ){
					printf("-----序号为%d已出单-----\n",e->number);
				} else {
					printf("-----出单失败-----\n");
				}
				break;
			case 3:
				e = getHead( queue );
				if( e != NULL ){
					printf("\n-----第一个订单的信息为：-----\n");
					visit( e );
				} else {
					printf("-----获取失败-----\n");
				}
				break;
			case 4:
				if( clearQueue( queue ) ){
					printf("-----订单已清除!-----\n");
				} else {
					printf("-----操作失败-----\n");
				}
				break;
		}
		if( select == 5 ){
			break;
		}
	}
	
	return 0;
}

// 创建一个队列：参数为初始化队列的最大长度
Queue* creatQueue( int maxSize ){
	if( maxSize < 2 ){
		return NULL;
	}
	// 初始化队列
	// 分配队列所需空间
	Queue* queue = (Queue*)malloc( sizeof(Queue) );
	if( queue == NULL ){
		return NULL;
	}
	queue->info = (ElemType*)malloc( maxSize * sizeof(ElemType) );
	if( queue->info == NULL ){
		free( queue );
		return NULL;
	}
	// 分配成功，初始化队列
	queue->maxSize = maxSize;
	queue->front = 0;
	queue->rear = 0;
	return queue;
}
// 摧毁队列*
Status destoryQueue( Queue* queue ){
	if( queue == NULL ){
		return ERROR;
	}
	free( queue->info );
	free( queue );

	return OK;
}
// 清空队列
Status clearQueue( Queue* queue ){
	assert( queue != NULL );
	queue->front = queue->rear;
	return OK;
}
// 判断队列是否为空
Status isEmpty( Queue* queue ){
	// queue != NULL 则不报错
	assert( queue != NULL );
	// 空
	if( queue->front == queue->rear ){
		return OK;
	}
	// 不空
	return ERROR;
}
// 向队尾插入元素
Status enQueue( Queue* queue, char* ttime, int number ){
	if( queue == NULL ){
		return ERROR;
	}
	// 判断队列是否已满
	if( (queue->rear + 1) % queue->maxSize == queue->front ){
		return ERROR;
	}
	queue->info[queue->rear].number = number;
	queue->info[queue->rear].ttime = ttime;
	queue->rear = (queue->rear + 1) % queue->maxSize;
	return OK;
}
// 访问单个数据域
void visit( ElemType* elem ){
	printf("序号：%d\t时间：%s",elem->number,elem->ttime);
}
// 从头访问队列元素
void printQueue( Queue* queue ){
	assert( queue != NULL );
	int i;
	for( i = queue->front; i != queue->rear; i = (i + 1)%queue->maxSize ){
		visit( queue->info + i );
		printf("\n");
	}
	
}
// 返回队头元素
ElemType* getHead( Queue* queue ){
	assert( queue != NULL );
	if( queue->front == queue->rear ){
		return NULL;
	}
	return queue->info + queue->front;
}
// 返回队列元素个数
int getLength( Queue* queue ){
	assert( queue != NULL );
	
	if( queue->rear >= queue->front ){
		// 元素在中间
		return queue->rear - queue->front;
	} else {
		// 元素在两端
		return queue->rear - queue->front + queue->maxSize;
	}
	
}
// 删除队头元素,并返回
ElemType* deQueue( Queue* queue ){
	assert( queue != NULL );	
	if( queue->rear == queue->front ){
		return NULL;
	}
	int index = queue->front;
	queue->front = (queue->front + 1) % queue->maxSize;
	return queue->info + index;
}
// 菜单
int view( Queue* queue ){
	printf("\n********************\n");
	if( !isEmpty(queue) ){
		printf("总共有%d个订单\n",getLength(queue));
		printQueue( queue );
	} else {
		printf("总共有%d个订单\n",getLength(queue));	
	}
	printf("********************\n\n");
	printf("请选择以下功能:\n");
	printf("1.创建新订单\t2.出单\t3.获取第一个订单信息\n4.清空所有订单\n");
	int select;
	scanf("%d",&select);
	return select;
}


