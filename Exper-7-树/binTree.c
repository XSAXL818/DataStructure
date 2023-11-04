#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

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
// 队列结点--用于树的层序遍历
typedef struct _QNode{
	BinTree tree;
	struct _QNode* next;
} QNode;
typedef struct{
	QNode* front;//队头，用于访问并删除队头元素--即头删 时间复杂度O(1)
	QNode* tail;//队尾，用于添加新元素--时间复杂度O(1)
} Queue;
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
// ---------------------二叉树-----------------------
// 创建一个空树
BinTree* creatTree(void);
// 向二叉树插入元素
Status insert( BinTree* binTree, ElemType e );
BinTree insert1( BinTree binTree, ElemType e );
// 删除二叉树的元素
BinTree dele( BinTree binTree, ElemType e );
// 求树的深度
int getDepth( BinTree binTree );
// 查找,输入一个值，返回该值所在根节点
BinTree findValue( BinTree binTree, ElemType e );// 非递归
BinTree findValue1( BinTree binTree, ElemType e ); // 递归
// 查找最大最小元素
BinTree findMin( BinTree binTree );
BinTree findMax( BinTree binTree );
BinTree findMin1( BinTree binTree );// 非递归
BinTree findMax1( BinTree binTree );// 非递归
// 前序遍历二叉树：根，左，右
void preorderTravel( BinTree binTree );
void preorderTravel1( BinTree binTree );// 非递归
void preorderTravel2( BinTree binTree );// 非递归 -class
void preorderTravel3( BinTree binTree );// 非递归 -class-PPT
// 中序遍历二叉树：左，根，右
void inorderTravel( BinTree binTree );
void inorderTravel1( BinTree binTree );// 非递归
// 后序遍历二叉树：左，右，根
void postorderTravel( BinTree binTree );
void postorderTravel1( BinTree binTree );// 非递归
void postorderTravel2( BinTree binTree );// 非递归
void postorderTravel3( BinTree binTree );// 非递归
// 层序遍历二叉树
void levelorderTravel( BinTree binTree );
void printTree( BinTree binTree );
// 获取叶子结点个数
int getLeaf( BinTree binTree );// 递归
int getLeaf1( BinTree binTree );// 非递归
// 获取所有结点个数
int getTNode( BinTree binTree );
int getTNode1( BinTree binTree );
// ---------------------二叉树-----------------------

