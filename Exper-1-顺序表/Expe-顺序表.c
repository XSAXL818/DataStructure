#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define OK 1
#define ERROR 0

// 用于函数结果状态
typedef int Status;
// 一个学校的数据,包含学校的名字和学生人数,表中学校的位置按序号依次为 1，2，3，4.....
typedef struct{
	int numOfPeople;
	char* name;	
} SchoolData;
// 一个顺序表,包含一系列学校的数据
typedef struct{
	SchoolData *schoolData;
	int length;
	int maxSize;
} Schools;
// 字符串数组
typedef struct{
	char* name;
} SchoolName;
// 用于删除的算法：保存要删除元素的下标(小到大)
typedef struct _Elem{
	int index;
	struct _Elem* next;
} Elem;

typedef struct{
	Elem* head;
	Elem* tail;
} List;

// 初始化传入的顺序表,指明顺序表的最大容量,创建成功返回OK,否则返ERROR
Status InitSchools( Schools *s, int maxSize );
// 删除传入的列表,成功返回OK，否则返回ERROR
Status DestorySchools( Schools *s);
// 遍历表中的每一个元素
void printSchools( Schools *s );
// 向列表中添加元素,成功返回该元素在列表的位置,否则返回ERROR
// 为什么不返回OK,因为我觉得index和OK效果相同,且index或许另有用处
Status addElem( Schools *s, char* name, int num );
Status addSchoolData( Schools *s, SchoolData *sd);
// 定位添加
Status InsertElem(Schools* s,char *name, int num,int index);
// 定位删除：传入要删除的序号,成功返回该序号学校的名字,否则返回NULL
char*  DeleteElemAtIndex( Schools *s, int index );
// 按名删除:传入学校名称,成功删除后返回该校的序号,否则返回ERROR
Status DeleteElemAtName( Schools *s, char *name );
// 输入一个数,删除所有相同数据的元素
Status DeleteAllElemAtNum( Schools *s, int num);
Status DeleteAllElemAtNumUp( Schools* s, int num );
// 按名查询,找到返回序号
int getAtName( Schools* s, char* name);
// 按名查询,输入学校名，找到返回该学校人数，没找到返回-1
int getElemAtName(Schools *s, char* name);
// 按序号查询,返回该学校的信息(SchoolData*)，否则返回NULL
SchoolData* getElemAtIndex( Schools *s, int index );
// 按名修改学校人数,修改成功返回原人数,否则返回-1
Status putElemAtName(Schools *s, char* name, int num);
// 按序号修改,成功返回OK否则返回ERROR
Status putElemAtIndex( Schools* s, char* name, int num, int index );
// 对列表进行排序,按学校人数(便于管擦顺序)，成功返回OK,否则ERROR
Status selectSort( Schools *s);
Status bubbSort(Schools *s);
// 传两个有序表(小到大),然后合并一个新有序表并返回
Status mergerList( Schools *s1, Schools *s2, Schools* s );

// --------------------以下为界面化设计
// 登录界面
int view(void);
// 返回数值用于进入 所选列表 的操作界面
// 传入一个Schools类型的数组,如何在屏幕打印出已创建的列表,
// 第二个参数用于存在表的名字(各表名按创建时间排序,存在一些漏洞,但对本实验不重要)
Schools* showList(Schools schools[],SchoolName schoolName[],int length);
// 进入选择如何操作列表的功能
int selectFunction(void);

// 以下删除算法所需要的方法
Status add( List* list, int index ){
	
	Elem *e = (Elem*)malloc( sizeof(Elem) );
	if( e == NULL ){
		return ERROR;
	}
	e->index = index;
	e->next = NULL;

	if( list->head == NULL ){
		list->head = e;
	} else {
		list->tail->next = e;
	}
	list->tail = e;

	return OK;
}
void printList( List* list ){
	Elem* start;
	for( start=list->head; start; start = start->next ){
		printf("%d ",start->index);
	}
	printf("\n");
}
int getSize(List* list){
	int size = 0;
	Elem* start = list->head;
	for( ; start; start = start->next){
		size++;
	}
	return size;
}

