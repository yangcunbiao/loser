#include<stdio.h>
#include<stdlib.h>
#define LEN 500
struct node {
	char s[LEN];
	struct node *next;
};
typedef struct node* list;

FILE *fp = NULL;//文件指针
char name[100];//存放文件名
char q;//用于读掉回车

void menu();//输出菜单
void reporterror();//输入错误指令报错
int mystrlen(const char *);//返回字符串长度
char* mystrcpy(char *, const char*);//复制字符串
void mystrcat(char *, const char *);//连接字符串
int mystrcmp(const char*, const char *);//字符串比大小
int cot(list);//输入文件行数
list turnto(int l,list head);//返回第l-1行的节点;
char *search(char *s, char *t);//查找字符串，找到返回首地址。


list open(FILE *);//打开文件，建立链表
list print(list);//显示文件内容
list insert(list);//插入行
list dele(list);//删除行
list copy(list);//复制行
list modify(list);//修改行
list find(list);//查找字符串
list replace(list);//替换字符串
list save(list);//存盘退出
list quitedit(list);//放弃编辑

//定义
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
void menu()
{
	printf("请选择：1.打开文件(新或旧)  2.显示文件内容\n");
	printf("        3.插入行  4.删除行  5.拷贝行  6.修改行\n");
	printf("        7.查找字符串        8.替换字符串\n");
	printf("        9.存盘退出          0.放弃编辑\n");
}
void reporterror()
{
	printf("指令错误\n");
	printf("请输入0~9\n");
}
int mystrlen(const char *p)
{
	int count = 0;
	while (p[count] != '\0') {
		count++;
	}

	return count;
}
char* mystrcpy(char *p1, const char*p2)
{
	int count = 0;
	while ((p1[count] = p2[count]) != '\0') {
		count++;
	}
	return p1;
}
void mystrcat(char *p1, const char *p2)
{
	int count = 0, count1 = 0;
	while (p1[count] != '\0') {
		count++;
	}
	while ((p1[count] = p2[count1]) != '\0') {
		count++;
		count1++;
	}
}
int mystrcmp(const char*s1, const char *s2)
{
	int idx = 0;
	while (true)
	{
		if (s1[idx] != s2[idx]) {
			break;
		}
		else if (s1[idx] == '\0') {
			break;
		}
		idx++;
	}
	return s1[idx] - s2[idx];
}
int cot(list head)
{
	list tail = NULL;
	if (head->next != NULL) {
		tail = head->next;
	}
	int count = 0;

	while (tail != NULL) {
		count++;
		tail = tail->next;
	}

	return count;
}
char *search(char *s, char *t)
{
	char* p = NULL;

	int count = 0, flag = 0;

	while (t[count] != '\0') {
		count++;
	}
	count--;

	for (int i = 0; s[i + count] != '\0'; i++) {
		for (int j = 0; j <= count; j++) {
			if (t[j] != s[i + j]) {
				p = NULL;
				break;
			}
			p = &s[i];
			if (j == count)
				flag = 1;
		}
		if (flag)break;
	}

	return p;
}



