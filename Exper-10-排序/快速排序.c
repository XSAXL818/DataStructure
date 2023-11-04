#include<stdio.h>

// 找枢轴，返回left,right,(left+right)/2的中值，并将最小的和最大的放入数组两侧，中值放在右侧前一个位置
int getPivot( int arr[], int left, int right );
// 交换两个地址的元素的值
void swap( int* a, int* b );
// 快速排序中调用
void qSort( int arr[], int left, int right );
// 快速排序接口
void quickSort( int arr[], int len );// 参考C语言提供的快速排序，传参传入的是数组的长度,而不是传left,right


int main(){
	int i;
//	int arr[300];
//	for( i = 0; i < 300; i++ ){
//		arr[i] = 300-i;
//	}
	int arr[] = { 22, 12, 44, 13, 5, 49 };
	int len = sizeof(arr)/sizeof(arr[0]);
	quickSort( arr, len );
	
	for( i = 0; i < len; i++ ){
		printf("%d ",arr[i]);
	}
	
	return 0;
}


// 快速排序接口
void quickSort( int arr[], int len ){// 参考C语言提供的快速排序，传参传入的是数组的长度,而不是传left,right
	qSort( arr,0, len-1 );
}
// 快速排序中调用
// 对闭区间[left,right]之间的元素进行排序
void qSort( int arr[], int left, int right ){
//	printf("1\n");
//	printf("%d %d\n",left,right);
//	return ;
	if( right <= left ){// 只剩下一个元素，不排序
		return ;
	}
	// 获取枢轴,如果元素为2，3个时，已经排好序，下面的循坏不会进入
	int pivot = getPivot( arr, left, right );
//	printf("2\n");
	// 确定待排序列的区间
	int low = left;
	int high = right - 1;
	while( low < high ){// 当左右指针相等时，即为主元要插入的位置
		
		while( low < high && arr[low] < pivot ){
			low++;
		}
		arr[high] = arr[low];
		while( low < high && arr[high] > pivot ){
			high--;
		}
		arr[low] = arr[high];

	}
	arr[low] = pivot;// 找到枢轴并放入
	// 递归排序枢轴左右
	qSort( arr, left, low-1 );
	qSort( arr, low+1, right );
	
}
// 找枢轴，返回left,right,(left+right)/2的中值，并将最小的和最大的放入数组两侧，中值放在右侧前一个位置
int getPivot( int arr[], int left, int right ){
	int mid = ( left + right ) / 2;
	if( arr[left] > arr[mid] ){
		swap( arr + left, arr + mid );
	}
	if( arr[left] > arr[right] ){
		swap( arr + left, arr + right );
	}
	if( arr[mid] > arr[right] ){
		swap( arr + mid, arr + right );
	}
	// 此时 arr[left] <= arr[mid] <= arr[right]
	// 微操,将枢轴放在right前一位，此时left,right分别在mid左右两边,接下来只需要考虑 left-1 到 right-2之间
	swap( arr + mid, arr + right-1 );
	return arr[right-1];
}
// 交换两个地址的元素的值
void swap( int* a, int* b ){
	int t = *a;
	*a = *b;
	*b = t;
}