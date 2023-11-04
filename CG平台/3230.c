#include <stdio.h>

int main()
{
	int n1,n2;
	int dic = 0;
	for( n1=1; n1 < 43; n1++ ){
		for( n2=1; n2 < n1; n2++ ){
			if( n1*1.9 + n2*2.3 == 82.3 ){
				dic = 1;
				break;
			}
		}
		if( dic ){
			break;
		}
	}
	printf("%d",n2);
	return 0;
}