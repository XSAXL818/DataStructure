#include <stdio.h>


int main(){
	
	FILE* in = fopen( "article.txt", "r" );
	FILE* out = fopen( "hamlet.txt", "w" );
	char c = fgetc( in );
	
	while( c != EOF ){
		if( c >= 'A' && c <= 'Z' ){
			c += 32;
		}
		fputc( c, out );
		c = fgetc(in);
	}
	
	return 0;
}