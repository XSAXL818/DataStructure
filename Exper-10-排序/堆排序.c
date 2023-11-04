#include<stdio.h>

// 利用大根堆进行排序，元素按完全二叉树编号，由于从下标0开始所有有所调整
// 根结点i, 左子树：2i+1 右子树 2i+2
void heapSort( int arr[], int len );
// 对数组的index号进行 大根堆调整
void down( int arr[], int len, int index );
int main(){
	
	
	int arr[10];
	int i;
	for( i = 9; i >= 0; i-- ){
		arr[i] = i;
		printf("%d ",arr[i]);
	}
	printf("\n");
	heapSort( arr, 10 );
	for( i = 0; i < 10; i++ ){
		printf("%d ",arr[i]);
	}
	
	
	return 0;
}



// 利用大根堆进行排序，元素按完全二叉树编号，由于从下标0开始所有有所调整
// 根结点i, 左子树：2i+1 右子树 2i+2
void heapSort( int arr[], int len ){
	printf("2\n");
	// 将数组初始化为一个大根堆
	int i = (len - 1) / 2;// i指向最后一个元素的父节点
	for( ; i >= 0; i-- ){
		printf("i=%d\n",i);
		down( arr, len, i );// 把编号为i的根结点调整为一个大根堆
	}		
	printf("1\n");													// 数组 ---------------------******************
	
	// 基于选择排序，将大根堆的最大值插入到大根堆的后一位                     大根堆			已排序
	for( i = len-1; i > 0; i-- ){// 每次插入的位置为i
		// 把大根堆的最大值放入已排好序的前端
		int t = arr[0];
		arr[0] = arr[i];
		arr[i] = t;
		// 加入新元素后，调整为大根堆
		down( arr, i, 0 );
	}
}
// 对数组的index号进行 大根堆调整
void down( int arr[], int len, int index ){
	
	int t = arr[index];
	int parent,child;
	for( parent = index; parent*2 + 1 <= len-1; parent = child ){// parent*2 + 1 为其左孩子，若该值大于len-1,则说明没有左孩子
		child = parent*2 + 1;// 先获取左孩子的下标
		if( child != len-1 && arr[child] < arr[child+1] ){// 先	确保有右子树，r然后找到孩左右子中的最大值
			child++;
		}
		if( t > arr[child] ){// 满足大根堆
			break;
		} else {// 基于插入排序，将最大值的孩子结点放在其父节点
			arr[parent] = arr[child];
		}
	}
	arr[parent] = t;// 完全二叉树的根结点找到使其为大根堆的结点
	
}