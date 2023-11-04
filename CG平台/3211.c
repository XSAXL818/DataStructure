#include <stdio.h>

// 队列
typedef struct{
	char* ch;
	int front;
	int rear;
} Queue;
int main()
{
	char str[100000];
	gets( str );
	int i=0;
	int dic = 1;
	int length = 0;
	int maxLen = 0;
	// 每次找到最长单词的下标并保存
	int index = 0;
	while( str[i] != '\0' ){
		// 判断当前是否为字母
		if( str[i] == ' ' ){
			dic = 0;
		} else {
			dic = 1;
		}
		if( dic == 1 ){
//			printf("%c\n",str[i]);
			length++;
		} else {
//			printf("length=%d\n",length);
			if( maxLen < length ){
				maxLen = length;
				index = i-length;
			}
			length = 0;
		}
		i++;
	}
	// 最后一个单词循环漏掉
	if( maxLen < length ){
		maxLen = length;
		index = i-length;
	}
	for( i=index; i < index+maxLen; i++ ){
		printf("%c",str[i]);
	}



	return 0;
}
