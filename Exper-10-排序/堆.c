#include<stdio.h>
#include<stdlib.h> 
#include<assert.h>
#include<time.h>
#define ElemType int
#define Status int
#define OK 1
#define ERROR 0

// 最小堆，即每个根结点的值小于其左右孩子的值
// 所存储的值已完全二叉树的形式存储
// 完全二叉树的特性：i*2 是i的左孩子, i*2+1 是i的右孩子
typedef struct{
	ElemType* data;// 指定的一维数组,分配空间应为maxSize+1，同时下标为零的数可以保存机器最小数
	int maxSize;// 可存储最大元素的个数
	int length;// 当前堆内元素的个数
} MinHeap;
// 创建一个空堆
MinHeap* creatMinHeap(int maxSize);
// 给一个数组，建立一个最小堆
MinHeap* creatMinHeap1( int arr[], int len );
// 辅助上个函数,按完全二叉树的形式，将第i个根结点调整为最小堆
void down( MinHeap* minHeap, int index );
// 判断堆是否为空
Status isEmpty( MinHeap* minHeap );
// 向堆中插入元素
Status insert( MinHeap* minHeap, ElemType e );
// 删除堆中最小值,并返回
ElemType deleteMin( MinHeap* minHeap );


int arr[500000];
int main(){
	
	clock_t start_t,end_t;
	int len = 0;
	int i,j;
	for( i = 500000; i > 0; i-- ){
		arr[i] = i;
	}
	start_t = clock();
	printf("快速排序启动，start_t = %ld\n", start_t);
	
	MinHeap* minHeap = creatMinHeap1( arr, 500000 );
	for( i = 1; i <= 500000; i++ ){
//		printf("%d\n",deleteMin( minHeap ));
		deleteMin( minHeap );
	}
	
	end_t = clock();
	printf("结束，end_t = %ld\n", end_t);
	printf("%lf\n",(double)(end_t - start_t) / CLOCKS_PER_SEC);
//	MinHeap* minHeap = creatMinHeap1( arr, 10 );
//	for( i = 1; i <= 10; i++ ){
//		printf("%d\n",deleteMin( minHeap ));
//	}
	
	
	return 0;
}


// 创建一个空堆
MinHeap* creatMinHeap(int maxSize){
	MinHeap* heap = (MinHeap*)malloc( sizeof( MinHeap ) );
	if( heap == NULL ){
		return NULL;
	}
	// 初始化
	heap->data = (ElemType*)malloc( (maxSize+1)*sizeof(ElemType) );// 分配maxSize+1空间：因为数组下标为0不存放元素
	if( heap->data == NULL ){
		free( heap );
		return NULL;
	}
	heap->data[0] = -9999999;
	heap->maxSize = maxSize;
	heap->length = 0;// 由于完全二叉树从数组下标1开始，所以便于后续操作，length应该指向待插入新元素的下标，此时堆中元素个数为length-1
	return heap;
}
// 给一个数组，建立一个最小堆
// 思路，从完全二叉树的倒数第二层的最右边一个根结点开始，依次按从右到左，从下到上的顺序，调整
// 基于：如果根结点的左右堆是最小堆，则只需对
MinHeap* creatMinHeap1( int arr[], int len ){
	MinHeap* minHeap = creatMinHeap( len );
	minHeap->length = len;
	int i;
	// 将所有值按顺序复制到最小堆中
	for( i = 0; i < len; i++ ){
		minHeap->data[i+1] = arr[i];
	}
	i = minHeap->length/2;// 此为开始调整的结点
	for( ; i > 0; i-- ){
		down( minHeap, i );
	}
	
	return minHeap;
}
// 辅助上个函数,按完全二叉树的形式，将第i个根结点调整为最小堆
void down( MinHeap* minHeap, int index ){// 操作与删除异曲同工
	
	ElemType t = minHeap->data[index];
	int parent,child;
	for( parent = index; parent*2 <= minHeap->length; parent = child ){
		child = parent*2;
		if( parent != minHeap->length && minHeap->data[child] < minHeap->data[child+1] ){
			child++;
		}
		if( t > minHeap->data[child]  ){// 不是最小堆，将child的值移至parent,然后下次从child开始调整
			minHeap->data[parent] = minHeap->data[child];
		} else {// 符合最小堆
			break;
		}
	}
	// 插入到跟结点
	minHeap->data[parent] = t;
}
// 判断堆是否为空
Status isEmpty( MinHeap* minHeap ){
	assert( minHeap!=NULL );
	if( minHeap->length == 0 ){
		return OK;
	} else {
		return ERROR;
	}
}
// 向堆中插入元素
// 将新元素按完全二叉树插入到数组的最后一位，然后从其为起点，依次对其父母结点进行最小二叉堆的更新,结束标志为出现一个父节点符合最小堆
Status insert( MinHeap* minHeap, ElemType e ){
	assert( minHeap != NULL );
	if( minHeap->maxSize == minHeap->length ){// 堆满
		return ERROR;
	}
	int i = ++minHeap->length;// 此时在逻辑上将新元素放置在数组尾部
	for( ; e < minHeap->data[i/2]; i/=2 ){// 当找到根结点大于新元素时，根结点移至孩子结点 判断条件不溢出用到了哨兵,i/=2为找根结点
		minHeap->data[i] = minHeap->data[i/2];
	}
	// 循环结束，i指向
	minHeap->data[i] = e;
	return OK;
}
// 删除堆中最小值,并返回
// 删除头部，拿数组最后一个补充，然后调整
ElemType deleteMin( MinHeap* minHeap ){
	assert( minHeap != NULL );
	assert( minHeap->length != 0 );
	
	ElemType min = minHeap->data[1];// 去除最小值
	int t = minHeap->data[minHeap->length--];// 物理上删除堆中最后一个元素，逻辑上将其放入堆的第一个元素
	int parent,child;
	// 将最后一个元素从堆以完全二叉树的形式逐渐下沉，循环结束找到最后一个元素需插入的位置
	for( parent = 1; parent*2 <= minHeap->length; parent = child ){// 从根结点开始，判断条件：如果根结点的孩子结点不存在，则找到要插入的位置。
		child = parent*2;// 指向左孩子
		// 找到左右孩子的最小值的下标
		if( child != minHeap->length && minHeap->data[child] > minHeap->data[child+1] ){// 根结点如果有右孩子，则进行比较
			child++;// 指向根结点的右孩子
		}
		// 接下来看是否符合最小堆
		if( t <= minHeap->data[child] ){// 根结点比左右孩子最小值还小，符合最小堆,则结束
			break;
		} else {
			minHeap->data[parent] = minHeap->data[child];// 将根结点最小值前移
		}
	}
	// 插入到根结点
	if( minHeap->length != 0 ){
		minHeap->data[parent] = t;
	}
	
	return min;
}