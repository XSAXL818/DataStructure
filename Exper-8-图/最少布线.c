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
void DFS( Graph* g, int vexIndex );// 递归实现，传入一个结点在图中的下标，然后以此为起点，访问一条连通路径
void DFSTravel( Graph* g, int startVex );
void DFSTravel1( Graph* g, int startVex );// 非递归
// 广度优先搜索,使用队列实现,startVex为选定开始结点
void BFSTravel( Graph* g, int startVex );
LNode* findMinVex( Graph* g, int dist[] );// 找出未进入树的结点到该树最小距离的结点在图中储存的下标
int prim( Graph* g );// 传入一个图，返回最小生成树的权重和,新树以图的邻接表方式储存


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
int getInt( char* str ){
	int sum = 0;
	int i;
	int len = strlen( str );
	for( i = 0; i < len; i++ ){
		sum *= 10;
		sum += str[i]-'0';
	}
	return sum;
}


int visited[MaxSize];// 用于表示当前结点是否被访问过
Graph* MST;// 最小生成树

int main(){
	
	Graph* g = creatGraph( WAG );
	VexType vex1 = { 0, "" };
	VexType vex2 = { 0, "" };
	ArcType* arc;
	
	int v1,v2,n1,n2,i,j;
	scanf("%d %d",&n1,&n2);
	for( i = 0; i < n1; i++ ){
		vex1.mark = i;
		addVex( g, &vex1 );
	}
	char* id;
	int weight;
	int t = n2;
	InfoType info;
	for( i = 0; i < t; i++ ){
		id = (char*)malloc( 3*sizeof(char) );
		scanf("%s %d %d %d", id, &n1, &n2, &weight);
		vex1.mark = n1;
		vex2.mark = n2;
		info.str = id;
		info.weight = weight;
		arc = creatArc( NULL, &vex1, &vex2, &info );
		addArc( g, arc );
	}
	
	int sum = prim( g );
	
	printf("%d\n",sum);
	int ids[t+1];
	LNode* node;
	for( i = 1; i <= t; i++ ){
		ids[i] =  0;
	}
	for( i = 0; i < MST->vexNum; i++ ){
		node = MST->adjList[i].firstArc;
		while( node ){
			int t = getInt( node->info.str );
			ids[t] = 1;
//			printf("***%s\n",node->info.str);
			node = node->next;
		}
	}
	
	for( i = 1; i <= t; i++ ){
		if( ids[i] ){
			printf("%d ",i);
		}
	}
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

		LNode* node1 = (LNode*)malloc( sizeof( LNode ) );
		LNode* node2 = (LNode*)malloc( sizeof( LNode ) );
		node1->adjVex = index2;
		node1->info = a->info;
		node2->adjVex = index1;
		node2->info = a->info;
		// 头插法
		node1->next = g->adjList[index1].firstArc;
		g->adjList[index1].firstArc = node1;
		node2->next = g->adjList[index2].firstArc;
		g->adjList[index2].firstArc = node2;
		g->adjList[index1].inDegree++;
		g->adjList[index1].outDegree++;
		g->adjList[index2].inDegree++;
		g->adjList[index2].outDegree++;
	}

	return 1;
}
// DTS,深度优先搜索-对无向图有向图都适用
void DFS( Graph* g, int vexIndex ){// 递归实现，传入一个结点在图中的下标，然后以此为起点，访问一条连通路径

	visited[vexIndex] = 1;

	printf("代号：%d 名称：%s\n",g->adjList[vexIndex].data.mark,g->adjList[vexIndex].data.name);

	LNode* start = g->adjList[vexIndex].firstArc;
	while( start ){// 遍历传入结点的所有邻接结点
		if( !visited[start->adjVex] ){// 该结点未被访问则依次结点开始深度搜索
			DFS( g, start->adjVex );
		}
		start = start->next;
	}

}
// startVex用于确认从何结点开始BFS
void DFSTravel( Graph* g, int startVex ){// 递归实现，传入一个结点在图中的下标，然后以此为起点，访问一条连通路径
	assert( g != NULL );

	int i;
	for( i = 0; i < g->vexNum; i++ ){// 初始化访问数组
		visited[i] = 0;
	}

	DFS( g, startVex );

	for( i = 0; i < g->vexNum; i++ ){ // 遍历所有结点
		if( !visited[i] ){ // 对还没遍历到的结点做BFS搜索，
			DFS( g, i );
		}
	}
}
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
	for( i = 0; i < g->vexNum; i++ ){
		while( vexIndex != -1 ){
			if( !visited[vexIndex] ){
				visited[vexIndex] = 1;
				printf("代号：%d 名称：%s\n",g->adjList[vexIndex].data.mark,g->adjList[vexIndex].data.name);
				
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
	for( i = 0; i < g->vexNum; i++ ){// 访问所有结点，对未访问的结点访问
		while( !isEmptyAtQ( que ) ){
			vexIndex = deQueue( que );
			if( !visited[vexIndex] ){
				visited[vexIndex] = 1;
				printf("代号：%d 名称：%s\n",g->adjList[vexIndex].data.mark,g->adjList[vexIndex].data.name);
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
Graph* CreatMST( Graph* g ){// 创建一个含g的所有结点但不含其边的图
	int i;
	Graph* mst = creatGraph( WDG );
	for( i = 0; i < g->vexNum; i++ ){
		addVex( mst, &g->adjList[i].data );
	}

	return mst;
}
LNode* findMinVex( Graph* g, int dist[] ){// 找出未进入树的结点到该树最小距离的结点在图中储存的下标

//	int minVex = -1;// 没找到返回-1，找到即返回该结点的下标
	LNode* minVex = NULL;// 对本图优化一下，返回值不只是下标，同时附带该边的信息如权值和名称
	int minDist = INFINITY;
	int i;
	LNode* start;
	for( i = 0; i < g->vexNum; i++ ){// 遍历所有结点,找到离树最小距离的点
		if( dist[i] == 0 ){// 即从已有树的结点出发，找到离树最小的结点
			start = g->adjList[i].firstArc;
			while( start ){ // dist[start->adjVex]！=0的意思为，新找的到树最小距离的结点不得为树本身内部的结点
				if( dist[start->adjVex] != 0 && minDist > dist[start->adjVex] ){// 第二个条件即可更新dist[start->adjVex]到树的值
//					minVex = start->adjVex;
					minVex = start;
					minDist = start->info.weight;
				}
				start = start->next;
			}
		}
	}
	// 循环树中所有结点
	return minVex;
}
// startIndex 为以其为
int prim( Graph* g ){// 传入一个图，返回最小生成树的权重和，mst用于带回生成的新树，新树以图的邻接表方式储存
	int dist[g->vexNum];// dist[i] 的意思是 i结点到 正在形成的树的最小距离,且dist[i]==0说明已该结点进入树中
	int parent[g->vexNum];// parent[i] 的意思是结点i的双亲结点在图中的位置
	int totalWeight = 0;
	int vexCount = 0;// 统计加入树的结点树，用于判断最后是否创建成功
	// 初始化：默认图的0下标结点作为树根,且其他结点到该树的距离设为最大值
	int i;
	for( i = 1; i < g->vexNum; i++ ){
		dist[i] = INFINITY;
		parent[i] = 0;
	}
	vexCount++;
	parent[0] = -1;// 将其设为树根
	dist[0] = 0;// 添加到树中的标识
	// 细化：将以0为根，更新该树到其他结点的距离
	LNode* start = g->adjList[0].firstArc;
	while( start ){
		dist[start->adjVex] = start->info.weight;
		start = start->next;
	}
	// 创建一个包含图所有结点，但不包含边的图
	MST = CreatMST( g );
	int minVex;
	LNode* minNode;
	ArcType arc;
	char* name;
	while( 1 ){
		minNode = findMinVex( g, dist );
		if( !minNode ){// 即未找到离树最小的结点，两种情况：1.图中所有结点都加入到mst中，2.图不连通
			break;
		}
		minVex = minNode->adjVex;
		// 找到后,添加向mst中加边,更新该结点加入树后对其他结点距离的影响,同时更新以新结点找到的结点的parent[]
		arc.vex1 = g->adjList[parent[minVex]].data;// 
		arc.vex2 = g->adjList[minVex].data;
		arc.info = minNode->info;
		// 将新边 <parent(minVex),minVex> 加入到mst
		addArc( MST, &arc );
		// 更新已加入树中的结点树和权值
		vexCount++;
		totalWeight += dist[minVex];
		// 加入新结点后，更新各结点到树的距离
		dist[minVex] = 0;
		start = g->adjList[minVex].firstArc;
		while( start ){// 
			if( dist[start->adjVex] != 0 && start->info.weight < dist[start->adjVex] ){
				dist[start->adjVex] = start->info.weight;// 更新距离
				parent[start->adjVex] = minVex;// 更新双亲结点
			}
			start = start->next;
		}
	
	}
	if( vexCount != g->vexNum ){
		totalWeight = -1;
	}

	return totalWeight;
	
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




