#include <stdio.h>

int main(){
	char str[100];
	scanf("%s",str);
	int cnt = 0;
	int i=0;
	while( str[i] != '\0' ){
		if( str[i] >= '0' && str[i] <= '9' ){
			cnt++;
		}
		i++;
	}
	printf("%d",cnt);
	return 0;
}