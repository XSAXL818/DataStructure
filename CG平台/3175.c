#include <stdio.h>

int main(){
	
	char str1[100];
	char str2[100];
	scanf("%s",str1);
	scanf("%s",str2);
	char str3[200];
	int i = 0;
	while( str1[i] != '\0' ){
		str3[i] = str1[i];
		i++;
	}
	int j = 0;
	while( str2[j] != '\0' ){
		str3[i] = str2[j];
		i++;
		j++;
	}
	str3[i] = '\0';
	printf("%s",str3);
	return 0;
}