int main(){

	// 用于储存已有的列表
	Schools schools[10];
	int length = 0;
	// 用于显示列表的名称
	SchoolName schoolName[10];
	
	Schools s1;
	InitSchools(&s1,20);
	addElem(&s1, "西北师范大学",3300);
	addElem(&s1, "兰州交通大学",2600);
	addElem(&s1, "兰州大学",4300);
	SchoolData t;
	t.name = "兰州政法大学";
	t.numOfPeople = 3420;
	addSchoolData( &s1, &t );
	
	bubbSort( &s1 );
	
	Schools s2;
	InitSchools(&s2,20);
	addElem(&s2, "西安交通大学",3500);
	addElem(&s2, "西北工业大学",2800);
	addElem(&s2, "西北大学",4200);
	addElem(&s2, "陕西师范大学",2700);
	selectSort( &s2 );
		
	schools[0] = s1;
	schools[1] = s2;
	schoolName[0].name = "甘肃高校";
	schoolName[1].name = "陕西高校";
	length = 2;

	while( 1 ){
		// 进入菜单,并返回所选的数字
		int select = view();
		if( select == 1 ){
			// 选择要操作的列表
			Schools *s = showList(schools, schoolName, length);
			while( 1 ){
				// 进入操作列表的功能,返回选项
				// 打印所选列表的信息
				printSchools(s);
				printf("\n"); 
			/*
			1.增   		2.定位增	 3.按名删    
			4.按序号删	 5.按名查    6.按序号查
			7.按名改     8.按序号改  9.排序(小到大)
			10.删除所有相同人数的学校	  11 .退出  
			*/
				int fun = selectFunction();
				SchoolData *sd = (SchoolData*)malloc( sizeof( SchoolData ) );
				char* name = malloc( sizeof(char) * 10 );
				int index = 0;
				int num = 0;
				switch( fun ){
					case 1:	
						printf("请输入学校的名字\n");
						scanf("%s",name);
						sd->name = name;
						printf("请输入该学校的人数\n");
						scanf("%d",&(sd->numOfPeople));
						addSchoolData( s, sd );
						printf("添加成功！\n");
						break; 
					case 2:
						printf("请输入要插入的位置\n");
						scanf("%d",&index);
						printf("请输入该学校的名称\n");
						scanf("%s",name);
						sd->name = name;
						printf("请输入该学校的人数\n");
						scanf("%d",&(sd->numOfPeople));
						InsertElem( s, name, sd->numOfPeople, index);
						printf("\n");
						break;
					case 3:	
						printf("请输入该学校的名字\n");
						getchar();
						gets(name);
						index = DeleteElemAtName( s, name );
						if( index == 0 ){
							printf("未找到该学校\n");
						} else {
							printf("删除成功!\n");
						}
						printf("\n");
						break;
					case 4:
						printf("请输入要删除的序号\n");
						scanf("%d",&index);
						char *name = DeleteElemAtIndex( s, index );
						if( index == 0 ){
							printf("未找到该学校\n");
						} else {
							printf("%s已被删除!\n",name);
						}
						printf("\n");
						break;
					case 5:
						printf("请输入你要查询学校的名字\n");
						char schoolName[10];
						scanf("%s",schoolName);
						int num = getElemAtName( s, schoolName );
						if( num == 0 ){
							printf("未找到该学校\n");
						} else {
							printf("学校名称:%s\t人数:%d\n",schoolName,num);
						}
						printf("\n");
						break;
					case 6:
						printf("请输入你要查询学校的序号\n");
						scanf("%d",&index);
						SchoolData* sd = getElemAtIndex( s, index );
						if( sd == NULL ){
							printf("未找到该学校\n");
						} else {
							printf("学校名称：%s\t人数：%d\n",sd->name,sd->numOfPeople);
						}
						printf("\n");
						break;
					case 7:
						printf("请输入你要修改学校的名字\n");
						char schoolName2[10];
						scanf("%s",schoolName2);
						int index = getAtName( s, schoolName2 );
						if( index == 0 ){
							printf("未找到该学校\n");
						} else {
							printf("请输入修改后学校的名字\n");
							char schoolName1[10];
							scanf("%s",schoolName1);
							printf("请输入修改后学校的人数\n");
							scanf("%d",&num);
							putElemAtIndex( s, schoolName1, num, index);
						}
						printf("\n");
						
						break;
					case 8:
						printf("请输入你要修改学校的序号\n");
						scanf("%d",&index);
						SchoolData* t = getElemAtIndex( s, index );
						printf("要修改学校的名字：%s\t人数：%d\n",t->name,t->numOfPeople);
						printf("请输入修改后学校的名字(如不修改输入0)\n");
						char schoolName1[10];
						scanf("%s",schoolName1);
						printf("请输入修改后学校的人数\n");
						scanf("%d",&num);
						if( schoolName1[0] == '0' ){
							putElemAtIndex( s, t->name, num, index);
						} else {
							putElemAtIndex( s, schoolName1, num, index);
						}
					
						printf("修改成功!\n\n");
						break;
					case 9:
						selectSort( s );
						break;
					case 10:
						printf("请输入你要删除的人数\n");
						scanf("%d",&num);
						int disc = DeleteAllElemAtNumUp( s, num );
						if( disc ){
							printf("删除成功!\n");
						} else {
							printf("输出数据有误！\n");
						}

						break;
				}
				if( fun == 11 ){
					break;
				}
			}
			
		} else {
			printf("请输入要合并的两个列表的序号(格式：序号1 序号2)\n");
			int index1;
			int index2;
			scanf("%d %d",&index1,&index2);
			printf("请输入新列表的名称\n");
			char ss[10];
			scanf("%s",ss);
			Schools t;
			Schools *t1 = &schools[index1-1];
			Schools *t2 = &schools[index2-1];
			if( mergerList( t1, t2, &t ) ){
				printf("新列表创建成功！\n");
			} else {
				printf("创建失败!\n");
			}
			schools[length] = t;
			schoolName[length].name = ss;
			length++;
		}
		
	}

	return 0;
}
// 初始化一个顺序表,指明顺序表的最大容量,创建成功返回OK,否则返ERROR
Status InitSchools( Schools *s, int maxSize ){
	// 判断 s maxSize 输入是否合法
	if( s == NULL || maxSize < 0 ){
		return ERROR;
	}
	// 初始化
	s->schoolData = (SchoolData*)malloc( sizeof(SchoolData) * maxSize );
	if( s->schoolData == NULL ){
		return ERROR;
	}
	s->length = 0;
	s->maxSize = maxSize;
	return OK;
}
// 摧毁列表
Status DestorySchools( Schools *s){
	if( s== NULL ){
		return ERROR;
	}
	int i;
	for(i=0; i < s->length; i++){
		free( s->schoolData + i );
	}	
	
	return OK;
}
// 向列表中添加元素,成功返回该元素在列表的序号,否则返回ERROR
Status addElem( Schools *s, char* name, int num ){
	if( s == NULL || name == NULL || num < 0 ){
		return ERROR;
	}
	SchoolData *t = s->schoolData + s->length;
	t->name = name;
	t->numOfPeople = num;
	s->length++;
	return s->length;
}
Status addSchoolData( Schools *s, SchoolData *sd){
	if( s == NULL || sd == NULL ){
		return ERROR;
	}
	*(s->schoolData + s->length) = *sd;
	s->length++;
	return s->length;
	
}
// 向列表第i个位置插入一个元素,成功返回元素位置的序号,否则ERROR
// 为什么不返回OK,因为我觉得index和OK效果相同,且index或许另有用处
Status InsertElem(Schools* s,char *name, int num,int index){
	if( s== NULL || name == NULL ){
		return ERROR;
	}
	if( index > (s->length + 1) || index < 1 || num < 0 || index > s->maxSize ){
		return ERROR;
	}
	
	int i;
	for( i=s->length; i >= index; i--){
		*(s->schoolData + i) = *(s->schoolData + i - 1);
	}
	SchoolData* sd = s->schoolData + i;
	sd->numOfPeople = num;
	sd->name = name;

	s->length++;
	return index;
}
// 定名查询：输入学校名字返回所在的序号，未找到返回ERROR
int getAtName( Schools* s, char* name){

	int index = 1;
	SchoolData *t = s->schoolData;
	while( strcmp( (t++)->name, name ) != 0 ){
		index++;
		if( index > s->length ){
			return ERROR;
		}
	}

	return index;
}
// 定位删除：传入要删除的序号,成功返回该序号学校的名字,否则返回NULL
char*  DeleteElemAtIndex( Schools *s, int index ){
	if( s == NULL ){
		return NULL;
	}
	if( index < 1 || index > s->length ){
		return NULL;
	}
	char *str = ( s->schoolData + index - 1 )->name;
	int i;
	for( i=index-1; i < s->length-1; i++){
		*(s->schoolData + i) = *(s->schoolData + i + 1);
	}
	s->length--;
	return str;
}
// 按名删除:传入学校名称,成功删除后返回该校的序号,否则返回ERROR
Status DeleteElemAtName( Schools *s, char *name ){
	if( s->schoolData == NULL || s == NULL || name == NULL ){
		return ERROR;
	}
	
	int index = getAtName( s, name );
	if( index == 0 ){
		return ERROR;
	}
	
	int i;
	for( i=index-1; i < s->length-1; i++){
		*(s->schoolData + i) = *(s->schoolData + i + 1);
	}
	s->length--;
	return index;
}
// 输入一个数,删除所有相同数据的元素
// 算法弊端：1.如果要删除的元素靠后,则前期进行了不必要的赋值运算 2.算法需要创建与列表长度相同的数组,浪费空间
Status DeleteAllElemAtNum( Schools *s, int num){
	if( s == NULL || num < 0 ){
		return ERROR;
	}
	
	int arr[s->length];
	int i;
	for( i=0; i < s->length; i++ ){
		if( num == (s->schoolData + i)->numOfPeople ){
			arr[i] = 0;
		} else {
			arr[i] = 1;
		}
	}
					
	int index = 0;
	int sLength = s->length;
	// 针对 1 进行改进 创建一个int dic = 0 ,出现要删除的元素前 进行 dic判断：dic == 0，则不赋值
	int dic = 0;
	//
	for( i=0; i < sLength; i++ ){
		if( arr[i] ){
			// 改进后	
			if( dic ){
				*(s->schoolData + index) = *(s->schoolData + i);
			}
			// 
			index++;                                       
		} else {
			// 改进后
			dic = 1;
			//
			s->length--;
		}
	}
	return OK;
}
// 针对二进行改进,用链表存储所要删除的元素,当要删除的元素较少时内存占用大大减少
Status DeleteAllElemAtNumUp( Schools* s, int num ){
	List L;
	L.head = NULL;
	int i;
	// 保存所有要删除的元素
	for( i=0; i < s->length; i++ ){
		if( num == (s->schoolData + i)->numOfPeople ){
			add( &L, i );
		} 
	}
	
	int sLength = s->length;
	Elem* start = L.head;
	int index = start->index;

	int dic = 0;
	for( i=start->index; i < sLength; i++ ){
		if( i != start->index ){
			*(s->schoolData + index) = *(s->schoolData + i);
			index++;                                       
		} else {
			dic = 1;
			s->length--;
			start = start->next;
		}
	}
		
	return OK;
}
// 按名查询,输入学校名，找到返回该学校人数，没找到返回-1
int getElemAtName(Schools *s, char* name){
	if( s == NULL || name == NULL ){
		return -1;
	}
	int index = getAtName( s, name );
	if( index == 0 ){
		return -1;
	}
	return (s->schoolData + index - 1)->numOfPeople;
}
// 按序号查询,返回该学校的信息(SchoolData*)，否则返回NULL
SchoolData* getElemAtIndex( Schools *s, int index ){
	if( s == NULL ){
		return NULL;
	}
	if( index < 1 || index > s->length ){
		return NULL;
	}
	return s->schoolData + index - 1;
}
// 按名修改学校人数,修改成功返回原人数,否则返回-1
int putElemAtName(Schools *s, char* name, int num){
	if( s == NULL || name == NULL ){
		return -1;
	}
	int index = getAtName(s,name);
	if( index == 0 ){
		return -1;
	}
	SchoolData* sd = s->schoolData + index - 1 ;
	int t = sd->numOfPeople;
	sd->numOfPeople = num;
	return t;
}
// 按序号修改,成功返回OK否则返回ERROR
Status putElemAtIndex( Schools* s, char* name, int num, int index ){
	if( s == NULL || name == NULL ){
		return ERROR;
	}
	if( index < 1 || index > s->length ){
		return ERROR;
	}
	SchoolData *sd = s->schoolData + index - 1;
	sd->name = name;
	sd->numOfPeople = num;
	return OK;
}
// 对列表进行排序,按学校人数(便于观察顺序)，成功返回OK,否则ERROR
// 选择排序
Status selectSort( Schools *s){
	if( s == NULL ){
		return ERROR;
	}
	int i,j;
	for( i=s->length-1; i > 0; i--){
		int max = (s->schoolData + 0)->numOfPeople;
		int index = 0;
		for(j=1; j <= i; j++){
			SchoolData* sd = s->schoolData + j;
			if( max < sd->numOfPeople ){
				max = sd->numOfPeople;
				index = j;
			}
		}
		// 所寻列表的末元素
		SchoolData* sd1 = s->schoolData + i;
		// 所寻列表的最大值的元素
		SchoolData* sd2 = s->schoolData + index;
		// 交换元素
		SchoolData t = *sd1;
		*sd1 = *sd2;
		*sd2 = t;
	}
	return OK;
}
// 冒泡排序
Status bubbSort(Schools *s){
	if( s == NULL ){
		return ERROR;
	}
	int i,j;
	for(i=s->length-1; i > 0; i--){
		for(j=0; j < i; j++){
			SchoolData *sd1 = s->schoolData + j;
			SchoolData *sd2 = s->schoolData + j + 1;
			if( sd1->numOfPeople > sd2->numOfPeople ){
				SchoolData t = *sd1;
				*sd1 = *sd2;
				*sd2 = t;
			}
		}
	}
}
// 传两个有序表(小到大),然后合并一个新有序表并返回
// 思路：取两个下标0,从s1,s2开始,然后每次对比表头元素,将较小者放入表中,然后直到填满
// 1.定义三个int变量index1=0,index2=0,index=0;
	//说明：index1,index2分别指向s1,s2作为有序表的表头元素（即index1=1时,s1的第一个元素失效,第二个元素为表头）,index指明存在在新列表的位置
