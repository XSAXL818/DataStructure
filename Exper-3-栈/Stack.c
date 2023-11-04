#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define ElemType int 
#define Status int
#define ERROR 0
#define OK 1
// 顺序存储
typedef struct{
	ElemType *data;
	int top;
	int maxSize;
} Stack;
// 初始化栈
Status InitStack( Stack* stack, int maxSize );
//判断栈是否为空
Status isEmpty( Stack* stack );
// 将元素压入堆栈
Status Push( Stack* stack, ElemType e );
// 遍历堆栈元素
void printStack( Stack* stack );
// 判断堆栈是否已满
Status isFull( Stack* stack );
// 出栈：删除并返回栈顶元素
ElemType Pop( Stack* stack );
// 十进制转换为八进制
int conversion( int num );
// 清栈
void clearStack( Stack* stack );
// 获取栈顶元素
ElemType getTop( Stack* stack );
//  图形化界面
// 菜单
int view( Stack* stack );


int main(){
	
	Stack stack;
	InitStack( &stack, 10 );
	
	while( 1 ){
		int select = view( &stack );
//		1.入栈   2.出栈   3.获取栈顶元素   4.判空   5.判满  6.进制转换(10->8)
		ElemType e;
		switch( select ){
			case 1:
				printf("请输入新元素：");
				scanf("%d",&e);
				if( Push( &stack, e ) ){
					printf("\n****入栈成功！****\n");
				} else {
					printf("\n****入栈失败！****\n");
				}
				break;
			case 2:
				e = Pop( &stack );
				printf("\n****%d已出栈!****\n",e);
				break;
			case 3:
				if( isEmpty( &stack) ){
					printf("\n****堆栈为空!****\n");
				} else {
					printf("\n****堆栈不为空!****\n");
				}
				break;
			case 4:
				if( isEmpty( &stack ) ){
					printf("栈空！\n");
				} else {
					printf("栈顶元素为：%d\n",getTop( &stack ));
				}
				break;
			case 5:
				if( isFull( &stack) ){
					printf("\n****堆栈已满！****\n");
				} else {
					printf("\n****堆栈未满！****\n");
				}
				break;
			case 6:
				printf("请输入一个十进制数：");
				int num;
				scanf("%d",&num);
				num = conversion( num );
				printf("八进制为：%d\n",num);
				break;
		}
	}
	
	return 0;
}



// 初始化栈
Status InitStack( Stack* stack, int maxSize ){
	if( stack == NULL || maxSize < 1 ){
		return ERROR;
	}
	stack->data = (ElemType*)malloc( sizeof(ElemType) * maxSize );
	if( stack == NULL ){
		return ERROR;
	}
	stack->maxSize = maxSize;
	stack->top = -1;
	return OK;
}
//判断栈是否为空
Status isEmpty( Stack* stack ){
	if( stack == NULL ){
		return ERROR;
	}
	if( stack->top == -1 ){
		return OK;
	}
	
	return ERROR;	
}
// 将元素压入堆栈
Status Push( Stack* stack, ElemType e ){
	if( stack == NULL ){
		return ERROR;
	}
	// 堆栈已满
	if( stack->maxSize == stack->top+1 ){
		return ERROR;
	}
	// 压栈
	stack->top++;
	stack->data[stack->top] = e;
	return OK;
}
// 遍历堆栈元素
void printStack( Stack* stack ){
	int i;
	for( i = stack->top; i > -1; i-- ){
		printf("‖%3d‖\n",stack->data[i]);
	}
	printf(" ¯¯¯¯¯\n");
//	––—————‗¯¯¯¯¯¯|‖‖‖‖‖⁞⁞⁞……
}
// 判断堆栈是否已满
Status isFull( Stack* stack ){
	// stack != NULL 则程序往下进行，否则报错
	assert( stack != NULL );
	if( stack->maxSize == stack->top+1 ){
		return OK;
	}
	return ERROR;
}
// 出栈：删除并返回栈顶元素
ElemType Pop( Stack* stack ){
	assert( stack != NULL );
	assert( stack->top != -1 );

	return stack->data[stack->top--];
}

//  菜单
int view( Stack* stack ){
	if( !isEmpty( stack ) ){
		printf("\n");
		printStack( stack );
	}
	printf("------------------------------\n1.入栈\t2.出栈\t3.判空\t4.获取栈顶元素\t5.判满\t6.进制转换(10->8)\n------------------------------\n");
	printf("请输入所选功能的序号：");
	int select;
	scanf("%d",&select);
	return select;
}
// 清栈
void clearStack( Stack* stack ){
	free( stack->data );
	free( stack );
}
// 十进制转换为八进制
int conversion( int num ){
	
	Stack* stack = (Stack*)malloc( sizeof(Stack) );
	InitStack( stack , 20 );
	while( num > 0 ){
		Push( stack, num%8 );
		num /= 8;
	}
	int sum = 0;
	while( !isEmpty( stack ) ){
		sum *= 10;
		sum += Pop( stack );
	}
	clearStack( stack );
	return sum;
	
}
// 获取栈顶元素
ElemType getTop( Stack* stack ){
	return stack->data[stack->top];
}

