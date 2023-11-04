#include <stdio.h>
#include <stdlib.h>

typedef struct _Node{
	double constNum;
	int expo;
	struct _Node *next;
} Poly;

// 头插法
int add( Poly* poly, double constNum, int expo );
// 尾插法
int add1( Poly* poly, double constNum, int expo );
// 打印多项式
void printPoly( Poly* poly);
// 多项式的计算
double solvePoly( Poly* poly, double x );
// 多项式相加
Poly* addPolys( Poly* src1, Poly* src2 );
// 多项式相乘
Poly* multiPolys( Poly* src1, Poly* src2 );
// 多项式链接
Poly* attchPolys( Poly* src1, Poly* src2 );
// 多项式相除
//Poly* diviPolys( Poly* src1, Poly* src2 );


// 显示菜单
void showPolys( Poly* polys[10], int* pLength );

int main(){
	
	Poly poly1;
	poly1.next = NULL;
	add1( &poly1, 5, 6 );	
	add1( &poly1, 4, 5 );
	add1( &poly1, 1, 3 );
	add1( &poly1, 2, 1 );

	Poly poly2;
	poly2.next = NULL;	
	add1( &poly2, 3, 6 );
	add1( &poly2, 5, 4 );
	add1( &poly2, 5, 3 );
	add1( &poly2, 11, 1 );
	
	Poly* polys[10] = { &poly1, &poly2 };
	int pLength = 2;
	while( 1 ){
		
		int select;
		printf("请选择以下功能：\n1.显示已存在的多项式(可添加新多项式)\n2.一元多项式的相加\n3.一元多项式的相乘\n4.退出\n");
		scanf("%d",&select);
		int index1;
		int index2;
		Poly* p;
		switch( select ){
			case 1:
				showPolys( polys, &pLength );	
				break;
			case 2:
				printf("请输入你要相加多项式的序号：(如 1 2 )\n");
				scanf("%d %d",&index1,&index2);
//				Poly* p2 = addPolys( polys[index1-1], polys[index2-1] );
				p = addPolys( polys[index1-1], polys[index2-1] );
				polys[pLength] = p;
				pLength++;
				break;
			case 3:
				printf("请输入你要相乘多项式的序号：(如 1 2 )\n");
				scanf("%d %d",&index1,&index2);
//				Poly* p3 = multiPolys( polys[index1-1], polys[index2-1] );
				p = multiPolys( polys[index1-1], polys[index2-1] );
				polys[pLength] = p;
				pLength++;
				break;
//			case 4:
//				printf("请输入你要相除的多项式的序号：( 1 / 2 )\n");
//				scanf("%d %d",&index1,&index2);
//				p = diviPolys( polys[index2-1], polys[index1-1] );
//				polys[pLength] = p;
//				pLength++;
//				break;
		}
		if( select == 4 ){
			break;
		}
	
	
	}
	
	
	
	
	
	
	return 0;
}

// 头插法O(1)
int add( Poly* poly, double constNum, int expo ){
	if( poly == NULL ){
		return 0;
	}
	Poly* p = (Poly*)malloc( sizeof(Poly) );
	p->constNum = constNum;
	p->expo = expo;
	p->next = poly->next;
	poly->next = p;

	return 1;	
}
// 尾插法 时间复杂度O(N)
int add1( Poly* poly, double constNum, int expo ){
	if( poly == NULL ){
		return 0;
	}

	while( poly->next ){
		poly = poly->next;
	}
	Poly* node = (Poly*)malloc( sizeof( Poly ) );
	node->constNum = constNum;
	node->expo = expo;
	node->next = NULL;
	poly->next = node;
	
	return 1;	
}
// 打印多项式
void printPoly( Poly* poly){
	Poly* head = poly;
	int dic = 0;
	while( head->next ){
		head = head->next;
		if( dic == 1 ){
			printf(" + (%.4f)x^%d ",head->constNum, head->expo );
		} else {
			printf(" (%.4f)x^%d ",head->constNum, head->expo );
			dic = 1;
		} 
	}
	printf("\n");
}

