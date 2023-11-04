#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define OK 1
#define ERROR 0
// 函数返回状态
typedef int Status;

// 学生成绩信息
typedef struct{
	int math;
	char* name;
} StudentGrade;
// 结点,链表的结点,每个结点存储一个学生的信息
typedef struct _Node{
	StudentGrade stu;
	struct _Node* next;
} Node;
// 链表的表头表尾,存储学生成绩的链表,学生序号从1开始
typedef struct{
	int length;
	Node* head;
	Node* tail;	
} *LinkList,List;
// 创建一个链表
LinkList creatLinkList();
// 摧毁链表
Status freeLinkList( LinkList list );
// 插入到表头
Status addByHead( LinkList list, int math, char* name);
// 插入到表尾
Status addByTail( LinkList list, int math, char* name);
// 打印列表元素
void printList( LinkList list );
// 获取链表长度
int getSize( LinkList list );
// 按位插入
Status InsertElemAtIndex( LinkList list, int math, char* name, int index );
// 按位删除
Status DeleteElemAtIndex( LinkList list, int index );
// 按名删
Status DeleteElemAtName( LinkList list, char* name );
// 删除所有成绩相同的人
Status DeleteAllElemAtNum( LinkList list, int num );
// 按序号修改
Status putElemAtIndex( LinkList list, char* name, int num, int index );
// 按名字修改
Status putElemAtName( LinkList list, char* name, int num, char* src );
// 按序号查找,返回该结点的地址
Node* getElemAtIndex( LinkList list, int index );
// 按名字查找,返回结点的地址
Node* getElemAtName( LinkList list, char* name );
// 链表的冒泡排序
Status bubbSort( LinkList list );
// 链表的选择排序
Status selectSort( LinkList list );
// 合并两个有序的链表
Status mergerList( LinkList src1, LinkList src2, LinkList dest);

// --------------------以下为界面化设计
typedef struct{
	LinkList list;
	char* name;
} Lists;
// 登录界面
int view(void);
// 显示操作链表的功能
int selectFunction(void);
// 显示列表
LinkList showList(Lists lists[],int length);




