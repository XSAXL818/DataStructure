#include<stdio.h>




int cnt1 = 0;
int cnt2 = 0;
int cnt3 = 0;
int cnt4 = 0;
int cnt5 = 0;

// 选择
void selectSort(int *arr,int len){
	int i;
	int j;	
	for(i=len-1; i > 0; i--){
		int maxid = 0;
		// find max 
		for(j=i; j>0; j--){
			cnt1++;
			if( arr[maxid] < arr[j] ){
				maxid = j;
			}
		}
		int t = arr[i];
		arr[i] = arr[maxid];
		arr[maxid] = t;		
	}
}

void popSort(int *arr,int len){
	int i,j,dic;
	for(i=len-1; i > 0; i--){
		dic = 1;
		for(j=0; j < i; j++){
			cnt2++;
			if(arr[j] > arr[j+1]){
				dic = 0;
				int t = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = t;
			}
		}
		if( dic ){
			break;
		}
	}
	
}

// 利用大根堆进行排序，元素按完全二叉树编号，由于从下标0开始所有有所调整
// 根结点i, 左子树：2i+1 右子树 2i+2
void heapSort( int arr[], int len );
// 对数组的index号进行 大根堆调整
void down( int arr[], int len, int index );


void merge(int arr[], int start, int mid, int end) {
	int result[101];
	int k = 0;
	int i = start;
	int j = mid + 1;
	while (i <= mid && j <= end) {
		cnt4++;
		if (arr[i] < arr[j]){
			result[k++] = arr[i++];
        }
		else{
			result[k++] = arr[j++];
        }
	}
	if (i == mid + 1) {
		while(j <= end)
			result[k++] = arr[j++];
	}
	if (j == end + 1) {
		while (i <= mid)
			result[k++] = arr[i++];
	}
	for (j = 0, i = start ; j < k; i++, j++) {
		arr[i] = result[j];
	}
}
 
void mergeSort(int arr[], int start, int end) {
	if (start >= end)
		return;
	int mid = ( start + end ) / 2;
	mergeSort(arr, start, mid);
	mergeSort(arr, mid + 1, end);
	merge(arr, start, mid, end);
}
 

void swap( int* a, int* b ){
	int t = *a;
	*a = *b;
	*b = t;
}
void quickSort(int k[ ],int left,int right){
    int i, last;
    if(left<right){
        last=left; 
        for(i=left+1;i<=right;i++){
        	cnt5++;
        	if(k[i]<k[left]){
        		
        		swap(&k[++last],&k[i]); 
			}
		}      
        swap(&k[left],&k[last]);
        quickSort(k,left,last-1); 
        quickSort(k,last+1,right);   
    }
}



int main(){
	
	int arr[101];
	int arr1[101];

	int select,num,i;
	scanf("%d %d",&num,&select);
	for( i = 0; i < num; i++ ){
		scanf("%d",arr+ i);
	}
	int cnt;
	switch(select){
		case 1:
			selectSort( arr, num );
			cnt = cnt1;
			break;
		case 2:
			popSort( arr, num );
			cnt = cnt2;
			break;
		case 3:
			heapSort( arr, num );
			cnt = cnt3;
			break;
		case 4:
			mergeSort( arr, 0, num-1 );
			cnt = cnt4;
			break;
		case 5:
			quickSort( arr, 0, num-1 );
			cnt = cnt5;
			break;
	}
	for( i = 0; i < num; i++ ){
		printf("%d ",arr[i]);
	}
	printf("\n");
	printf("%d",cnt);
	return 0;
}

// 利用大根堆进行排序，元素按完全二叉树编号，由于从下标0开始所有有所调整
// 根结点i, 左子树：2i+1 右子树 2i+2
void heapSort( int arr[], int len ){
	// 将数组初始化为一个大根堆
	int i = (len - 1) / 2;// i指向最后一个元素的父节点
	for( ; i >= 0; i-- ){
		down( arr, len, i );// 把编号为i的根结点调整为一个大根堆
	}																	// 数组 ---------------------******************
	
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
		cnt3++;
		if( t > arr[child] ){// 满足大根堆
			break;
		} else {// 基于插入排序，将最大值的孩子结点放在其父节点
			arr[parent] = arr[child];
		}
	}
	arr[parent] = t;// 完全二叉树的根结点找到使其为大根堆的结点
	
}