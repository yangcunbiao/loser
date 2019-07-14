#ifndef ELEVATOR_H
#define ELEVATOR_H
#include"Node.h"
#include"passenger.h"

enum state {
	Opening,
	Opened,
	Closing,
	Closed,
	Waiting,
	Up,
	Down,
	In,
	Out,
	//Decelerate
};

int holdtime = 0, record = 0, near = 0;
enum timeX
{
	test = 40,
	open = 20,
	close = 20,
	in = 25,
	out = 25,
	//quick = 15,
	up = 20,
	//updecelerate = 14,
	down = 20,
	//downdecelerate = 23,
	peoplewait = 300,
	wait = 300
};

class elevator {
private:
	state State = Waiting;
	int floor = 2;
	PNODE Wait = p_head;
	int DiantiLi[10] = { 0 };
	int All = 0;
	int Dir = -1;//�ж����µ����
public:
	state getnowState()const;
	void setnowState(state t);
	int getfloor()const;
	void setfloor(int floor1);
	int getAll()const;
	void setAll(int num);//numΪ�ⲿ�ϵ��ݵ�����
	int getDir()const;
	void setDir(int x);
	void addpassenger(const passenger& x);//��ӳ˿�
	bool NoPassenger();//�ж��Ƿ��г˿�����
	void JudgeDirction();//�жϵ������߷���
	bool JudgeOpen();//�ж��Ƿ���
	void Open();//�����Ŵ�
	bool JudgeOut();//�жϳ˿ͳ�ȥ
	void OUT();//�˿ͳ�ȥ
	bool JudgeIn();//�жϳ˿ͽ���
	void IN();//�˿ͽ���
	void Close();//����
	void MoveUp();//�����ƶ�
	void MoveDown();//�����ƶ�
	void JudgeClose();//40tʱ�����ж��Ƿ����
	void MoveDirction(const int floor1);//�����ı���ݵ�״̬
	void JudgeGiveUp(int waittime);//�ж��Ƿ����˷��������ں����ʼ
};

state elevator::getnowState()const {
	return State;
}
void elevator::setnowState(state t) {
	State = t;
}
int elevator::getfloor()const {
	return floor;
}
void elevator::setfloor(int floor1) {
	floor = floor1;
}
int elevator::getAll()const {
	return All;
}
void elevator::setAll(int num) {
	All += num;
}
int elevator::getDir()const {
	return Dir;
}
void elevator::setDir(int num) {
	Dir = num;
}
void elevator::addpassenger(const passenger& x) {
	append(x);
	cout << " ��" << x.getID() << "���˿ͽ���ȴ����� ";
}
bool elevator::NoPassenger() {
	//�����жϵ����Ƿ���ճ˿͵�����
	if (getnowState() == Waiting) {
		if (holdtime == 300 && floor != 2) {
			//����ȹ���300t���Ҳ���1¥�Ļ�����ʼ����
			if (floor > 2) {
				setnowState(Down);
				setDir(0);
				MoveDown();
			}
			else {
				setnowState(Up);
				setDir(1);
				MoveUp();
			}
			holdtime = 0;
			return true;
		}
		else if (holdtime == 300 && floor == 2) {
			//������ݱ�����һ¥����Ҫ���в���
			cout << "���ݿ������ˣ����ڵȴ�";
			holdtime = 0;
			return true;
		}
		else if (All == 0 && empty() == true) {
			cout << "���ݿ������ˣ����ڵȴ�";
			holdtime++;
			return true;
		}
		else {
			JudgeDirction();
			return false;
		}
	}
	else {
		JudgeDirction();
		return false;
	}
}

