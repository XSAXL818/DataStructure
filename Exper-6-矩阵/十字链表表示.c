#include <stdio.h>
#include <stdlib.h>

#define Status int 
#define OK 1
#define ERROR 0

// 结点，储存一个非零元的行列数,值，指向当前行后一个元素和指向当前列下一个结点的指针
typedef struct _Node{
	int i;// 行
	int j;// 列
	int value; // 值
	struct _Node* right;// 行后驱节点
	struct _Node* down;// 列后继结点
} Node,*LNode;
// 矩阵,储存矩阵的行数，列数，非零元个数,行列链表头指针
typedef struct{
	int row;// 矩阵行数
	int col;// 矩阵列数
	int number;// 矩阵非零元个数
	LNode *rhead;// 行链表头指针
	LNode *chead;// 列链表头指针
} CrossList;
// 返回一个初始化为row行col列的矩阵
CrossList* creatCrossList( int row, int col );
// 打印矩阵
void printMatrix( CrossList* list );
void printNice( CrossList* list );
// 矩阵相加
Status add( CrossList* m1, CrossList* m2 );



int main(){
	
	int row,col;
	printf("请输入第一个矩阵的行列数：\n");
	scanf("%d %d",&row,&col);
	CrossList* m1 = creatCrossList( row, col );
	printf("矩阵的矩阵图打印：\n");
	printNice( m1 );
	CrossList* m2;
	while( 1 ){
		printf("请输入第二个矩阵的行列数：\n");
		scanf("%d %d",&row,&col);
		m2 = creatCrossList( row, col );
		printf("第二个矩阵的矩阵图打印：\n");
		printNice( m2 );
		add( m1, m2 );
		printf("结果矩阵的非零元打印：\n");
		printMatrix( m1 );
		printf("-------\n");
		printf("结果矩阵的矩阵图打印：\n");
		printNice( m1 );
	}
	return 0;
}

