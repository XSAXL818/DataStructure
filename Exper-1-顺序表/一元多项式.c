#include <stdio.h>
#include <stdlib.h>
#define OK 1
#define ERROR 0

typedef int Status;
// 方法一： 使用C自带的数组
double f( double *a, double x, int length );
// 方法二：自定义结构体,数组中的元素包含 ax^n 一个常数项 和 指数
typedef struct{
	int expo;
	double constNum;
} EC;
typedef struct{
	EC *ec;
	int length;
	int maxSize;
} POLY;
Status InitPoly( POLY* p, int maxSize );
Status addElemInPoly( POLY* p, int expo, double constNum );
double f1( POLY *p , double);
// 实现两个多项式相乘
// 传入一个项, 如果找到expo指数相同
void attachECInPoly( POLY* poly, int expo, int constNum );
// 显示一元多项式
void showPolys( POLY* polys, int* pLength );
void printPoly( POLY* poly );
// 多项式相加
int addPolys( POLY* p1, POLY* p2, POLY* p );
// 多项式相乘
void multiPolys( POLY* p1, POLY*p2, POLY*p  );



int main(){

	double x = 1;
	// 举例： 3 + (x+1)(x+2)(x+3) + 3x^5 = 3x^5 + x^3 + 6x^2 + 11x + 9 
	// 该方法的弊端：如 x + x^20000, 则会占用不必要的内存,也会进行不必要的运算
//	double test[] = { 9, 11, 6, 1, 0, 3 };
//	printf("结果为：%.4f\n", f( test, x, sizeof(test) / sizeof(test[0]) ) );
	
	// 顺序表存储: 按指数从大到小
	POLY poly1;
	InitPoly( &poly1, 15 );
	
	addElemInPoly( &poly1, 5, 3 );
	addElemInPoly( &poly1, 3, 1 );
	addElemInPoly( &poly1, 2, 6 );
	addElemInPoly( &poly1, 1, 11 );
//	addElemInPoly( &poly1, 0, 9 );	
//	printf("结果为：%.4f\n", f1( &poly1, x ));

	POLY poly2;
	InitPoly( &poly2, 15 );
	
	addElemInPoly( &poly2, 9, 2 );
	addElemInPoly( &poly2, 7, 8 );
	addElemInPoly( &poly2, 5, 7 );
	addElemInPoly( &poly2, 3, 4 );
	addElemInPoly( &poly2, 0, 11 );	
//	printf("结果为：%.4f\n", f1( &poly2, x ));
	
	POLY polys[10];
	polys[0] = poly1;
	polys[1] = poly2;
	int pLength = 2;

	while( 1 ){
		int select;
		printf("请选择以下功能：\n1.显示已存在的多项式(可添加新多项式)\n2.进行两个一元多项式的相加\n3.进行两个一元多项式的相乘\n4.退出\n");
		scanf("%d",&select);
		int index1;
		int index2;
		switch( select ){
			case 1:
				showPolys( polys, &pLength );	
				break;
			case 2:
				printf("请输入你要相加多项式的序号：(如 1 2 )\n");
				scanf("%d %d",&index1,&index2);
				POLY p2;
				InitPoly( &p2, polys[index1-1].length + polys[index2-1].length );
				// 增加新多项式后用 pLength需+1
				if( addPolys( &(polys[index1-1]), &(polys[index2-1]), &p2 ) ){
					polys[pLength] = p2;
					pLength++;
				}	
				break;
			case 3:
				printf("请输入你要相乘多项式的序号：(如 1 2 )\n");
				scanf("%d %d",&index1,&index2);
				POLY p3;
				InitPoly( &p3, polys[index1-1].length * polys[index2-1].length );
				multiPolys( &(polys[index1-1]), &(polys[index2-1]), &p3);
				polys[pLength] = p3;
				pLength++;
				break;
		}
		if( select == 4 ){
			break;
		}
	}
	
	
	
	
	return 0;
}

// 算法思路：形如 3 + 4x + 2x^2 + 3x^3  =  3 + x( 4 + x( 2 + x( 3 ) ) ) = a0 + x(a1 + x(a2 + x (...an-1 + x(an)    ) ) )
// 关键：通过循环，每次能得到  ai + a(i+1)*(x^(i+1)) 即循环 n-1 次
// 具体例子： 3x^5 + 2x^3 + 4x + 1 = 1 + x(4 + x(0 + x(2 + x(0 + x(3) ) ) ) )
// 基本思路： 第一次循环得到 2 + x(0 + x(3))
// 			  第二次循环得到 4 + x(0 + x(2 + x(0 + x(3) ) ) )
//			  第三次循环得到 1 + x(4 + x(0 + x(2 + x(0 + x(3) ) ) ) )
//            结束

double f( double *a, double x, int length ){
	double ret = *( a + length - 1 );
	int i;
	for(i=length-2; i >= 0; i-- ){
		ret *= x;
		ret += *( a + i );	
	}
	
	return ret;
}

