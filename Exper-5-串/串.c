#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define Status int
#define OK 1
#define ERROR 0

// 串，堆存储
// 成员变量：str指向堆分配的空间  length串的长度
// 串的初始化即空串的条件 str=NULL length=0
typedef struct{
	char* str;
	int length;// 字符串长度
} String;
// 创造一个初始化了的空串
String* creatString(void);
//生成一个与 传入的字符串常量 等值的串
Status StrAssign( String* string, char* str );
// 获取串长度,-1说明输入错误
int getLength( String* string );
// 比较大小
int StrCompare( String* string1, String* string2 );
// 输出字符串
void printString( String* string );
// 清为空串
Status clearString( String* string );
// 将src1,src2前后链接后赋值给dest
Status Concat( String* dest, String* src1, String* src2 );
// 从src的第pos个字符开始，求往后len个字符串赋值给dest
// "123456" 2 3  得字串"234"
Status SubString( String* dest, String* src, int pos, int len );
// 求字串位置：即模式匹配  从src的第pos的位置开始，查找dest在src中第一次出现的位置,未找到返回0
// 只使用五大基础操作实现
int Index1( String* src, String* dest, int pos );
// 较优版本
int Index2( String* src, String* dest, int pos );
// 模式匹配的改进版
int IndexKMPByMySelf( String* src, String* dest, int pos );
// 模式匹配-KMP
int getNext( String* dest, int next[] );
int getNextval( String* dest, int nextval[] );
int IndexKMP( String* src, String* dest, int pos );

// 界面化设计
// 菜单
int view( String* strings[], int length );


int main(){
	
	String* strings[10];// 用于保存串
	int length = 2; // 串的个数
	String* string1 = creatString();// 二进制文本
	StrAssign( string1, "000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001");
//StrAssign( string1, "00000000000001000000100000010001 00000000000000000000000011100001 00000000000000000000000000001100 00000000010000000000000000000110 "
//"00000000000000000000100000000000 00000000000000000000100000100100 00000000001000000010000000100001 00000000001000010010100100001000 "
//"00000000000000000000100000000000 00000000000000000000100000100100 00000000000000000000000000000001 00000000000000000000000000000000");
	String* string2 = creatString();// 英文文本
	StrAssign( string2, "On January 3rd newspapers carried reports of large seizures of pirated “Super Mario Bros.”."
" The seizure took place in the parking lot of a resident of a middleman who also handled used software for video game consoles."
" Judging by this report, Tomohiko thinks the middleman is Matsuura.abaabc"
" The whereabouts of Matsuura are unknown, and the police believe that the suspects and the sources of the pirated software are most likely linked to the Mafia,"
" but there are no other clues and no mention of Tongyuan at all.");
	strings[0] = string1;
	strings[1] = string2;
	int select;
	String* tString;
	char str[50] = {'\0'};
	int n1,n2,dic,pos,len,index;
	while( 1 ){
		int select = view( strings, length );
	// 1.串赋值 2.串比较 3.串链接 4.求子串 5.查子串 6.串清除 7.退出
		switch( select ){
			case 1:
				printf("------请输入你想要输入的文本：------\n");
				scanf("%s",str);
				tString = creatString();
				if( StrAssign( tString, str ) ){
					printf("------      输入成功！        ------\n\n");
					strings[length++] = tString;
				} else {
					printf("------输入错误！------\n\n");
				}
				break;
			case 2:
				printf("------请输入你要比较的两个字符串的序号：------\n");
				scanf("%d %d",&n1,&n2);
				dic = StrCompare( strings[n1-1], strings[n2-1] );
				if( dic == 0 ){
					printf("------串值相等------\n\n");
				} else {
					printf("------序号为%d的串值大------\n\n",dic > 0 ? n1 : n2 );
				}
				break;
			case 3:
				printf("------请输入你要链接的两个字符串的序号：------\n");
				scanf("%d %d",&n1,&n2);	
				tString = creatString();
				if( Concat( tString, strings[n1-1], strings[n2-1] ) ){
					printf("------链接成功------\n\n");
					strings[length++] = tString;
				} else {
					printf("------链接失败------\n\n");
				}
				break;
			case 4:
				printf("------请输入主串的序号：------\n");
				scanf("%d",&n1);
				printf("------请输入开始的位置：------\n");
				scanf("%d",&pos);
				printf("------请输入子串的长度：------\n");
				scanf("%d",&len);
				tString = creatString();
				if( SubString( tString, strings[n1-1], pos, len ) ){
					printf("------操作成功！------\n\n");
					strings[length++] = tString;
				} else {
					printf("------操作失败！------\n\n");
				}
				break;
			case 5:
				printf("------请输入你要查询的主串的序号：------\n");
				scanf("%d",&n1);
				printf("------请输入你要查的子串：------\n");
				scanf("%s",str);
				tString = creatString();
				StrAssign( tString, str );
				printf("------请输入开始的位置：------\n");
				scanf("%d",&pos);
				printf("****************朴素模式匹配**************\n");
				index = Index2( strings[n1-1], tString, pos );
				if( index > 0 ){
					printf("------子串第一次出现的位置为：%d------\n",index);
				} else {
					printf("------未找到!------\n");
				}
				printf("******************************************\n\n");
				printf("************模式匹配改进版-KMP************\n");
//				index = IndexKMPByMySelf( strings[n1-1], tString, pos );
				index = IndexKMP( strings[n1-1], tString, pos );
				if( index > 0 ){
					printf("------子串第一次出现的位置为：%d------\n",index);
				} else {
					printf("------未找到!------\n");
				}
				printf("******************************************\n\n");
				clearString( tString );
				break;
			case 6:
				printf("------请输入要清除的串的序号：------\n");
				scanf("%d",&n1);
				if( clearString( strings[n1-1] ) ){
					printf("已赋为空串!\n");
				} else {
					printf("操作失败!\n");
				}
	
				break;
		}
		if( select == 7 ){
			break;
		}
	}
	
	return 0;
}

