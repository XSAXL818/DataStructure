#include <stdio.h>

int main()
{
	char t;
	for( t = 0; t < 32; t++ ){
		int n = t;
		if( n >= 16 ){
			printf("1");
			n %= 16;
		} else {
			printf("0");
		}
		if( n >= 8 ){
			printf("1");
			n %= 8;
		} else {
			printf("0");
		}
		if( n >= 4 ){
			printf("1");
			n %= 4;
		} else {
			printf("0");
		}
		if( n >= 2 ){
			printf("1");
			n %= 2;
		} else {
			printf("0");
		}
		if( n == 1 ){
			printf("1");
		} else {
			printf("0");
		}
		printf("\n");
	}
	return 0;
}