#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define ElemType int
#define Status int
#define OK 1
#define ERROR 0

// 二叉树结构体 空树：NULL，根结点是一个指向 指向树的指针 的指针 
typedef struct _BinTree{
	ElemType data; // 数据域
	struct _BinTree* left;// 左子树
	struct _BinTree* right;// 右子树
} BinNode,*BinTree;
// 栈--用于树的前序，中序，后序
// 带头结点
typedef struct _Node{
	BinTree tree;
	struct _Node* next;
} Stack;

// ---------------------栈-----------------------
// 创建一个空栈
Stack* creatStack(void);
// 入栈-头插法
void push( Stack* stack, BinTree );
// 出栈
BinTree pop( Stack* s );
// 判空
Status isEmpty( Stack* stack );
// ---------------------栈-----------------------

// ---------------------二叉树-----------------------
// 创建一个空树
BinTree* creatTree(void);
// 向二叉树插入元素
Status insert( BinTree* binTree, ElemType e );
// 求树的深度
void getDepth( BinTree binTree, int hight );


int main(){
	

	BinTree* tree = creatTree();
	int num;
	scanf("%d",&num);
	int i;
	ElemType t;
	for( i = 0; i < num; i++ ){
		scanf("%d",&t);
		insert( tree, t );
	}
	
	getDepth( *tree, 1 );
		
	return 0;
}
// ---------------------栈-----------------------
// 创建一个空栈
Stack* creatStack(void){
	Stack* s = (Stack*)malloc( sizeof(Stack) );
	if( !s ){
		return NULL;
	}
	s->next = NULL;
	return s;
}
// 入栈-头插法
void push( Stack* stack, BinTree tree ){
	Stack* s = (Stack*)malloc( sizeof(Stack) );
	s->tree = tree;
	s->next = stack->next;
	stack->next = s;
}
// 出栈
BinTree pop( Stack* s ){
	Stack* t = s->next;
	BinTree tree = t->tree;
	s->next = t->next;
	free( t );
	return tree;
}
// 判空
Status isEmpty( Stack* stack ){
	assert( stack != NULL );
	if( stack->next == NULL ){
		return OK;
	} else {
		return ERROR;
	}
}
// ---------------------栈-----------------------

// ---------------------二叉树-----------------------
// 创建一个空树
BinTree* creatTree(void){ // 搭配非递归法使用
	BinTree* tree = (BinTree*)malloc( sizeof(BinTree) );
	*tree = NULL;
	return tree;
}
// 向二叉树插入元素
Status insert( BinTree* binTree, ElemType e ){// 非递归法-传入参数为指向根结点的指针
	BinTree tree = (BinTree)malloc( sizeof(BinNode) );
	if( !tree ){
		return ERROR;
	}
	tree->data = e;
	tree->left = NULL;
	tree->right = NULL;
	if( *binTree == NULL ){
		*binTree = tree;
	} else {
		BinTree pre;// 指向要要插入位置的父结点
		while( *binTree ){// 找到要插入的位置
			pre = *binTree;
			if( (*binTree)->data > e ){
				binTree = &(*binTree)->left;
			} else if( (*binTree)->data < e ){
				binTree = &(*binTree)->right;
			} else { // 已存在该元素
				return ERROR;
			}
		}
		if( pre->data > e ){
			pre->left = tree;
		} else {
			pre->right = tree;
		}
	}
	return OK;
}

// 求深度
void getDepth( BinTree binTree, int hight ){// 递归法
	if( binTree ){
		if( binTree->left ){
			getDepth( binTree->left, hight+1 );
		}
		if( binTree->right, hight+1 ){
			getDepth( binTree->right, hight+1 );
		}
		
		if( !binTree->left && !binTree->right){
			printf("%d %d\n",binTree->data, hight);
		}

	} 
}
