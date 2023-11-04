#include <stdio.h>

int main(){
	
	int V,n;
	scanf("%d %d",&V,&n);
	int nn[n];
	int i,j;
	for( i=0; i < n; i++ ){
		scanf("%d",nn+i);
	}
	// 第i个位置为1，说明可以组合出体积为i的组合方法
	// 第一个设为1，即存在不放物品的情况
	char v[V+1];
	v[0] = 1;
	for( i = 1; i <= V; i++ ){
		v[i] = 0;
	}
	// 倒序装箱
	// i控制装入物品的个数
	for( i= 0; i < n; i++ ){
		for( j = V; j >= nn[i]; j-- ){
			if( v[j] == 0 ){
				v[j] = v[ j-nn[i] ];
			}
		}
	}
	for( i = V; i >= 0; i-- ){
		if( v[i] == 1 ){
			break;
		}
	}
	printf("%d",V-i);
	return 0;
}