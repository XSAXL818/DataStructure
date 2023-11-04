#include <stdio.h>

int main(){
	
	char c;
	int num1,num2;
	scanf("%c %d %d",&c,&num1,&num2);
	switch( c ){
		case '+':
			printf("%d",num1+num2);
			break;
		case '-':
			printf("%d",num1-num2);
			break;
		case '*':
			printf("%d",num1*num2);
			break;
		case '/':
			printf("%d",num1/num2);
			break;
	}
	return 0;
}