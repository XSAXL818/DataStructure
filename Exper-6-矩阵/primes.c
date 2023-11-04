#include <stdio.h>
#include <math.h>

// 判断是否为质数
int isPrime( int n ){
	int i;
	if( n < 2 ){
		return 0;
	}
	int dic = 1;
	for( i = 2; i < (int)abs(n) ; i++ ){
		if( n % i == 0 ){
			dic = 0;
			break;
		}
	}
	return dic;
}


int main(){
	
	int n;
	scanf("%d",&n);
	int i;
	int t = n / 2;
	for( i = 2; i <= t; ){
		if( isPrime( i ) && n % i == 0 ){
			printf("%d ",i);
			n /= i;
		} else {
			++i;
		}
		if( n == 1 ){
			break;
		}
	}

		

	
	return 0;
}