// 创造一个初始化了的空串
String* creatString(void){
	String* string = (String*)malloc( sizeof(String) );
	string->length = 0;
	string->str = NULL;
	return string;
}
//生成一个与 传入的字符串常量 等值的串
Status StrAssign( String* string, char* str ){
	// 保证参数传入正确
	if( string == NULL || str == NULL ){
		return ERROR;
	}
	// 释放原有空间
	if( string->str ){
		free( string->str );
	}
	// 获取 字符串常量 长度
	int length = 0;
	while( str[length] != '\0' ){	
		length++;
	}
	// 传入的是空串
	if( length == 0 ){
		return OK;
	}
	// 分配空间
	string->str = (char*)malloc( length*sizeof(char) );
	if( string->str == NULL ){
		return ERROR;
	}
	string->length = length;
	// 赋值
	while( --length >= 0 ){
		string->str[length] = str[length];
	}
	return OK;
}
// 获取串长度,-1说明输入错误
int getLength( String* string ){
	if( string == NULL ){
		return -1;
	}
	return string->length;
}
// 比较大小
int StrCompare( String* string1, String* string2 ){
	// 输入错误
	assert( string1 != NULL );
	assert( string2 != NULL );
	int i = 0;
	// 依此比较
	while( i < string1->length && i < string2->length ){
		if( (string1->str[i] != string2->str[i]) ){
			return string1->str[i] - string2->str[i];
		}
		i++;
	}
	// 当未比较出结果
	// 1.其中一个空串 2.两个空串 3.存在字串：123 12345
	return string1->length - string2->length;
}
// 输出字符串
void printString( String* string ){
	assert( string != NULL );
	int i = 0;
	while( i < string->length ){
		printf("%c",string->str[i]);
		i++;
	}
}
// 清为空串
Status clearString( String* string ){
	if( string == NULL ){
		return ERROR;
	}
	if( string->str ){
		free( string->str );
	}
	string->length = 0;
	return OK;
}
// 将src1,src2先后链接后赋值给dest
Status Concat( String* dest, String* src1, String* src2 ){
	if( dest == NULL || src1 == NULL || src2 == NULL ){
		return ERROR;
	}
	// 新串长度,两个都是空串则dest置为空串
	int length = src1->length + src2->length;
	if( dest->str ){
		free( dest->str );
	}
	if( length == 0 ){
		dest->length = 0;
		dest->str = NULL;
		return OK;
	}
	// 分配空间
	dest->str = (char*)malloc( length*sizeof(char) );
	if( dest->str == NULL ){
		return ERROR;
	}
	dest->length = length;
	// 赋值先src1 后 src2
	int i;
	// src1  若空串则越过
	for( i = 0; i < src1->length; i++ ){
		dest->str[i] = src1->str[i];
	}
	// src2
	for( ; i < length; i++ ){
		dest->str[i] = src2->str[i-src1->length];
	}	
	return OK;
}
// 从src的第pos位置开始，求往后len个字符串赋值给dest
Status SubString( String* dest, String* src, int pos, int len ){
	// 判断输入串的正确
	if( dest == NULL || src == NULL ){
		return ERROR;
	}
	// 判断 位置与长度 
	if( pos <= 0 || pos > (src->length + 1 - len) || len <= 0 ){
		return ERROR;
	}
	// 求字串
	// 释放dest的原有空间
	if( dest->str ){
		free( dest->str );
	}
	// 赋值字串
	dest->length = len;
	dest->str = (char*)malloc( len*sizeof(char) );
	int i;
	for( i = 0; i < len; i++ ){
		dest->str[i] = src->str[pos-1+i];
	}
	return OK;
}
// 求字串位置：即模式匹配  从src的第pos的位置开始，查找dest在src中第一次出现的位置,未找到返回0
// 只使用五大基础操作实现
int Index1( String* src, String* dest, int pos ){
	// 判断输入,使pos在有效范围内即使用 SubString 返回不是ERROR
	if( src == NULL || dest == NULL || pos < 1 || pos > src->length-dest->length + 1 ){
		return ERROR;
	}
	// 找子串
	int i;
	String* t = creatString();
	for( i = pos; i <= src->length-dest->length+1; i++ ){
		// 将找出来的子串与目标字串对比,找到则跳出循环
		SubString( t, src, i, dest->length);
		if( StrCompare( dest, t ) == 0 ){
			return i;
		}
	}
	return ERROR;
}
// 模式匹配较优版本 :最坏情况下 src="0000000000000001" dest="000001" 时间复杂度O(N*M)
// 一般情况下时间复杂度接近O(N+M),所以至今仍在采用
int Index2( String* src, String* dest, int pos ){
	// 判断输入是否合法
	if( src == NULL || dest == NULL ){
		return 0;
	}
	// 使pos的值在合法的区间,存在一个空串则返回未找到
	if( pos < 1 || pos > src->length - dest->length + 1 || src->length == 0 || dest->length == 0 ){
		return 0;
	}
	// 开始遍历
	int i;
	int cnt = 0;// 计数器
	for( i = pos-1; i <= src->length - dest->length+1; i++ ){
		// 每次从i的位置找子串
		int j = 0;// 每次为dest的一个字符下标
		// 开始比较
		while( j < dest->length ){
			cnt++;
			if( src->str[i] == dest->str[j] ){// 当前字符相等则同时后移一位
				i++;
				j++;
			} else {// 找到不同则使i回到开始对比前位置的并退出
				i -= j;// i 加了j次1
				break;
			}
		}
		// 如果走到此且 j == dest->length 说明找到字串
		if( j == dest->length ){
			printf("------共执行%d次循环!\n",cnt);
			return i-j+1;
		}
	}
	printf("------共执行%d次循环!\n",cnt);
	return 0;
}
// 模式匹配的改进版
//  001000000000000000000001  0001
int IndexKMPByMySelf( String* src, String* dest, int pos ){
	if( src == NULL || dest == NULL ){
		return 0;
	}
	if( dest->length == 0 ){
		return 0;
	}
	// 求dest的前几个字符相同的数目
	int dLen = 0;
	while( dest->str[0] == dest->str[dLen] ){
		dLen++;
	}
	// 如果第一个字符和第二个字符相同，则按原先方法比较
//	if( dLen == 1 ){
//		return Index2( src, dest, pos );
//	}
	// 针对000021001
	//      00021 方法优化
	int i=0;
	int j = 0;
	int cnt = 0;// 计数器
	while( i < src->length ){	
		while( j < dest->length ){
			cnt++;
			
			if( src->str[i] == dest->str[j] ){ // 匹配相等则同时后移
				i++;
				j++;
			} else { // 匹配不成功，判断i是否回溯以及回溯几位,共三大种情况
				if( j < dLen ){ // 主：01000  对应此情况,i不回溯，且j也回到0
					i++;        // 子：0001
					j=0;								//                       1        2
				} else if( j == dLen ){    				// 此情况又为两种: 主：  000002   000020      
					if( src->str[i] == dest->str[0] ){  // 		    	   子：  00002    00001
						i++; // 针对1，需要对i不需回溯,j保持原位         dLen=4  i=j=4   i=j=4
					} else { // 针对2，i不需要回溯,j置为0
						i++; 
						j = 0;
					}
				} else {			 				// 主:  0101010200011012000
					i = i - (j-dLen) + 1; 		    // 子： 010102
					j=0; // 此时i=j=7 dLen=5,
				}
				break;	
			}
		}	
		// 找到子串
		if( j == dest->length ){
			break;
		}
	}
	printf("------共执行%d次循环！\n",cnt);
	if( j == dest->length ){
		return i-dest->length+1;
	}
	return 0;
}
// 模式匹配的getNext(),即当dest的下标为j的字符匹配不成功,netx[j] 的值即为 j 该回溯的位置
int getNext( String* dest, int* next ){
	int i = 0,j = 0;// i   j
	next[0] = 0;//    														abababc               abababc
	int cnt = 0;
	while( i < dest->length ){							//                  ba                    ababac
		cnt++;
		if( j == 0 || dest->str[i] == dest->str[j-1] ){// 对应两个情况：首次匹配失败      下标为i(4)匹配失败                   ababa  
		 	i++;										   //              j=1 则next[i] = 1    j=max{前缀子串与后缀子串重叠长度}  j=2 
		 	j++;											// 									i=
		 	next[i] = j;									// abaabc
		} else {
			j = next[j-1];
		}
	}
	return cnt;
}
// getNext改进版getNextval
int getNextval( String* dest, int nextval[] ){
	int i = 0,j = 0;
	nextval[0] = 0;
	int cnt = 0;
	while( i < dest->length ){
		if( j == 0 || dest->str[i] == dest->str[j-1] ){
			i++;
			j++;
			if( dest->str[i] != dest->str[j-1] ){
				nextval[i] = j;
			} else {
				nextval[i] = nextval[j-1];
			}
		} else {
			j = nextval[j-1];
		}
	}
	printf("nextval: ");
	for( i=0; i < dest->length; i++ ){
		printf("%d ",nextval[i]);
	}
	printf("\n");
	return cnt;
}


