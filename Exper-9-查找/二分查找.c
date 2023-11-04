#include <stdio.h>



int binSearch( int* arr, int length, int value ){
	int low = 0;
	int hight = length-1;
	int mid;
	int cnt = 0;
	do{
		cnt++;
		mid = (low+hight)/2;
		if( arr[mid] == value ){
			break;
		} else if( arr[mid] < value ){
			low = mid+1;
		} else {
			hight = mid-1;
		}
	}while( low <= hight );
	
	printf("cont=%d\n",cnt);
	
	if( low > hight ){
		return -1;
	} else {
		return mid;
	}
}


int main(){
	
	
	
	
	int arr[] = { 1, 3, 6, 7, 12, 43, 56, 76, 88 };
	int ret = binSearch( arr, sizeof(arr)/sizeof(arr[0]), 88 );
	printf("%d",ret);
	
	
	
	
	
	
	return 0;
}