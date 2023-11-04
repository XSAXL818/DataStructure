#include <stdio.h>
#include <string.h>

int main(){
	
	char s1[1000];
	char s[1000];
	char s2[100];
	gets( s1 );
	gets( s2 );
//	scanf("%s",s2);
	int len1 = strlen( s1 );
	int len = 0;
	int len2 = strlen( s2 );
	int i = 0;
	int cnt = 0;
	while( i < len1 ){
		if( s1[i] != s2[cnt] ){
			
			cnt = 0;
			
		} else {
			cnt++;
			if( len2 == cnt ){
				len -= cnt-1;
				cnt = 0;
				i++;
			}
		}
		s[len++] = s1[i];
		i++;
	}
	s[len] = '\0';
	printf("%s",s);

	return 0;
}