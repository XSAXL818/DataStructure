#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define maxSize 10000
typedef struct{
	char* name;
	int isNode;
} _Tree;

typedef struct{
	_Tree* tree;
	int maxLen;
} Tree;

Tree* creatTree(void);
void addChildren( Tree* tree, char* parent, char* c1, char* c2 );

int main(){
	Tree* tree = creatTree();
	int num;
	FILE* in = fopen( "in.txt", "r" );
	fscanf( in, "%d", &num );
	char parent[21];
	char c1[21];
	char c2[21];
	
	while( num >0 ){
		fscanf( in, "%s %s %s", parent, c1, c2 );
		addChildren( tree, parent, c1, c2 );
		num--;
	}
	
//	int i;
//	for( i = 1; i < tree->maxLen; i++ ){
//		if( tree->tree[i].isNode ){
//			printf("%s\n",tree->tree[i].name);
//		}
//	}
	int i;
	int child1 = 0;
	int child2 = 0;
	scanf("%s %s",c1,c2);
	for( i = 1; i <= tree->maxLen; i++ ){
		if( tree->tree[i].isNode ){
			if( strcmp( c1, tree->tree[i].name ) == 0 ){
				child1 = i;
			}
			if( strcmp( c2, tree->tree[i].name ) == 0 ){
				child2 = i;
			}
		}
	}

	int t1 = child1;
	int t2 = child2;
	int h1 = 0;
	int h2 = 0;
	while( t1 >= 1 ){
		h1++;
		t1 /= 2;
	}
	while( t2 >= 1 ){
		h2++;
		t2 /= 2;
	}
	if( h1 == h2 ){// 同辈
		
		int parent = 2;
		while( child1/parent != child2/parent && tree->tree[parent].isNode ){
			parent *= 2;
		}
		parent = child1/parent;
		int t3 = parent;
		int h3 = 0;
		while( t3 >= 1 ){
			h3++;
			t3 /= 2;
		}
		printf("%s %s %d\n",tree->tree[parent].name, tree->tree[child1].name, h1 - h3 );
		printf("%s %s %d\n",tree->tree[parent].name, tree->tree[child2].name, h2 - h3 );
	} else {
	if( child1 < child2 ){// 小辈放前
		int t = child1;
		child1 = child2;
		child2 = t;
		
		t = h1;
		h1 = h2;
		h2 = t;
	}
		printf("%s %s %d", tree->tree[child1].name, tree->tree[child2].name, h1 - h2 );
	}

	return 0;
}


Tree* creatTree(){
	Tree* tree = (Tree*)malloc( sizeof( Tree ) );
	tree->tree = (_Tree*)malloc( sizeof( _Tree ) * maxSize );
	int i;
	for( i = 1; i < maxSize; i++ ){
		tree->tree[i].isNode = 0;
	}
	tree->maxLen = 0;
	return tree;
}
void addChildren( Tree* tree, char* parent, char* c1, char* c2 ){
	int i;
	for( i = 1; i <= tree->maxLen; i++ ){
		if( tree->tree[i].isNode ){
			if( strcmp( parent, tree->tree[i].name ) == 0 ){
				break;
			}
		}
	}
	if( i > tree->maxLen ){// 没找到,即第一次插入
		tree->tree[i].name = (char*)malloc( (strlen(parent) + 1) * sizeof( char ) );
		strcpy( tree->tree[i].name, parent );
		tree->tree[i].isNode = 1;
	}
	tree->tree[2*i].name = (char*)malloc( (strlen(c1) + 1) * sizeof( char ) );
	strcpy( tree->tree[2*i].name, c1 );
	tree->tree[2*i].isNode = 1;
	if( 2*i > tree->maxLen ){
		tree->maxLen = 2*i;
	}
	if( strcmp( c2, "NULL" ) != 0 ){
		tree->tree[2*i+1].name = (char*)malloc( (strlen(c2) + 1) * sizeof( char ) );
		strcpy( tree->tree[2*i+1].name, c2 );
		if( tree->maxLen < 2*i+1 ){
			tree->maxLen = 2*i+1;
		}
		
		tree->tree[2*i + 1].isNode = 1;
	}
	
}
