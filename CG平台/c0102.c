#include <stdio.h>


int main(){
	int num;
	scanf("%d",&num);
	if( num >= 100 && num <= 999 ){
		
	} else {
		printf("-1");
		return 0;
	}
	// 将头数字入栈
	int mi = 100;
	while( mi > 0 ){
		if( num%10 != 0 ){
			printf("%d",num%10);
		}
		num /= 10;
		mi /= 10;
	}
	return 0;
}