#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 动态规划， 定义一个int数组arr，arr[i]的值表示 以字符串第i个字符作为结尾的 最大长度
// arr[i] = max{ arr[0], arr[1] .... arr[i-1] } 其中 str[0] .... str[i-1] 均小于 str[i]

int main(){

	
	char str[10000];
	scanf("%s",str);
	int len = strlen( str );
	int arr[10000] = { 1, 0 };// 初始化,
	int i,j;
	int max;// 用于保存i之前的最大字符
	for( i = 1; i < len; i++ ){
		max = 0;
		for( j = 0; j < i; j++ ){
			if( str[i] >= str[j] ){
					if( max < arr[j] ){
						max = arr[j];
					}
			}
		}
		arr[i] = max + 1;
	}
	max = 0;
	for( i = 0; i < len; i++ ){
		if( max < arr[i] ){
			max = arr[i];
		}
	}
	printf("%d",max);
	return 0;
}
