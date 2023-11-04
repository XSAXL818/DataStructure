#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include<time.h>
// ---------------------- 希尔排序---------------------------
// 希尔排序,基于插入排序的前提，通过一个增量序列如arr[] = { 4, 2, 1 },每一次循环将 所有相距为arr[i]的元素作为一个整体进行插入排序，直到增量为1
// 思路：最外层循环:用于控制增量的选择，次数为增量序列的长度
//       下一层：利用增量，对划分出的数组进行插入排序
// arr为使用哨兵的数组，len为arr的长度,seq为要选取的增量序列,需传入一个不用哨兵作为存储的的数组
void shellSort( int arr[], int len, int select );
// ---------------------- 希尔排序---------------------------

// ---------------------- 快速排序---------------------------
// 找枢轴，返回left,right,(left+right)/2的中值，并将最小的和最大的放入数组两侧，中值放在右侧前一个位置
int getPivot( int arr[], int left, int right );
// 交换两个地址的元素的值
void swap( int* a, int* b );
// 快速排序中调用
void qSort( int arr[], int left, int right );
// 快速排序接口
void quickSort( int arr[], int len );// 参考C语言提供的快速排序，传参传入的是数组的长度,而不是传left,right
// ---------------------- 快速排序---------------------------

// ---------------------- 堆排序---------------------------

// 利用大根堆进行排序，元素按完全二叉树编号，由于从下标0开始所有有所调整
// 根结点i, 左子树：2i+1 右子树 2i+2
void heapSort( int arr[], int len );
// 对数组的index号进行 大根堆调整
void down( int arr[], int len, int index );

// ---------------------- 堆排序---------------------------

// 读取文件函数,将文件中的数字读入到数组中，元素从下标为1开始存,返回创建数组的长度
int readInt( FILE* in, int** arr, int len, int maxSize );
// 将待排序的数组传入，并生成已排好序的文件
void outData( FILE* in, int arr[], int len );

// 选择
void selectSort(int *arr,int len){
	int i;
	int j;	
	for(i=len-1; i > 0; i--){
		int maxid = 0;
		// find max 
		for(j=i; j>0; j--){
			if( arr[maxid] < arr[j] ){
				maxid = j;
			}
		}
		
		int t = arr[i];
		arr[i] = arr[maxid];
		arr[maxid] = t;	
		
	}
	
}


int view(void);
int arr1[10000000];
int arr2[10000000];
int arr3[10000000];
int arr4[10000000];
int arr5[10000000];

int main(){
	
	while( 1 ){
		view();
	}
		
	return 0;
}
// 菜单
int view(void){
	char str[20];
	printf("请输入待排序的文件名：(结束输入0)");
	scanf("%s",str);
	if( strlen( str ) == 1 && str[0] == '0' ){
		exit( 0 );
	}
	int i,j;
	FILE* in = fopen( str, "r" );
	
	int* arr[] = { arr1, arr2, arr3, arr4, arr5 };
	int len = readInt( in, arr, sizeof(arr)/sizeof(arr[0]), sizeof(arr1)/sizeof(arr[0]) );
//	printf("读取的原数据：\n");
//	FILE* out1 = fopen( "shellSort.txt", "w" );
//	FILE* out2 = fopen( "quickSort.txt", "w" );
//	FILE* out3 = fopen( "heapSort.txt", "w" );
//	for( i = 0; i < len; i++ ){
//		fprintf( out1, "%d ", arr[i] );
//	}
//	for( i = 0; i < len; i++ ){
//		printf("%d ",arr1[i]);
//	}
//	printf("\n");
//	for( i = 0; i < len; i++ ){
//		printf("%d ",arr2[i]);
//	}
//	printf("\n");
//	for( i = 0; i < len; i++ ){
//		printf("%d ",arr3[i]);
//	}
//	printf("\n");
//	printf("len=%d ", len);
	clock_t start_t,end_t;
	double times[5];
	// 希尔
	start_t = clock();
	printf("希尔(希尔增量)排序启动，start_t = %ld\n", start_t);
	shellSort( arr1, len, 2 );
	
	end_t = clock();
	printf("结束，end_t = %ld\n", end_t);
	times[0] = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	
	printf("希尔(Sedgewick增量)排序启动，start_t = %ld\n", start_t);
	shellSort( arr2, len, 1 );
	
	end_t = clock();
	printf("结束，end_t = %ld\n", end_t);
	times[1] = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	
	// 快速
	start_t = clock();
	printf("快速排序启动，start_t = %ld\n", start_t);
	quickSort( arr3, len );
	
	end_t = clock();
	printf("结束，end_t = %ld\n", end_t);
	times[2] = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	// 堆
	start_t = clock();
	printf("堆排序启动，start_t = %ld\n", start_t);
	heapSort( arr4, len );
	
	end_t = clock();
	printf("结束，end_t = %ld\n", end_t);
	times[3] = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	// 直接选择
	start_t = clock();
	printf("直接选择排序启动，start_t = %ld\n", start_t);
	selectSort( arr5, len );
	
	end_t = clock();
	printf("结束，end_t = %ld\n", end_t);
	times[4] = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	
	
	for( i = 0; i < sizeof(arr)/sizeof(arr[0]); i++ ){
		switch( i ){
			case 0:
				printf("希尔(希尔增量): 花费时间%f\n",times[i]);
				break;
			case 1:
				printf("希尔(Sedgewick增量)：花费时间%f\n",times[i]);
				break;
			case 2:
			 	printf("快速: 花费时间%f\n",times[i]);
				break;
			case 3:
			 	printf("堆: 花费时间%f\n",times[i]);
				break;
			case 4:
				printf("直接选择: 花费时间%f\n",times[i]);
		}
		for( j = 0; j < len; j++ ){
			printf("%d ",arr[i][j]);
		}
		printf("\n");
	}
}

