#include <stdio.h>

typedef struct{
	char arr[50];
	int top;
} Stack;

void pop( Stack* stack, int num ){
	stack->arr[++stack->top] = num;
}
int push( Stack* stack ){
	return stack->arr[stack->top--];
}

int main(){
	
	Stack stack;
	stack.top = -1;
	int num;
	scanf("%d",&num);
	if( num == 0 ){
		pop( &stack, '0' );
	}
	while( num > 0 ){
		char c = num%16;
		if( c >= 0 && c <= 9 ){
			pop( &stack, '0' + c );
		} else {
			pop( &stack, 'A' + c - 10 );
		}
		num /= 16;
	}
	while( stack.top >= 0 ){
		printf("%c",push( &stack ));
	}
	return 0;
}