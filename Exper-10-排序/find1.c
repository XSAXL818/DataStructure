#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#define ID 20
typedef struct{
	char* id;
	char* name;
	int grade;
} Student;
typedef struct{
	int len;
	Student* students;
} *GList,Node;
GList creatGList( int maxSize ){
	GList list = (GList)malloc( sizeof(Node) );
	list->len = 0;
	list->students = (Student*)malloc( maxSize * sizeof(Student) );
	return list;
}
void addStudent( GList list, char* id, char* name, int grade ){
	Student* stu = list->students + list->len;
	stu->grade =grade;
	stu->id = id;
	stu->name = name;
	list->len++;
}
int binSearch( Student* students, int len, char* key ){
	int low = 0;
	int high = len-1;
	int mid;
	while( low <= high ){
		mid = ( low + high ) / 2; //                                     0           1            2           3              4
		printf("%d ",mid);//                                           X11         X12           X14        X23            X44
		int ret = strcmp( key, students[mid].id );//      find 15       low                      mid                       high
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
void find( GList list, char* id, char* name, int grade ){
	int index = binSearch( list->students, list->len, id );
	printf("\n");
	if( index != list->len && strcmp( id, list->students[index].id ) == 0 ){
		if( list->students[index].grade == grade ){
			printf("F ");
		} else {
			list->students[index].grade = grade;
			printf("U ");
		}
	} else {
		int i;
		for( i = list->len; i > index; i-- ){
			list->students[i] = list->students[i-1];
		}
		list->students[i].grade = grade;
		list->students[i].id = id;
		list->students[i].name = name;
		printf("I ");
	}
	printf("%d",index);
}
int main(){
	
	int num,grade;
	char *id,*name;
	int i;
	scanf("%d",&num);
	GList list = creatGList( 200 );
	for( i = 0; i < num; i++ ){
		id = (char*)malloc( ID*sizeof(char) );
		name = (char*)malloc( 40*sizeof(char) );
		scanf("%s %s %d ", id, name, &grade );
		addStudent( list, id, name, grade );
//		printf("----------%s %S %d\n", id, name, grade );
	}
	id = (char*)malloc( ID*sizeof(char) );
	name = (char*)malloc( 40*sizeof(char) );
	scanf("%s %s %d ", id, name, &grade );

	find( list, id, name, grade );
	
	
	return 0;
}


