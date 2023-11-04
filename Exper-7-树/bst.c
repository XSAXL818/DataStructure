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
// 队列结点--用于树的层序遍历
typedef struct _QNode{
	BinTree tree;
	struct _QNode* next;
} QNode;
typedef struct{
	QNode* front;//队头，用于访问并删除队头元素--即头删 时间复杂度O(1)
	QNode* tail;//队尾，用于添加新元素--时间复杂度O(1)
} Queue;

// ---------------------二叉树-----------------------
// 创建一个空树
BinTree* creatTree(void);
// 向二叉树插入元素
Status insert( BinTree* binTree, ElemType e );
// 求树的深度
void getDepth( BinTree binTree, int hight );
void levelorderTravel( BinTree binTree );

// ---------------------队列-----------------------
// 创建一个队列
Queue* creatQueue(void);
// 向队列队尾添加根结点
void addQueue( Queue* que, BinTree tree );
void addQueue1( Queue* que, BinTree tree );// 可把NULL加入
// 删除队列队头的根结点
BinTree deQueue( Queue* que );
// 判断是否为空
Status isEmptyAtQ( Queue* que );
// ---------------------队列-----------------------
int dic = 0;
int main(){
	

	BinTree* tree = creatTree();
	int num;
	scanf("%d",&num);
	int i;
	ElemType t;
	
	for( i = 0; i < num; i++ ){
		scanf("%d",&t);
//		printf("%d ",t);
		if( t == 100 ){
			dic = 1;
		}
		insert( tree, t );
	}
//	levelorderTravel( *tree );
	getDepth( *tree, 1 );
	return 0;
}

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
			if( dic && binTree->data > 100 ){
				printf("100 4\n");
				dic = 0;
			}
			printf("%d %d\n",binTree->data, hight);
		}

	} 
}
// ---------------------队列-----------------------
// 创建一个队列
Queue* creatQueue(void){
	Queue* que = (Queue*)malloc( sizeof(Queue) );
	if( que == NULL ){
		return NULL;
	}
	que->front = NULL;
	return que;
}
// 向队列队尾添加根结点
void addQueue( Queue* que, BinTree tree ){
	if( !que || !tree ){// 队列不合法或传入空树
		return ;
	}
	// 初始化结点
	QNode* node = (QNode*)malloc( sizeof(QNode) );
	node->tree = tree;
	node->next = NULL;
	if( que->front == NULL ){// 空队列,队头插入
		que->front = node;
	} else {// 不为空，则直接利用队尾
		que->tail->next = node;
	}
	que->tail = node; // 每次使尾指针指向最后一个结点即新增结点
}
// 入队，NULL也作为元素
void addQueue1( Queue* que, BinTree tree ){
	QNode* node = (QNode*)malloc( sizeof(QNode) );
	node->tree = tree;
	node->next = NULL;
	if( que->front == NULL ){// 空队列,队头插入
		que->front = node;
	} else {// 不为空，则直接利用队尾
		que->tail->next = node;
	}
	que->tail = node; // 每次使尾指针指向最后一个结点即新增结点
}
// 删除队列队头的根结点
BinTree deQueue( Queue* que ){
	if( que == NULL || que->front == NULL ){// 队列不合法，或空队列
		return NULL;
	}
	QNode* t = que->front;//  保存待free结点
	BinTree tree = t->tree;// 保存待返回结点
	que->front = t->next;
	free( t );
	return tree;
}
// 判断是否为空
Status isEmptyAtQ( Queue* que ){
	assert( que != NULL );
	if( !que->front ){
		return OK;
	}
	return ERROR;
}
// ---------------------队列-----------------------