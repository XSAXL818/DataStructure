#include <stdio.h>
#include <string.h>
#include <stdlib.h>


// 思路 数据域是一个数组，数组下标表示该单词出现的次数
//						   1		  2			  3
//                     单词1，2     3，4        4，5

// 顺序表
typedef struct _Node{
	char* *word; // word[i]表示该结点保存的第i个单词的首地址,初始分配20个空间
	int length; // // 用于表示当前结点的状态，-1表示未有元素覆盖过,0表示覆盖过元素,>0表示有多少个单词
	int maxSize;// 存储单词最大个数
} Node;
typedef struct{
	Node* data; // 数据域，data[i]内的元素未出现次数为i的结点
	int maxSize;// 数据域的个数
} List;
// 创建一个新表
List* creatList( int maxSize ){
	List* list = (List*)malloc( sizeof(List) );
	list->data = (Node*)malloc( maxSize*sizeof(Node) );
	// 初始化状态
	int i;
	// 出现一次的单词的默认储存量为100
	// 出现两次到10次的默认储存量为20
	// 之后的全部默认容量5
	list->data[0].length = 0;
	list->data[0].maxSize = 100;
	list->data[0].word = (char**)malloc( 100*sizeof(char*) );
	for( i = 1; i < 10; i++ ){
		list->data[i].length = 0;
		list->data[i].maxSize = 20;
		list->data[i].word = (char**)malloc( 20*sizeof(char*) );
	}
	for( ; i < maxSize; i++ ){
		list->data[i].length = 0;
		list->data[i].maxSize = 5;
		list->data[i].word = (char**)malloc( 5*sizeof(char*) );
	}
	list->maxSize = maxSize;
	return list;
}
// 添加元素
void add( List* list, char* str ){
	// 先遍历是否存在该字符串
	int i;
	int dic = 0;// 如果dic==1，说明已存在该单词
	int j;
	Node* t;
	for( i = 0; i < list->maxSize; i++ ){
		// 找到最后单词的位置的有效位置
		if( list->data[i].length < 0 ){
			break;
		}
		// 遍历单词出现i+1次的所有单词
		t = list->data + i;
		for( j = 0; j < t->length; j++ ){
			if( strcmp( str, t->word[j] ) == 0 ){ // 找到时,j为该单词的下标,i为该单词当前出现的次数-1
				dic = 1;
				break;
			}
		}
		if( dic == 1 ){
			break;
		}
	}
	
	if( dic == 1 ){ // 找到存在该字符
		// 先将当前字符保存到链表的i处
		Node* node = list->data + i + 1;
		Node* t = list->data + i;
		if( node->length == -1 ){ // 判断出现次数为i+2的数据域是否有过元素
			node->length++;
		} else if( node->length == node->maxSize ){ // 判断是否溢出
			node->word = realloc( node->word, 2*node->maxSize*sizeof(char*) );
			node->maxSize = 2*node->maxSize;
		}
		// 向结点末尾插入单词
		node->word[node->length++] = t->word[j];
		// 抹去原有单词的储存
		t->word[j] = t->word[--t->length];
	} else {// 未找到则在i=0添加新元素
		Node* node = list->data;
		if( node->length == -1 ){
			node->length++;
		}
		node->word[node->length++] = str;
	}	
}
// 遍历
void printList( List* list, FILE* pf ){
	int i,j,cnt=0;
	for( i = list->maxSize-1; i >= 0; i-- ){
		Node* t = list->data + i;
		if( t->length <= 0 ){
			
		} else {
			for( j = 0; j < t->length; j++ ){
				fprintf( pf, "%s %d\n",t->word[j],i+1);
				cnt++;
				if( cnt <= 100 ){
					printf("%s %d\n",t->word[j],i+1);
				}
			}
		}
	}
}
// 对每个结点中的单词进行排序
void sort( Node* node ){
	int i,j;
	for( i = node->length; i > 1; i-- ){
		for( j = 0; j < i-1; j++ ){
			if( strcmp( node->word[j], node->word[j+1] ) > 0 ){
				char* t = node->word[j];
				node->word[j] = node->word[j+1];
				node->word[j+1] = t;
			}
		}
	}
}
// 对链表排序
void Sort( List* list ){
	int i;
	for( i = 0; i < list->maxSize; i++ ){
		Node* node = list->data + i;
		if( node->length == -1 ){
			break;
		}
		sort( node );
	}
}
int main(){
	
	List* list = creatList( 20000 );
	FILE* pf = fopen( "article.txt", "r" );

	// 打开成功
	int cnt = 0;
	char c = fgetc( pf );
	char str[15];
	char* s;
	// 等于0即正好获取一个单词
	int dic = 0;
	while( c != EOF ){
		// 前两个if：将单词字母添加入 字符串缓冲
		if( c >= 'a' && c <= 'z' ){
			str[cnt] = c;
			cnt++;
		} else if( c >= 'A' && c <= 'Z' ){
			str[cnt] = c+32;
			cnt++;
//		} else if( c == ' ' || c == '.' || c == ';' || c == '-' ) {
		// 说明单词已全部加入缓冲，dic=1，为后续将缓冲加入链表,此时存在一个弊端：行首非字母或 he like.", ."连续非字母都会使缓冲为空加入到链表
		//                          解决办法：1.英文标点符号ASCI值几乎都在a的前面，所以链表的第一个元素是是空，z以后的值都会在链表的最后一位,遍历时忽略即刻
		//									2.全面无死角：向链表加入元素时进行cnt == 0 判断，cnt == 0 说明非字母,dic置0不操作, cnt ！= 0 则操作
		} else {
			dic = 1;
		}
		// 找到一个单词
		if( dic ){
			if( cnt == 0 ){
				dic = 0;
			} else {
				str[cnt] = '\0';
				s = (char*)malloc( cnt * sizeof(char) );
				strcpy( s,str );
				dic = 0;
				cnt = 0;
				add( list, s );
			}
			
		}
		c = fgetc( pf );
	}
	Sort( list );

	fclose( pf );
	pf = NULL;
	pf = fopen( "wordfreq.txt", "w" );
	printList( list, pf );
	return 0;
	
}