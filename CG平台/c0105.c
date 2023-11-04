#include <stdio.h>

int main(){
	
	int num;
	scanf("%d",&num);
	int ten = 0;
	int five = 0;
	int two = 0;
	int one = 0;
	while( num > 0 ){
		if( num >= 10 ){
			ten = num/10;
			num = num - 10*ten;
		} else if( num >= 5 ){
			five = num/5;
			num -= 5*five;
		} else if( num >= 2 ){
			two = num/2;
			num -= 2*two;
		} else {
			one = num;
			num /= 10;
		}
	}
	printf("%d %d %d %d",ten,five,two,one);
	return 0;
}