// 返回一个初始化为row行col列的矩阵
CrossList* creatCrossList( int row, int col ){
	CrossList* list = (CrossList*)malloc( sizeof(CrossList) );
	if( !list ){
		return NULL;
	}
	// 初始化
	list->row = row;
	list->col = col;
	list->chead = (LNode*)malloc( col*sizeof(LNode) );
	if( list->chead == NULL ){
		return NULL;
	}
	list->rhead = (LNode*)malloc( row*sizeof(LNode) );
	if( list->rhead == NULL ){
		return NULL;
	}
	// 将行列头指针置NULL
	int i,j;
	for( i=0; i < row; i++ ){
		list->rhead[i] = NULL;
	}
	for( i=0; i < col; i++ ){
		list->chead[i] = NULL;
	}
	// 向矩阵中加入一个非零元,可插入任意位置，但是不可重复插入某一位置两次
	int num = 0;
	printf("请输入矩阵图：\n");
	int value;
	for( i = 1; i <= row; i++ ){
		for( j = 1; j <= col; j++ ){
			scanf("%d",&value);
			if( value == 0 ){
				
			} else {
				num++;
				LNode node = (LNode)malloc( sizeof(Node) );// 创建新结点
				node->i = i;
				node->j = j;
				node->value = value;
				LNode rp = list->rhead[i-1];// 行
				LNode cp = list->chead[j-1];// 列
				// 行逻辑链接上
				if( rp == NULL || rp->j > j ){ //情况一，作为改行首个非零元插入
					// 链接后继结点
					node->right = rp; 
					list->rhead[i-1] = node;
				} else { //情况二，非该行首个非零元,查找插入的位置
					while( rp->right != NULL ){// 找到应该插入位置的前一个结点
						if( rp->right->j < j ){
							rp = rp->right;
						} else {
							break;
						}
					}
					node->right = rp->right;// 插入结点
					rp->right = node;
				}
				// 列逻辑链接上
				if( cp == NULL || cp->i > i ){ // 作为该列首个非零元		
					node->down = cp;
					list->chead[j-1] = node;
				} else { // 非首个非零元
					while( cp->down != NULL ){ // 找到应该插入位置的前一个结点
						if( cp->down->i < i ){
							cp = cp->down;
						} else {
							break;
						}
					}
					node->down = cp->down;
					cp->down = node;
				}
			}
		}
	}
	list->number = num;
	return list;
}
// 打印矩阵
void printMatrix( CrossList* list ){
	int i,j;
	LNode rp;
	for( i = 0; i < list->row; i++ ){
		rp = list->rhead[i];
		if( rp == NULL ){
			
		} else {
			for( ; rp != NULL; rp = rp->right ){
				printf("%d %d %d\n",rp->i,rp->j,rp->value);
			}
		}
		
	}
}
void printNice( CrossList* list ){
	int row,col;
	for( row = 1; row <= list->row; row++ ){
		LNode node = list->rhead[row-1];
		for( col = 1; col <= list->col; col++  ){
			if( node == NULL ){
				printf("0\t");
			} else {
				if( node->i == row && node->j == col ){
					printf("%d\t",node->value);
					node = node->right;
				} else {
					printf("0\t");
				}
			}
		}
		printf("\n");
	}
}
// 矩阵相加 m1自身加上m2矩阵
//******思路：每次遍历相加矩阵的同一行，任何对目标矩阵进行结点的增删改
//******技巧：遍历一行的结点时，需要一个指针pre指向正在操作结点的行前驱节点，同时需要一个指针数组hl[]来指向结点的列前驱节点
Status add( CrossList* m1, CrossList* m2 ){
	if( m1 == NULL || m2 == NULL ){
		return ERROR;
	}
	// 矩阵行列不同
	if( m1->row != m2->row || m1->col != m2->col ){
		return ERROR;
	}
	// 加上零矩阵
	if( m2->number == 0 ){
		return OK;
	}
	// 加非零矩阵
	int i;
	LNode pre;// 指向行前驱节点 为NULL则说明该结点是是行首个非零元
	LNode hl[m1->col+1];// 指向列前驱节点
	for( i = 1; i <= m1->col; i++ ){ // 初始化
		hl[i] = m1->chead[i-1]; // 为NULL则说明该结点是是列首个非零元
	}
	LNode p1; // 指向m1的结点
	LNode p2; // 指向m2的结点
	for( i = 0; i < m1->row; i++ ){ // 遍历行
//		printf("3\n");
		pre = NULL;// 指向p1的前一个结点
		p1 = m1->rhead[i];
		p2 = m2->rhead[i];
		while( p2 ){ // 将p2的项加完为止   a+b
			if( p1 == NULL || p1->j > p2->j ){ // 0+b
				LNode node = (LNode)malloc( sizeof(Node) );//    0  0  0       0  2  1
				node->i = p2->i;                           //    0  1  1       1  0  1      1  1  2
				node->j = p2->j;
				node->value = p2->value;
				// 行链接
				if( pre == NULL ){// p1当前无结点
					m1->rhead[i] = node;
				} else {
					pre->right = node;
				}
				node->right = p1;
				pre = node; // 关键一
				// 列链接
				if( m1->chead[p2->j-1] == NULL || m1->chead[p2->j-1]->i > p2->i ){ // p1列前无元素
					node->down = m1->chead[p2->j-1];
					m1->chead[p2->j-1] = node;
					hl[p2->j] = node;// 关键二
				} else {
					node->down = hl[p2->j];
					hl[p2->j] = node;// 关键二
				}
				p2 = p2->right;
				m1->number++;
			} else if( p1->j < p2->j ) { // a+0 将a1行后移一个
//				printf("2\n");
				pre = p1;// 关键一
				p1 = p1->right;
			} else { // a+b
//				printf("3\n");
				if( p1->value + p2->value == 0 ){// 删除该结点
					LNode t = p1;
					// 行删除
					if( pre == NULL ){
						m1->chead[p2->j-1] = p1->right;
					} else {
						pre->right = p1->right;
					}
					pre->right = p1->right;			
					// 列删除
					if( m1->chead[p1->j-1] == p1 ){// 当前结点是列上的首个非零元
						m1->chead[p1->j-1] = m1->chead[p1->j-1]->down;
					} else {// 利用辅助指针
						hl[p1->j]->down = p1->down;
					}
					m1->number--;
					free( t );
				} else { // 直接相加
					p1->value += p2->value;
					pre = p1;
				}
				// 结点后移一位
				p1 = p1->right;
				p2 = p2->right;
			}
		}
	}	
}



