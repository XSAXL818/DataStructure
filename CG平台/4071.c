#include <stdio.h>
#include <stdlib.h>



int main(){
	
	
	int n;
	scanf("%d",&n);
	int i;
	char arr[1000000] = {0};
	int t;
	int max = -999;
	int min = 999;
	for( i = 0; i < n; i++ ){
		scanf("%d",&t);
		if( t > max ){
			max = t;
		} 
		if( t < min ){
			min = t;
		}
		arr[t+500000] = 1;
	}
 	printf("%d",max);
 	for( i=min+500001; i < max+500000; i++ ){
 		if( arr[i] == 1 ){
 			printf(" %d",i-500000);
		 }
	}
	printf(" %d",min);
	return 0;
}