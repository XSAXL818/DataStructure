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
Graph* CreatMST( Graph* g );// 创建一个含g的所有结点但不含其边的图
int topSort( Graph* g );// 拓扑排序-队列实现
void criticalPath( Graph* g );// 关键路径

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
// 用于保存关键路径的链表
typedef struct _Node{
	int index;
	struct _Node* next;
} *List,Node;
List creatList(void){
	List list = (List)malloc( sizeof(Node) );
	list->next = NULL;
	return list;
}
void add( List list, int index ){
	while( list->next ){
		list = list->next;
	}
	Node* node = (Node*)malloc( sizeof(Node) );
	node->index = index;
	node->next = NULL;
	list->next = node;
}
void copyList( List dest, List src ){// dest 为 空表,出最后一个结点，其他结点共用
	Node* node;
	while( src->next ){
		src = src->next;
		node = (Node*)malloc( sizeof(Node) );
		node->index = src->index;
		node->next = NULL;
		dest->next = node;
		dest = node;
	}
	
}
void printList( List list ){
	while( list->next ){
		list = list->next;
		printf("%d ",list->index);
	}
	printf("\n");
}
// 打印图的类型
void printGraphKind( Graph* g ){
	switch( g->kind ){
		case AG:
			printf("无向图\n");
			break;
		case WAG:
			printf("带权无向图\n");
			break;
		case DG:
			printf("有向图\n");
			break;
		case WDG:
			printf("带权有向图\n");
	}
}
// 菜单
int view( Graph* graph ){

	int select,i,j;
	printf("\n所在下标\t顶点信息\t其邻接点\n");
	for( i = 0; i < graph->vexNum; i++ ){
		printf("%d\t\t%s\t\t",i,graph->adjList[i].data.name);
		LNode* start = graph->adjList[i].firstArc;
		while( start ){
			printf("%d ",start->adjVex);
			start = start->next;
		}
		printf("\n");
	
	}

	printf("************************************\n");
	printf("************请选择以下功能：\n");
	printf("1.深度优先搜索\t2.广度优先搜索\t3.最小生成子树\t4.拓扑排序\t5.求关键路径\t6.退出\n");
	scanf("%d",&select);
	
	return select;
}


