#include <stdio.h>

int f( int n ){
	int sum = 0;
	int t = n;
	while( t > 0 ){
		sum *= 10;
		sum += t%10;
		t /= 10;
	}
	if( sum == n ){
		return 1;
	} else {
		return 0;
	}
}

int main()
{
	int i;
	int dic = 0;
	for( i = 1001; i <= 9999; i++ ){
		if( i%10 == 10 ){
			
		} else {
			dic = f( i );
			if( dic == 1 ){
				printf("%d\n",i);
			}
		}
	}
	
	
	return 0;
}