int main(){
	// 初始化两个链表
	LinkList list1 = creatLinkList();
	addByTail( list1, 55, "a1" );
	addByHead( list1, 43, "a2" );
	addByTail( list1, 55, "a3" );
	addByTail( list1, 78, "a4" );
	addByHead( list1, 63, "a5" );
	addByTail( list1, 55, "a6" );
	addByHead( list1, 73, "a7" );

	LinkList list2 = creatLinkList();
	addByTail( list2, 78, "b1" );
	addByHead( list2, 48, "b2" );
	addByTail( list2, 97, "b3" );
	addByTail( list2, 23, "b4" );
	addByHead( list2, 46, "b5" );
	addByTail( list2, 55, "b6" );
	addByHead( list2, 86, "b7" );
	Lists lists[10] = { { list1, "list1"}, { list2, "list2"} };
	int length = 2;
	while( 1 ){
		int select =  view();
		if( select == 1 ){
			LinkList list = showList( lists,length );
			while( 1 ){
				// 显示要操作列表的所有元素
				printList( list );
//					1.头插入   2.尾插入   3.按位插入
//					4.按位删除 5.按名删除 6.删除指定分数以下的人
//					7.按名改*  8.按序号改*
//					9.按名查*  10.按序号查*
//					11.排序(大到小) 12.退出
				int func = selectFunction();
				char *name = (char*)malloc( sizeof( char ) * 10 );
				int math;
				int index;
				Node* node;
				switch( func ){
					case 1:
						printf("请输入该学生的姓名：");
						scanf("%s",name);
						printf("请输入该学生的数学成绩：");
						scanf("%d",&math);
						if( addByHead( list, math, name ) ){
							printf("添加成功！\n");
						} else {
							printf("添加失败\n");
						}
						break;
					case 2:
						printf("请输入该学生的姓名：");
						scanf("%s",name);
						printf("请输入该学生的数学成绩：");
						scanf("%d",&math);
						if( addByTail( list, math, name ) ){
							printf("添加成功！\n");
						} else {
							printf("添加失败\n");
						}	
						break;
					case 3:
						printf("请输入要插入的位置：");
						scanf("%d",&index);
						printf("请输入该学生的姓名：");
						scanf("%s",name);
						printf("请输入该学生的数学成绩：");
						scanf("%d",&math);
						if( InsertElemAtIndex( list, math, name, index ) ){
							printf("插入成功！\n");
						} else {
							printf("插入失败\n");
						}
						break;
					case 4:
						printf("请输入要删除学生的序号：");
						scanf("%d",&index);
						if( DeleteElemAtIndex( list, index ) ){
							printf("删除成功！\n");
						} else {
							printf("删除失败\n");
						}
						break;
					case 5:
						printf("请输入该学生的姓名：");
						scanf("%s",name);
						if( DeleteElemAtName( list, name ) ){
							printf("删除成功！\n");
						} else {
							printf("删除失败\n");
						}
						break;
					case 6:
						printf("请输入要删除的指定分数：");
						scanf("%d",&math);
						if( DeleteAllElemAtNum( list, math ) ){
							printf("删除成功！\n");
						} else {
							printf("删除失败\n");
						}
						break;
					case 7:
						printf("请输入该学生的姓名：");
						char src[10];
						scanf("%s",src);
						node = getElemAtName( list, src );
						if( node ){
							printf("该学生成绩为%d    请输入要修改的分数：",node->stu.math);
							scanf("%d",&math);
							node->stu.math = math;
						} else {
							printf("不存在该学生！\n");
						}
						break;
					case 8:
						printf("请输入要修改学生的序号：");
						scanf("%d",&index);
						node = getElemAtIndex( list, index );
						
						if( node ){
							printf("学生姓名=%s\t成绩=%d\n",node->stu.name, node->stu.math );
							printf("是否修改姓名(1.yes\t2.no)\n");
							int dic;
							scanf("%d",&dic);
							if( dic == 1 ){
								printf("请输入修改后的名字：");
								scanf("%s",name);
								node->stu.name = name;
							}
							printf("请输入修改后的成绩：");
							scanf("%d",&(node->stu.math));
							printf("删除成功！\n");
						} else {
							printf("删除失败\n");
						}
						break;
					case 9:
						printf("请输入该学生的姓名：");
						scanf("%s",name);
						node = getElemAtName( list, name );
						if( node ){
							printf("\n该学生姓名为%s\t成绩为%d\n\n",node->stu.name,node->stu.math);
						} else {
							printf("\n不存在该学生！\n\n");
						}
						break;
					case 10:
						printf("请输入要修改学生的序号：");
						scanf("%d",&index);
						node = getElemAtIndex( list, index );
						if( node ){
							printf("\n该学生姓名为%s\t成绩为%d\n\n",node->stu.name,node->stu.math);
						} else {
							printf("\n不存在该学生！\n\n");
						}
						break;
					case 11:	
						if( selectSort( list ) ){
							printf("排序成功！\n");
						} else {
							printf("排序失败！\n");
						}
						break;
				}
				if( func == 12 ){
					break;
				}
			}
		} else if( select == 2 ) {
			printf("输入要合并链表的序号：(序号1 序号2)\n");
			int index1,index2;
			scanf("%d %d",&index1,&index2);
			printf("请输入新链表的名称：");

			char name[10];
			scanf("%s",name);
			LinkList list = creatLinkList();
			if( mergerList( lists[index1-1].list, lists[index2-1].list, list ) ){
				lists[length].list = list;
				lists[length].name = name;
				length++;
				printf("合并成功！\n");	
			} else {
				printf("合并失败!\n");
			}
		} else {
			break;
		}
	}
	
	return 0;
}
// 创建一个链表
LinkList creatLinkList(){
	LinkList list = (LinkList)malloc( sizeof(List) );
	if( list == NULL ){
		return NULL;
	}
	list->head = NULL;
	list->length = 0;
	return list;
}
// 摧毁链表
Status freeLinkList( LinkList list ){
	if( list == NULL ){
		return ERROR;	
	}
	while( list->head ){
		Node* t = list->head;
		list->head = list->head->next;
		free( t );
	}
	list->length = 0;
	list->head = NULL;
	return OK;
}
// 插入到表头
Status addByHead( LinkList list, int math, char* name){
	if( math < 0 || math > 100 || name == NULL ){
		return ERROR;
	}
	
	Node* node = (Node*)malloc( sizeof(Node) );
	node->stu.math = math;
	node->stu.name = name;
	// 第一次添加元素
	if( list->head == NULL ){
		node->next = NULL;
		list->head = node;
		list->tail = node;
		list->length++;
		return OK;
	}

	node->next = list->head;
	list->head = node;
	list->length++;
	return OK;
	
}
// 插入到表尾
Status addByTail( LinkList list, int math, char* name){
	if( math < 0 || math > 100 || name == NULL ){
		return ERROR;
	}
	Node* node = (Node*)malloc( sizeof(Node) );
	node->stu.math = math;
	node->stu.name = name;
	node->next = NULL;
	// 第一次添加元素
	if( list->head == NULL ){
		list->head = node;
	} else {
		list->tail->next = node;
	}

	list->tail = node;
	list->length++;
	return OK;
}
// 获取链表长度
int getSize( LinkList list ){
	if( list == NULL ){
		return 0;
	}
	int cnt = 0;
	Node* start = list->head;
	while( start ){
		cnt++;
		start = start->next;
	}
	return cnt;
}
// 打印列表元素
void printList( LinkList list ){
	printf("---------共有%d个人------------\n",list->length);
	Node* start = list->head;
	printf("序号\t\t姓名\t\t成绩\n");
	int dic = 0;
	while( start ){
		printf("%d\t\t%s\t\t%d\n",++dic,start->stu.name,start->stu.math);
		start = start->next;
	}
}