// 菜单
int view( BinTree binTree );
int main(){
	
	clock_t start,end;
	double total;

	BinTree* tree = creatTree();
	insert( tree, 50 );
	insert( tree, 20 );
	insert( tree, 70 );
	insert( tree, 10 );
	insert( tree, 12 );
	insert( tree, 30 );
	insert( tree, 5 );
	insert( tree, 25 );
	insert( tree, 60 );
	insert( tree, 80 );
	insert( tree, 84 );
	insert( tree, 77 );
	insert( tree, 65 );
	int select;
	int num;
	while( 1 ){
		select = view( *tree );
//		1.删除结点		2.添加结点		3.查值 	4.获取最大最小元素
		switch( select ){
			case 1:
				printf("请输入要删除的值：\n");
				scanf("%d",&num);
				dele( *tree, num );
				break;
			case 2:
				printf("请输入要添加的值：\n");
				scanf("%d",&num);
				insert( tree, num );
				break;
			case 3:
				printf("请输入要查找的值：\n");
				scanf("%d",&num);
				if( !findValue( *tree, num ) ){
					printf("未找到！\n");
				} else {
					printf("存在该元素!\n");
				}
				break;
			case 4:
				printf("最大值为：%d\n最小值为：%d\n",findMax1( *tree )->data,findMin1( *tree )->data);
				break;
		}
	}
	
	
	
	printf("\n");
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
BinTree insert1( BinTree binTree, ElemType e ){// 递归法
	BinTree tree = (BinTree)malloc( sizeof(BinNode) );
	tree->left = NULL;
	tree->right = NULL;
	tree->data = e;
	if( !binTree ){// 传入NULL返回一个根结点
		return tree;
	} else {
		if( binTree->data > e ){
			binTree->left = insert1( binTree->left, e );
		} else if( binTree->data < e ){
			binTree->right = insert1( binTree->right, e );
		} else {
			return binTree;
		}
	}
	return binTree;
}
// 删除二叉树的元素
// 函数只递归一次的功能：非找到-根结点左右子域指向一个新树即调用本函数后返回的根结点,找到-
// 1.有两个孩子，则找到最小右孩子
// 2.一个或没有，根结点直接换作其孩子结点
// 1.具体操作-根结点指向 调用本函数返回的结点
// 2.有左右：找到最小右孩子，然后根结点拷贝其值，再调用删除函数，将最小右孩子删除-最小右孩子必定是没有左孩子
//    不同时左右：当前结点直接赋值其为其子孩子
// 思路： 如果当前结点未找到要删的元素，则让根结点的左右结点分别指向
BinTree dele( BinTree binTree, ElemType e ){//递归
	if( !binTree ){ // 所有结点访问完，打印未找到！
		printf("未找到！\n");
	} else if( binTree->data > e ){// 当前未找到
		binTree->left = dele( binTree->left, e );// 转移去删除左子树
	} else if( binTree->data < e ){
		binTree->right = dele( binTree->right, e );//  转移去删除左子树
	} else {// 找到要删的结点,判断是否有两个孩子结点
		if( binTree->left && binTree->right ){
			BinTree min = findMin( binTree->right );// 最小右孩子
			binTree->data = min->data;// 拷贝最小右孩子的值
			binTree->right = dele( binTree->right, binTree->data );// 将最小右孩子删除
		} else {// 最多一个孩子结点,当前结点的根结点直接舍去，赋值其子孩子
			BinTree t = binTree;
			if( binTree->left ){
				binTree = binTree->left;
			} else {
				binTree = binTree->right;
			}
			free( t );// 释放需删除结点
		}
	}
	return binTree; // 递归的关键所在，起到老树链接新树的作用
}
// 查找,输入一个值，返回该值所在根节点
BinTree findValue1( BinTree binTree, ElemType e ){ // 非递归
	while( binTree ){
		if( binTree->data > e ){
			binTree = binTree->left;
		} else if( binTree->data < e ){
			binTree = binTree->right;
		} else {
			return binTree;
		}
	}
	return NULL;
}
BinTree findValue( BinTree binTree, ElemType e ){ // 递归
	if( !binTree ){
		return NULL;
	} else {
		if( binTree->data > e ){
			return findValue( binTree->left, e );
		} else if( binTree->data > e ){
			return findValue( binTree->right, e );
		} else {
			return binTree;
		}
	}
	
}
// 查找最大最小元素
BinTree findMin( BinTree binTree ){// 递归
	if( !binTree ){
		return NULL;
	} else if( !binTree->left ){
		return binTree;
	} else {
		return findMin( binTree->left );
	}
}
BinTree findMin1( BinTree binTree ){// 非递归
	if( !binTree ){
		return NULL;
	}
	while( binTree->left ){
		binTree = binTree->left;
	}
	return binTree;
}
BinTree findMax( BinTree binTree ){
	if( !binTree ){
		return NULL;
	} else if( !binTree->right ){
		return binTree;
	} else {
		return findMax( binTree->right );
	}
}
BinTree findMax1( BinTree binTree ){
	if( !binTree ){
		return NULL;
	}
	while( binTree->right ){
		binTree = binTree->right;
	}
	return binTree;
}
// 求深度
int getDepth( BinTree binTree ){// 递归法
	int left,right;
	if( binTree ){
		left = 1 + getDepth( binTree->left );
		right = 1 + getDepth( binTree->right );
		return left > right ? left : right;
	} else {
		return 0;
	}
}
// 前序遍历二叉树：根，左，右
void preorderTravel( BinTree binTree ){// 递归法
	if( binTree ){
		printf("%d ",binTree->data);
		preorderTravel( binTree->left );
		preorderTravel( binTree->right );
	}		
}
void preorderTravel1( BinTree binTree ){// 非递归
	Stack* stack = creatStack();
	while( 1 ){
		while( binTree ){// 每次先输出根节点，再遍历其左子树
			printf("%d ", binTree->data );
			push( stack, binTree );// 先进后出-保证可以从现有基础逆推出右子树
			binTree = binTree->left;
		}
		// 根-左结点访问完，此时令上循环遍历右子树
		if( !isEmpty( stack ) ){ // 为空即，最开始树的右子树访问完，结束循环
			binTree = pop( stack )->right;
		} else {
			return;
		}
	}	
	free( stack );
}
void preorderTravel2( BinTree binTree ){// 非递归 -class
	if( !binTree ){
		return;
	}
	BinTree stack[1000];// 栈
	int top = 0;// 栈顶指针
	
	while( 1 ){
		printf("%d ",binTree->data);
		if( binTree->right ){ // 右子树不为空则进栈
			stack[top++] = binTree->right;
		} 
		if( top == 0 ){ // 栈空说明右子树访问完
			break;
		}
		if( binTree->left ){// 左子树入栈
			binTree = binTree->left;
		} else {// 左子树为空则说明左子树遍历完，此时出栈遍历当前结点的右子树
			binTree = stack[--top];
		}
	}
}
void preorderTravel3( BinTree binTree ){// PPT
	if( !binTree ){
		return;
	}
	BinTree stack[1000];
	int top = 0;
	BinTree p = binTree;
	BinTree q;
	do{
		printf("%d ",p->data);
		q = p->right;
		if( q ){
			stack[top++] = q;
		}
		p = p->left;
		if( p == NULL ){
			if( top == 0 ){
				break;
			}
			p = stack[--top];
		}
	} while( p!= NULL );
}
// 中序遍历二叉树：左，根，右
void inorderTravel( BinTree binTree ){// 递归法
	if( binTree ){
		inorderTravel( binTree->left );
		printf("%d ",binTree->data);
		inorderTravel( binTree->right );
	}
}
void inorderTravel1( BinTree binTree ){// 非递归,在前序的基础上更改访问的时间即可
	Stack* stack = creatStack();
	while( 1 ){
		while( binTree ){// 每次先输出根节点，再遍历其左子树
			push( stack, binTree );// 先进后出-保证可以从现有基础逆推出右子树
			binTree = binTree->left;
		}
		// 根-左结点访问完，此时令上循环遍历右子树
		if( !isEmpty( stack ) ){ // 为空即，最开始树的右子树访问完，结束循环
			binTree = pop( stack );
			printf("%d ", binTree->data );
			binTree = binTree->right;
		} else {
			return;
		}
	}
	free( stack );
}
// 后序遍历二叉树：左，右，根
void postorderTravel( BinTree binTree ){// 递归法
	if( binTree ){
		postorderTravel( binTree->left );
		postorderTravel( binTree->right );
		printf("%d ",binTree->data);
	}
}
// 利用前序与后序的关系转换,前序：根左右  入栈时调换左右子树即得 根右左，然后逆序得到 左右根
void postorderTravel1( BinTree binTree ){// 非递归法
	Stack* stack1 = creatStack();// 用于获取前序的左右子树转换
	Stack* stack2 = creatStack();// 用于获取后序
	while( 1 ){
		while( binTree ){// 每次先输出根节点，再遍历其右子树
			push( stack2, binTree );
			push( stack1, binTree );// 先进后出-保证可以从现有基础逆推出左子树
			binTree = binTree->right;
		}
		// 根-右结点访问完，此时令上循环遍历左子树
		if( !isEmpty( stack1 ) ){ // 为空即，最开始树的左子树访问完，结束循环
			binTree = pop( stack1 );
			binTree = binTree->left;
		} else {
			break;
		}
	}
	while( !isEmpty( stack2 ) ){
		printf("%d ",pop( stack2 )->data);
	}
	free( stack1 );
	free( stack2 );
}
void postorderTravel2( BinTree binTree ){// 非递归法-PPT
	if( !binTree ){
		return;
	}
	BinTree stack1[1000];
	int stack2[1000];
	int top = 0;
	BinTree p = binTree;
	do{
		while( p ){
			++top;
			stack1[top] = p;
			stack2[top] = 0;
			p = p->left;
		}
		if( stack2[top] == 0 ){
			p = stack1[top]->right;
			stack2[top] = 1;
		} else {
			p = stack1[top--];
			printf("%d ",p->data);
			p = NULL;
		}
	}while( top != 0 );
	
}
void postorderTravel3( BinTree binTree ){
	if( !binTree ){
		return;
	}
	BinTree stack1[1000];
	int stack2[1000];
	int top=0,b=1;
	BinTree p = binTree;
	do{
		while( p ){
			stack1[++top] = p;
			stack2[top] = 0;
			p = p->left;
		}
		if( top == 0 ){
			b = 0;
		} else if( stack2[top] == 0 ){
			stack2[top] = 1;
			p = stack1[top]->right;
		} else {
//			p = stack1[top--];
//			printf("%d ",p->data);
//			p = NULL;
			printf("%d ",stack1[top--]->data);
		}
		
	}while( b );
}
// 层序遍历二叉树--利用队列，将树的某一层的从左到右的出队所有结点，并将结点的左右结点依此入队到队尾
void levelorderTravel( BinTree binTree ){
	if( !binTree ){// 空树
		return ;
	}
	Queue* que = creatQueue();
	addQueue( que, binTree );
	BinTree tree;
	while( !isEmptyAtQ(que) ){
		tree = deQueue( que );
		printf("%d ",tree->data);
		if( tree->left ){
			addQueue( que, tree->left );
		}
		if( tree->right ){
			addQueue( que, tree->right );
		}
	}
	printf("\n");
}
// 获取叶子结点个数-递归
int getLeaf( BinTree binTree ){
	if( !binTree ){
		return 0;
	} else {
		if( binTree->left && binTree->right ){
			return 1 + getLeaf( binTree->left ) + getLeaf( binTree->right );
		} else {
			if( binTree->left ){
				return getLeaf( binTree->left );
			} else if( binTree->right ) {
				return getLeaf( binTree->right );
			}
		}
	}
}
int getLeaf1( BinTree binTree ){//非递归
	int cnt = 0;//计数器
	Stack* stack = creatStack();
	while( 1 ){
		while( binTree ){// 每次先输出根节点，再遍历其左子树
			if( binTree->left == NULL && binTree->right == NULL ){
				cnt++;
			}
			push( stack, binTree );// 先进后出-保证可以从现有基础逆推出右子树
			binTree = binTree->left;
		}
		// 根-左结点访问完，此时令上循环遍历右子树
		if( !isEmpty( stack ) ){ // 为空即，最开始树的右子树访问完，结束循环
			binTree = pop( stack )->right;

			
		} else {
			break;
		}
	}
	free( stack );
	return cnt;
}
// 获取所有结点个数
int getTNode( BinTree binTree ){
	
	int cnt;
	if( !binTree ){
		return 0;
	} else {
		cnt = 1;
	}
	
	if( binTree->left ){
		cnt += getTNode( binTree->left );
	}
	if( binTree->right ){
		cnt += getTNode( binTree->right );
	}
	return cnt;
}
int getTNode1( BinTree binTree ){
	int cnt = 0;
	Stack* stack = creatStack();
	while( 1 ){
		while( binTree ){
			cnt++;
			push( stack, binTree );
			binTree = binTree->left;
		}
		if( !isEmpty( stack ) ){
			binTree = pop( stack )->right;
		} else {
			break;
		}
	}
	return cnt;
}
// 菜单
int view( BinTree binTree ){
	int select;
	printf("\n(非递归)前序：    ");
	preorderTravel3( binTree );
	printf("\n(递归)前序：      ");
	preorderTravel( binTree );
	printf("\n**********************\n");
	printf("\n(非递归)中序：    ");
	inorderTravel1( binTree );
	printf("\n(递归)中序：      ");
	inorderTravel( binTree );
	printf("\n**********************\n");
	printf("\n(非递归)后序：    ");
	postorderTravel3( binTree );
	printf("\n(递归)后序：      ");
	postorderTravel( binTree );
	printf("\n**********************\n");
	printf("\n层序遍历 ：       ");
	levelorderTravel( binTree );
	printf("\n**********************\n");
	printf("\n深度=%d\n",getDepth( binTree ));
	printf("叶子结点个数为%d(递归) %d(非递归)\n",getLeaf( binTree )+1,getLeaf1( binTree ));
	printf("所有结点个数为%d(递归) %d(非递归)\n",getTNode( binTree ),getTNode1( binTree ));
	printf("************请输入要选择的功能：*****************\n1.删除结点\t2.添加结点\t3.查值\t4.获取最大最小元素\n");
	scanf("%d",&select);
	return select;
}
//void printTree( BinTree binTree ){// 按照打印出树图
//	if( !binTree ){
//		return ;
//	}
//	int depth = getDepth( binTree );
//	int dic = 1;
//	int cnt = 0;
//	Queue* que = creatQueue();
//	addQueue( que, binTree );
//	BinTree tree;
//	while( depth-- ){
//		while( !isEmptyAtQ(que) ){
//			tree = deQueue( que );
//			cnt++;
//			// 如果是NULL则也加入队列，作为打印时是否填入空格
//			if( !tree ){
//				printf("NULL");
//				addQueue1( que, NULL );
//				addQueue1( que, NULL );
//			} else {
//				printf("%d",tree->data);
//				addQueue1( que, tree->left );
//				addQueue1( que, tree->right );
//			}
//			if( cnt == dic ){
//				cnt = 0;
//				break;
//			}
//		}
//		printf("\n");
//		dic *= 2;
//	}
//}
// ---------------------二叉树-----------------------