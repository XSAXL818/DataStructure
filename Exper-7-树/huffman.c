#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

typedef union Data Elem;

// 哈夫曼树
typedef struct _TNode{
	struct _TNode* left;// 左右子树
	struct _TNode* right;
	int cnt;// 该结点被访问的次数
	char c;// 作为叶子结点，保留的字符信息
} *Huffman,TNode;// 哈夫曼树
union Data{
	int value;
	TNode* tree;
};
// 栈,头插
typedef struct _SNode{
	struct _SNode* next;
	union Data data;
} *Stack,SNode;

// 建立一个空栈
Stack creatStack(void){
	Stack stack = (Stack)malloc( sizeof(SNode) );
	stack->next = NULL;
	return stack;
}
// 判空
int isEmpty( Stack stack ){
	assert( stack!=NULL );
	
	if( !stack->next ){
		return 1;
	} else {
		return 0;
	}
}
// 入栈-头插
void push1( Stack stack, int value ){
	SNode* node = (SNode*)malloc( sizeof(SNode) );
	node->data.value = value;
	node->next = stack->next;
	stack->next = node;
}
void push2( Stack stack, TNode* tree ){
	SNode* node = (SNode*)malloc( sizeof(SNode) );
	node->data.tree = tree;
	node->next = stack->next;
	stack->next = node;
}

// 出栈
int pop1( Stack stack ){
	assert( stack != NULL && stack->next != NULL );
	
	SNode* p = stack->next;
	int value = p->data.value;
	stack->next = p->next;
	free( p );
	return value;
}
TNode* pop2( Stack stack ){
	assert( stack != NULL && stack->next != NULL );
	
	SNode* p = stack->next;
	TNode* node = p->data.tree;
	stack->next = p->next;
	free( p );
	return node;
}
// 或许栈顶元素
int getTop1( Stack stack ){
	assert( stack != NULL && stack->next != NULL );
	return stack->next->data.value;
}
TNode* getTop2( Stack stack ){
	assert( stack != NULL && stack->next != NULL );
	return stack->next->data.tree;
}
// 摧毁栈
void destoryStack( Stack stack ){
	SNode* start;
	while( stack ){
		start = stack;
		stack = stack->next;
		free( start );
	}
}

TNode* creatTNode(void){// 创建一个根结点(叶子节点)
	TNode* node = (TNode*)malloc( sizeof( TNode ) );
	node->left = NULL;
	node->right = NULL;
	return node;
}

void insert( Huffman huffman, char* code ){// 传入一个字符串，创建相应的叶子结点
	int len = strlen( code );
	TNode* start = huffman;
	int i = 2;
	while( i < len ){
		if( code[i] == '0' ){// 左子树
			if( !start->left ){// 左子树为空
				start->left = creatTNode();
			}
			start = start->left;
		} else {
			if( !start->right ){
				start->right = creatTNode();
			}
			start = start->right;
		}
		i++;
	}// 循环结束后，start所指向的即为叶子节点，用于保存编码符号
	start->c = code[0];
}
void preoder( Huffman huffman ){
	Stack stack1 = creatStack();// 用于保存该结点出现的次数
	Stack stack2 = creatStack();// 保存根结点
	TNode* start = huffman;
	
	do{
		while( start ){
			push1( stack1, 0 );
			push2( stack2, start );
			start = start->left;
		}
		
		if( pop1( stack1 ) ){
			printf("%c\n",pop2( stack2 )->c);
		} else {
			start = getTop2( stack2 )->right;
			push1( stack1, 1 );
		}
		
	} while( !isEmpty( stack2 ) );
}
// 传入一个编码集和其长度，返回一个创建好的哈夫曼树
Huffman creatHuffman( char* strs[], int len ){
	
	Huffman huffman = creatTNode();
	int i;
	for( i = 0; i < len; i++ ){
		insert( huffman, strs[i] );
	}
//	preoder( huffman );
	return huffman;
}
// 传入一个哈夫曼树，将各个结点的访问计数器清零,后序遍历,可能麻烦，但不为别的，为的是复习一遍
void clearCnt( Huffman huffman ){
	Stack stack1 = creatStack();// 用于判断当前结点是否第二次访问，后序第一次遍历到根结点不访问
	Stack stack2 = creatStack();// 用于保存待访问的结点
	
	TNode* node = huffman;
	do{
		while( node ){
			push1( stack1, 0 );
			push2( stack2, node );
			node = node->left;
		}

		if( pop1( stack1 ) ){
//			printf("%c\n",pop2( stack2 )->c);// 后序遍历访问处
			pop2( stack2 )->cnt = 0;
//			node = NULL;// 后序遍历的最后一个元素时，不设为NULL为导致死循环
		} else {

			node = getTop2( stack2 )->right;
			push1( stack1, 1 );

		}
	}while( !isEmpty( stack2 ) );
	
}
void printCnt( Huffman huffman ){
	Stack stack1 = creatStack();// 用于保存该结点出现的次数
	Stack stack2 = creatStack();// 保存根结点
	TNode* start = huffman;
	
	do{
		while( start ){
			push1( stack1, 0 );
			push2( stack2, start );
			start = start->left;
		}
		
		if( pop1( stack1 ) ){
			printf("%d ",pop2( stack2 )->cnt);
		} else {
			start = getTop2( stack2 )->right;
			push1( stack1, 1 );
		}
		
	} while( !isEmpty( stack1 ) );
}

void conver( Huffman huffman, char* code, int length ){
	int i = 0;
	TNode* start = huffman;
	while( i < length ){
		start->cnt++;
		if( code[i] == '0' ){
			
			start = start->left;
		} else {
			start = start->right;
		}
		
		if( !start->left && !start->right ){
			start->cnt++;
			printf("%c",start->c);
			start = huffman;
		}
		
		i++;
	}
	printf("\n");
	printCnt( huffman );
	printf("\n");
}

int main(){
	

	
	char* strs[50];// strs[i]保存第i个编码的信息 编码符号：编码
	int length;
	int n;
	char str[1000];
	char* code;
	scanf("%d",&n);
	length = n;
	while( n-- ){
		scanf("%s",str);
		code = (char*)malloc( (strlen(str) + 1)*sizeof(char) );
		strcpy( code, str );
		strs[n] = code;
	}
	
	FILE* in = fopen( "in.txt", "r" );
	fscanf( in, "%s", str );
	Huffman huffman = creatHuffman( strs, length );

	clearCnt( huffman );

	conver( huffman, str, strlen(str) );

	in = NULL;
	
	return 0;
}
