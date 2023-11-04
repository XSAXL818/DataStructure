#include <stdio.h>

int main(){
	
	int isPrime[] = {2,3,5,7,11,13,17}; 
	int t;
	int i,j,k;
	
	for(i=1; i < 9; i++){
		for(j = 2; j < 10; j++){
			for(k=0; k < j-i; k++){
				int disc = 1;
				if( i == 8 && j == 9 && k == 0 ){
				}
				if( i != k ){
					for( t=0; t < 7; t++){
						if( j + i == isPrime[t] ){
							disc = 0;
							break;
						}
					}
					
					if(disc){
						printf("%d%d%d\n",i,j,k);
					}
				}
			}
		}
	}
	
	
	return 0;
} 
