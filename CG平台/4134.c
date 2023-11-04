#include <stdio.h>

int f( int n ){
	int sum = 2;
	while( sum < n ){
		sum *= 2;
	}
	return sum;
}


int main(){
	
	int n;
	scanf("%d",&n);
	int i;
	int t;
	for( i=0; i < n; i++ ){
		scanf("%d",&t);
		printf("%d\n",f(t));
	}
	
	
	
	
	return 0;
}