int visited[MaxSize];// 用于表示当前结点是否被访问过
int top[MaxSize];
int inDegree[MaxSize];// 用于拓扑排序,保存结点的入度
int outDegree[MaxSize];
Graph* MST;// 最小生成树
List lists[10];// 保存关键路径
int llength = 0;
int main(){
	
	
	
	// 初始化,加边加点
	Graph* g = creatGraph( WDG );
	VexType v1 = { 1, "P城" };
	VexType v2 = { 2, "G港" };
	VexType v3 = { 3, "农场" };
	VexType v4 = { 4, "防空洞" };
	VexType v5 = { 5, "研究所" };
	addVex( g, &v1 );
	addVex( g, &v2 );
	addVex( g, &v3 );
	addVex( g, &v4 );
	addVex( g, &v5 );
	// 边的信息包括边的权重和名称,名称当前无用处，后续用于关键路径的边活动表示
	ArcType arc1 = { v1, v2, { "边1", 11 } };
	ArcType arc2 = { v1, v3, { "边2", 10 } };
	ArcType arc3 = { v1, v4, { "边3", 19  } };
	ArcType arc4 = { v1, v5, { "边4", 400} };
	ArcType arc5 = { v2, v4, { "边5", 500} };
	ArcType arc6 = { v3, v2, { "边6", 8  } };
	ArcType arc7 = { v3, v4, { "边7", 111} };
	ArcType arc8 = { v4, v1, { "边8", 222} };
	ArcType arc9 = { v5, v2, { "边9", 333} };
	addArc( g, &arc1 );
	addArc( g, &arc2 );
	addArc( g, &arc3 );
	addArc( g, &arc4 );
	addArc( g, &arc5 );
	addArc( g, &arc6 );
	addArc( g, &arc7 );
	addArc( g, &arc8 );
	addArc( g, &arc9 );
	
	Graph* g1 = creatGraph( WAG );
	VexType v11 = { 1, "V1" };
	VexType v12 = { 2, "V2" };
	VexType v13 = { 3, "V3" };
	VexType v14 = { 4, "V4" };
	VexType v15 = { 5, "V5" };
	VexType v16 = { 6, "V6" };
	VexType v17 = { 7, "V7" };
	ArcType arc10 = { v11, v12, { "边1", 2 } };
	ArcType arc11 = { v11, v13, { "边2", 4 } };
	ArcType arc12 = { v11, v14, { "边3", 1 } };
	ArcType arc13 = { v13, v14, { "边4", 2 } };
	ArcType arc14 = { v13, v16, { "边5", 5 } };
	ArcType arc15 = { v16, v14, { "边6", 8 } };
	ArcType arc16 = { v16, v17, { "边7", 1 } };
	ArcType arc17 = { v17, v4, { "边8", 4 } };
	ArcType arc18 = { v17, v15, { "边9", 6 } };
	ArcType arc19 = { v5, v14, { "边10", 7 } };
	ArcType arc20 = { v14, v12, { "边11", 3 } };
	ArcType arc21 = { v15, v12, { "边12", 10 } };
	addVex( g1, &v11 );
	addVex( g1, &v12 );
	addVex( g1, &v13 );
	addVex( g1, &v14 );
	addVex( g1, &v15 );
	addVex( g1, &v16 );
	addVex( g1, &v17 );
	addArc( g1, &arc10 );
	addArc( g1, &arc11 );
	addArc( g1, &arc12 );
	addArc( g1, &arc13 );
	addArc( g1, &arc14 );
	addArc( g1, &arc15 );
	addArc( g1, &arc16 );
	addArc( g1, &arc17 );
	addArc( g1, &arc18 );
	addArc( g1, &arc19 );
	addArc( g1, &arc20 );
	addArc( g1, &arc21 );
	// 用于检测拓扑排序
	Graph* g2 = creatGraph( WDG );
	VexType C1 = { 1, "C1" };
	VexType C2 = { 2, "C2" };
	VexType C3 = { 3, "C3" };
	VexType C4 = { 4, "C4" };
	VexType C5 = { 5, "C5" };
	VexType C6 = { 6, "C6" };
	VexType C7 = { 7, "C7" };
	VexType C8 = { 8, "C8" };
	VexType C9 = { 9, "C9" };
	VexType C10 = { 10, "C10" };
	VexType C11 = { 11, "C11" };
	VexType C12 = { 12, "C12" };
	VexType C13 = { 13, "C13" };
	VexType C14 = { 14, "C14" };
	VexType C15 = { 15, "C15" };
	ArcType carc1 = { C1, C3, { "边1", 1 } };
	ArcType carc2 = { C2, C3, { "边2", 1 } };
	ArcType carc3 = { C2, C13, { "边3", 1 } };
	ArcType carc4 = { C8, C9, { "边4", 1 } };
	ArcType carc5 = { C4, C5, { "边5", 1 } };
	ArcType carc6 = { C3, C7, { "边6", 1 } };
	ArcType carc7 = { C9, C10, { "边7", 1 } };
	ArcType carc8 = { C9, C11, { "边8", 1 } };
	ArcType carc9 = { C5, C6, { "边9", 1 } };
	ArcType carc10 = { C7, C12, { "边10", 1 } };
	ArcType carc11 = { C7, C10, { "边11", 1 } };
	ArcType carc12 = { C7, C11, { "边12", 1 } };
	ArcType carc13 = { C6, C15, { "边13", 1 } };
	ArcType carc14 = { C10, C14, { "边14", 1 } };

	addVex( g2, &C1 );
	addVex( g2, &C2 );
	addVex( g2, &C3 );
	addVex( g2, &C4 );
	addVex( g2, &C5 );
	addVex( g2, &C6 );
	addVex( g2, &C7 );
	addVex( g2, &C8 );
	addVex( g2, &C9 );
	addVex( g2, &C10 );
	addVex( g2, &C11 );
	addVex( g2, &C12 );
	addVex( g2, &C13 );
	addVex( g2, &C14 );
	addVex( g2, &C15 );
	addArc( g2, &carc1 );
	addArc( g2, &carc2 );
	addArc( g2, &carc3 );
	addArc( g2, &carc4 );
	addArc( g2, &carc5 );
	addArc( g2, &carc6 );
	addArc( g2, &carc7 );
	addArc( g2, &carc8 );
	addArc( g2, &carc9 );
	addArc( g2, &carc10 );
	addArc( g2, &carc11 );
	addArc( g2, &carc12 );
	addArc( g2, &carc13 );
	addArc( g2, &carc14 );
	// 关键路径
	Graph* g3 = creatGraph( WDG );
//	VexType vv0 = { 1, "V0" };
	VexType vv1 = { 1, "V1" };
	VexType vv2 = { 2, "V2" };
	VexType vv3 = { 3, "V3" };
	VexType vv4 = { 4, "V4" };
	VexType vv5 = { 5, "V5" };
	VexType vv6 = { 6, "V6" };
	VexType vv7 = { 7, "V7" };
	VexType vv8 = { 8, "V8" };
	VexType vv9 = { 9, "V9" };
	VexType vv10 = { 10, "V10" };
	VexType vv11 = { 11, "V11" };

//	ArcType aarc1 = { vv0, vv1, { "a1", 3 } };
//	ArcType aarc2 = { vv0, vv2, { "a2", 10 } };
//	ArcType aarc3 = { vv1, vv3, { "a3", 9 } };
//	ArcType aarc4 = { vv1, vv4, { "a4", 13 } };
//	ArcType aarc5 = { vv2, vv4, { "a5", 12 } };
//	ArcType aarc6 = { vv2, vv5, { "a6", 7 } };
//	ArcType aarc7 = { vv3, vv6, { "a7", 8 } };
//	ArcType aarc8 = { vv3, vv7, { "a8", 4 } };
//	ArcType aarc9 = { vv4, vv7, { "a9", 6 } };
//	ArcType aarc10 = { vv5, vv7, { "a10", 11 } };
//	ArcType aarc11 = { vv6, vv8, { "a11", 2 } };
//	ArcType aarc12 = { vv7, vv8, { "a12", 5 } };
	
	ArcType aarc1 = { vv1, vv2, { "a1", 3 } };
	ArcType aarc2 = { vv1, vv3, { "a2", 4 } };
	ArcType aarc3 = { vv2, vv4, { "a3", 2 } };
	ArcType aarc4 = { vv2, vv5, { "a4", 1 } };
	ArcType aarc5 = { vv3, vv5, { "a5", 3 } };
	ArcType aarc6 = { vv3, vv6, { "a6", 5 } };
	ArcType aarc7 = { vv4, vv7, { "a7", 6 } };
	ArcType aarc8 = { vv5, vv7, { "a8", 8 } };
	ArcType aarc9 = { vv5, vv8, { "a9", 4 } };
	ArcType aarc10 = { vv6, vv9, { "a10", 2 } };
	ArcType aarc11 = { vv7, vv11, { "a11", 7 } };
	ArcType aarc12 = { vv8, vv10, { "a12", 4 } };
	ArcType aarc13 = { vv8, vv9, { "a13", 10 } };
	ArcType aarc14 = { vv9, vv10, { "a14", 1 } };
	ArcType aarc15 = { vv10, vv11, { "a15", 6 } };
	
//	addVex( g3, &vv0 );
	addVex( g3, &vv1 );
	addVex( g3, &vv2 );
	addVex( g3, &vv3 );
	addVex( g3, &vv4 );
	addVex( g3, &vv5 );
	addVex( g3, &vv6 );
	addVex( g3, &vv7 );
	addVex( g3, &vv8 );
	addVex( g3, &vv9 );
	addVex( g3, &vv10 );
	addVex( g3, &vv11 );

	addArc( g3, &aarc1 );
	addArc( g3, &aarc2 );
	addArc( g3, &aarc3 );
	addArc( g3, &aarc4 );
	addArc( g3, &aarc5 );
	addArc( g3, &aarc6 );
	addArc( g3, &aarc7 );
	addArc( g3, &aarc8 );
	addArc( g3, &aarc9 );
	addArc( g3, &aarc10 );
	addArc( g3, &aarc11 );
	addArc( g3, &aarc12 );
	addArc( g3, &aarc13 );
	addArc( g3, &aarc14 );
	addArc( g3, &aarc15 );
//	criticalPath( g3 );
	
	Graph* graphs[10];
	graphs[0] = g;
	graphs[1] = g1;
	graphs[2] = g2;
	graphs[3] = g3;
	int length = 4;
	int select;

	int vexIndex;
	int totalWeight;
	char* names[10];
	names[0] = "做遍历";
	names[1] = "求子树";
	names[2] = "课程图";
	names[3] = "AOE网";
	while( 1 ){
		printf("编号\t图的名称\t类型\n");
		int i;
		for( i = 0; i < length; i++ ){
			printf("%d\t%s\t\t",i+1,names[i]);
			printGraphKind( graphs[i] );
		}
		printf("请输入要选择图的编号：\n");
		scanf("%d",&select);
//		1.生成最小子树    2.深度优先搜索    3.广度优先搜索
		Graph* sp = graphs[select-1];
		while( 1 ){
			select = view( sp );
			switch( select ){
				case 1:
					printf("请输入从哪个结点开始:");
					scanf("%d",&vexIndex);
					printf("递归：\n");
					printf("***************************\n");
					DFSTravel( sp, vexIndex );
					printf("***************************\n");
					printf("非递归：\n");
					printf("***************************\n");
					DFSTravel1( sp, vexIndex );
					printf("***************************\n");
					break;
					
					break;
				case 2:
					printf("请输入从哪个结点开始:");
					scanf("%d",&vexIndex);
					printf("***************************\n");
					BFSTravel( sp, vexIndex );
					printf("***************************\n");
					break;
				case 3:
					totalWeight = prim( sp );
					graphs[length] = MST;
					names[length++] = "MST";
					printf("最小路径和:%d\n",totalWeight);
					printf("操作成功！\n");
				case 4:
					topSort( sp );
					break;
				case 5:
					criticalPath( sp );
					break;
			}
			if( select == 6 ){
				break;
			}
		
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
// startVex用于确认从何结点开始DFS
void DFSTravel( Graph* g, int startVex ){// 递归实现，传入一个结点在图中的下标，然后以此为起点，访问一条连通路径
	assert( g != NULL );

	int i;
	for( i = 0; i < g->vexNum; i++ ){// 初始化访问数组
		visited[i] = 0;
	}

	DFS( g, startVex );

	for( i = 0; i < g->vexNum; i++ ){ // 遍历所有结点
		if( !visited[i] ){ // 对还没遍历到的结点做DFS搜索，
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
int topSort( Graph* g ){// 拓扑排序-队列实现
	if( !g ){
		return ERROR;
	}
	Queue* que = creatQueue();
	int i;
	int vexIndex;
	LNode* node;
	for( i = 0; i < g->vexNum; i++ ){// 统计各点的入度
		inDegree[i] = g->adjList[i].inDegree;
		if( inDegree[i] == 0 ){// 将入度为0的顶点入队
			enQueue( que, i );	
		}
	}
	i = 0;
	while( !isEmptyAtQ( que ) ){// 当队列中无元素则说明 已不存在入度为0的顶点
		vexIndex = deQueue( que );// 入队并将其加入到拓扑排序中
		top[i++] = vexIndex;
		node = g->adjList[vexIndex].firstArc;
		while( node ){
			if( --inDegree[node->adjVex] == 0 ){// 随时将入度为0的顶点加入队列
				enQueue( que, node->adjVex );
			}
			node = node->next;
		}
	}
	if( i != g->vexNum ){// 说明图中有回路
		return ERROR;
	}
	printf("拓扑排序为：");
	for( i = 0; i < g->vexNum; i++ ){
		printf("%d ",top[i]);
	}
	printf("\n");
	return OK;
}
// 找到关键路径-递归查询
void findSP( Graph* g, List list, int startIndex, int ve[], int vl[] ){
	int dic = 0;
	int t = 0;
	LNode* node = g->adjList[startIndex].firstArc;
	while( node ){
		if( !dic ){
			if( ve[startIndex] + node->info.weight == vl[node->adjVex] ){// 找到一个顶点
				dic = 1;// 标记
				t = node->adjVex;// 保存该结点的下标
			}
		} else {// 找寻其他分路
			if( ve[startIndex] + node->info.weight == vl[node->adjVex] ){ // 新建一个链表，用于保存别的路径
				List list1 = creatList();
				copyList( list1, list );// 复制原有路径
				add( list1, node->adjVex );
				lists[llength++] = list1;
				findSP( g, list1, node->adjVex, ve, vl );
			}
		}
		node = node->next;
	}
	if( t ){ // 当前路径没有分叉或者其他分叉路径已走完，才能开始本条路径的寻找，主要避免其他路径重复复制
		add( list, t);
		findSP( g, list, t, ve, vl );
	}
	
	
}
void criticalPath( Graph* g ){// 关键路径
	assert( g!=NULL );
	// 拓扑排序，获取活动发生顺序,排序的表为全局变量
	if( !topSort( g ) ){
		printf("AOE网有回路!\n");
		return;
	} else {
		int ve[g->vexNum];// 事件最早发生时间
		int vl[g->vexNum];// 时间最晚发生时间
		int i;
		for( i = 0; i < g->vexNum; i++ ){// 初始化,便于后续计算
			ve[i] = 0;
		}
		int vexIndex;
		LNode* node;
		// 获取ve
		for( i = 0; i < g->vexNum; i++ ){// 按拓扑排序遍历
			vexIndex = top[i];
			node = g->adjList[vexIndex].firstArc;
			while( node ){// 更新以该结点为前驱的结点的值
				if( ve[node->adjVex] < ve[vexIndex] + node->info.weight ){
					ve[node->adjVex] = ve[vexIndex] + node->info.weight;
				}
//				ve[node->adjVex] = ve[node->adjVex] < ve[vexIndex] + node->weight ? ve[vexIndex] + node->weight : ve[node->adjVex];
				node = node->next;
			}
		}
		int t;
		// 获取vl
//		for( i = 0; i < (g->vexNum)/2; i++ ){// 获取逆拓扑排序
//			t = top[i];
//			top[i] = top[g->vexNum-1-i];
//			top[g->vexNum-1-i] = t;
//		}
		for( i = 0; i < g->vexNum; i++ ){// 初始化vl
			vl[i] = ve[g->vexNum-1];
		}
		for( i = g->vexNum-1; i >= 0; i-- ){// 按逆拓扑排序遍历
			vexIndex = top[i];
			node = g->adjList[vexIndex].firstArc;
			while( node ){// 更新以该结点为前驱的结点的值
				if( vl[vexIndex] > vl[node->adjVex] - node->info.weight ){
					vl[vexIndex] = vl[node->adjVex] - node->info.weight;
				}
				node = node->next;
			}
		}
		// 打印信息
		printf("结点\t");
		for( i = 0; i < g->vexNum; i++ ){
			printf("%s\t",g->adjList[i].data.name);
		}
		printf("\n");
		printf("ve\t");
		for( i = 0; i < g->vexNum; i++ ){
			printf("%d\t",ve[i]);
		}
		printf("\n");
		printf("vl\t");
		for( i = 0; i < g->vexNum; i++ ){	
			printf("%d\t",vl[i]);
		}
		printf("\n");
		// 初始化一个关键路径，且默认关键路径都下标为0的顶点开始
		List list = creatList();
		add( list, 0 );
		lists[llength++] = list;
		findSP( g, list, 0, ve, vl );// 调用找关键路径函数
		printf("关键路径有%d个\n",llength);
		for( i = 0; i < llength; i++ ){// 打印关键路径
			printf("**%d**\t",i+1);
//			printList( lists[i] );
			Node* start = lists[i]->next;
			while( start ){
				printf("%s\t",g->adjList[start->index].data.name);
				start = start->next;
			}
			printf("\n");
		}
		// 打印关键路径，利用邻接矩阵，act[i][j]表示 i->j 边上的活动,值为1表示是关键活动
		int act[g->vexNum][g->vexNum];
		int j;
		for( i = 0; i < g->vexNum; i++ ){
			for( j = 0; j < g->vexNum; j++ ){
				act[i][j] = 0;
			}
		}
		// 遍历关键路径,标记关键活动
		int nextIndex;
		Node* tnode;
		for( i = 0; i <llength; i++ ){
			tnode = lists[i]->next;
			while( tnode->next ){
				vexIndex = tnode->index;
				nextIndex = tnode->next->index;
				node = g->adjList[vexIndex].firstArc;
				while( node ){
					if( node->adjVex == nextIndex ){
						if( !act[vexIndex][node->adjVex] ){
							printf("边<%d,%d> 名称%s 权值%d\n",vexIndex, node->adjVex, node->info.str, node->info.weight);
						}
						
						act[vexIndex][node->adjVex] = 1;
						break;
					}	
					node = node->next;
				}
				tnode = tnode->next;
			}
		}
		
	}	


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