void elevator::JudgeDirction() {
	//ʹ�øú��������жϵ��ݵ�����
	near = floor;//��ʼ��near��ֵ��Ϊ��ֹ�������������������ʱ���ɿ���ʹ��MoveDirction����
	int upoutfar = 0, downoutfar = 10;//����2����¼���³�ȥ��Զ����ı���
	int upinfar = 0, downinfar = 10;//����2����¼���½�����Զ����ı���
	if (State == Closed) {
		if (getAll() == 0 && empty() == true) {
			setnowState(Waiting);
			return;
		}
		if (floor == 1) {
			setnowState(Up); setDir(1);
		}
		if (floor == 5) {
			setnowState(Down); setDir(0);
		}
		if (getAll() != 0) {//��������������
			//��ʱ��Ҫ���ֵ��ݵ����з��򣬷��������������Ŀǰ��δ����
			for (int i = 1; i < 10; i++) {
				if (DiantiLi[i] != 0) {
					near = i;
					if (i > floor) {
						upinfar = i;
						setnowState(Up);
						setDir(1);
						break;
					}
					else if (i < floor) {
						downinfar = i;
						setnowState(Down);
						setDir(0);
						break;
					}
				}
			}
		}
		if (empty() == false) {//������ȴ����˲�Ϊ��
			PNODE ptemp = p_head->next;
			while (ptemp != NULL) {
				if (getDir() == 1) {//ֻ�����г˿�
					if (ptemp->data.getnowfloor() > floor) {//�˿�����¥���ڵ���¥���ϣ��������п��ܵ���ǰ������
						//��ʼ�����������еĳ˿ͣ����ҽ����ж��Ƿ���Ҫ���е�
						if (ptemp->data.getgofloor() > ptemp->data.getnowfloor()) {
							//������������У��������ڵ������з����¥�ϣ���Ҫǰ������
							if (ptemp->data.getgofloor() > upoutfar)upoutfar = ptemp->data.getgofloor();
						}
						if (ptemp->data.getgofloor() < ptemp->data.getnowfloor()) {
							if (ptemp->data.getnowfloor() > upoutfar)upoutfar = ptemp->data.getnowfloor();
						}
					}
					if (upinfar == 0 && upoutfar == 0) { setnowState(Down); setDir(0); }
					if (upinfar <= upoutfar)near = upoutfar;
					else near = upinfar;
				}

				else if (getDir() == 0) {//ֻ�����г˿�
					if (ptemp->data.getnowfloor() < floor) {//�˿�����¥���ڵ���¥���£��������п��ܵ���ǰ������
								//��ʼ�����������еĳ˿ͣ����ҽ����ж��Ƿ���Ҫ���е�
						if (ptemp->data.getgofloor() < ptemp->data.getnowfloor()) {
							//������������У��������ڵ������з����¥�£���Ҫǰ������
							if (ptemp->data.getgofloor() < downoutfar)downoutfar = ptemp->data.getgofloor();
						}
						if (ptemp->data.getgofloor() > ptemp->data.getnowfloor()) {
							if (ptemp->data.getnowfloor() < downoutfar)downoutfar = ptemp->data.getnowfloor();
						}
					}
					if (downinfar == 10 && downoutfar == 10) { setnowState(Up); setDir(1); }
					if (downinfar <= downoutfar)near = downinfar;
					else near = downoutfar;
				}
				ptemp = ptemp->next;
			}
		}

	}
	if (State == Waiting) {
		PNODE ptemp = p_head->next;
		int time_now = 0;
		while (ptemp != NULL) {
			int Time_now = ptemp->data.getwhenwait();//���ڼ�¼���Ȱ�����
			time_now = Time_now;
			if (ptemp->data.getwhenwait() < time_now) {//��ѡ�����Ȱ������ˣ�Ȼ����иı���ݵķ���
				time_now = ptemp->data.getwhenwait();
			}
			ptemp = ptemp->next;
		}
		ptemp = p_head->next;
		while (ptemp != NULL) {
			int up(floor), down(floor);
			if (ptemp->data.getwhenwait() == time_now) {
				int x = ptemp->data.getgofloor() - ptemp->data.getnowfloor();
				//��ʱ�����4�����������ֻ����2���ǵ������У�2���ǵ�������
				if ((x > 0 && (ptemp->data.getnowfloor() > floor)) || (x < 0 && (ptemp->data.getnowfloor() > floor))) {
					setnowState(Up);
					setDir(1);
					upinfar = ptemp->data.getnowfloor();
					if (up < upinfar) {
						up = upinfar;
					}
				}
				else if ((x > 0 && (ptemp->data.getnowfloor() < floor)) || (x < 0 && (ptemp->data.getnowfloor() < floor))) {
					setnowState(Down);
					setDir(0);
					downinfar = ptemp->data.getnowfloor();
					if (down > downinfar) {
						down = downinfar;
					}
				}
				if (down != floor && up != floor) {//������ͬʱ��������ʱ���������ϵ�ԭ��
					setnowState(Up); near = upinfar; setDir(1);
				}
				else if (up != floor) {//ֻ�����е�����
					setnowState(Up); near = upinfar; setDir(1);
				}
				else if (down != floor) {//ֻ�����е�����
					setnowState(Down); near = downinfar; setDir(0);
				}
				if (floor == 1) { setnowState(Up); setDir(1); }
			}
			ptemp = ptemp->next;
		}
		if (near == floor)  Open();
	}
	if (State == Up) {
		if (getAll() != 0) {//����������
			for (int i = 1; i < 10; i++) {
				if (DiantiLi[i] != 0) {
					if (i >= near) {
						upinfar = i;
					}
				}
			}
		}
		if (empty() == false) {
			PNODE ptemp = p_head->next;
			while (ptemp != NULL) {
				if (ptemp->data.getnowfloor() >= near) {
					if (ptemp->data.getgofloor() >= upoutfar) {
						upoutfar = ptemp->data.getgofloor();
					}
					if (ptemp->data.getnowfloor() >= upoutfar) {
						upoutfar = ptemp->data.getnowfloor();
					}
				}
				ptemp = ptemp->next;
			}
		}
		if (getAll() == 0 && empty() == true)near = 2;
		else if (upinfar >= upoutfar)near = upinfar;
		else near = upoutfar;
	}
	if (State == Down) {
		//downinfar = 10, downoutfar = 10;
		if (getAll() != 0) {//����������
			for (int i = 1; i < 10; i++) {
				if (DiantiLi[i] != 0) {
					if (i <= near) {
						downinfar = i;
						break;
					}
				}
			}
		}
		if (empty() == false) {
			PNODE ptemp = p_head->next;
			while (ptemp != NULL) {
				if (ptemp->data.getnowfloor() <= near) {
					if (ptemp->data.getnowfloor() <= downoutfar) {
						downoutfar = ptemp->data.getnowfloor();
					}
					if (ptemp->data.getgofloor() <= downoutfar) {
						downoutfar = ptemp->data.getgofloor();
					}
				}
				ptemp = ptemp->next;
			}
		}
		if (getAll() == 0 && empty() == true)near = 2;
		else if (downinfar >= downoutfar)near = downoutfar;
		else near = downinfar;
	}
	MoveDirction(near);
}

