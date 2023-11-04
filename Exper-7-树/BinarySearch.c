#include <stdio.h>

int binarySearch( int num, int arr[], int length ){
	int left = 0;
	int right = length - 1;
	int mid = (left + right)/2;
	while( left <= right ){
		
		if( arr[mid] > num ){
			right = mid - 1;
		} else if( arr[mid] < num ){	
			left = mid + 1;
		} else {
			break;
		}
		mid = (left + right)/2;
	}
	if( left > right ){
		return -1;
	} else {
		return mid;
	}
	
}


int main(){
	
	int arr[9] = { 1, 7, 10, 13, 18, 21, 32, 43, 99 };
	int index = binarySearch( 12, arr, 9 );
	printf("%d\n",index);
	
	return 0;
}