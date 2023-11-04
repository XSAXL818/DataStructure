#include <stdio.h>

void str_bin(char str1[], char str2[]){
	int len1 = 0;
	int len2 = 0;
	while( str1[len1++] ){
	}
	while( str2[len2++] ){
	}
	len1--;
	len2--;
	char str3[201];
	int i=0,j=0;
	int k = 0;
	while( i < len1 && j < len2 ){
		if( str1[i] > str2[j] ){
			str3[k] = str2[j];
			j++;
		} else if( str1[i] < str2[j] ){
			str3[k] = str1[i];
			i++;
		} else {
			str3[k] = str1[i];
			i++;
			k++;
			str3[k] = str2[j];
			j++;
		}
		k++;
	}
	while( i < len1 ){
		str3[k++] = str1[i++];
	}
	while( j < len2 ){
		str3[k++] = str2[j++];
	}
	str3[k] = '\0';
	printf("%s",str3);
}
int main(){
	
	char str1[101];
	char str2[101];
	scanf("%s %s",str1,str2);
	str_bin( str1, str2 );
	return 0;
}