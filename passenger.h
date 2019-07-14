#ifndef PASSENGER_H
#define PASSENGER_H
#include<iostream>
using namespace std;

class passenger {
private:
	int ID;
	int nowfloor;
	int gofloor;
	int whenwait;
public:
	passenger();
	void setdata(int ID1);
	void setnowfloor(int nowfloor1);
	void setgofloor(int gofloor1);
	void setwhenwait(int whenwait1);
	int getnowfloor()const;
	int getgofloor()const;
	int getID()const;
	int getwhenwait()const;
};

passenger::passenger() {
	ID = 0;
	nowfloor = 0;
	gofloor = 0;
	whenwait = 0;
}

void passenger::setdata(int ID1) {
	ID = ID1; int i = 1;
	while (i) {
		cout << "请输入第" << ID << "位乘客的信息" << endl;
		cout << "该乘客目前在哪一层："; cin >> nowfloor;
		if (nowfloor == -1) { nowfloor = 1; }
		else { nowfloor++; }
		cout << "该乘客去哪一层："; cin >> gofloor;
		if (gofloor == -1) { gofloor = 1; }
		else { gofloor++; }
		cout << "该乘客何时上电梯："; cin >> whenwait;
		if (nowfloor > 5 || nowfloor < 1) {
			cout << "乘客目前的楼层有误，请重输入！" << endl;
		}
		if (gofloor > 5 || gofloor < 1) {
			cout << "乘客要去的楼层有误，请重输入！" << endl;
		}
		else i = 0;
	}
}

void passenger::setnowfloor(int nowfloor1) {
	nowfloor = nowfloor1;
}

void passenger::setgofloor(int gofloor1) {
	gofloor = gofloor1;
}

void passenger::setwhenwait(int whenwait1) {
	whenwait = whenwait1;
}

int passenger::getnowfloor()const {
	return nowfloor;
}

int passenger::getgofloor()const {
	return gofloor;
}

int passenger::getID()const {
	return ID;
}

int passenger::getwhenwait()const {
	return whenwait;
}

#endif // !PASSENGER_H
#pragma once
