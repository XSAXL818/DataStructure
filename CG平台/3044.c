#include <stdio.h>

void bubb( int arr[], int length ){
	int i,j;
	for( i=length-1; i > 0 ; i-- ){
		for( j=0; j < i; j++ ){
			if( arr[j] > arr[j+1] ){
				int t = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = t;
			}
		}
	}
}
int main(){
	
	int i;
	int arr[5];
	for( i = 0; i <5; i++ ){
		scanf("%d",arr+i);
	}
	bubb( arr, 5 );
	for( i = 0; i <5; i++ ){
		printf("%d ",arr[i]);
	}
	
	return 0;
}