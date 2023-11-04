#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 带头结点
typedef struct _LNode{
	char* word;// 单词
	int cnt;//次数
	struct _LNode* pre;// 前驱
	struct _LNode* next;// 后继
} LNode;

typedef struct{
	LNode* head;
	LNode* tail;
} LinkList;
LinkList* creatList(){
	LinkList* list = (LinkList*)malloc( sizeof( LinkList ) );
	list->head = NULL;// 为NULL是空表
	list->tail = NULL;
	return list;
}

// 向链表末尾加入新字符串
void add( LinkList* list, char* word ){
	LNode* node = (LNode*)malloc( sizeof( LNode ) );
	node->pre = list->tail;// 第一次加入时，链表的头结点pre是NULL
	node->next = NULL;
	node->word = word;
	node->cnt = 1;
	if( list->head == NULL ){
		list->head = node;
	} else {
		list->tail->next = node;
	}
	list->tail = node;
}
// 判断字符串中是否存在该字符，存在则次数加1，然后向前移，否则返回0
int contain( LinkList* list, char* word ){
	LNode* start = list->head;
	int dic = 0;
	while( start ){
		if( strcmp( start->word, word ) == 0 ){
			dic = 1;
			start->cnt++;
			LNode* t = start->pre;
			while( t ){
				if( start->cnt <= t->cnt ){
					char* str = start->word;
					int temp = start->cnt;
					start->word = t->next->word;
					start->cnt = t->next->cnt;
					t->next->word = str;
					t->next->cnt = temp;
					break;
				}
				t = t->pre;
			}
			if( !t ){
				LNode tnode = *list->head;
				list->head->word = start->word;
				list->head->cnt = start->cnt;
				start->word = tnode.word;
				start->cnt = tnode.cnt;
			}
			break;
		}
		start = start->next;
	}
	return dic;
}

void printList( LinkList* list, FILE* out ){
	LNode* start = list->head;
	int cnt = 0;
	while( start ){	
//		printf("%s %d\n",start->word, start->cnt);
		fprintf( out, "%s %d\n",start->word, start->cnt );
		
		cnt++;
		if( cnt <= 100 ){
			printf("%s %d\n",start->word, start->cnt );
		}
		start = start->next;
	}
}

// 对指定区域[start,last]元素排序
void sortSub( LNode* start, LNode* last ){
	if( start == last ){
		return ;
	}
	LNode* min;
	LNode* i;
	LNode* j;
	for( i = start; i != last; i = i->next ){
		min = i;
		for( j = i->next; j != last->next; j = j->next ){
			if( strcmp( min->word, j->word ) > 0 ){
				min = j;
			}
		}
		char* st = min->word;
		min->word = i->word;
		i->word = st;
	}
}

void sort( LinkList* list ){
	LNode* start = list->head;
	LNode* last = start->next;
	int dic = 1;// 为1表示找到相同次数的单词段
	int cnt = 0;
	while( dic ){
		
		while( last && last->cnt == start->cnt   ){
			last = last->next;
			cnt++;
		}

		if( !last ){
			last = list->tail;
			dic = 0;
		} else {
			last = last->pre;
		}

		if( start != last ){
			sortSub( start, last );
			if( cnt == 102 ){
				return ;
			}
		}
		
		last = last->next;
		start = last;
	}
}

int main(){
	// 一：按次数排序，次数多的放头部，避免其在末尾，造成过多的访问
	// 二：输出时，从次数多输出，并且判断是否有次数相同的，如有同对其字符串排序输出
	// 实现结构： 链表：结点含有前驱和后继结点的指针域，还有保存字符串，次数的数据域
	
	
	LinkList* list = creatList();
	
	FILE* in = fopen( "article.txt", "r" );
	if( in == NULL ){
		return 0;
	}
	FILE* out = fopen( "wordfreq.txt", "w" );
	if( out == NULL ){
		return 0;
	}
	char word[20];// 保存要匹配的字符
	int cnt = 0;// 保存单词的长度
	char c = fgetc( in );
	while( c != EOF ){
		fputc( c, out );
		if( c >= 'A' && c <= 'Z' ){// 转换为小写
			c += 32;
		}
		if( c >= 'a' && c <= 'z' ){
			word[cnt++] = c;
		} else { // 找到一个单词
			if( cnt != 0 ){ // 确保存在. 的情况
				word[cnt] = '\0';
				if( !contain( list, word ) ){
					char* str = (char*)malloc( cnt*sizeof( char ) );
					strcpy( str, word );
					add( list, str );
				}
				cnt = 0;
			}
		}
		fputc( c, out );
		c = fgetc( in );
	}
	in = NULL;
	sort( list );
	printList( list, out );

	out = NULL;
	return 0;
}