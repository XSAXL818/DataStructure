#include <stdio.h>

int main(){
	
	double i = 2;
	double j = 1;
	double sum = 0;
	int cnt = 20;
	int t;
	while( cnt > 0 ){
		sum += i/j;
		t = i;
		i = i + j;
		j = t;
		cnt--;
	}
	printf("%f",sum);
	return 0;
}