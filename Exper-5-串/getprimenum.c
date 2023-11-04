#include <stdio.h>
#include <math.h>

int isPrime( int num ){
	int i;
	for( i = 2; i < abs(num); i++ ){
		if( num % i == 0 ){
			return 0;
		}
	}
	return 1;
}
int getNum( int num ){
	int sum = 0;
	while( num > 0 ){
		sum *= 10;
		sum += num%10;
		num /= 10;
	}
	return sum;
}

int main(){
	
	int num;
	scanf("%d",&num);
	if( isPrime( num ) ){
		if( isPrime( getNum( num ) ) ){
			printf("yes");
		} else {
			printf("no");
		}
	} else {
		printf("no");
	}

	return 0;
}