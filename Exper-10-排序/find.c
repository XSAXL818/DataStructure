#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#define NHASH  3001

#define MULT  37

int hash(char *str)
{
       unsigned int h=0;
       char *p;
       for(p=str; *p!='\0'; p++){
    	   	h = MULT*h + *p;
	   }	
       return h % NHASH;
}

int cnt1 = 0;
int cnt2 = 0;
int cnt3 = 0;
int cnt4 = 0;

int find1( char* words[], int len, char* word  ){
	int i;
	for( i = 0; i < len; i++ ){
		cnt1++;
		int ret = strcmp( words[i], word );
		if( ret == 0 ){
			return 1;
		} else if( ret > 0 ){
			return 0;
		}
	}
	return 0;
}
int binSearch( char* arr[], int length, char* value ){
	int low = 0;
	int hight = length-1;
	int mid;
	do{
		cnt2++;
		mid = (low+hight)/2;
		int ret = strcmp( arr[mid], value );
		if( ret == 0 ){
			break;
		} else if( ret < 0 ){
			low = mid+1;
		} else {
			hight = mid-1;
		}
	}while( low <= hight );
	
	if( low > hight ){
		return 0;
	} else {
		return 1;
	}
}

typedef struct{
	char c;
	int start;// 起始位置
	int num;// 单词个数
} *Index,Node;
Index list1;
Index creatIndex( char* words[], int len ){
	char c = 'a';
	int iLen = 0;
	Index list = (Node*)malloc( 26*sizeof(Node) );
	int start = 0;
	int num = 0;
	int i;
	for( i = 0; i < len; i++ ){
		if( c == (words[i])[0] ){
			num++;
		} else {
			list[iLen].c = c;
			list[iLen].start = start;
			list[iLen++].num = num;
			start += num;
			num = 0;
			c++;
			i--;
		}
	}
	list1 = list;
	return list;
}
// 找到数在索引表应在分块的下标---二分查找
int binSearch1( Index list, char* key ){
	
	
	int low = 0,high = 25;
	int mid;
	do{
//		cnt3++;
		mid = ( low + high ) / 2;
		int ret = strcmp( &(list[mid].c), key );
		if( ret < 0 ){
			low = mid + 1;
		} else if( ret > 0 ){
			high = mid - 1;//           0     1    2     3      4
		} else {//                     60    70    80    90    100  
			return mid;//    65                    2
		}//								0	
	}while( low <= high );//                  1
	//    		                         high  low
//	printf("********%d %d\n", low, high);
	return high;// data在low所指定的块内
	
}

int binSearch2( char* arr[], int length, char* value ){
	int low = 0;
	int hight = length-1;
	int mid;

	while( low <= hight ){
		cnt3++;
		mid = (low+hight)/2;
		int ret = strcmp( arr[mid], value );
		if( ret == 0 ){
			break;
		} else if( ret < 0 ){
			low = mid+1;
		} else {
			hight = mid-1;
		}
	}
	
	if( low > hight ){
		return 0;
	} else {
		return 1;
	}
}

int find3( char* words[], int len, char* str ){
	Index list = creatIndex( words, len );
	int index = binSearch1( list, str );
//	printf("%s %c....\n",str, list[index].c);
	return binSearch2( words + list[index].start, list[index].num, str );
}


typedef struct _Node{
	char* str;
	struct _Node* next;
} *List,LNode;

List creatList(void){
	List list = (List)malloc(sizeof(LNode));
	list->next = NULL;
	return list;
}
// 头插，倒序遍历字典,简易实现冲突时按字典顺序
void add( List list, char* str ){
	LNode* node = (LNode*)malloc(sizeof(LNode));
	node->str = str;
	node->next = list->next;
	list->next = node;
}
// 创建哈希表，一维链表数组
List* creatHashList( char* words[], int len ){
	List* hashList = (List*)malloc( NHASH * sizeof(List) );
	int i;
	for( i = 0; i < NHASH; i++ ){// 初始化
		hashList[i] = creatList();
	}
	int hashCode;
	for( i = len-1; i >= 0; i-- ){// 倒序
		hashCode = hash( words[i] );
		add( hashList[hashCode], words[i] );
	}
	return hashList;
}

int find4( List* hashList, char* str ){
	int hashCode = hash( str );
	LNode* start = hashList[hashCode]->next;
	while( start ){
		cnt4++;
		int ret = strcmp( str, start->str );
		if( ret == 0 ){
			return 1;
		} else if( ret < 0 ){
			return 0;
		}
		start = start->next;
	}
	return 0;
}


int main(){
	
	char* words[3500];
	int len = 0,end;
	char* word;
	char str[40];
	FILE* in = fopen( "dictionary3000.txt", "r" );
	List* hashList;
//	int i;
//	char str[20];
//	for( i = 0; i < 3500; i++ ){
//		fscanf( in, "%s", str);
//		printf("%s\n",str);
//	}
	while( 1 ){
		end = fscanf( in, "%s", str );
		if( end == EOF ){
			break;
		}
		word = (char*)malloc( strlen(str)*sizeof(char) );
		strcpy( word, str );
		words[len++] = word;
//		printf("%s\n",word);
	}
	int cnt,select,ret;
	scanf("%s %d",str,&select);
	int i;
//	Index list = creatIndex( words, len );
//	for( i = 0; i < 26; i++ ){
//		printf("%c %d %d\n",list[i].c, list[i].num, list[i].start );
//	}
	switch( select ){
		case 1:
			ret = find1( words, len, str );
			cnt = cnt1;
//			printf("****1\n");
			break;
		case 2:
			ret = binSearch( words, len, str );
			cnt = cnt2;
//			printf("****2\n");
			break;
		case 3:
			
			ret = find3( words, len, str );
//			printf("%s\n",str);
//			for( i = 0; i < 10; i++ ){
//				printf("%c %d %d\n",list1[i].c, list1[i].num, list1[i].start );
//			}
//			printf("****3\n");
			cnt = cnt3;
			break;
		case 4:
			hashList = creatHashList( words, len );
			ret = find4( hashList, str );
			cnt = cnt4;
			break;
	}
	
	printf("%d %d",ret, cnt );
	return 0;
}


