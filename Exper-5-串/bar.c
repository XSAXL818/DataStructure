#include <stdio.h>
#include <string.h>

typedef struct{
	char word[26];
	int num[26];
} List;


int main(){
	
	int num[26] = { 0 };
//	char str[10000];
//	gets( str );
//	int len = strlen( str );
	int i = 0;
//	while( i < len ){
//		num[str[i]-'a']++;
//		i++;
//	}
	char c = getchar();
	while( c != EOF ){
		num[c-'a']++;
		c = getchar();
	}
	int max = 0;
	for( i = 0; i < 26; i++ ){
		if( max < num[i] ){
			max = num[i];
		}
	}
	
	while( max ){
		for( i = 0; i < 26; i++ ){
			if( num[i] >= max ){
				printf("*");
			} else {
				printf(" ");
			}
		}
		printf("\n");
		max--;
	}
	for( c = 'a'; c <= 'z'; c++ ){
		printf("%c",c);
	}
	return 0;
}