#include <stdio.h>

// 返回n的位平方
int f( int n ){
	int sum = 0;
	while( n > 0 ){
		sum += (n%10)*(n%10);
		n /= 10;
	}
	return sum;
}


int main()
{
	int x,n;
	scanf("%d %d",&x,&n);
	while( n > 0 ){
		x = f( x );
		n--;
	}
	printf("%d",x);
	return 0;
}