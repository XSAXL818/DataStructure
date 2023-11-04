#include<stdio.h>

int main(){
	
	int i = 0;
	FILE* in = fopen( "data.txt", "w" );
	
//	for( i = 500000; i >= 0; i-- ){
	for( i = 500; i >= 0; i-- ){
		fprintf( in, "%d ", i );
	}
	in = NULL;
	return 0;
}