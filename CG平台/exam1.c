#include <stdio.h>


int main(){
	
	int num1;
	scanf("%d",&num1);
	// 求num1逆序数
	int t = num1;
	int num2 = 0;
	while( t ){
		num2 *= 10;
		num2 += t%10;
		t /= 10;
	}
	// 判断倍逆序式
	if( num2%num1 == 0 ){
		printf("%d=%d*%d",num2,num1,num2/num1);
	} else {
		// 若输入的数末尾为0
		while( num1%10 == 0 ){
			printf("0");
			num1 /= 10;
		}
		printf("%d",num1);
	}
	
	return 0;
}