// ---------------------- 希尔排序---------------------------

// 希尔排序,基于插入排序的前提，通过一个增量序列如arr[] = { 4, 2, 1 },每一次循环将 所有相距为arr[i]的元素作为一个整体进行插入排序，直到增量为1
// 思路：最外层循环:用于控制增量的选择，次数为增量序列的长度
//       下一层：利用增量，对划分出的数组进行插入排序

// len为arr的长度,seq为要选取的增量序列
void shellSort( int arr[], int len, int select ){
	// 选择增量序列
	int shell[] = { 16384, 8192, 4096, 2048, 1024, 512, 256, 128, 64, 32, 16, 8, 4, 2, 1, 0  };
	int sedgeWick[] = { 16001, 8929, 3905, 2161, 929, 505, 209, 109, 41, 19, 5, 1, 0 };
	int* seq;
	int sLen;
	if( select == 1 ){
		seq = shell;
		sLen = sizeof(shell)/sizeof(shell[0]);
	} else {
		seq = sedgeWick;
		sLen = sizeof(sedgeWick)/sizeof(sedgeWick[0]);
	}
	int i = 0;
	int d,j,k;
	// 找到不大于数组元素个数的增量
	while( seq[i] >= len ){	// 带哨兵，实际元素为len-1个,如果相等，则划分为len-1个数组，等于没排，所以条件为等于
		i++;
	}
	int t;
	for( ; seq[i] > 0; i++ ){//最外层循环，次数为 增量序列的长度
		d = seq[i];// 保存增量
		for( j = d; j < len; j++ ){// 初始时插入排序默认第一个为有序，所有j=d+1为从每个划分数组元素的第二个元素开始插入排序
			// 进行插入排序
			t = arr[j];// 保存待排序的值
			for( k = j-d; k >= 0 && arr[k] > t; k -= d ){// j的下标指向前移和后移一位的长度为d
				arr[k+d] = arr[k];// 后移一位
			}
			// 找到要插入的位置
			arr[k+d] = t;
		}
	}
	
}

// ---------------------- 希尔排序---------------------------

// ---------------------- 快速排序---------------------------

// 快速排序接口
void quickSort( int arr[], int len ){// 参考C语言提供的快速排序，传参传入的是数组的长度,而不是传left,right
	qSort( arr, 0, len-1 );
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
	if( right - left <= 2 ){
		return ;
	}
//	printf("2\n");
	// 确定待排序列的区间
	int low = left + 1;
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

// ---------------------- 快速排序---------------------------

// ---------------------- 堆排序---------------------------

// 利用大根堆进行排序，元素按完全二叉树编号，由于从下标0开始所有有所调整
// 根结点i, 左子树：2i+1 右子树 2i+2
void heapSort( int arr[], int len ){
	// 将数组初始化为一个大根堆
	int i = (len - 1) / 2;// i指向最后一个元素的父节点
	for( ; i >= 0; i-- ){
		down( arr, len, i );// 把编号为i的根结点调整为一个大根堆
	}														// 数组 ---------------------******************
	
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
// ---------------------- 堆排序---------------------------

// 读取文件函数,将文件中的数字读入到数组中，元素从下标为1开始存
int readInt( FILE* in, int* *arr, int len, int maxSize ){
	int end = 0;
	int cnt = 0;
	int num;
	int i;
	while( 1 ){
		end = fscanf( in, "%d", &num );
		if( end == EOF ){
			break;
		}
		if( cnt == maxSize ){
			break;
		}
		for( i = 0; i < len; i++ ){
			arr[i][cnt] = num;
		}
		cnt++;
	}
	return cnt;
}
// 将待排序的数组传入，并生成已排好序的文件
void outData( FILE* in, int arr[], int len ){
	int i;
	for( i = 0; i < len; i++ ){
		printf("****%d\n",arr[i]);
		fprintf( in, "%d ", arr[i] );
	}
}
