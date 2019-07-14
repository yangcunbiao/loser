#include"lift.h"

int main() {
	long int time = 0;
	int a = 0, j = 1;
	long int Time = 0;
	cout << "请输入时钟终值:";
	cin >> Time;
	cout << endl;
	cout << "请输入共有几位乘客使用电梯：";
	cin >> a;
	passenger* people = new passenger[a + 1];
	for (int i = 1; i < a + 1; i++) {
		people[i].setdata(i);
		cout << endl;
	}
	elevator x;
	for (int b = 1; b < a + 1; b++) {
		if (people[b].getwhenwait() > Time)Time = people[b].getwhenwait();
	}
	for (; time < Time; time++) {
		cout << time << "t时刻  ";
		for (int i = 1; i < a + 1; i++) {
			if (people[i].getwhenwait() == time)x.addpassenger(people[i]);
		}
		cout << "电梯在" << ((x.getfloor()==1)?(-1):(x.getfloor()-1)) << "层  ";
		x.JudgeGiveUp(time);
		cout << endl;
	}
	delete[]people;
	return 0;
}

