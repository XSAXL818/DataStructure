#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 判断src 是否为 dest 外加一个空格 n为字符串的长度加1
int dic( char* src, char* dest, int n ){
	int dic = 1;
	int i;
	for( i = 0; i < n - 1; i++ ){
		if( src[i] != dest[i] ){
			dic = 0;
			break;
		}
	}
	if( src[i] != ' ' ){
		dic = 0;
	}
	return dic;
}


int main(){
	
	char* arr[20];
	int cnt = 0;
	char str[1000];
	gets( str );

	char* s;

	int len = strlen( str );
	int i = 0;
	while( str[i] != ' ' ){
		i++;
	}
	int t = i;
	s = (char*)malloc( (i+1)*sizeof(char) );
	s[i] = '\0';
	while( --i > -1 ){
		s[i] = str[i];
	}
	arr[cnt++] = s;
	i = t;
	while( str[i] != '(' ){
		++i;
	}
	int dic = 1;// dic为1,则进行类型获取
	int j;
	i++;
	while( i < len ){
		if( str[i] == ')' ){
			break;
		}
		if( dic ){
			if( str[i] != ' ' ){
				s = (char*)malloc( 7*sizeof( char ) );
				j = 0;
				while( str[i] != ' ' ){
					s[j] = str[i];
					++j;
					++i;
				}
				s[j] = '\0';
				arr[cnt++] = s;
				dic = 0;
			}
			
		}
		if( str[i] == ',' ){
			dic = 1;
		}
		i++;
	}
	for( i = 0; i < cnt; i++ ){
		printf("%s ",arr[i]);
	}
	printf("\n");
	

	cnt = 0;

	gets( str );

	int tmp = len;
	len = strlen( str );
	if( tmp == len ){
		return 0;
	}
	i = 0;
	while( str[i] != ' ' ){
		i++;
	}
	t = i;
	s = (char*)malloc( (i+1)*sizeof(char) );
	s[i] = '\0';
	while( --i > -1 ){
		s[i] = str[i];
	}
	arr[cnt++] = s;
	i = t;
	while( str[i] != '(' ){
		++i;
	}
	dic = 1;// dic为1,则进行类型获取
	j;
	i++;
	while( i < len ){
		if( str[i] == ')' ){
			break;
		}
		if( dic ){
			if( str[i] != ' ' ){
				s = (char*)malloc( 7*sizeof( char ) );
				j = 0;
				while( str[i] != ' ' ){
					s[j] = str[i];
					++j;
					++i;
				}
				s[j] = '\0';
				arr[cnt++] = s;
				dic = 0;
			}
			
		}
		if( str[i] == ',' ){
			dic = 1;
		}
		i++;
	}
	for( i = 0; i < cnt; i++ ){
		printf("%s ",arr[i]);
	}
	printf("\n");

	cnt = 0;

	gets( str );
	tmp = len;
	len = strlen( str );
	if( tmp == len ){
		return 0;
	}
	i = 0;
	while( str[i] != ' ' ){
		i++;
	}
	t = i;
	s = (char*)malloc( (i+1)*sizeof(char) );
	s[i] = '\0';
	while( --i > -1 ){
		s[i] = str[i];
	}
	arr[cnt++] = s;
	i = t;
	while( str[i] != '(' ){
		++i;
	}
	dic = 1;// dic为1,则进行类型获取
	j;
	i++;
	while( i < len ){
		if( str[i] == ')' ){
			break;
		}
		if( dic ){
			if( str[i] != ' ' ){
				s = (char*)malloc( 7*sizeof( char ) );
				j = 0;
				while( str[i] != ' ' ){
					s[j] = str[i];
					++j;
					++i;
				}
				s[j] = '\0';
				arr[cnt++] = s;
				dic = 0;
			}
			
		}
		if( str[i] == ',' ){
			dic = 1;
		}
		i++;
	}
	for( i = 0; i < cnt; i++ ){
		printf("%s ",arr[i]);
	}
	printf("\n");
	
	return 0;
}
