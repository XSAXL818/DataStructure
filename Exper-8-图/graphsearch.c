#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define Weight int // 权重
#define MaxSize 100 //最大结点数
#define OK 1
#define ERROR 0
#define INFINITY 999999
typedef enum{
	DG,AG,WDG,WAG
} GraphKind;// 图的种类，分别为有向图，无向图，带权有向图，带权无向图

typedef struct{ //信息域，用于表示边的特殊属性
	char* str;// 存储字符串
	Weight weight;// 存储权值,类型宏定义
} InfoType;// 顶点的信息域

typedef struct _LNode{
	int adjVex;// 邻接点在结点表的下标
	InfoType info;// 点到该邻接点的信息域
	struct _LNode* next;// 指向下一个邻接点
} LNode;// 邻接点的链表

typedef struct{
	int mark;// 该顶点代号
	char* name;// 该顶点的名称
} VexType;// 顶点自身信息

typedef struct _VexNode{
	VexType data;// 顶点信息
	int outDegree;// 出度
	int inDegree;// 入度
	LNode* firstArc;// 指向一个由该结点确定的所有边的邻接点的点集
} VexNode;// 顶点结点

typedef struct{
	VexType vex1;// 始点
	VexType vex2;// 终点
	InfoType info;// 改变的信息，如权值
} ArcType;// 边<v1,v2>

typedef struct{
	GraphKind kind;// 图的种类
	int vexNum;// 顶点数
	VexNode* adjList;// 邻接表
} Graph;// 图
// 创建一个空图
Graph* creatGraph( GraphKind kind );
// 顶点定位
int LocateVex( Graph* g, VexType* v, int select );// select为1则按mark(代号)查找结点，为0则按name查找
// 添加一个顶点,成功返回其下标，否则返回-1， 已存在该结点也返回-1
int addVex( Graph* g, VexType* v );
// 创建一条弧,arc为NULL则创建新边，不为NULL则对自身改变
ArcType* creatArc( ArcType* arc, VexType* v1, VexType* v2, InfoType* info );
// 添加一条弧,成功1，否则-1
int addArc( Graph* g, ArcType* a );
// BTS,深度优先搜索
void DFSTravel1( Graph* g, int startVex );// 非递归
// 广度优先搜索,使用队列实现,startVex为选定开始结点
void BFSTravel( Graph* g, int startVex );


//---------------------队列(链式储存)-------------------
typedef struct _QNode{// 单个结点
	int index; // 图中某个结点在图的表头数组的下标
	struct _QNode* next;
} QNode;
typedef struct{
	QNode* head;
	QNode* tail;
} Queue;
// 创建一个空队列
Queue* creatQueue( void );
// 入队
void enQueue( Queue* que, int index );
// 出队
int deQueue( Queue* que );
// 判空
int isEmptyAtQ( Queue* que );
// 摧毁队列
void destoryQueue( Queue* que );
//---------------------队列-------------------
//---------------------栈-------------------
typedef struct _SNode{// 用于存储一个结点的邻接点的链表
	struct _SNode* next;
	LNode* data;
} *Stack,SNode;
// 创建一个空栈
Stack creatStack(void);
// 入栈-带头结点-头插
void push( Stack stack, LNode* lnode );
// 出栈
LNode* pop( Stack stack );
// 判空
int isEmptyByStack( Stack stack );
// 销毁栈
void destoryStack( Stack stack );
//---------------------栈-------------------

void dele( Graph* g, int num ){
	int i;
	LNode* t,*node;
	for( i = 0; i < g->vexNum && i != num; i++ ){
		t = g->adjList[i].firstArc;
		if( t ){
			if( t->adjVex == num ){
				g->adjList[i].firstArc = t->next;
				free( t );
			} else {
				while( t->next ){
					if( t->next->adjVex == num ){
						node = t->next;
						t->next = node->next;
						free( node );
						break;
					}
					t = t->next;
				}
			}
		}
	}
}

int visited[MaxSize];// 用于表示当前结点是否被访问过
int isDe = 89;
int main(){
	
	
	Graph* g = creatGraph( AG );
	int n1,n2,i;
	scanf("%d %d",&n1,&n2);
	VexType v1 = { 1, "" };
	VexType v2 = { 2, "" };
	for( i = 0; i < n1; i++ ){
		v1.mark = i;
		addVex( g, &v1 );
	}
	ArcType* arc;
	int t = n2;
	InfoType info = { " ", 2 };
	for( i = 0; i < t; i++ ){
		scanf("%d %d",&n1,&n2);
		v1.mark = n1;
		v2.mark = n2;
		arc = creatArc( NULL, &v1, &v2, &info );
		addArc( g, arc );
	}
//	LNode* node;
//	for( i = 0; i < g->vexNum; i++ ){
//		node = g->adjList[i].firstArc;
//		printf("%d ",i);
//		while( node ){
//			printf("%d ",node->adjVex);
//			node = node->next;
//		}
//		printf("\n");
//	}
	printf("\n");
	DFSTravel1( g, 0 );
	printf("\n");
	BFSTravel( g, 0 );
	printf("\n");
	scanf("%d",&isDe);
	
	dele( g, isDe );
	
//	for( i = 0; i < g->vexNum; i++ ){
//		node = g->adjList[i].firstArc;
//		printf("%d ",i);
//		while( node ){
//			printf("%d ",node->adjVex);
//			node = node->next;
//		}
//		printf("\n");
//	}
	
	DFSTravel1( g, 0 );
	printf("\n");
	BFSTravel( g, 0 );
	printf("\n");

	

	return 0;
}