// 2.进入循环,循环判断条件为 (index1+index2) <= (s1->length + s2->length)
// 		2.1 判断两个有序表的表头,小的元素放入放入s的index位置,然后小元素的下标+1；若相同则两个同时放入,并index1,index2都+1
//  	2.2 判断index1,index2是否超过各表的长度,如超过,则将另一个有序表全部放入新表并跳出2循环，没超过则进入下一次循环

Status mergerList( Schools *s1, Schools *s2, Schools* s ){
	if( s1 == NULL || s2 == NULL ){
		return ERROR;
	}
	
	int length = s1->length + s2->length;
	InitSchools( s, s1->maxSize+s2->maxSize );
	
	int index1 = 0;
	int index2 = 0;
	int index = 0;
	// 这里是 length-1 是因为 index表示s的下标,index=0,index=length-1 为s1+s2的元素的总和
	while( index <= length-1  ){
		if( (s1->schoolData+index1)->numOfPeople <  (s2->schoolData+index2)->numOfPeople ){
			*(s->schoolData+index) = *(s1->schoolData+index1);
			index1++;
			index++;
			s->length++;	
		} else if( (s1->schoolData+index1)->numOfPeople ==  (s2->schoolData+index2)->numOfPeople ){
			*(s->schoolData+index) = *(s1->schoolData+index1);
			index++;
			index1++;
			*(s->schoolData+index) = *(s2->schoolData+index2);
			index++;
			index2++;
			s->length += 2;
		} else {
			*(s->schoolData+index) = *(s2->schoolData+index2);
			index2++;
			index++;
			s->length++;
		}
		
		if( index1 == s1->length ){
			while( index2 < s2->length ){
				*(s->schoolData+index) = *(s2->schoolData+index2);
				index2++;
				index++;
				s->length++;
			}
		} else if( index2 == s2->length ){
			while( index1 < s1->length ){
				*(s->schoolData+index) = *(s1->schoolData+index1);
				index1++;
				index++;
				s->length++;
			}
		}
	}	
	return OK;
}
// 遍历表中的每一个元素
void printSchools( Schools *s ){
	int i;
	printf("--------------------------------------\n序号\t学校名称\t\t人数\n");
	for( i=0; i < s->length; i++){
		SchoolData *t = s->schoolData + i;
		printf("%d\t%-8s\t\t%d\n",i+1,t->name,t->numOfPeople);
	}
	printf("--------------------------------------\n");
}
// ----------------------------以下为实现界面化的函数
// 登录界面
int view(void){
	printf("---------------------------------------------\n");
	printf("请选择以下功能:\n");
	printf("1.显示已有列表(可编辑列表)\n");
	printf("2.合并列表\n");
	printf("---------------------------------------------\n");
	printf("请输入你要选择的功能\n");
	int select;
	while( 1 ){
		scanf("%d",&select);
		if( select == 1 || select == 2 ){
			break;
		}
		printf("输入错误！请重新输入!\n");
	}
	return select;
}
// 返回 所选列表 
// 传入一个Schools类型的数组,便于返回进入的列表
// 第二个参数用于存在表的名字(各表名按创建时间排序,存在一些漏洞,但对本实验不重要)
Schools* showList(Schools schools[],SchoolName schoolName[],int length){
	int i;
	printf("****************************************\n");
	printf("序号\t列表名称\n");
	for(i=0; i < length; i++){
		printf("%d\t%s\n",i+1,schoolName[i].name);
	}
	printf("****************************************\n");
	printf("请选择要操作的列表(按序号)\n");
	int select;
	while( 1 ){
		scanf("%d",&select);
		if( select > 0 || select <= length ){
			break;
		}
		printf("输入非法,请重新输入!\n");
	}
	
	return &(schools[select-1]);
}
// 选择操作列表的功能
int selectFunction(void){
	printf("请输入你要选择的操作\n");
	printf("1.增*\t\t2.插入*\t3.按名删(表中第一个)\n");
	printf("4.按序号删*\t5.按名查人数\t6.按序号查*\n");
	printf("7.按名改*\t8.按序号改*\t9.排序(小到大)\n");
	printf("10.删除人数相同的学校\t11.退出\n");
	int select;
	scanf("%d",&select);
	return select;
}


