#include"lift.h"

int main() {
	long int time = 0;
	int a = 0, j = 1;
	long int Time = 0;
	cout << "������ʱ����ֵ:";
	cin >> Time;
	cout << endl;
	cout << "�����빲�м�λ�˿�ʹ�õ��ݣ�";
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
		cout << time << "tʱ��  ";
		for (int i = 1; i < a + 1; i++) {
			if (people[i].getwhenwait() == time)x.addpassenger(people[i]);
		}
		cout << "������" << ((x.getfloor()==1)?(-1):(x.getfloor()-1)) << "��  ";
		x.JudgeGiveUp(time);
		cout << endl;
	}
	delete[]people;
	return 0;
}

