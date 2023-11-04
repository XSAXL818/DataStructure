#include <stdio.h>


int f( int n ){
	if( n > 0 ){
		return n + f( n - 2 );
	} else {
		return 0;
	}
}


int main(){
	
	
	int n;
	scanf("%d",&n);
	printf("%d", f( n ) );
	
	return 0;
}