#include <stdio.h>
#include <math.h>

typedef struct{
	int num1;
	int num2;
} Data;
int main(){
	
	int n=2,m=45;
	int a,b;
	int i;
	int cnt = 0;
	Data data[30] = {0};
	int t=0;
	for( i=1; i <= m;i++ ){
		for( a=1; a < (n*i)/2; a++ ){
			if( (m*i)%(n*i-a) == 0 && (m*i)%(a) == 0 ){
				int tt=0;
				int dic = 1;
				while( tt < t ){
					if( a/data[tt].num1 == (n*i-a)/data[tt].num2 ){
						dic = 0;
						break;
					}
					tt++;
				}
				if( dic ){
					data[t].num1 = a;
					data[t].num2 = n*i-a;
					t++;
					cnt++;
				}			
			}
		}
	}
	printf("%d",cnt);
	
	return 0;
}