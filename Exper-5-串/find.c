#include <stdio.h>

int main(){
	
	
	FILE* in = fopen( "stringin.txt", "r" );
	FILE* out = fopen( "string.out.txt", "w" );
	if( in == NULL ){
		return 1;
	}
//	char c = fgetc( in );
//	while( c != EOF ){
//		printf("%c",c);
//		c = fgetc( in );
//	}
	
	
	
	
	return 0;
}