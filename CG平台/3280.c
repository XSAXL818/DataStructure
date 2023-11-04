#include <stdio.h>
#include <string.h>

int main(){
	
	// 为1则为可能的名次
	int A[5] = {1,1,1,1,1};
	int B[5] = {1,1,1,1,1};
	int C[5] = {1,1,1,1,1};
	int D[5] = {1,1,1,1,1};
	int E[5] = {1,1,1,1,1};
	int *p[5] = { A, B, C, D, E };
	int i;// 同时i为偶数则说明该人说假话
	int j;
	for( i=0; i < 5; i++ ){
		// 依次处理A,B,C,D,E
		char str[5];
		scanf("%s",str);
		// 判断关系运算符是否为一个
		int num;
		if( str[3] == '\0' ){
			// 判断是否说假话
			num = str[2]-48;// 关系符后的数字
			if( i%2 == 0 ){ // 假话
				if( str[1] == '=' ){
					(p[i])[num-1] = 0;
				} else if( str[1] == '>' ){
					int t;
					for( t=4; t > num-1; t-- ){
						(p[i])[t] = 0;
					}
				} else {
					int t;
					for( t=4; t >= num-1; t-- ){
						(p[i])[t] = 0;
					}
				}
			} else {// 真话
				if( str[1] == '=' ){
					int t;
					for( t=0; t < num-1; t++ ){
						(p[i])[num-1] = 0;
					}
					for( t++; t < 5; t++ ){
						(p[i])[num-1] = 0;
					}
				} else if( str[1] == '>' ){
					int t;
					for( t=0; t < num-1; t++ ){
						(p[i])[t] = 0;
					}
				} else {
					int t;
					for( t=num-1; t < 5; t++ ){
						(p[i])[t] = 0;
					}
				}
			}
		} else {// 两个运算符
			num = str[3]-48;
			// 判断真假话
			if( i%2 == 0 ){//假
				if( str[1] == '!' ){
					int t;
					for( t=0; t < num-1; t++ ){
						(p[i])[t] = 0;
					}
					for( t++; t < 5; t++ ){
						(p[i])[t] = 0;
					}
				} else if( str[1] == '>' ){
					int t;
					for( t=0; t < num; t++ ){
						(p[i])[t] = 0;
					}
				} else {
					int t;
					for( t=0; t < num; t++ ){
						(p[i])[t] = 0;
					}
				}
			} else {// 真
				if( str[1] == '!' ){
					(p[i])[num-1] = 0;
				} else if( str[1] == '>' ){
					int t;
					for( t=0; t < num-1; t++ ){
						(p[i])[t] = 0;
					}
				} else {
					int t;
					for( t=0; t < num; t++ ){
						(p[i])[t] = 0;
					}
				}
			}	
		}
		if( p[0] == A ){
			printf("--%d--\n",i);
		}
	}
	for( i=0; i < 5; i++ ){
		for( j=0; j < 5; j++ ){
			printf("%d ",(p[i])[j]);
		}
		printf("\n");
	}

	return 0;
}