#include <stdio.h>


int f( int num1, int num2 ){
	int n1 = num1;
	int n2 = num2;
	if( num1 > num2 ){
		int t = num1;
		num1 = num2;
		num2 = t;
	}
	int n = num1;
	while( num1%num2 != 0 ){
		n = num1%num2;
		num1 = num2;
		num2 = n;
	}
	return n1*n2/n;
}
int main(){
	
	int a,b,c;
	scanf("%d %d %d",&a,&b,&c);
	printf("%d",f( f(a,b),c ));
	
	return 0;
}