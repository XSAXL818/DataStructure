#include <stdio.h>
#include <string.h>

// 传入两个字符，是字母，且不考虑大小写相等则返回1
int cmp( char c1, char c2 ){
	if( c1-c2 == 0 || c1-c2 == 32 || c1-c2 == -32 ){
		return 1;
	} else {
		return 0;
	}
}



int main(){
	
	// 模式匹配-当前字符串未匹配需要回溯至第二个字符
	char str1[20];
	char str2[20];
	scanf("%s",str1);
	scanf("%s",str2);
	int len1 = strlen( str1 );

	FILE* in = fopen( "filein.txt", "r" );
	FILE* out = fopen( "fileout.txt", "w" );
	
	char str[100000];
	
	int len = 0;
	char c = fgetc( in );

	if( len1 == 0 ){
		while( c != EOF ){
			fputc( c,out );
			c = fgetc( in );
		}
		fputc( '1', out );
		return 0;
	}

	
	while( c != EOF ){
		str[len++] = c;
		c = fgetc( in );
	}
	str[len] = '\0';

	int i = 0;//字符串回溯指针
	int j = 0;//用于保存已匹配的字符的长度
	while( i < len  ){
		if( cmp( str[i], str1[j] ) ){
			i++;
			j++;
			if( j == len1 ){
				fputs( str2, out );
				j = 0;
			}		
		} else {
			i -= j-1;
			fputc( str[i-1], out );
			j = 0;
		}
		
	}
	i -= j;
	while( i < len ){
		fputc( str[i], out );
		i++;
	}
	
	return 0;
}