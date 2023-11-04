#include<stdio.h>

// 希尔排序,基于插入排序的前提，通过一个增量序列如arr[] = { 4, 2, 1 },每一次循环将 所有相距为arr[i]的元素作为一个整体进行插入排序，直到增量为1
// 思路：最外层循环:用于控制增量的选择，次数为增量序列的长度
//       下一层：利用增量，对划分出的数组进行插入排序

// arr为使用哨兵的数组，len为arr的长度,seq为要选取的增量序列
void shellSort( int arr[], int len, int select ){
	// 选择增量序列
	int shell[] = { 2048, 1024, 512, 256, 128, 64, 32, 16, 8, 4, 2, 1, 0  };
	int sedgeWick[] = { 2161, 929, 505, 209, 109, 41, 19, 5, 1, 0 };
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
	while( seq[i] >= len-1 ){	// 带哨兵，实际元素为len-1个,如果相等，则划分为len-1个数组，等于没排，所以条件为等于
		i++;
	}
	for( ; seq[i] > 0; i++ ){//最外层循环，次数为 增量序列的长度
		printf("1\n");
		d = seq[i];// 保存增量
		for( j = d+1; j < len; j++ ){// 初始时插入排序默认第一个为有序，所有j=d+1为从每个划分数组元素的第二个元素开始插入排序
			// 进行希尔排序
			arr[0] = arr[j];// 哨兵保存待排序的值
			for( k = j-d; k > 0 && arr[k] > arr[0]; k -= d ){// j的下标指向前移和后移一位的长度为d
				arr[k+d] = arr[k];// 后移一位
			}
			// 找到要插入的位置
			arr[k+d] = arr[0];
		}
	}
	
}

int main(){
	
	int arr[10] = { 1, 5, 2, 10, 87, 22, 32, 12, 77, 54 };
	shellSort( arr, 10, 1 );
	int i;
	for( i = 1; i < 10; i++ ){
		printf("%d ",arr[i]);
	}
	
	
	
	
	return 0;
}