// 多项式的计算
double solvePoly( Poly* poly, double x ){
	if( poly->next == NULL ){
		return 0.0;
	}
	Poly* head = poly->next;
	int i;
	double sum = head->constNum;

	if( head->next == NULL ){
		for( i = head->next->expo; i >0 ; i-- ){
			sum *= x;
		}
		return sum;
	}

	while( head->next ){
		for( i = head->expo; i > head->next->expo; i-- ){
			sum *= x;
		}
		head = head->next;
		sum += head->constNum;
	}
	// 多项式最后一项不为0则漏算了
	if( head->expo != 0 ){
		for( i=0; i < head->expo; i++ ){
			sum *= x;
		}
	}
	
	return sum;
}
// 多项式相加
Poly* addPolys( Poly* src1, Poly* src2 ){
	Poly* dest = (Poly*)malloc( sizeof(Poly) );
	dest->next = NULL;
	
	Poly* start1 = src1->next;
	Poly* start2 = src2->next;
	
	while( start1 && start2 ){
		if( start1->expo > start2->expo ){
			add1( dest, start1->constNum, start1->expo );
			start1 = start1->next;
		} else if( start1->expo < start2->expo ){
			add1( dest, start2->constNum, start2->expo );
			start2 = start2->next;
		} else {
			if( start1->expo + start2->expo == 0 ){
				
			} else {
				add1( dest, start2->constNum + start1->constNum, start1->expo );
			}
			start1 = start1->next;
			start2 = start2->next;
		}
	}
	if( start1 == NULL ){
		while( start2 ){
			add1( dest, start2->constNum, start2->expo );
			start2 = start2->next;
		}
	} else {
		while( start1 ){
			add1( dest, start1->constNum, start1->expo );
			start1 = start1->next;
		}
	}
	return dest;
}
// 多项式链接
Poly* attchPolys( Poly* src1, Poly* src2 ){
	Poly* dest = src1;
	
	Poly* start1 = src1->next;
	Poly* start2 = src2->next;
	Poly* start3 = dest;
	Poly* p1;
	Poly* p2;
	while( start1 && start2 ){
		if( start1->expo > start2->expo ){
			start3->next = start1;
			start3 = start1;
			start1 = start1->next;
		} else if( start1->expo < start2->expo ){
			start3->next = start2;
			start3 = start2;
			start2 = start2->next;
		} else {
			if( start1->constNum + start2->constNum == 0 ){
				p1 = start1;
				p2 = start2;
				start1 = start1->next;
				start2 = start2->next;	
				free( p1 );
				free( p2 );
			} else {
				start1->constNum = start1->constNum + start2->constNum;
				start3->next = start1;
				start3 = start1;
				p1 = start2;
				start1 = start1->next;
				start2 = start2->next;
				free( p1 );
			}
		}
	}
	if( start1 ){
		start3->next = start1;
	}
	if( start2 ){
		start3->next = start2;
	}
//	free( src2 );
	return dest;	
}
// 多项式相乘
Poly* multiPolys( Poly* src1, Poly* src2 ){
	Poly* dest = (Poly*)malloc( sizeof(Poly) );
	dest->next = NULL;
	// 两个多项式的表头
	Poly* start1 = src1->next;
	Poly* start2 = src2->next;
	
	while( start1 ){ // 循环第一个多项式的每一项
		Poly* t = (Poly*)malloc( sizeof(Poly) );// 每次循环，可得到一个 第一个多项式 ai 的项 乘 第二个多项式的 新多项式
		t->next = NULL;// 初始化t为空表
		while( start2 ){ // 将新乘的项加入t链表中
			add1( t, start1->constNum * start2->constNum, start1->expo + start2->expo );
			start2 = start2->next;
		}
		start2 = src2->next; // 将指针指向第二个多项式的头，便于下次循环
		dest = attchPolys( t, dest );// 把新乘的所有项加入到最后的结果多项式中
		start1 = start1->next;// 指向第一个多项式的指针向后移一位
	}	
	
	return dest;
}
// 显示菜单
void showPolys( Poly* polys[10], int* pLength ){
	printf("序号\t一元多项式\n");
	int i;
	for(i=0; i < *pLength; i++){
		printf("%d\t",i+1);
		printPoly( polys[i] );
	}
	printf("请选择以下功能：\n1.添加新列表\t2.计算一元多项式\t3.退出\n");
	int select;
	scanf("%d",&select);
	if( select == 1 ){
		int num;
		printf("请输入该一元多项式的项数：\n");
		scanf("%d",&num);
		Poly* p = (Poly*)malloc( sizeof(Poly) );
		p->next = NULL;
		printf("请按系数大到小输入(常数 系数)\n");
		while( num > 0 ){
			double constNum;
			int expo;
			scanf("%lf %d",&constNum,&expo);
			add1( p, constNum, expo );
			num--;
		}
		polys[*pLength] = p;
		(*pLength)++;
	} else if( select == 2 ){
		printf("请输入该一元多项式的序号：\n");
		int index;
		scanf("%d",&index);
		Poly* p = polys[index - 1];
		double x;
		printf("请输入X的值：\n");
		scanf("%lf",&x);
		printf("结果为：%.2lf\n", solvePoly( p, x ) );
	} 
}


// 多项式相除, src2 / src1  错误
//Poly* diviPolys( Poly* src1, Poly* src2 ){
//	Poly* dest = (Poly*)malloc( sizeof(Poly) );
//	dest->next = NULL;
//	
//	Poly* start1 = src1->next;
//	Poly* start2 = src2->next;
//	
//	while( start1 ){
//		Poly* t = (Poly*)malloc( sizeof(Poly) );
//		t->next = NULL;
//		while( start2 ){
//			add1( t, start2->constNum / start1->constNum, start2->expo - start1->expo );
//			start2 = start2->next;
//		}
//		start2 = src2->next;
//		dest = attchPolys( t, dest );
//		start1 = start1->next;
//	}	
//	
//	return dest;
//}