// 创建一个空图
Graph* creatGraph( GraphKind kind ){
	Graph* g = (Graph*)malloc( sizeof(Graph) );
	g->kind = kind;
	g->vexNum = 0;
	g->adjList = (VexNode*)malloc( MaxSize*sizeof( VexNode ) );
	return g;
}
// 顶点定位
int LocateVex( Graph* g, VexType* v, int select ){
	int i;
	if( select ){// 按mark
		for( i = 0; i < g->vexNum; i++ ){
			VexType t = g->adjList[i].data;
			if( t.mark == v->mark ){
				return i;
			}
		}
	} else { // 按name
		for( i = 0; i < g->vexNum; i++ ){
			VexType t = g->adjList[i].data;
			if( strcmp( t.name, v->name ) == 0 ){
				return i;
			}
		}
	}
	
	return -1;
}
// 添加一个顶点,成功返回其下标，否则返回-1， 已存在该结点也返回-1
int addVex( Graph* g, VexType* v ){
	assert( g != NULL && v != NULL );// g or v为NULL报错
	
	if( LocateVex( g, v, 1 ) != -1 ){// 存在该结点，返 - 1, 第三个参数默认使用结点代号查重
		return ERROR;
	}
	if( g->vexNum >= MaxSize ){ // 图满
		return ERROR;
	}
	// 创建新结点
	g->adjList[g->vexNum].data = *v;
	g->adjList[g->vexNum].outDegree = 0;// 出度
	g->adjList[g->vexNum].inDegree = 0;// 出度
	g->adjList[g->vexNum].firstArc = NULL;
	
	return g->vexNum++;// 返回插入位置的下标，然后结点数加1
}
// 创建一条弧,arc为NULL则创建新边，不为NULL则对自身改变,<v1,v2>
ArcType* creatArc( ArcType* arc, VexType* v1, VexType* v2, InfoType* info ){
	if( !arc ){// 创建新边
		ArcType* arc = (ArcType*)malloc( sizeof( ArcType ) );
		arc->info = *info;
		arc->vex1 = *v1;
		arc->vex2 = *v2;
		return arc;
	} else { // 修改边属性
		arc->info = *info;
		arc->vex1 = *v1;
		arc->vex2 = *v2;
		return NULL;
	}
}
// 添加一条弧,成功1，否则-1
int addArc( Graph* g, ArcType* a ){
	assert( g!=NULL && a !=NULL );// g or a为NULL报错
	// 获取弧的始点和终点在图中邻接表的下标
	int index1 = LocateVex( g, &a->vex1, 1 );// 1即默认为按代号查找
	int index2 = LocateVex( g, &a->vex2, 1 );
	if( index1 == -1 || index2 == -1 ){// <v1,v2>,v1 or v2 不存在
	
		return -1;
	}
	if( g->kind == DG || g->kind == WDG ){// 对于有向图(无权，加权),只需处理<v1,v2>
		LNode* node = (LNode*)malloc( sizeof( LNode ) );
		node->adjVex = index2;// 终点所在图中的下标
		node->info = a->info;// 边的信息
		// 头插法
		node->next = g->adjList[index1].firstArc;
		g->adjList[index1].firstArc = node;
		g->adjList[index1].outDegree++;
		g->adjList[index2].inDegree++;
	} else {// 无向图, 处理<v1,v2> <v2,v1>
//		printf("1\n");
		LNode* node1 = (LNode*)malloc( sizeof( LNode ) );
		LNode* node2 = (LNode*)malloc( sizeof( LNode ) );
		node1->adjVex = index2;
		node1->info = a->info;
		node2->adjVex = index1;
		node2->info = a->info;
		node1->next = NULL;
		node2->next = NULL;
		
		// 小到大
		LNode* t = g->adjList[index1].firstArc;
		if( t == NULL ){
//			printf("2\n");
			g->adjList[index1].firstArc = node1;
		} else {
//			printf("3\n");
			while( t->next ){
				if( t->adjVex > index2 ){
					node1->adjVex = t->adjVex;
					t->adjVex = index2;
					node1->next = t->next;
					t->next = node1;
					break;
				}
				t = t->next;
			}
//			printf("4\n");
			if( t->next == NULL ){
				if( t->adjVex > index2 ){
					node1->adjVex = t->adjVex;
					t->adjVex = index2;
				}
				t->next = node1;
			}
		}
		
		t = g->adjList[index2].firstArc;
		if( t == NULL ){
//			printf("5\n");
			g->adjList[index2].firstArc = node2;
		} else {
//			printf("6\n");
			while( t->next ){
				if( t->adjVex > index1 ){
					node2->adjVex = t->adjVex;
					t->adjVex = index1;
					node2->next = t->next;
					t->next = node2;
					break;
				}
				t = t->next;
			}
//			printf("7\n");
			if( t->next == NULL ){
				if( t->adjVex > index1 ){
					node2->adjVex = t->adjVex;
					t->adjVex = index1;
				}
				t->next = node2;
			}
		}
		
		g->adjList[index1].inDegree++;
		g->adjList[index1].outDegree++;
		g->adjList[index2].inDegree++;
		g->adjList[index2].outDegree++;
	}

	return 1;
}

