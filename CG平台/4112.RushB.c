#include <stdio.h>

int main(){
	
	// 前n个字母为ABC... 后n-1个字母从尾开始为abc..
	char num;
	scanf("%d",&num);
	int i;
	for( i=0; i < num; i++ ){
		printf("%c",i+'A');
	}
	// i从'A'+num-1开始
	for( i='a'+num-2; i >= 'a'; i-- ){
		printf("%c",i);
	}
	
	return 0;
}