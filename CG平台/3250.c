#include <stdio.h>


int f( int n ){
	if( n > 0 ){
		if( n > 1 ){
			return f(n-1) + f(n-2);
		} else {
			return f(n-1);
		}
		
	} else {
		return 1;
	}
}

int main()
{
	int n;
	scanf("%d",&n);
	printf("%d",f(n));
	return 0;
}