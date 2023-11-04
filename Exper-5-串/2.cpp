#include <stdio.h>

int main(){
	
	int male = 15;
	int fmale = 9;
	int child = 1;
	int money = 300;
	int all = 100;
	int i,j,k;
	int dic = 0;
	for( i = 0; i <= 20; i++ ){
		for( j = 0; j <= 33; j++ ){
			for( k = 0; k <= 300; k++ ){
				if( i + j + k == 100 && male*i + fmale*j + child*k == money ){
					dic = 1;
					printf("公鸡%d只 母鸡%d只 小鸡%d只\n",i,j,k);
					break;
				}
			}
			if( dic ){
				break;
			}
		}
		if( dic ){
			break;
		}
	}
	
	
	return 0;
}