bool elevator::JudgeOpen() {//�жϴ�¥���Ƿ�������Ҫ����
	if (JudgeIn() || JudgeOut()) {
		Open();
		return true;
	}
	else return false;
}

void elevator::Open() {
	if (getnowState() != Opening) {
		setnowState(Opening);
		record = 0;
		return;
	}
	if (record < open) {
		record++;
		cout << "���ݿ�����";
		return;
	}
	else {//������ɺ�
		record = 0;
		cout << "�������";
		setnowState(Opened);
		if (JudgeOut())OUT();
		if (JudgeIn())IN();
		JudgeClose();
	}
}

bool elevator::JudgeOut() {
	if (getAll() != 0) {
		int j = floor;
		if (DiantiLi[j] != 0)return true;
	}
	return false;
}

void elevator::OUT() {
	if (record < out) {
		if (getnowState() == Opened) {
			record++;
			cout << "�˿������µ���";
			if (DiantiLi[floor] != 0) {
				cout << "�ڸò�һ����ȥ" << DiantiLi[floor] << "����";
				setAll(-DiantiLi[floor]);
				DiantiLi[floor] = 0;
			}
			setnowState(Out);
			return;
		}
		if (getnowState() == Out) {
			record++;
			cout << "�˿������µ���";
			return;
		}
	}
	else {
		cout << "��������Ҫ�µĳ˿Ͷ�����ȥ";
		record = 0;
		setnowState(Opened);
	}
}

