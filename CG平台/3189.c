#include <stdio.h>

void f( int num ){
	int HH,MM,SS;
	SS = num%60;
	num -= SS;
	MM = (num%3600)/60;
	num -= MM*60;
	HH = num/3600;
	if( HH < 10 ){
		printf("0");
	}
	printf("%d:",HH);
	if( MM < 10 ){
		printf("0");
	}
	printf("%d:",MM);
	if( SS < 10 ){
		printf("0");
	}
	printf("%d\n",SS);
	
}
// 思路
// SS 是1的倍数 MM 是60的倍数 HH 是60*60 的倍数 所以通过求余再相减即可得到所有值
int main(){
	
	int t;
	scanf("%d",&t);
	while( t > 0 ){
		int n;
		scanf("%d",&n);
		f( n );
		t--;
	}
	
	return 0;
}