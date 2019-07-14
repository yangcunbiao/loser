#ifndef NODE_H
#define NODE_H
#include<iostream>
#include"passenger.h"
using namespace std;

typedef struct node {
	passenger data;
	struct node* next;
}NODE, * PNODE;

NODE head;//ͷ�ڵ�

PNODE p_head = &head;//ͷָ��
PNODE p_tail = &head;//βָ��

void append(passenger data) {
	PNODE pnew = (PNODE)malloc(sizeof(NODE));
	pnew->data = data; pnew->next = NULL;
	if (p_head == NULL) {
		p_head = pnew;
		p_tail = pnew;
	}
	else {
		p_tail->next = pnew;
		p_tail = pnew;
	}
}

bool empty() {
	if (p_head->next == NULL)return true;
	else return false;
}

void Remove(int ID) {//dataΪ�ڵ����洢�����ݣ��鵽��ɾ��
	int pnew = ID;
	PNODE ptemp = p_head->next;
	if (ptemp->data.getID() == pnew) {
		if (ptemp == p_tail) {//�����һ���ڵ�
			p_head->next = ptemp->next;
			p_tail = p_head;
			ptemp = NULL;
		}
		else { //����Ƕ���ڵ�
			p_head->next = ptemp->next;
			ptemp = NULL;
		}
	}
	while (ptemp != NULL) {
		if (ptemp->next->data.getID() == pnew) {
			if (ptemp->next == p_tail) {
				ptemp->next = NULL;
				p_tail = ptemp;
			}
			else ptemp->next = ptemp->next->next;
		}
		ptemp = ptemp->next;
	}
}

#endif // !NODE_H
#pragma once

