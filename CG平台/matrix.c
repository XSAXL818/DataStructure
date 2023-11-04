#include <stdio.h>

int main(){
		
	int n;
	char op = '+';
	int i,j;
	scanf("%d",&n);
	int arr[n][n];
	for( i=0; i < n; i++ ){
		for( j=0; j < n; j++ ){
			arr[i][j] = 0;
		}
	}
	while( op != '#' ){
		for( i=0; i < n; i++ ){
			for( j=0; j < n; j++ ){
				int num;
				scanf("%d",&num);
				if( op == '+' ){
					arr[i][j] += num;
				} else {
					arr[i][j] -= num;
				}
			}
		}
		getchar();
		scanf("%c",&op);
		if( op == '#' ){
			break;
		}
	}
	for( i=0; i < n; i++ ){
		for( j=0; j < n; j++ ){
			printf("%5d",arr[i][j]);
		}
		printf("\n");
	}
	
	return 0;
}