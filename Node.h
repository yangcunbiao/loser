#ifndef NODE_H
#define NODE_H
#include<iostream>
#include"passenger.h"
using namespace std;

typedef struct node {
	passenger data;
	struct node* next;
}NODE, * PNODE;

NODE head;//头节点

PNODE p_head = &head;//头指针
PNODE p_tail = &head;//尾指针

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

void Remove(int ID) {//data为节点所存储的数据，查到就删除
	int pnew = ID;
	PNODE ptemp = p_head->next;
	if (ptemp->data.getID() == pnew) {
		if (ptemp == p_tail) {//如果就一个节点
			p_head->next = ptemp->next;
			p_tail = p_head;
			ptemp = NULL;
		}
		else { //如果是多个节点
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

