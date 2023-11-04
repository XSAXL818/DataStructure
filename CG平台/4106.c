#include <stdio.h>

int main(){
	
	int num;
	scanf("%d",&num);
	int arr[13] = {0};
	while( num > 0 ){
		if( num >= 10000 ){
			arr[0] = num/10000;
			num %= 10000;
		} else if( num >= 5000 ){
			arr[1] = num/5000;
			num %= 5000;
		} else if( num >= 2000 ){
			arr[2] = num/2000;
			num %= 2000;
		} else if( num >= 1000 ){
			arr[3] = num/1000;
			num %= 1000;
		} else if( num >= 500 ){
			arr[4] = num/500;
			num %= 500;
		} else if( num >= 200 ){
			arr[5] = num/200;
			num %= 200;
		} else if( num >= 100 ){
			arr[6] = num/100;
			num %= 100;
		} else if( num >= 50 ){
			arr[7] = num/50;
			num %= 50;
		} else if( num >= 20 ){
			arr[8] = num/20;
			num %= 20;
		} else if( num >= 10 ){
			arr[9] = num/10;
			num %= 10;
		} else if( num >= 5 ){
			arr[10] = num/5;
			num %= 5;
		} else if( num >= 2 ){
			arr[11] = num/2;
			num %= 2;
		} else {
			arr[12] = num;
			num %= 1;
		}
	}
	int i;
	for( i=0; i < 13; i++ ){
		printf("%d\n",arr[i]);
	}
	
	return 0;
}