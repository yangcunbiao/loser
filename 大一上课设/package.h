#include<stdio.h>
#include<stdlib.h>
#define LEN 500
struct node {
	char s[LEN];
	struct node *next;
};
typedef struct node* list;

FILE *fp = NULL;//�ļ�ָ��
char name[100];//����ļ���
char q;//���ڶ����س�

void menu();//����˵�
void reporterror();//�������ָ���
int mystrlen(const char *);//�����ַ�������
char* mystrcpy(char *, const char*);//�����ַ���
void mystrcat(char *, const char *);//�����ַ���
int mystrcmp(const char*, const char *);//�ַ����ȴ�С
int cot(list);//�����ļ�����
list turnto(int l,list head);//���ص�l-1�еĽڵ�;
char *search(char *s, char *t);//�����ַ������ҵ������׵�ַ��


list open(FILE *);//���ļ�����������
list print(list);//��ʾ�ļ�����
list insert(list);//������
list dele(list);//ɾ����
list copy(list);//������
list modify(list);//�޸���
list find(list);//�����ַ���
list replace(list);//�滻�ַ���
list save(list);//�����˳�
list quitedit(list);//�����༭

//����
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
void menu()
{
	printf("��ѡ��1.���ļ�(�»��)  2.��ʾ�ļ�����\n");
	printf("        3.������  4.ɾ����  5.������  6.�޸���\n");
	printf("        7.�����ַ���        8.�滻�ַ���\n");
	printf("        9.�����˳�          0.�����༭\n");
}
void reporterror()
{
	printf("ָ�����\n");
	printf("������0~9\n");
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
	int lon;//�ַ�������
	list tail = NULL, p = NULL;
	head = NULL;
	head = (list)malloc(sizeof(struct node));
	head->next = NULL;
	tail = head;
	printf("�������ļ�(�ɰ����̷���·����������19���ַ�)��");
	scanf("%c", &q);
	scanf("%[^\n]s", name);
	lon = mystrlen(name);
	if (name[lon - 1] != 't' || name[lon - 2] != 'x' || name[lon - 3] != 't' || name[lon - 4] != '.') {
		printf("�ļ���ʽ����\n");
		return head;
	}
	fp = fopen(name, "r");
	//�ж��ļ����Ƿ�ɹ�����Ļ��Զ��������ļ�
	if (fp == NULL) {
		printf("�ļ������ڣ��Զ������ļ�\n");
		fp = fopen(name, "w");
	}
	else {
		printf("�򿪳ɹ���\n");
	}
	//β�巨��������
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
	int count = 1;//����������
	list tail = head->next;

	if (head ->next!= NULL){//�ļ�������������ݣ�û������ļ�Ϊ�ա�
		while (tail != NULL) {
			printf("%d��%s\n", count, tail->s);
			tail = tail->next;
			count++;
		}
	}
	else {
		printf("�ļ�Ϊ��\n");
	}

	return head;
}
list insert(list head)
{
	int l, m;
	list tail = NULL, p = NULL, head1 = NULL, tail1 = NULL;
	printf("��ǰ��%d��\n", cot(head));
	printf("�ڵ�l��ǰ����m�У�������l m��");
	scanf("%d %d", &l, &m);
	if (l > 0 && l <= cot(head)+1) {}//�ж�������к��Ƿ��ڷ�Χ�ڡ�
	else {
		printf("�����кŴ���\n");
		return head;
	}
	
	printf("\n��˳���������������ݣ�\n");
	//��������ַ�����������
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
	//���������������ԭ����
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
	printf("��ǰ��%d�С�\n", cot(head));
	printf("�ӵ�l����ɾ��m�У���������l m:");
	
	scanf("%d %d", &l, &m);
	if (l > 0 && l <= cot(head)&&m<=cot(head)+1-l){}//�ж�����������Ƿ��ڷ�Χ�ڡ�
	else if(l<0||l>cot(head)){
		printf("ɾ���кŴ���.\n");
		return head;
	}
	else {
		printf("ɾ���й���.\n");
		return head;
	}
	//��Ҫɾ���Ĳ��ֶϿ�
	tail = turnto(l, head);
	tail1=head1 = tail->next;
	for (int count = 1; count < m; count++) {
		tail1 = tail1->next;
	}
	tail->next = tail1->next;
	//�ͷſռ䡣
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
	list head1 = NULL, tail = NULL, tail1 = NULL, p = NULL, tail2 = NULL;//head1Ϊ�������ͷ��tail1Ϊ�������β��tailΪ���ӵĽڵ㣬tail2�����������Ʋ��֡�
	printf("��ǰ��%d��\n", cot(head));
	printf("�ѵ�l��ʼ��m�в���ԭk��ǰ��������l m k��");
	scanf("%d %d %d", &l, &m, &k);
	if (l > 0 && (l <= cot(head) + 1) && (cot(head) + 1 - l >= m) && k > 0 && k <= cot(head) + 1) {}
	else {
		printf("��������\n");
		return head;
	}
	//�����Ʋ��ִ���������
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
	//������������ԭ����Ĳ���λ��
	if (tail1->next != NULL) {
		tail1 = tail1->next;
	}
	tail1->next = tail->next;
	tail->next = head1;

	return head;
}
list modify(list head)
{
	int m;//�޸ĵ��к�
	list tail;//�޸��еĽڵ�
	printf("��������޸ĵ��кţ�");
	scanf("%d", &m);
	if (head->next == NULL) {
		printf("�ļ�Ϊ���޷��޸�\n");
		return head;
	}
	if (m < 0 || m > cot(head)) {
		printf("������кŴ���\n");
		return head;
	}
	tail = turnto(m, head);
	tail = tail->next;
	printf("%d:%s\n", m, tail->s);
	printf("�����������ݣ�");
	scanf("%c", &q);
	scanf("%[^\n]s", tail->s);
	return head;
}
list find(list head)
{
	char ch[LEN] = { 0 }, ch1[LEN] = { 0 }, *p, *p1 = NULL, ch2, *p2 = NULL, q;//chװ�����ҵ��ַ�����ch1װ�ҵ������е��ַ�����p1��pָ�������е��ַ���
	int count = 0, count1 = 0, flag = 0, count2 = 1, length, flag2 = -1;//count�Ǵ��滻�ַ����ĳ��ȣ�count1����ͳ���ҵ����ַ���������count2��¼�ڼ��У�flag��������ѭ����flag2���ڼ�¼״̬��
	list tail = head;
	tail = tail->next;
	printf("����������ҵ��ַ�����");
	scanf("%s", ch);
	count = mystrlen(ch);
	//�����ַ���
	while (tail != NULL) {
		//�м�
		p2 = p = tail->s;
		mystrcpy(ch1, tail->s);
		length = mystrlen(tail->s);
		//����
		while ((p + count - 1) < (p2 + length))
		{
			p1 = search(p, ch);
			if (p1 != NULL) {
				printf("��%d�У�%s\n", count2, ch1);
				printf("��%d���ַ����ҵ�������������(Y/N)��", ++count1);
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
		printf("û�ҵ�\n");
	}
	return head;
}
list replace(list head)
{
	char ch[LEN] = { 0 }, ch1[LEN] = { 0 }, *p, *p1 = NULL, ch2, *p2 = NULL, q, ch3[LEN], ch4;
	int count = 0, count1 = 0, flag = 0, count2 = 1, length, flag2 = -1, count4;
	list tail = head;
	tail = tail->next;
	printf("��������滻���ַ�����");
	//scanf("%c", &q);
	scanf("%s", ch);
	printf("�滻Ϊ��");
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
				printf("��%d�У�%s\n", count2, p2);
				printf("��%d���ַ����ҵ����Ƿ��滻(Y/N)��", ++count1);
				scanf("%c", &q);
				scanf("%c", &ch4);
				if (ch4 == 'Y') {
					int cnt, cnt1, cnt2 = 0;
					cnt = mystrlen(ch);
					cnt1 = mystrlen(ch3);
					//����滻�ʹ��滻�ַ�����С��һ�¶��ַ������е�����
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
				printf("�����滻��(Y/N)?");
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
		printf("û�ҵ�\n");
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
