#include <stdio.h>
#include <stdlib.h>
// 用于储存后缀表达式的链表,ch == '.'则储存的为数字，否则为运算符
typedef struct _Node{
	int number;
	char ch;
	struct _Node* next;
} *LinkList,Node;
// 用于储存运算符的堆栈 用于中缀表达式转换为后缀表达式
typedef struct{
	char *ch;
	int top;
} chStack;
// 用于储存运算符的堆栈 用于中缀表达式转换为后缀表达式
typedef struct{
	int *number;
	int top;
} numberStack;

// 向链表添加元素
void addElem( LinkList list, int number, char ch ){
	Node* start = list;
	// 找到末尾结点
	while( start->next ){
		start = start->next;
	}
	Node* node = (Node*)malloc( sizeof(Node) );
	node->number = number;
	node->ch = ch;
	node->next = NULL;
	start->next = node;
}
// 入栈
void chPop( chStack* chstack, char ch ){
	chstack->ch[++chstack->top] = ch;
}
void numberPop( numberStack* numberstack, int number ){
	numberstack->number[++numberstack->top] = number;
}
// 出栈
char chPush( chStack* chstack ){
	return chstack->ch[chstack->top--];
}
int numberPush( numberStack* numberstack ){
	return numberstack->number[numberstack->top--];
}
// 用于判断运算符优先级,c1>c2: 1  否则为0
int compare( char c1, char c2 ){
	if( c1 == '*' || c1 == '/' ){
		if( c2 == '+' || c2 == '-' ){
			return 1;
		} else {
			return 0;
		}
	} else {
		if( c2 == '+' || c2 == '-' ){
			return 0;
		} else {
			return -1;
		}
	}
}
// 将中缀表达式转换为后缀
LinkList conversion( char* polyn ){
	LinkList list = (Node*)malloc( sizeof(Node) ); 
	list->next = NULL;
	// 用于储存运算符
	chStack chstack;
	chstack.top = -1;
	chstack.ch = (char*)malloc( 10*sizeof(char) );
	int number = 0;
	
	while( *polyn != '=' ){
		if( *polyn == ' ' ){
			// 空格略过
		} else {
			// 获取数字,否则获取运算符
			if( *polyn >= '0' && *polyn <= '9' ){
				// 判断是否为多位数
				number = *polyn - 48;
				while( *(polyn+1) >= '0' && *(polyn+1) <= '9' ){
					number *= 10;
					number += *(polyn+1) - 48;
					polyn++;
				}
				// 将数字加入链表
				addElem( list, number, '.' );
			} else {
				// 将运算符加入链表
				// 空栈则先进入一个运算符,否则进行运算符比较
				if( chstack.top == -1 ){
					chPop( &chstack, *polyn );
				} else {
					int dic = compare( chstack.ch[chstack.top], *polyn );
					if( dic > 0 ){
						addElem( list, 0, chPush( &chstack ) );
						polyn--;
					} else if( dic == 0 ){
						addElem( list, 0, chPush( &chstack ) );
						chPop( &chstack, *polyn );
					} else {
						chPop( &chstack, *polyn );
					}
				}
			}
		}
		polyn++;
	}
	// 将运算符全部加入链表
	while( chstack.top > -1 ){
		addElem( list, 0, chPush( &chstack ) );
	}
//	Node* start = list->next;
//	while( start ){
//		if( start->ch == '.' ){
//			printf("%d ",start->number);
//		} else {
//			printf("%c ",start->ch);
//		}
//		start = start->next;
//	}
//	printf("\n");
	return list;
}
// 求后缀表达式值
int solve( LinkList list ){
	// 用于计算的堆栈
	numberStack numStack;
	numStack.top = -1;
	numStack.number = (int*)malloc( 10 * sizeof(int) );
	int sum = 0;
	// 遍历多项式
	list = list->next;
	while( list ){
		if( list->ch == '.' ){
			numberPop( &numStack, list->number );
		} else {
			int num2 = numberPush( &numStack );
			int num1 = numberPush( &numStack );
			if( list->ch == '+' ){
				sum = num1 + num2;
			} else if( list->ch == '-' ){
				sum = num1 - num2;
			} else if( list->ch == '*' ){
				sum = num1 * num2;
			} else{
				sum = num1 / num2;
			}
			numberPop( &numStack, sum );
		}
		list = list->next;
	}
	
	return numberPush( &numStack );
}
int main(){
	
	// 读取表达式
	char polyn[70];
	gets( polyn );
	// 将表达式转换为后缀表达式
	LinkList list = conversion( polyn );
	// 计算中缀表达式
	int sum = solve( list );
	printf("%d",sum);
	return 0;
}