bool elevator::JudgeIn() {//�������δ�����򷵻�true�����Լ�������
	//Ŀǰ��Ҫ���ƣ���Ϊ���Ȱ���ɾ����������飬������Ҫ�����и��ж�
	if (getAll() != 13) {
		if (!empty()) {//��Ϊ����ִ��if���
			PNODE ptemp = p_head->next; int upnum1 = 0, downnum1 = 0;
			while (ptemp != NULL) {
				if (ptemp->data.getnowfloor() == floor) {
					if ((ptemp->data.getnowfloor() < ptemp->data.getgofloor()) && (getDir() > 0)) {
						//�˿��������ߵ�
						return true;
					}
					if ((ptemp->data.getnowfloor() > ptemp->data.getgofloor()) && (getDir() == 0)) {
						//�˿�����
						return true;
					}
					if (near == ptemp->data.getnowfloor()) {
						//�ﵽ���������¥�㣬���������ݷ���ͬ���򲻸ı䷽�򣬲����������
						//����������ͬ����ı䷽���������������У�����������ͬ�����
						if (getDir() == 1||getDir()==-1) {
							if (ptemp->data.getnowfloor() < ptemp->data.getgofloor()) {
								setDir(1); upnum1++;
							}
							if (ptemp->data.getnowfloor() > ptemp->data.getgofloor()) {
								setDir(0); downnum1++;
							}
							if (upnum1 != 0 && downnum1 != 0)setDir(1);
						}
						else if (getDir() == 0) {
							if (ptemp->data.getnowfloor() < ptemp->data.getgofloor()) {
								setDir(1); upnum1++;
							}
							if (ptemp->data.getnowfloor() > ptemp->data.getgofloor()) {
								setDir(0);  downnum1++;
							}
							if (upnum1 != 0 && downnum1 != 0)setDir(0);
						}
						return true;
					}
				}
				ptemp = ptemp->next;
			}
		}
	}
	return false;
}

void elevator::IN() {
	if (getAll() < 13) {
		if (record < in)
		{
			if (getnowState() == Opened) {
				record++;
				PNODE ptemp = p_head->next;
				while (ptemp != NULL) {
					if (ptemp->data.getnowfloor() == floor) {//�����˵��ڵ���¥�㣬����ܽ����ж�
						if ((ptemp->data.getnowfloor() < ptemp->data.getgofloor()) && (getDir() > 0)) {
							//�˿��������ߵ�
							cout << "��" << ptemp->data.getID() << "���˿����ڽ������";
							DiantiLi[ptemp->data.getgofloor()] += 1;
							setAll(1);
							Remove(ptemp->data.getID());
							setnowState(In);
							return;
						}
						if ((ptemp->data.getnowfloor() > ptemp->data.getgofloor()) && (getDir() == 0)) {
							//�˿�����
							cout << "��" << ptemp->data.getID() << "���˿����ڽ������";
							DiantiLi[ptemp->data.getgofloor()] += 1;
							setAll(1);
							Remove(ptemp->data.getID());
							setnowState(In);
							return;
						}
					}
					ptemp = ptemp->next;
				}
			}
			if (getnowState() == In) {
				record++;
				cout << "�˿����ڽ������";
				return;
			}
		}
		else {
			cout << "�˿��Ѿ��������";
			record = 0;
			setnowState(Opened);
		}
	}
	else {
		cout << "�����������Ѿ��ﵽ���ֵ";
		setnowState(Closing);
	}
}

