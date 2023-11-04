#include <stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct{
	char* tel;
	char* name;
} People;

typedef struct{
	int len;
	int maxSize;
	People* people;
} *GList,Node;

GList creatGList( int maxSize ){
	GList list = (GList)malloc( sizeof(Node) );
	list->len = 0;
	list->maxSize = 0;
	list->people = (People*)malloc( maxSize * sizeof(People) );
	return list;
}

void addPeople( GList list, char* name, char* tel ){
	People* peo = list->people + list->len;
	peo->tel = tel;
	peo->name = name;
	list->len++;
}

int binSearch( People* people, int len, char* key ){
	int low = 0;
	int high = len-1;
	int mid;
	while( low <= high ){
		mid = ( low + high ) / 2; //                                     0           1            2           3              4
		printf("%d ",mid);//                                           X11         X12           X14        X23            X44
		int ret = strcmp( key, people[mid].name );//      find 15       low                      mid                       high
		if( ret == 0 ){//                                                     							 low (mid)           high
			return mid;//                                                                       hight       low
		} else if( ret < 0 ){///                                                                            应插入的位置
			high = mid - 1;//                             find 55       low                       mid                      high
		} else if( ret > 0 ){//                                                                             low(mid)       high    
			low = mid + 1;//                                                                                               low(mid)high
		}//                                                                                                                  high          low
	}//                                                  find  1        low                        mid                        high
	return low;//                                                     low(mid)         high               
}//                                                          high       low
//                                   									综上，low是插入新学生的位置，只需从low开始整体后移一位即可
void find( GList list, char* name, char* tel ){
	int index = binSearch( list->people, list->len, name );
	printf("\n");
//	printf("%d %s %s***\n", index, id, list->students[index].id );
	if( index != list->len && strcmp( name, list->people[index].name ) == 0 ){
		if( strcmp( list->people[index].tel, tel ) == 0 ){
			printf("F ");
		} else {
			list->people[index].tel = tel;
			printf("U ");
		}
	} else {
		int i;
		for( i = list->len; i > index; i-- ){
			list->people[i] = list->people[i-1];
//			list->students[i].grade = list->students[i-1].grade;
//			list->students[i].id = list->students[i-1].id;
//			list->students[i].name = list->students[i-1].name;
		}
		list->people[i].name = name;
		list->people[i].tel = tel;
		printf("I ");
	}
	printf("%d",index);
}
// 这题完全可以不考虑名字。。。栓Q
int main(){
	
	int num;
	char *tel,*name;
	int i;
	scanf("%d",&num);
	GList list = creatGList( 200 );
	for( i = 0; i < num; i++ ){
		tel = (char*)malloc( 12*sizeof(char) );
		name = (char*)malloc( 40*sizeof(char) );
		scanf("%s %s", name, tel );
		addPeople( list, name, tel );
//		printf("----------%s %S %d\n", id, name, grade );
	}
	tel = (char*)malloc( 12*sizeof(char) );
	name = (char*)malloc( 40*sizeof(char) );
	scanf("%s %s", name, tel );

	find( list, name, tel );
	
	
	return 0;
}
