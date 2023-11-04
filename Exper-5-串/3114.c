#include <stdio.h>

void f( int n1, int arr[] ){
	arr[n1%10] = 0;
	n1 /= 10;
	arr[n1%10] = 0;
	n1 /= 10;
	arr[n1%10] = 0;
	n1 /= 10;
}

int main(){
	
	int i,j,k;
	int num = 0;
	for( i = 2; i < 8; i++ ){
		num = i*100;
		for( j = 1; j < 10; j++ ){
			if( j == i ){
			} else {
				num += j*10;
				for( k = 2; k < 10; k++,k++ ){
					if( k == j || k == i ){
					} else {
						num += k;
						if( num > 666 ){
							break;
						}
						int arr[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
						f( num, arr );
						f( num/2, arr );
						f( (num/2)*3, arr );
						int dic = 1;
						int t;
						for( t = 1; t < 10; t++ ){
							if( arr[t] != 0 ){
								dic = 0;
								break;
							}
						}
						if( dic == 1 ){
							printf("%d %d %d\n",num/2,num,num/2*3);
						}
						num -= k;
					}
				}
				num -= 10*j;
			}
			if( num > 666 ){
				break;
			}
			
		}
		if( num > 666 ){
			break;
		}
	}
	
	return 0;
}