/*
	实验总结：1.定位增删操作是容易漏掉将数组长度加1或者减1
			  2.为了算法的健壮性,需要对函数的形参做检查
			  3.按名删改的函数中包含按名查询,为了书写简便可以先写好按名查询,然后内嵌在别的函数,减少了代码的书写
			  4.有序表合并操作关键点在于对各表下标的控制
			  	4.1 循环条件：即index从0到原表元素相加-1,
			  	4.2 循环体中的主要思想: 找出两个表头的最小元素,但存在表头相等,此时即需要三个if语句,在两个表头相等情况下则需要双管齐下,
			  		犯的错误：在if语句中,每次新表添加新元素后忘记了 新表长度加1;同时书写不够简洁
			  	4.3 上面的if是在 双表的表头都存在的情况下进行的,因此4.2结束后需要判断是否一方已经全部放入新表
				  												判断条件为：if(index1 == s1.length) {将s2全部放入新表 }
				  															else if(index2 == s2.length) {将s1全部放入新表}	  
				  	犯的错误: 在操作体中,循环的条件输入错误,比如 在一个if的操作中, 写成 index2 <= s2.length 此时index2==s2.length 访问会越界
			  5.让列表删除所有同种元素,时间复杂度位T(N),思路：创建一个int arr[],有序表需要保留元素的所有下标index,使arr[index]=1,
			  	即让 index=0,i=0,然后依此遍历数组,若arr[i]=1,则让有序表第index个元素等于有序表第i个元素并index+1；arr[i]=0,则有序表长度-1
			  	犯的错误：在遍历数组使用的循环条件是 i < 每次操作完后有序表的长度,这使得一旦删除删除一个元素后,有序表长度-1,
				  						因此循环次数变少,能arr就无法访问完,
				解决: 提前创建一个变量保存一个开始列表的长度
			  	
*/