Status InitPoly( POLY* p, int maxSize ){
	if( p == NULL || maxSize < 0 ){
		return ERROR;
	}
	
	p->ec = (EC*)malloc( sizeof(EC) * maxSize );
	p->length = 0;
	p->maxSize = maxSize;
	return OK;
	
}

Status addElemInPoly( POLY* p, int expo, double constNum ){
	
	// 不做错误输入判断了
	EC *ec = p->ec + p->length;
	ec->expo = expo;
	ec->constNum = constNum;
	p->length++;
	
	return OK;
}
// 
double f1( POLY *p , double x){
	
	int length = p->length;
	EC *ec = p->ec;
	int i,j;
	// 举例：3 + 3x^2 + x^200  ==  3 + x^2( 3 + x^198(1) )
	int ret = ec->constNum;

	if( length == 1 ){
		int t;
		i = ec->expo;
		for( t=0; t < i; t++){
			ret *= x;
		}
		return ret;
	}
	while( length > 1 ){
		i = ec->expo;
		j = ( ec + 1 )->expo;
		int t;
		for( t=i; t > j; t-- ){
			ret *= x;
		}
		ret += ( ec + 1 )->constNum;
		ec++;	
		length--;
	}
	if( ec->expo != 0 ){
		for( i = 0; i < ec->expo; i++ ){
			ret *= x;
		}
	}
	return ret;
}
// 向列表中添加元素，如果已存在相同的expo指数，则进行系数的相加，相加为0则删除原列表中的元素，不为零则按大到小插入到列表中
void attachElemInPoly( POLY* poly, int expo, int constNum ){


	
}

//
void showPolys( Poly* polys, int* pLength ){
	printf("序号\t一元多项式\n");
	int i;
	for(i=0; i < *pLength; i++){
		printf("%d\t",i+1);
		printPoly( polys + i );
	}
	printf("请选择以下功能：\n1.添加新列表\t2.计算一元多项式\t3.退出\n");
	int select;
	scanf("%d",&select);
	if( select == 1 ){
		int num;
		printf("请输入该一元多项式的项数：\n");
		scanf("%d",&num);
		POLY p;
		InitPoly( &p, num );
		printf("请按系数大到小输入(常数 系数)\n");
		while( num > 0 ){
			double constNum;
			int expo;
			scanf("%lf %d",&constNum,&expo);
			addElemInPoly(&p,expo,constNum);
			num--;
		}
		polys[*pLength] = p;
		(*pLength)++;
	} else if( select == 2 ){
		printf("请输入该一元多项式的序号：\n");
		int index;
		scanf("%d",&index);
		POLY* p = polys + index - 1;
		double x;
		printf("请输入X的值：\n");
		scanf("%lf",&x);
		printf("结果为：%.2lf\n", f1(p,x) );
	} 
}
//
int addPolys( POLY* p1, POLY* p2, POLY* p ){

	int index1 = 0;
	int index2 = 0;
	
	while( index1 < p1->length && index2 < p2->length ){
		EC* ec1 = p1->ec + index1;
		EC* ec2 = p2->ec + index2;
		if( ec1->expo > ec2->expo ){
			addElemInPoly(p, ec1->expo, ec1->constNum );
			index1++;
		} else if( ec1->expo < ec2->expo ){
			addElemInPoly(p, ec2->expo, ec2->constNum );
			index2++;
		} else {
			if( (ec1->constNum + ec2->constNum) != 0 ){
				addElemInPoly( p, ec1->expo, ec1->constNum + ec2->constNum );
			}
			index1++;
			index2++;
		}
	}
	if( index1 == p1->length ){
		for(; index2 < p2->length; index2++ ){
			EC* ec = p2->ec + index2;
			addElemInPoly(p,ec->expo,ec->constNum);
		}
	} else {
		for( ; index1 < p1->length; index1++ ){
			EC* ec = p1->ec + index1;
			addElemInPoly(p,ec->expo,ec->constNum);
		}
	}
	
	return OK;
}
// 
void multiPolys( POLY* p1, POLY*p2, POLY*p ){
	int i,j;
	POLY  t;
	InitPoly( &t, p2->length );
	POLY  tt;
	InitPoly( &tt, 1 );
	POLY tp;
	InitPoly( &tp, p->maxSize );
	
	for( i=0; i < p1->length; i++ ){
		EC* ec1 = p1->ec + i;
		for( j=0; j < p2->length; j++ ){
			EC* ec2 = p2->ec + j;
			addElemInPoly( &t, ec1->expo + ec2->expo, ec1->constNum * ec2->constNum );
		}

		addPolys( &t, &tp, p );
		tp.length = 0;
		if( i < p1->length - 1 ){
			addPolys( &tt, p, &tp);
			p->length = 0;
			t.length = 0;
		}
			
	}
}
//
void printPoly( POLY* poly ){
	int i;
	int dic = 0;
	for(i=0; i < poly->length; i++){
		EC* ec = (poly->ec + i);
		if( dic ){
			printf(" + ");
		}
		printf("(%.2lf)x^%d", ec->constNum, ec->expo);
		dic = 1;
	}
	printf("\n");
}
	