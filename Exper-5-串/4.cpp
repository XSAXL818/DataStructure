#include <stdio.h>

void inverse( int* arr, int len ){
	int i = 0;
	int j = len - 1;
	int t;
	while( i < j ){
		t = arr[i];
		arr[i] = arr[j];
		arr[j] = t;
		i++;
		j--;
	}
}

int main(){
	
	int arr[10] = { 2, 1, 1, 1, 0, 7, 0, 0, 5, 3, };
	inverse( arr, 10 );
	int i;
	for( i = 0; i < 10; i++ ){
		printf("%d",arr[i]);
	}
	
	return 0;
}