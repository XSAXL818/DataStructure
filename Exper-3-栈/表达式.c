#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
// 存储后缀表达式的链表，带头结点，使用头插法
typedef struct _Node{
	double num;
	char ch;
	struct _Node* next;
} Node;
typedef struct{
	Node* head;
	Node* tail;
} *LinkList,List;
// 堆栈-用于计算表达式
typedef struct _Expre{
	double data;
	struct _Expre* next;
} *Expression,Expre;
typedef struct _Ch{
	char ch;
	struct _Ch* next;
} *ChStack,chStack;
// 创建一个链表-
LinkList creatLinkList();
// 创建一个堆栈
Expression creatExpre();
ChStack creatChStack();
// 入栈
void exprePush( Expression expre, double data );
void chPush( ChStack chstack, char ch );
// 遍历后缀表达式元素
void printLinkList( LinkList list );
// 添加一个元素-尾插法
void add( LinkList, double num, char ch );
// 出栈
double exprePop( Expression expre );
char chPop( ChStack chstack );
// 计算后缀表达式
double solveExpre( LinkList list );
// 比较两个字符的优先级 返回1，c1优先级大于c2，否则c2优先级大于等于c1
int highPriority( char c1, char c2 );
// 中缀表达式换算为后缀表达式,返回链表形式
LinkList getPostExpre( char* str, int length );


int main(){
	
	
	
//	3+5*(2+(3*4-1)-3/1-4)-3
//	6-2*(3-2*3)+3/1-4
	char t[1000];
	char str[1000];
	gets( t );
	int i;
	int length = 0;
	for( i = 0; i < strlen(t) && t[i] != '='; i++ ){
		if( t[i] != ' ' ){
			str[length++] = t[i];
		}
	}
	str[length] = '\0';
	printf("%s",str);
//	printf("请输入所求中缀表达式：\n");
//	scanf("%s",str);
//	LinkList list = getPostExpre( str, strlen(str) );
//	printf("后缀表达式为：\n");
//	printLinkList( list );
//	printf("表达式值为：");
//	double sum = solveExpre( list );
//	printf("%.2f\n",sum);
	return 0;
}
// 创建一个链表
LinkList creatLinkList(){
	LinkList list = (LinkList)malloc( sizeof(List) );
	list->head = NULL;
	return list;	
}
// 创建一个表达式-链表结构
Expression creatExpre(){
	Expression expre = (Expression)malloc( sizeof(Expre) );
	expre->next = NULL;
	return expre;
}
// 存储运算符的堆栈
ChStack creatChStack(){
	ChStack chstack = (ChStack)malloc( sizeof(chStack) );
	chstack->next = NULL;
	return chstack;
}
// 添加一个元素
void add( LinkList list, double num, char ch ){
	Node* node = (Node*)malloc( sizeof(Node) );
	node->ch = ch;
	node->num = num;
	node->next = NULL;
	if( list->head == NULL ){
		list->head = node;
		list->tail = node;
	} else {
		list->tail->next = node;
	}
	list->tail = node;
}
// 入栈
void exprePush( Expression expre, double data ){
	Expre* node = (Expre*)malloc( sizeof(Expre) );
	node->data = data;
	node->next = expre->next;
	expre->next = node;
}
void chPush( ChStack chstack, char ch ){
	ChStack node = (ChStack)malloc( sizeof(chStack) );
	node->ch = ch;
	node->next = chstack->next;
	chstack->next = node;
}
// 遍历链表元素
void printLinkList( LinkList list ){
	Node* head = list->head;
	while( head ){
		if( head->ch == '!' ){
			printf("%.2f ",head->num);
		} else {
			printf("%c ",head->ch);
			
		}
		head = head->next;
	}
	printf("\n");
}

// 出栈
double exprePop( Expression expre ){
	assert( expre->next != NULL );
	double t = expre->next->data;
	Expre* node = expre->next;
	expre->next = node->next;
	free( node );
	return t;
}
char chPop( ChStack chstack ){
	assert( chstack->next != NULL );
	chStack* node = chstack->next;
	char t = node->ch;
	chstack->next = node->next;
	free( node );
	return t;
}
// 计算后缀表达式
double solveExpre( LinkList list ){
	Expression expre = creatExpre();
	Node* head = list->head;
	while( head ){
		double sum;
		if( head->ch == '!' ){
			exprePush( expre, head->num );
		} else {
			int num2 = exprePop( expre );
			int num1 = exprePop( expre );
			if( head->ch == '+' ){
				sum = num1 + num2;
			} else if( head->ch == '-' ){
				sum = num1 - num2;
			} else if( head->ch == '*' ) {
				sum = num1 * num2;
			} else {
				sum = num1 / num2;
			}
			exprePush( expre, sum );
		}
		head = head->next;
	}
	return exprePop( expre );
}
// 比较两个字符的优先级
int highPriority( char c1, char c2 ){
	if( c1 == '(' && (c2 == '+' || c2 == '-' || c2 == '*' || c2 == '/' ) ){
		return 1;
	} else if( ( c1 == '*' || c1 == '/' ) && ( c2 == '+' || c2 == '-' ) ){
		return 1;
	} else if( ( c1 == '+' || c1 == '-') && ( c2 == '+' || c2 == '-') ){
		return 0;
	} else if( ( c1 == '*' || c1 == '/') && ( c2 == '*' || c2 == '/') ){
		return 0;
	} else {
		return -1;
	}
}
// 中缀表达式换算为后缀表达式,返回链表形式 
// 当前者运算符大于等于后者，则把前者输出
// 
LinkList getPostExpre( char* str, int length ){
	int i;
	LinkList list = creatLinkList();
	ChStack chstack = creatChStack();
	add( list, str[0] - 48, '!' );
	chPush( chstack, str[1] );
	ChStack t;
	for( i=2; i < length; i++ ){
		
		if( str[i] >= '0' && str[i] <= '9' ){
			add( list, str[i] - 48, '!' );
		} else if( str[i] == '(' ){
			chPush( chstack, str[i] );
		} else if( str[i] == ')' ){
			char ch;
			do{
				ch = chPop( chstack );
				if( ch != '(' ){
					add( list, 0, ch );
				}	
			}while( ch != '(' );
		} else {
			char c1 = chPop( chstack );
			char c2 = str[i];
			int dic = highPriority( c1, c2 );
			if( dic == 0 ){
				add( list, 0, c1 );
				chPush( chstack, c2 );
			} else if( dic == -1 ){
				chPush( chstack, c1 );
				chPush( chstack, c2 );
			} else {
				if( c1 == '(' ){
					chPush( chstack, c1 );
					chPush( chstack, c2 );
				} else {
					add( list, 0, c1 );
					chPush( chstack, c2 );
					if( chstack->next->next != NULL ){
						
						char c3 = chPop( chstack );
						char c4 = chPop( chstack );
						int dic = highPriority( c3, c4 );
						if( dic == 0 ){
							add( list, 0, c4 );
							chPush( chstack, c3 );
						} else {
							chPush( chstack, c4 );
							chPush( chstack, c3 );
						}
					}
				}
			}

		}	
//		t = chstack->next;
//		while( t ){	
//			printf("%c ",t->ch);
//			t = t->next;
//		}
//		printf("\n");
//		printLinkList( list );
	}

	t = chstack->next;
	while( t ){	
		if( t->ch != '(' ){
			add( list, 0, t->ch );
		}
		t = t->next;
	}
	return list;
}

