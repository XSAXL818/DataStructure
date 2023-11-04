#include <stdio.h>
#include <stdlib.h>
#include <math.h>


// 判断是否为素数
int isPrime( int num ){
	int i;
	if( num == 1 ){
		return 0;
	}
	int dic = 1;
	for( i=2; i < abs( num ); i++ ){
		if( num % i == 0 ){
			dic =0;
			break;
		}
	}
	return dic;
}
// 判断是否为可逆素数
char* getprimenum( int num ){
	
	// 判断是否为素数
	int dic = isPrime( num );
	if( dic == 0 ){
		return "no";
	}
	// 获取逆序整数
	int num1 = 0;
	while( num > 0 ){
		num1 *= 10;
		num1 += num%10;
		num /= 10;
	}
	if( isPrime( num1 ) == 1 ){
		return "yes";
	} else {
		return "no";
	}
}


int main(){
	
	int num;
	scanf("%d",&num);
	char* ret = getprimenum( num );
	printf("%s",ret);
	return 0;
}