// 按序号查找,返回该结点的地址
Node* getElemAtIndex( LinkList list, int index ){
	if( list == NULL){
		return NULL;
	}
	
	if( index < 1 || index > list->length ){
		return NULL;
	}
	Node* start = list->head;
	// 方法一：利用列表中的长度
	while( --index ){
		start = start->next;
	}
	return start;
//	if( index < 1 ){
//		return NULL;
//	}
//	int i = 1;
//	while( start && i < index ){
//		start = start->next;
//		i++;
//	}
//	// 循环结束有两种可能 1.start==NULL 可兼或 2.i==index 
//	if( start == NULL ){
//		// 只发生1
//		return NULL;
//	} else {
//		// 发生2 或 1,2(start可能是一个结点或NULL) 
//		return start;
//	}

}
// 按位后插,插入位置3,则将3移至4
Status InsertElemAtIndex( LinkList list, int math, char* name, int index ){
	if( list->head == NULL || list == NULL ){
		return ERROR;
	}
	// 方法一：链表有长度参数, 可插入到链表的末尾
//	if( math < 0 || math > 100 || name == NULL || index < 1 || index > list->length+1 ){
//		return ERROR;
//	}
//	Node* start = list->head;
//	Node* node = (Node*)malloc( sizeof(Node) );
//	// 插入链表的末尾
//	if( index == list->length+1 ){
//		node->stu.name = name;
//		node->stu.math = math;
//		list->tail->next = node;
//		list->tail = node;
//		return OK;
//	}
//	// 不插入到末尾,找到要插入位置的元素
//	while( --index ){
//		start = start->next;
//	}
//	node->next = start->next;
//	node->stu = start->stu;
//	start->stu.name = name;
//	start->stu.math = math;
//	start->next = node;
//	list->length++;

	// 方法二：链表无长度参数, 不可插入链表的末尾
	if( math < 0 || math > 100 || index < 1 ){
		return ERROR;
	}
	// 先找到要插入的位置的元素
	Node* start = list->head;
	while( index > 1 && start ){
		start = start->next;
		index--;
	}
	// 要插入的位置前无元素则插入位置错误
	if( start == NULL ){
		return ERROR;
	}

	Node* node = (Node*)malloc( sizeof(Node) );
	node->stu = start->stu;
	node->next = start->next;
	start->stu.name = name;
	start->stu.math = math;
	start->next = node;
	list->length++;	
	
	return OK;
}
// 按位删除,返回被删除的元素
Status DeleteElemAtIndex( LinkList list, int index ){
	// 方法一：使用长度参数
	if( list->head == NULL || list == NULL || index < 1 || index > list->length ){
		return ERROR;
	}
	// 要到要被删除的的元素的前一个元素
	if( index == 1 ){
		Node* t = list->head;
		list->head = list->head->next;
		free( t );
		list->length--;
		return OK;
	}
	Node* start = list->head;
	while( index > 2 ){
		start = start->next;
		index--;
	}
	Node* t = start->next;
	start->next = t->next;
	list->tail = start;
	free( t );
	list->length--;
	return OK;

//	// 方法二：不使用长度参数
//	if( list->head == NULL || list == NULL || index < 1 ){
//		return ERROR;
//	}
//	// 若为第一个元素
//	if( index == 1 ){
//		
//		if( list->head->next == NULL ){
//			free( list->head );
//			list->head = NULL;	
//		} else {
//			Node* t = list->head;
//			list->head = t->next;
//			free( t );
//		}
//		list->length--;
//		return OK;
//	}
//	Node* start = list->head;
//	// 找到要删除元素的前一个元素
//	while( index > 2 && start ){
//		start = start->next;
//		index--;
//	}
//	// 要删除的元素下标多于链表的元素个数
//	if( start->next == NULL ){
//		return ERROR;
//	}
//	Node* t = start->next;
//	start->next = t->next;
//	free(t);
//	list->length--;
//	return OK;
}
// 按名删
Status DeleteElemAtName( LinkList list, char* name ){
	
	if( list->head == NULL || list == NULL || name == NULL ){
		return ERROR;
	}
	// 方法一：使用长度参数
//	Node* start = list->head;
//	int length = list->length;
//	// 掐头
//	if( strcmp( start->stu.name, name ) == 0 ){
//		list->head = start->next;
//		list->length--;
//		free( start );
//		return OK;
//	} else if( length == 1 ) {
//		return ERROR;
//	}
//	
//	// 找要删除元素的前一个元素
//	while( length > 1 ){
//		if( strcmp( start->next->stu.name, name ) == 0 ){
//			Node* t = start->next;
//			start->next = t->next;
//			free( t );
//			list->length--;
//			return OK;
//		}
//		start = start->next;
//		length--;
//	}
//	return ERROR;
	// 方法二：无长度
	Node* start = list->head;
	// 掐头
	if( strcmp( start->stu.name, name ) == 0 ){
		list->head = list->head->next;
		free( start );
		list->length--;
		return OK;
	}
	// 找到要删除元素的前一个元素
	while( start->next ){
		if( strcmp( start->next->stu.name, name ) == 0 ){
			Node* t = start->next;
			start->next = start->next->next;
			free( t );
			list->length--;
			return OK;
		}
		start = start->next;
	}
	return ERROR;
}
// 删除所有成绩相同的人
Status DeleteAllElemAtNum( LinkList list, int num ){
	if( list == NULL || list->head == NULL || num < 0 || num > 100 ){
		return ERROR;
	}
	// 掐头
	Node* start;
	Node* t;
	if( list->head->stu.math < num ){
		t = list->head;
		list->head = list->head->next;
		list->length--;
		free( t );
	}
	// 找到删元素的前一个元素
	start = list->head;
	while( start->next ){
		if( start->next->stu.math < num ){
			t = start->next;
			start->next = start->next->next;
			free( t );	
			list->length--;
		} else {
			start = start->next;
		}	
		
	}
	return OK;
}
// 按序号修改
Status putElemAtIndex( LinkList list, char* name, int num, int index ){
	Node* node = getElemAtIndex( list, index );
	if( node == NULL ){
		return ERROR;
	}
	node->stu.name = name;
	node->stu.math = num;
	return OK;
}
// 按名字查找,返回结点的地址
Node* getElemAtName( LinkList list, char* name ){
	if( list == NULL){
		return NULL;
	}
	Node* start = list->head;
	while( start ){
		if( strcmp( start->stu.name, name ) == 0 ){
			return start;
		}
		start = start->next;
	}
	return NULL;
}
// 链表的冒泡排序
Status bubbSort( LinkList list ){
	if( list->head == NULL || list == NULL ){
		return ERROR;
	}
	int i,j;
	for( i = list->length; i > 1; i-- ){
		Node* start = list->head;
		for( j = 1; j < i; j++ ){
			if( start->stu.math < start->next->stu.math ){
				StudentGrade t = start->stu;
				start->stu = start->next->stu;
				start->next->stu = t;
			}
			start = start->next;
		}
	}
	
	return OK;
}
// 链表的选择排序
Status selectSort( LinkList list ){
	if( list->head == NULL || list == NULL ){
		return ERROR;
	}
	int i,j;
	for( i = list->length; i > 1; i-- ){
		Node* start = list->head;
		Node* min = list->head;
		for( j = 1; j < i; j++ ){
			start = start->next;
			if( start->stu.math < min->stu.math ){
				min = start;
			}
		}
		StudentGrade t = min->stu;
		min->stu = start->stu;
		start->stu = t;
	}
	return OK;
}
// 合并两个有序的链表
Status mergerList( LinkList src1, LinkList src2, LinkList dest){
	if( src1 == NULL || src2 == NULL || dest == NULL ){
		return ERROR;
	}
	// 创建两个头指针
	Node* head1 = src1->head;
	Node* head2 = src2->head;
	// 当两个头指针不为空时
	while( head1 && head2 ){
		if( head1->stu.math > head2->stu.math ){
			addByTail( dest, head1->stu.math, head1->stu.name );
			head1 = head1->next;
		} else if( head1->stu.math < head2->stu.math ){
			addByTail( dest, head2->stu.math, head2->stu.name );
			head2 = head2->next;
		} else {
			addByTail( dest, head1->stu.math, head1->stu.name );
			head1 = head1->next;
			addByTail( dest, head2->stu.math, head2->stu.name );
			head2 = head2->next;
		}
	}
	// 当一个链表全部加入新链表后
	if( head1 == NULL ){
		while( head2 ){
			addByTail( dest, head2->stu.math, head2->stu.name );
			head2 = head2->next;
		}
	} else {
		while( head1 ){
			addByTail( dest, head1->stu.math, head1->stu.name );
			head1 = head1->next;
		}
	}
	return OK;
}

