#include <stdio.h>
#include <stdlib.h>

#define maxSize 12500 // 矩阵储存非零元最大个数
#define Status int 
#define OK 1
#define ERROR 0
// 三元组的一个结点
typedef struct{
	int i;// 行
	int j;// 列
	int value;// 值
} TNode; 
// 三元组表示的矩阵
typedef struct{
	int row;// 矩阵的行数
	int col;// 列数
	int num;// 非零元个数
	int* rpos;// rpos[i]的值 表示为矩阵第i行首个非零元素出现的位置
	TNode* data;
} TSMatrix; // 三元顺序组形式的矩阵
// 创建一个矩阵,形参数为行列数
TSMatrix* creatTSMatrix( int row, int col );
// 按行优先向矩阵中添加一个项,不考虑复杂存储情况
Status addElem( TSMatrix* matrix, int i, int j, int value );
// 为矩阵赋值
void scanTSMatrix( TSMatrix* matrix );
// 行分割线
void printRow( int length );
// 输出矩阵,参数输入1只打印储存的非零元，参数输入2，则按矩阵形式打印
Status printTSMatrix( TSMatrix* matrix, int select );
// 求稀疏矩阵的转置矩阵,成功返回转置矩阵的地址，否则返回NULL
TSMatrix* transposeMatrix( TSMatrix* matrix );
// 矩阵的乘法
TSMatrix* multTSMatrix( TSMatrix* src1, TSMatrix* src2 );

// 界面化
int view( TSMatrix* ms[], int length ){
	int i;
	printf("序号：\t\t\t矩阵数据\n");
	for( i = 0; i < length; i++ ){
		printf("\n***%d***\t转化为含零元的矩阵图：",i+1);
		int j;
		for( j = 0; j < ms[i]->col-1; j++ ){
			printf("\t");
		}
		printf("三元组实际存储：共%d个非零元\n",ms[i]->num);
		printTSMatrix( ms[i], 2 );
	}
	printf("\n***************************************************请输入你要选择的功能：********************************************************************\n************************************1.求转置矩阵\t2.求矩阵相乘\t3.添加矩阵********************************************************************\n");
	int select;
	scanf("%d",&select);
	return select;
}

int main(){
	
	TSMatrix* m1 = creatTSMatrix( 5, 7 );
	addElem( m1, 1, 5, 51 );
	addElem( m1, 1, 7, 7 );
	addElem( m1, 2, 1, 1 );
	addElem( m1, 2, 4, 4 );
	addElem( m1, 3, 6, 6 );
	addElem( m1, 4, 2, 2 );
	addElem( m1, 4, 7, 7 );
	addElem( m1, 5, 4, 4 );
	TSMatrix* matrixs[10] = { m1 };
	int length = 1;
	int select;
	TSMatrix* matrix3;
	int i,j,num,value;
	int fun;
	while( 1 ){
		select = view( matrixs, length );
		switch( select ){
			case 1:
				printf("请输入矩阵的序号：");
				scanf("%d",&i);
				matrix3 = transposeMatrix( matrixs[i-1] );
				matrixs[length++] = matrix3;
				break;
			case 2:
				printf("请输入矩阵的序号：");
				scanf("%d %d",&i,&j);
				matrix3 = multTSMatrix( matrixs[i-1], matrixs[j-1] );
				matrixs[length++] = matrix3;
				break;
			case 3:
				printf("请选择添加的方式：1.矩阵图\t2.非零元：");
				scanf("%d",&fun);
				printf("请输入矩阵的行列数：");
				scanf("%d %d",&i,&j);
				matrix3 = creatTSMatrix( i, j );
				if( fun == 1 ){
					scanTSMatrix( matrix3 );
				} else {
					printf("请输入非零元个数：");
					scanf("%d",&num);
					while( num-- ){
						scanf("%d %d %d",&i,&j,&value);
						addElem( matrix3, i, j, value );
					}
				}
				matrixs[length++] = matrix3;
				printf("*****创建完成！*****\n");
		}
		if( select == 4 ){
			break;
		}
	}
	
	
	return 0;
}


