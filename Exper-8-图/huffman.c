#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Hnode* Node;
typedef char EleType;   //每个节点储存的数据种类

int number = 1;   //数据中字符总数
char chars[1000];   //数据所有字符
char codes[1000][15], code_end[15];  //每个字符对应的哈夫曼编码，单独记录‘\0’的编码
int pos = 0;   //动态记录已经读取出的字符数

struct Hnode {
	EleType Data;  //记录字符
	int Times;   //记录字符出现的次数
	Node Lchild, Rchild;   //哈夫曼树的左右子孩
	Node Next;   //读取字符时按照单项链表储存，便于排序、插入新节点
};
//创建并初始化一个节点
Node init(EleType data)
{
	Node N;
	N = (Node)malloc(sizeof(struct Hnode));
	N->Lchild = N->Rchild = N->Next = NULL;
	N->Data = data;
	N->Times = 1;
	return N;
}
//创建一个链表储存data中所有字符以及出现次数
Node CreatChain(Node N, EleType data[])
{
	Node H = N;
	int i, l = strlen(data);  //遍历字符串，储存每个字符
	for (i = 0; i < l; i++) {
		if (data[i] != '\n') {   //‘\n’不编码
			Node p = H;
			while (H) {     //如果字符在前面读取到则将其出现次数增加1
				if (data[i] == H->Data) {
					H->Times++;
					break;
				}
				p = H;
				H = H->Next;
			}
			if (!H) {   //如果遍历完了链表，说明没有找到该字符，则在最后创建其对应的节点
				p->Next = init(data[i]);
				number++;
			}
		}
		H = N;    //每次查询结束都要将指针回归
	}
	return N;
}
//交换两个节点的数据
void exchange(Node p, Node q)
{
	EleType c = p->Data;
	int time = p->Times;
	p->Data = q->Data;
	p->Times = q->Times;
	q->Data = c;
	q->Times = time;
}
//对链表进行排序
Node rank(Node N)
{
	Node H = N;
	int i, j;     //冒泡法对链表排序
	for (i = 1; i < number; i++) {
		for (j = 0; j < number - i; j++) {
			Node p = H->Next;
			if (p->Times < H->Times) {    //频次高的字符在后面
				exchange(H, p);
			}
			if (p->Times == H->Times && p->Data < H->Data) {   //频次相同的字符按照ASCII码大小排序
				exchange(H, p);
			}
			H = H->Next;
		}
		H = N;
	}
	return N;
}
//向链表中插入一个节点
void insert(Node N, Node r)
{
	Node H = N->Next, p = N;
	int flag = 0;
	while (H) {      //将r节点插入第一个比它频次高的节点前面
		if (H->Times > r->Times) {
			p->Next = r;
			r->Next = H;
			flag = 1;
			break;
		}
		p = H;
		H = H->Next;
	}
	if (!flag) {   //如果r的频次最高，则插入链表最后
		p->Next = r;
		r->Next = H;
	}
}
//利用排好序的链表创建哈夫曼树
Node creatHTree(Node N)
{
	Node p = N, q = N->Next;
	while (p && q) {
		Node r = init(1);   //将频次最小的两个节点频次相加创建新节点，并创建哈夫曼树结构
		r->Times = p->Times + q->Times;
		r->Lchild = p;  //频次小的作为左树
		r->Rchild = q;   //频次大的作为又树
		insert(q, r);   //将新节点插入链表
		p = q->Next;   //遍历剩余节点
		q = p->Next;
	}
	return p;
}
//获取每个字符的哈夫曼编码
void getCode(Node N, char code[])
{
	char c[15];
	if (N->Lchild) {   //左孩的编码为0
		strcpy(c, code);
		strcat(c, "0\0");
		getCode(N->Lchild, c);
	}
	if (N->Rchild) {   //右孩的编码为1
		strcpy(c, code);
		strcat(c, "1\0");
		getCode(N->Rchild, c);
	}
	if (!N->Lchild && !N->Rchild) {   //叶子节点，记录下其对应的字符及哈夫曼编码
		chars[pos] = N->Data;
		strcpy(codes[pos++], code);
		if (N->Data == '\0')   //单独记录‘\0’的编码
			strcpy(code_end, code);
	}
}
//每八位进行一次十六进制输出(可避免结果高位出现0)
void output(char str[])
{
	int i, j, l = strlen(str);
	for (i = 0; i < l; i += 8) {   //每八位做一次输出
		int a = 0;
		for (j = 0; j < 8; j++)   //将八位二进制转为十进制，以十六进制格式输出
			a = a * 2 + (str[i + j] - '0');
		printf("%x", a);
	}
	printf("\n");
}
//主函数
int main()
{
	char str[1000], code[10] = { '\0' }, coding[10000] = { '\0' }, ch;
	Node N = init('\0');
	int i = 0, l;
	FILE* fp = fopen("input.txt", "r");
	while (!feof(fp)) {					// feof 读到文件末尾的函数
		ch = fgetc(fp);					// 获取下一个字符
		str[i++] = ch;					// 输出文件中的字符
	}
	str[i-1] = '\0';
	N = CreatChain(N, str);  //创建链表
	N = rank(N);  //对链表排序
	N = creatHTree(N);  //创建哈夫曼树
	strcpy(code, "");
	getCode(N, code);  //获取每个字符的哈夫曼编码
	for (i = 0; i < strlen(str); i++)    //编码，储存到coding
		for (pos = 0; pos < number; pos++)
			if (str[i] == chars[pos]) {
				strcat(coding, codes[pos]);
				break;
			}
	strcat(coding, code_end);   //最后添加‘\0’的编码
	l = strlen(coding);
	for (i = 0; l % 8 && i < 8 - l % 8; i++) {
		strcat(coding, "0");
	}
	output(coding);
	fp = fopen("output.txt", "a");
	fwrite(coding, strlen(coding), 1, fp);
	fclose(fp);

	return 0;
}