// 登录界面
int view(void){
	printf("---------------------------------------------\n");
	printf("请选择以下功能:\n");
	printf("1.显示已有链表(可编辑链表)\n");
	printf("2.合并有序链表\n");
	printf("3.退出\n");
	printf("---------------------------------------------\n");
	printf("请输入你要选择的功能\n");
	int select;
	while( 1 ){
		scanf("%d",&select);
		if( select == 1 || select == 2 || select == 3 ){
			break;
		}
		printf("输入错误！请重新输入!\n");
	}
	return select;
}
// 显示操作链表的功能
int selectFunction(void){
	printf("\n请输入你要选择的操作：\n");
	printf("1.头插入*\t2.尾插入*\t3.按位插入*\n");
	printf("4.按位删除\t5.按名删除\t6.删除小于指定成绩的人\n");
	printf("7.按名改*\t8.按序号改*\n");
	printf("9.按名查*\t10.按序号查*\n");
	printf("11.排序(大到小)\t12.退出\n");
	int select;
	scanf("%d",&select);
	return select;
}
// 显示列表
LinkList showList(Lists lists[],int length){
	int i;
	printf("-------------------------------------------\n");
	printf("序号\t\t列表名称\n");
	for( i = 0; i < length; i++ ){
		printf("%d\t\t%s\n",i+1,lists[i].name);
	}
	printf("-------------------------------------------\n");
	printf("请输入要操作链表的序号\n");
	scanf("%d",&i);
	return lists[i-1].list;
}

