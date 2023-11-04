#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 一个储存字符串和int的结点
typedef struct{
	int cnt;
	char* str;
} Word;
// 结点,链表的结点,每个结点存储一个单词和其频率
typedef struct _Node{
	Word word;
	struct _Node* next;
} *LinkList,Node;
// 创建一个链表
LinkList creatLinkList(){
	LinkList list = (LinkList)malloc( sizeof(Node) );
	if( list == NULL ){
		return NULL;
	}
	list->next = NULL;
	return list;
}
// 向链表链接元素，按字符串从小到大
void add( LinkList list, char* str, int cnt ){
	
	// 如果dic = 1,正在比较的结点的前一个结点比str小
	int dic = 0;
	Node* start = list;
	while( start->next ){
		dic = strcmp( str,start->next->word.str );
		if( dic == 0 ){
			start->next->word.cnt++;
			break;
		} else if( dic < 0 ){
			Node* p = (Node*)malloc( sizeof( Node ) );
			p->word.cnt = 1;
			p->word.str = str;
			p->next = start->next;
			start->next = p;
			break;
		}
		start = start->next;
	}
	if( start->next == NULL ){
		Node* p = (Node*)malloc( sizeof( Node ) );
		p->word.cnt = 1;
		p->word.str = str;
		p->next = start->next;
		start->next = p;
	}
	
}
void printList( LinkList list ){
	list = list->next;
	while( list ){
		printf("%s %d\n",list->word.str,list->word.cnt);
		list = list->next;
	}
}

int main(){
	
	LinkList list = creatLinkList();
	FILE* pf = fopen( "article.txt", "r" );
	// 文件是否打开失败
	if( pf == NULL ){
		printf("文件打开失败！\n");
		return 0;
	}
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
				add(list,s,1);
			}
			
		}
		c = fgetc( pf );
	}
	printList( list );
	// 排序
	fclose( pf );
	pf = NULL;
	
	return 0;
}