// startVex用于确认从何结点开始BFS
void DFSTravel1( Graph* g, int startVex ){// 非递归
	assert( g != NULL );
	if( startVex < 0 && startVex >= g->vexNum ){// 开始结点不存在
		return ;
	}
	Stack stack = creatStack();
	LNode* node = g->adjList[startVex].firstArc;
	int i;
	int vexIndex = startVex;
	if( !node ){
		push( stack,node );
	}
	for( i = 0; i < g->vexNum; i++ ){//初始化标记数组
		visited[i] = 0;
	}
	visited[isDe] = 1;
	for( i = 0; i < g->vexNum; i++ ){
		while( vexIndex != -1 ){
			if( !visited[vexIndex] ){
				visited[vexIndex] = 1;
				printf("%d ",g->adjList[vexIndex].data.mark);
				if( g->adjList[vexIndex].firstArc ){
					push( stack, g->adjList[vexIndex].firstArc );
				}
				
			}
			if( !isEmptyByStack( stack ) ){
				node = pop( stack );
				vexIndex = node->adjVex;
				if( node->next ){
					push( stack, node->next );
				}
				
			} else {
				vexIndex = -1;
			}
			
		}
		
		if( !visited[i] ){
			vexIndex = i;
		}
	}
	
}
// 广度优先搜索,使用队列实现,startVex为选定开始结点
void BFSTravel( Graph* g, int startVex ){
	assert( g != NULL );
	if( startVex < 0 || startVex >= g->vexNum ){
		printf("输入错误！\n");
		return ;
	}
	// 先对传入的结点进行第一层入队
	Queue* que = creatQueue();
	enQueue( que, startVex );

	int i,vexIndex;
	for( i = 0; i < g->vexNum; i++ ){// 初始化访问标记数组
		visited[i] = 0;
	}
	visited[isDe] = 1;
	for( i = 0; i < g->vexNum; i++ ){// 访问所有结点，对未访问的结点访问
		while( !isEmptyAtQ( que ) ){
			vexIndex = deQueue( que );
			if( !visited[vexIndex] ){
				visited[vexIndex] = 1;
				printf("%d ",g->adjList[vexIndex].data.mark,g->adjList[vexIndex].data.name);
			}
			
			LNode* start = g->adjList[vexIndex].firstArc;
			while( start ){
				if( !visited[start->adjVex] ){
					enQueue( que, start->adjVex );
				}
				
				
				start = start->next;
			}
		}
		if( !visited[i] ){
			enQueue( que, i );
		}
	}
	destoryQueue( que );
}


//---------------------队列(链式储存)-------------------
// 创建一个空队列
Queue* creatQueue( void ){
	Queue* que = (Queue*)malloc( sizeof(Queue) );
	que->head = NULL;
	return que;
}
// 入队
void enQueue( Queue* que, int index ){
	QNode* node = (	QNode* )malloc( sizeof( QNode ) );
	node->index = index;
	node->next = NULL;
	if( !que->head ){
		que->head = node;
	} else {
		que->tail->next = node;
	}
	que->tail = node;
}
// 出队
int deQueue( Queue* que ){
	assert( que->head != NULL );
	QNode* t = que->head;
	int index = que->head->index;
	que->head = que->head->next;
	free( t );
	return index;
}
// 判空
int isEmptyAtQ( Queue* que ){
	if( !que->head ){
		return 1;
	} else {
		return 0;
	}
}
// 摧毁队列
void destoryQueue( Queue* que ){
	QNode* start = que->head;
	QNode* t;
	while( start ){
		t = start;
		start = start->next;
		free( t );
	}
	que->head = NULL;
}
//---------------------队列-------------------
//---------------------栈-------------------
// 创建一个空栈
Stack creatStack(void){
	Stack stack = (Stack)malloc( sizeof( SNode ) );
	stack->next = NULL;
	return stack;
}
// 入栈-带头结点-头插
void push( Stack stack, LNode* lnode ){
	SNode* node = (SNode*)malloc( sizeof( SNode ) );
	node->data = lnode;
	node->next = stack->next;
	stack->next = node;
}
// 出栈
LNode* pop( Stack stack ){
	LNode* node = stack->next->data;
	stack->next = stack->next->next;
	return node;
}
// 判空
int isEmptyByStack( Stack stack ){
	assert( stack != NULL );
	if( stack->next ){
		return 0;
	} else {
		return 1;
	}
}
// 销毁栈
void destoryStack( Stack stack ){
	SNode* t;
	while( stack ){
		t = stack;
		stack = stack->next;
		free( t );
	}
}
//---------------------栈-------------------