void elevator::Close() {
	if (record < close) {
		record++;
		setnowState(Closing);
		cout << "�������ڹ�����";
	}
	else {
		record = 0;
		cout << "�����Ѿ�����";
		setnowState(Closed);
		if (near == floor) {//�����Ѿ������������¥�㣬���ܻ����4�����
			if (empty() == false || getAll() != 0) {//�ȴ��������˻������Ҳ����
				PNODE ptemp = p_head->next; int OutPeople = 0;
				while (ptemp != NULL) {
					if (ptemp->data.getnowfloor() == floor)OutPeople += 1;
					if (getAll() != 0 && OutPeople != 0) {//���������ˣ���������       �ж�ȥ�ķ���
						if (getDir() == 1 && (ptemp->data.getgofloor() > floor)) {//�������У��˿����У�����
							setnowState(Opening);
						}
						else if (getDir() == 0 && (ptemp->data.getgofloor() < floor)) {//�������У��˿����У�����
							setnowState(Opening);
						}
					}
					if (getAll() == 0 && OutPeople != 0) {//����û�ˣ���������
						if (getDir() == 1) {//��������
							if (ptemp->data.getgofloor() > floor)
								setnowState(Opening);
							else if (ptemp->data.getgofloor() < floor) {
								setDir(0); setnowState(Opening);
							}
						}
						if (getDir() == 0) {//��������
							if (ptemp->data.getgofloor() < floor)
								setnowState(Opening);
							else if (ptemp->data.getgofloor() > floor) {
								setDir(1); setnowState(Opening);
							}
						}
					}
					if (getAll() != 0 && OutPeople == 0) {
						//���������ˣ�����û�ˣ���ʱӦ�÷��Ƿ�����ͳ˿����л������У����ȱ�������õ��˿�Ҫȥ����
						for (int i = 1; i < 10; i++) {
							if (DiantiLi[i] != 0) {
								if (i < floor) { setnowState(Down); setDir(0); }
								if (i > floor) { setnowState(Up); setDir(1); }
							}
						}

					}
					ptemp = ptemp->next;
				}
			}
			else if (empty() == true && getAll() == 0) {//�ȴ�����û�ˣ�����Ҳû��
				setnowState(Waiting); setDir(-1);
			}
		}
		else if (near != floor) {
			if (getDir() == 1) {
				setDir(1); setnowState(Up);
			}
			if (getDir() == 0) {
				setDir(0); setnowState(Down);
			}
		}
		NoPassenger();
	}
}

void elevator::MoveUp() {
	if (record < up) {
		record++;
		cout << "����������¥";
		return;
	}
	else {
		floor++;
		record = 0;
		if (JudgeOpen() == false)
			MoveUp();
		else {
			cout << "����������¥";
			setnowState(Opening);
		}
	}

}

void elevator::MoveDown() {
	if (record < down) {
		record++;
		cout << "����������¥";
		return;
	}
	else {
		floor--;
		record = 0;
		if (JudgeOpen() == false)MoveDown();
		else {
			cout << "����������¥";
			setnowState(Opening);
		}
	}
}

void elevator::JudgeClose() {
	if (getnowState() == Opened) {
		if (record < test) {
			record++;
			cout << "���ڹ��ż��";
			return;
		}
		else {
			cout << "���ż�����";
			if (getnowState() == Opened) {
				record = 0;
				Close();
				return;
			}
			/*else {//���ƿ���ɾ��    
				record = 0;
				return;
			}*/
		}
	}
	else return;
}

void elevator::MoveDirction(const int near) {
	//nearΪ�˿͵�������Զ��¥��
	if (near < floor) {
		setnowState(Down);
		setDir(0);
		MoveDown();
		return;
	}
	if (near > floor) {
		setnowState(Up);
		setDir(1);
		MoveUp();
		return;
	}
	if (getnowState() == Opening) {
		Open();
		return;
	}
	if (getnowState() == In) {
		IN();
		JudgeClose();
		return;
	}
	if (getnowState() == Out) {
		OUT();
		JudgeClose();
		return;
	}
	if (getnowState() == Opened) {
		JudgeClose();
		if (JudgeOut())OUT();
		if (JudgeIn())IN();
		return;
	}
	if (getnowState() == Closing) {
		Close();
		return;
	}
	if (near == floor && empty() == true && getAll() == 0) {
		setnowState(Waiting);
		NoPassenger();
		return;
	}
	if (near == floor) {
		setnowState(Opening);
		Open();
		return;
	}
}

void elevator::JudgeGiveUp(int waittime) {
	//һ����ϵͳ�����жϸ�ʱ���Ƿ����˷���
	//waittimeΪ���ڵ�ʱ�䣬���ںͳ˿͵ȴ���ʱ��+wait�������жϳ˿��Ƿ����
	PNODE ptemp = p_head->next;
	while (ptemp != NULL) {
		if ((ptemp->data.getwhenwait() + peoplewait) <= waittime) {
			cout << "��" << ptemp->data.getID() << "���˿��ѷ����ȴ�  ";
			Remove(ptemp->data.getID());
		}
		ptemp = ptemp->next;
	}
	NoPassenger();
}

#endif // ELEVATOR_H
#pragma once

