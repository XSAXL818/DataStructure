#include <stdio.h>
#include <stdlib.h>

int* f(void){
	int* arr = (int*)malloc( 10*sizeof(int) );
	arr[0] = 3;
	arr[5] = 4;
	return arr;
}

int main(){
	
	int* arr = f();
	int i;
	int len = sizeof( arr )/sizeof( arr[0] );
	printf("%d\n", len );
	for( i = 0; i < len; i++ ){
		printf("%d ",arr[i]);
		
	}
	
	return 0;
}