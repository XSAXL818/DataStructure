#include <stdio.h>
#include <string.h>

int main()
{
	char str[100];
	scanf("%s",str);
	int length = strlen( str );
	int i;
	int dic = 1;
	for( i=0; i < length/2; i++ ){
		if( str[i] != str[length-i-1] ){
			dic = 0;
			break;
		}
	}
	if( dic == 1 ){
		printf("yes!");
	} else {
		printf("no!");
	}
	return 0;
}