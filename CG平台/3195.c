#include <stdio.h>
#include <math.h>

int main()
{
	// 暴力求解
	// 找到所有子集，然后找出子集中 <= 的最大子集和
	int V,n,i;
	scanf("%d",&V);
	scanf("%d",&n);
	int arr[n];
	for( i=0; i < n; i++ ){
		arr[i] = 0;
	}
	// 输入的数组
	int nn[n];
	for( i=0; i < n; i++ ){
		scanf("%d",nn+i);
	}
	// 用于储存子集的最大数,范围在 <= V
	int maxSize = nn[0];
	// 每次循环得到一个子集
	printf("%f\n",pow(2,0));
	for( i=0; i < pow(2,n)-1; i++ ){
		// 子集下标生成
		arr[0]++;
		int t;
		for( t=0; t < n-1; t++ ){
			if( arr[t] > 1 ){
				arr[t] = 0;
				arr[t+1]++;
			}
		}
		int sum = 0;
		for( t=0; t < n; t++ ){
			if( arr[t] == 1 ){
				sum += nn[t];
			}
		}
		if( sum > V ){
			// 丢弃
		} else {
			// 保存最靠近V的数
			if( sum > maxSize ){
				maxSize = sum;
			}
		}
		
	}
	
	printf("%d",V-maxSize);
	
	return 0;
}