list turnto(int l, list head)
{
	list tail = NULL;
	for (int count = 0; count < l; count++) {
		if (tail == NULL) {
			tail = head;
		}
		else {
			tail = tail->next;
		}
	}
	return tail;
}
list open(list head)
{
	int lon;//字符串长度
	list tail = NULL, p = NULL;
	head = NULL;
	head = (list)malloc(sizeof(struct node));
	head->next = NULL;
	tail = head;
	printf("请输入文件(可包括盘符、路径，不超过19个字符)：");
	scanf("%c", &q);
	scanf("%[^\n]s", name);
	lon = mystrlen(name);
	if (name[lon - 1] != 't' || name[lon - 2] != 'x' || name[lon - 3] != 't' || name[lon - 4] != '.') {
		printf("文件格式错误。\n");
		return head;
	}
	fp = fopen(name, "r");
	//判断文件打开是否成功，否的话自动创建新文件
	if (fp == NULL) {
		printf("文件不存在，自动创建文件\n");
		fp = fopen(name, "w");
	}
	else {
		printf("打开成功！\n");
	}
	//尾插法建立链表。
	p = (list)malloc(sizeof(struct node));
	p->next = NULL;
	if (fscanf(fp, "%[^\n]s", p->s) == -1) {
		p->s[0] = '\0';
	}
	
	if (p->s[0] != '\0') {
		while (p != NULL)
		{
			tail->next = p;
			p = (list)malloc(sizeof(struct node));
			p->next = NULL;
			fscanf(fp, "%c", &q);
			if (fscanf(fp, "%[^\n]s", p->s) == -1) {
				p->s[0] = '\0';
			}

			if (p->s[0] == '\0') {
				p = NULL;

				break;
			}
			tail = tail->next;
		}
	}
	fclose(fp);
	return head;
}
list print(list head)
{
	int count = 1;//计算行数。
	list tail = head->next;

	if (head ->next!= NULL){//文件有内容输出内容，没有输出文件为空。
		while (tail != NULL) {
			printf("%d：%s\n", count, tail->s);
			tail = tail->next;
			count++;
		}
	}
	else {
		printf("文件为空\n");
	}

	return head;
}
list insert(list head)
{
	int l, m;
	list tail = NULL, p = NULL, head1 = NULL, tail1 = NULL;
	printf("当前有%d行\n", cot(head));
	printf("在第l行前插入m行，请输入l m：");
	scanf("%d %d", &l, &m);
	if (l > 0 && l <= cot(head)+1) {}//判断输入的行号是否在范围内。
	else {
		printf("插入行号错误\n");
		return head;
	}
	
	printf("\n请顺序输入待插入的内容：\n");
	//将输入的字符串串成链表；
	p = (list)malloc(sizeof(struct node));
	p->next = NULL;
	scanf("%c", &q);
	scanf("%[^\n]s", p->s);
	tail1 = head1 = p;
	if (m > 1) {
		for (int count = 1; count < m; count++) {
			tail1 = p;
			p = (list)malloc(sizeof(struct node));
			p->next = NULL;
			scanf("%c", &q);
			scanf("%[^\n]s", p->s);
			tail1->next = p;
		}
	}
	//将输入的链表连进原链表
	if (tail1->next != NULL) {
		tail1 = tail1->next;
	}
	if (l <= cot(head)) {
		tail = turnto(l, head);
	}
	else {
		tail = head;
		while (tail->next != NULL) {
			tail = tail->next;
		}
	}
	tail1->next = tail->next;
	tail->next = head1;

	return head;
}
list dele(list head)
{
	int l, m;
	list tail1 = NULL, tail = NULL, head1 = NULL, pre = NULL;
	printf("当前有%d行。\n", cot(head));
	printf("从第l行起删除m行，请输入了l m:");
	
	scanf("%d %d", &l, &m);
	if (l > 0 && l <= cot(head)&&m<=cot(head)+1-l){}//判断输入的数字是否在范围内。
	else if(l<0||l>cot(head)){
		printf("删除行号错误.\n");
		return head;
	}
	else {
		printf("删除行过多.\n");
		return head;
	}
	//将要删除的部分断开
	tail = turnto(l, head);
	tail1=head1 = tail->next;
	for (int count = 1; count < m; count++) {
		tail1 = tail1->next;
	}
	tail->next = tail1->next;
	//释放空间。
	while (head1 != tail1) {
		pre = head1;
		head1 = head1->next;
		free(pre);
	}
	return head;
}
list copy(list head)
{
	int l, m, k;
	list head1 = NULL, tail = NULL, tail1 = NULL, p = NULL, tail2 = NULL;//head1为新链表的头，tail1为新链表的尾，tail为连接的节点，tail2用来遍历复制部分。
	printf("当前有%d行\n", cot(head));
	printf("把第l开始的m行插在原k行前，请输入l m k：");
	scanf("%d %d %d", &l, &m, &k);
	if (l > 0 && (l <= cot(head) + 1) && (cot(head) + 1 - l >= m) && k > 0 && k <= cot(head) + 1) {}
	else {
		printf("输入有误\n");
		return head;
	}
	//将复制部分创建新链表
	p = (list)malloc(sizeof(struct node));
	p->next = NULL;
	tail = turnto(k, head);
	tail2 = turnto(l, head);
	mystrcpy(p->s, tail2->next->s);
	tail1 = head1 = p;
	tail2 = tail2->next;
	if (m > 1) {
		for (int count = 1; count < m; count++) {
			tail1 = p;
			p = (list)malloc(sizeof(struct node));
			p->next = NULL;
			mystrcpy(p->s, tail2->next->s);
			tail2 = tail2->next;
			tail1->next = p;
		}
	}
	//将新链表连入原链表的插入位置
	if (tail1->next != NULL) {
		tail1 = tail1->next;
	}
	tail1->next = tail->next;
	tail->next = head1;

	return head;
}
list modify(list head)
{
	int m;//修改的行号
	list tail;//修改行的节点
	printf("请输入待修改的行号：");
	scanf("%d", &m);
	if (head->next == NULL) {
		printf("文件为空无法修改\n");
		return head;
	}
	if (m < 0 || m > cot(head)) {
		printf("输入的行号错误\n");
		return head;
	}
	tail = turnto(m, head);
	tail = tail->next;
	printf("%d:%s\n", m, tail->s);
	printf("请输入新内容：");
	scanf("%c", &q);
	scanf("%[^\n]s", tail->s);
	return head;
}
list find(list head)
{
	char ch[LEN] = { 0 }, ch1[LEN] = { 0 }, *p, *p1 = NULL, ch2, *p2 = NULL, q;//ch装待查找的字符串，ch1装找到的那行的字符串，p1、p指向现在行的字符串
	int count = 0, count1 = 0, flag = 0, count2 = 1, length, flag2 = -1;//count是待替换字符串的长度，count1用来统计找到的字符串个数，count2记录第几行，flag用于跳出循环，flag2用于记录状态。
	list tail = head;
	tail = tail->next;
	printf("请输入待查找的字符串：");
	scanf("%s", ch);
	count = mystrlen(ch);
	//查找字符串
	while (tail != NULL) {
		//行间
		p2 = p = tail->s;
		mystrcpy(ch1, tail->s);
		length = mystrlen(tail->s);
		//行内
		while ((p + count - 1) < (p2 + length))
		{
			p1 = search(p, ch);
			if (p1 != NULL) {
				printf("第%d行：%s\n", count2, ch1);
				printf("第%d个字符处找到。继续查找吗(Y/N)？", ++count1);
				scanf("%c", &q);
				scanf("%c", &ch2);
				flag2 = 1;
				if (ch2 == 'N') {
					flag = 1;
					break;
				}
				else {
					flag = 2;
					flag2 = 0;
				}
			}
			else {
				break;
			}
			p = p1;
			p = p + count;
			p1 = NULL;
		}
		if (flag == 1) {
			break;
		}
		tail = tail->next;
		count2++;
	}
	if (flag2 == -1 || flag == 2 && flag2 == 0) {
		printf("没找到\n");
	}
	return head;
}
list replace(list head)
{
	char ch[LEN] = { 0 }, ch1[LEN] = { 0 }, *p, *p1 = NULL, ch2, *p2 = NULL, q, ch3[LEN], ch4;
	int count = 0, count1 = 0, flag = 0, count2 = 1, length, flag2 = -1, count4;
	list tail = head;
	tail = tail->next;
	printf("请输入待替换的字符串：");
	//scanf("%c", &q);
	scanf("%s", ch);
	printf("替换为：");
	scanf("%c", &q);
	scanf("%[^\n]s", ch3);
	count = mystrlen(ch3);
	count4 = mystrlen(ch);
	while (tail != NULL) {
		p2 = p = tail->s;
		mystrcpy(ch1, tail->s);
		length = mystrlen(tail->s);
		while ((p + count4 - 1) < (p2 + length))
		{
			p1 = search(p, ch);
			if (p1 != NULL) {
				printf("第%d行：%s\n", count2, p2);
				printf("第%d个字符处找到。是否替换(Y/N)？", ++count1);
				scanf("%c", &q);
				scanf("%c", &ch4);
				if (ch4 == 'Y') {
					int cnt, cnt1, cnt2 = 0;
					cnt = mystrlen(ch);
					cnt1 = mystrlen(ch3);
					//如果替换和待替换字符串大小不一致对字符串进行调整。
					if (cnt > cnt1) {
						while (p1[cnt2 + (cnt - cnt1)] != '\0') {
							p1[cnt2] = p1[cnt2 + (cnt - cnt1)];
							cnt2++;
						}
						p1[cnt2] = '\0';
					}
					else if (cnt < cnt1) {
						cnt2 = mystrlen(p1);
						while (cnt2 > 0) {
							p1[cnt2 + (cnt1 - cnt)] = p1[cnt2];
							cnt2--;
						}
					}
					for (int count1 = 0; count1 < count; count1++) {
						p1[count1] = ch3[count1];
					}
				}
				printf("继续替换吗(Y/N)?");
				scanf("%c", &q);
				scanf("%c", &ch2);
				flag2 = 1;
				if (ch2 == 'N') {
					flag = 1;
					break;
				}
				else {
					flag = 2;
					flag2 = 0;
				}
			}
			else {
				break;
			}
			p = p1;
			p++;
			p1 = NULL;
		}
		if (flag == 1) {
			break;
		}
		tail = tail->next;
		count2++;
	}
	if (flag2 == -1 || flag == 2 && flag2 == 0) {
		printf("没找到\n");
	}
	return head;
}
list save(list head)
{
	fp=fopen(name, "w");
	list tail = head;
	tail = tail->next;
	while (tail!=NULL)
	{
		fprintf(fp,"%s\n", tail->s);
		tail = tail->next;
	}
	printf("Press any key to continue\n");
	system("pause");
	return head;
}
list quitedit(list head)
{
	list tail, pre;
	pre = tail = head->next;
	while (tail != NULL)
	{
		if (tail->next != NULL) {
			tail = tail->next;
		}
		else {
			tail = NULL;
		}
		free(pre);
		pre = tail;

	}
	free(head);
	head = NULL;
	return head;
}
