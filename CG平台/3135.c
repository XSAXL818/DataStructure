#include <stdio.h>
#include <math.h>
#include <string.h>

int main(){
	
	int n;
	scanf("%d",&n);
	char str[(int)pow(2,n)-1];
	char dest[(int)pow(2,n)-1];
	str[0] = 'A';
	str[1] = '\0';
	dest[0] = 'A';
	dest[1] = '\0';
	int i;
	for( i=1; i < (int)pow(2,n)-1; i++ ){
		str[i] = '\0';
		dest[i] = '\0';
	}
	for( i = 1; i < n; i++ ){
		strcpy( str, dest );	
		dest[(int)pow(2,i)-1] = 'A'+i;
		strcat( dest,str );
	}
	printf("%s",dest);

	
	
	
	return 0;
}