// 创建一个矩阵,形参数为行列数
TSMatrix* creatTSMatrix( int row, int col ){
	// 初始化矩阵
	TSMatrix* matrix = (TSMatrix*)malloc( sizeof(TSMatrix) );
	matrix->data = (TNode*)malloc( maxSize*sizeof(TNode) );
	if( matrix->data == NULL ){
		return NULL;
	}
	matrix->row = row;
	matrix->col = col;
	matrix->num = 0;
	matrix->rpos = NULL;
	return matrix;
}
// 按行优先向矩阵中添加一个项,不考虑复杂存储情况
Status addElem( TSMatrix* matrix, int i, int j, int value ){
	if( i <= 0 || j <= 0 || matrix == NULL ){
		return ERROR;
	}
	int num = matrix->num;
	matrix->data[num].i = i;
	matrix->data[num].j = j;
	matrix->data[num].value = value;
	matrix->num++;
	return OK;
}
// 为矩阵赋值
void scanTSMatrix( TSMatrix* matrix ){
	int i,j,value,num;
	printf("请输入一个矩阵(%d行%d列)：\n", matrix->row, matrix->col );
	for( i=1; i <= matrix->row; i++ ){ // 确定行
		for( j=1; j <= matrix->col; j++ ){ // 确定列
			scanf("%d",&value);
			if( value != 0 ){ // 非零元加入矩阵中
				addElem( matrix, i, j, value );
			}
		}
	}
}
// 行分割线
void printRow( int length ){
	int i;
	printf("-----");
	for( i=1; i <= length; i++ ){
		printf("--------");
	}
	printf("\n");
}
// 输出矩阵,参数输入1只打印储存的非零元，参数输入2，则按矩阵形式打印
Status printTSMatrix( TSMatrix* matrix, int select ){
	if( matrix == NULL ){
		return ERROR;
	}
	// 操作一
	if( select == 1 ){
		int i,j,cnt=0;
		printf("\t共%d个非零元\n",matrix->num);
		for( i=0; i < matrix->num; i++ ){
			TNode* node = matrix->data + i;
			printf("\t行：%d 列：%d 值：%d\t\t", node->i, node->j, node->value );
			printf("\n");
		}
	} else {// 操作二
		int i,j,cnt=0;
		printf("行\\列\t");
		int num = 0;
		for( i=1; i <= matrix->col; i++ ){
			printf("%d\t",i);
		}
		printf("\t行：%d 列：%d 值：%d\n", matrix->data[num].i, matrix->data[num].j, matrix->data[num].value );
		num++;
		printf("-----");
		for( i=1; i <= matrix->col; i++ ){
			printf("--------");
		}
		printf("\t\t行：%d 列：%d 值：%d\n", matrix->data[num].i, matrix->data[num].j, matrix->data[num].value );
		num++;
		for( i=1; i <= matrix->row; i++ ){
			printf("%d¦\t",i);
			for( j=1; j <= matrix->col; j++ ){
				if( matrix->data[cnt].i == i && matrix->data[cnt].j == j ){
					printf("%d\t", matrix->data[cnt++].value );
				} else {
					printf("0\t");
				}

			}
			if( num < matrix->num ){
				printf("\t行：%d 列：%d 值：%d\n", matrix->data[num].i, matrix->data[num].j, matrix->data[num].value );
				num++;
			}
		}
		while( num < matrix->num ){
			for( i = 0; i < matrix->col+1; i++ ){
				printf("\t");
			}
			printf("\t行：%d 列：%d 值：%d\n", matrix->data[num].i, matrix->data[num].j, matrix->data[num].value );
			num++;
		}
	}
}
// 求稀疏矩阵的转置矩阵,成功返回转置矩阵的地址，否则返回NULL
TSMatrix* transposeMatrix( TSMatrix* matrix ){// 快速置换法
	// 判断输入是否合法
	if( matrix == NULL ){
		return NULL;
	}
	// 创建转置矩阵
	TSMatrix* tmatrix = creatTSMatrix( matrix->col, matrix->row );
	tmatrix->num = matrix->num;
	if( tmatrix->num == 0 ){ // 零矩阵
		printf("转置矩阵是零矩阵\n");
		return tmatrix;
	}
	// 非零矩阵
	// 第一步，找寻所求矩阵中第i列非零元素的个数
	int cpot[matrix->col+1];// 初始化，数组意义：cpot[i]的值为矩阵中第i列的非零元素个数
	int i,j;
	for( i=1; i <= matrix->col; i++ ){
		cpot[i] = 0;
	}
	// 遍历矩阵的非零元素
	for( i=0; i < matrix->num; i++ ){
		++cpot[matrix->data[i].j];// 先找到矩阵第i个元素的列号，然后让cpot[列号]++
	}
	// 根据原矩阵每列的非零元素个数，求出原矩阵第i列第一个非零元素应出现在转置矩阵的位置,--优化版
	int num;
	int t = cpot[1];// 列上非零元的个数
	cpot[1] = 1;
	printf("cpot：1 ");
	for( i=2; i <= matrix->col; i++ ){ //cpot[n] = num[n-1] + cpot[n-1]
		num = cpot[i];
		cpot[i] = cpot[i-1] + t;// 当前列的位置等于前一列出现的位置加前一列的非零元素个数
		t = num;
		printf("%d ",cpot[i]);
	}
	printf("\n");
	// 开始为转置矩阵赋值,循环非零元素的个数
	int col;
	int pos;
	for( i=0; i < matrix->num; i++  ){
		col = matrix->data[i].j; // 找到原矩阵第i个元素的列数
		pos = cpot[col]-1; // 根据列数或许当前元素应在转置矩阵储存的位置
		// 数据交换
		tmatrix->data[pos].i = matrix->data[i].j;
		tmatrix->data[pos].j = matrix->data[i].i;
		tmatrix->data[pos].value = matrix->data[i].value;
		++cpot[col];// 将位置后移一位,为下一个做准备
	}
	// 转置结束
	return tmatrix;
}
// 用于求矩阵的行链接信息的数组
void getRpos( TSMatrix* matrix ){
	int i,j;
	if( !matrix->rpos ){
		matrix->rpos = (int*)malloc( (matrix->row+1)*sizeof(int) );
	}
	// 先获取各行有几个非零元素
	for( i=1; i <= matrix->row; i++ ){//初始化
		matrix->rpos[i] = 0;
	}
	for( i=0; i < matrix->num; i++ ){//统计个数
		++matrix->rpos[matrix->data[i].i];
	}
	int num;
	int t = matrix->rpos[1];
	matrix->rpos[1] = 1;
	for( i=2; i <= matrix->row; i++ ){// 获取各行首个非零的位置
		num = matrix->rpos[i];
		matrix->rpos[i] = matrix->rpos[i-1] + t;
		t = num;
	}
}
// 矩阵的乘法
TSMatrix* multTSMatrix( TSMatrix* src1, TSMatrix* src2 ){
	// 判断输入是否合法
	if( src1 == NULL || src2 == NULL ){
		return ERROR;
	}
	if( src1->col != src2->row ){ // 前矩阵的列等于后矩阵的行数
		return ERROR;
	}
	// 矩阵可相乘
	TSMatrix* dest = creatTSMatrix( src1->row, src2->col );
	if( src1->num == 0 || src2->num == 0 ){ // 存在一个零矩阵
		return dest;
	}
	// 开始相乘
	// 获取各行首个非零元素的位置
	getRpos( src1 );
	getRpos( src2 );
	int i,j;
	// 逐行相乘
	int row;// 用于访问行
	for( row=1; row <= src1->row; row++ ){ // 处理前矩阵的每一行
		int front1 = src1->rpos[row]; // 改行首个非零元素的位置
		int tail1; // 下一行首个非零元素的位置 case:rpos[i] = rpos[i-1]+num[i-1] 所以 rpos[i]==rpos[i-1]即当前行无元素
		if( row == src1->row ){
			tail1 = src1->num+1;
		} else {
			tail1 = src1->rpos[row+1];
		}
		// 行内有元素  Q[i][j] += M[i][k]*N[k][j] k=1,2,3,4...M.col
		// 手算思想：先把Q[1][1]算出,即M第一行和N第一列对应元素相乘的结果相加,即每次运算就可获取一项的具体值
		// 编程模拟：计算机实现手算较复杂,无法实现每次循环获取一个项,但是可以每次循环获取一行的所有非零项
		int colNum[src2->col+1];// colNum[i]的数值表示相乘后第几列的元素的值
		for( i=1; i <= src2->col; i++ ){// 初始化
			colNum[i] = 0;
		}
		for( ; front1 < tail1; front1++ ){ // 如果行内无元素，则直接将Q改行置0
			int k = src1->data[front1-1].j;// 当前行某个元素的列数
			int front2 = src2->rpos[k]; // k行的首个非0元素的位置
			int tail2; // k行下一行首非零元素的位置
			if( k == src2->row ){//k不是最后一行
				tail2 = src2->num+1;
			} else { // k是最后一行
				tail2 = src2->rpos[k+1];
			}
			for( ; front2 < tail2; front2++ ){
				colNum[src2->data[front2-1].j] += src1->data[front1-1].value*src2->data[front2-1].value;// 计算M的一个项作用与以该项行数为列数的所有非零元
			}
		}
		// 压缩入新矩阵
		int cnt = 0;
		for( i=1; i <= src2->col; i++ ){
			if( colNum[i] != 0 ){
				addElem( dest, row, i, colNum[i] );
			}
		}
		
	}
	
	return dest;	
}