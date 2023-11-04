#include <stdio.h>
#include <string.h>

char getNext( char c ){
	
//	if( c == 'Z' ){
//		return c + 7;
//	}

	return c + 1;


}
void expand( char* s1, char* s2 ){
	int len1 = strlen( s1 );
	int len2 = 0;
	int i = 0;
	char c;
	while( i < len1 ){
		if( s1[i] != '-' ){
			s2[len2++] = s1[i];
		} else {
			if( s1[i-1] >= s1[i+1] ){
				s2[len2++] = '-';
				s2[len2++] = s1[i+1];
			} else {
				c = getNext( s1[i-1] );
				while( c <= s1[i+1] ){
					s2[len2++] = c;
					c = getNext( c );
				}
			}
			i++;
		}
		i++;
	}
	s2[len2] = '\0';
}

int main(){
	
	char s1[100];
	char s2[1000];
	gets( s1 );
	expand( s1, s2 );
	printf("%s",s2);
	

	return 0;
}