// 模式匹配-KMP
int IndexKMP( String* src, String* dest, int pos ){
	// 判断输入是否合法
	if( src == NULL || dest == NULL ){
		return 0;
	}
	if( dest->length == 0 || pos < 1 || pos > (src->length - dest->length + 1) ){
		return 0;
	}
	int cnt = 0;

//	int next[dest->length];
	int i=pos-1,j=0;
	int next[dest->length];
	int *p = next;
//	cnt = getNext( dest, next );
	cnt = getNextval( dest, next );
//  	printf("p=%p\n",next);
	// i,j控制在正确范围内,当跳出循环时，若j == dest->length,则说明找到，否则即未找到
	while( i < src->length && j < dest->length ){
		cnt++;
		if( src->str[i] == dest->str[j] ){ // 匹配成功同时后移
			i++;
			j++;
		} else { // 匹配不成功，则i不回溯,j获取next
			j = next[j]-1;
			if( j == -1 ){
				i++;
				j++;
			}
		}
	}
	printf("--------共循环了%d次\n",cnt);
	if( j == dest->length ){ // +1 是因为i表示的是src串的下标,而位置因从1开始
		return i - dest->length + 1;
	}
	return 0;
}
// 菜单
int view( String* strings[], int length ){
	printf("**************************\n");
	int i;
	printf("序号\t串长\t文本数据\n\n");
	for( i = 0; i < length; i++ ){
		printf("%d\t%d\t",i+1,strings[i]->length);
		printString( strings[i] );
		printf("\n\n");
	}
	printf("**************************\n");
	printf("请输入要选择功能的序号：\n");
	printf("1.串赋值 2.串比较 3.串链接 4.求子串 5.查子串 6.串清除 7.退出\n");
	int select;
	scanf("%d",&select);
	return select;
}




