#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _Node{
	char* str;
	struct _Node* next;
} LNode,*List;

void add( List list, char* str ){
	if( list->next == NULL ){
		LNode* node = (LNode*)malloc( sizeof( LNode ) );
		node->next = NULL;
		node->str = str;
		list->next = node;
	} else {
		while( list->next != NULL ){
			list = list->next;
			if( strcmp( str, list->str ) == 0 ){
				return ;
			} else if( strcmp( str, list->str ) > 0 ) {
				
			} else {
				LNode* node = (LNode*)malloc( sizeof( LNode ) );
				node->str = list->str;
				node->next = list->next;
				list->str = str;
				list->next = node;		
				return;
			}
		}
		LNode* node = (LNode*)malloc( sizeof( LNode ) );
		node->str = str;
		node->next = NULL;
		list->next = node;
	}
}

void printList( List list, FILE* fp ){
	while( list->next ){
		list = list->next;
		fputs( list->str, fp );
		fputs( " ", fp );
	}
}
int main(int argc,char** argv){
	
//	FILE* in = fopen( "sort.in.txt", "r" );
//	FILE* out = fopen( "sort.out.txt", "w" );
	FILE* in = fopen( argv[1], "r" );
	FILE* out = fopen( argv[2], "w" );
	List list = (List)malloc( sizeof( LNode ) );
	list->next = NULL;
	char* str = (char*)malloc( 100 * sizeof( char ) );
	while( fscanf( in, "%s", str ) != EOF ){//fscanf( in, "%s", str ) != EOF
		add( list, str );
		str = (char*)malloc( 100 * sizeof( char ) );
	}

	printList( list, out );
	
	
	
	
	return 0;
}