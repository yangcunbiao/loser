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
	int Dir = -1;//判断上下的情况
public:
	state getnowState()const;
	void setnowState(state t);
	int getfloor()const;
	void setfloor(int floor1);
	int getAll()const;
	void setAll(int num);//num为外部上电梯的人数
	int getDir()const;
	void setDir(int x);
	void addpassenger(const passenger& x);//添加乘客
	bool NoPassenger();//判断是否有乘客请求
	void JudgeDirction();//判断电梯行走方向
	bool JudgeOpen();//判断是否开门
	void Open();//电梯门打开
	bool JudgeOut();//判断乘客出去
	void OUT();//乘客出去
	bool JudgeIn();//判断乘客进入
	void IN();//乘客进入
	void Close();//关门
	void MoveUp();//向上移动
	void MoveDown();//向下移动
	void JudgeClose();//40t时间来判断是否关门
	void MoveDirction(const int floor1);//用来改变电梯的状态
	void JudgeGiveUp(int waittime);//判断是否有人放弃，用在函数最开始
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
	cout << " 第" << x.getID() << "名乘客进入等待队列 ";
}
bool elevator::NoPassenger() {
	//用于判断电梯是否接收乘客的请求
	if (getnowState() == Waiting) {
		if (holdtime == 300 && floor != 2) {
			//如果等够了300t并且不在1楼的话，开始下行
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
			//如果电梯本身在一楼则不需要进行操作
			cout << "电梯空闲无人，正在等待";
			holdtime = 0;
			return true;
		}
		else if (All == 0 && empty() == true) {
			cout << "电梯空闲无人，正在等待";
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
	//使用该函数进行判断电梯的走向
	near = floor;//初始化near的值，为防止不满足条件的情况出现时依旧可以使用MoveDirction函数
	int upoutfar = 0, downoutfar = 10;//定义2个记录上下出去最远请求的变量
	int upinfar = 0, downinfar = 10;//定义2个记录上下进来最远请求的变量
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
		if (getAll() != 0) {//电梯里依旧有人
			//此时需要区分电梯的运行方向，分两种情况来处理（目前还未处理）
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
		if (empty() == false) {//电梯外等待的人不为空
			PNODE ptemp = p_head->next;
			while (ptemp != NULL) {
				if (getDir() == 1) {//只接上行乘客
					if (ptemp->data.getnowfloor() > floor) {//乘客所处楼层在电梯楼层上，这样才有可能电梯前往接人
						//开始检索在链表中的乘客，并且进行判断是否有要上行的
						if (ptemp->data.getgofloor() > ptemp->data.getnowfloor()) {
							//代表此人是上行，并且是在电梯运行方向的楼上，需要前往接人
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

				else if (getDir() == 0) {//只接下行乘客
					if (ptemp->data.getnowfloor() < floor) {//乘客所处楼层在电梯楼层下，这样才有可能电梯前往接人
								//开始检索在链表中的乘客，并且进行判断是否有要下行的
						if (ptemp->data.getgofloor() < ptemp->data.getnowfloor()) {
							//代表此人是下行，并且是在电梯运行方向的楼下，需要前往接人
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
			int Time_now = ptemp->data.getwhenwait();//用于记录最先按的人
			time_now = Time_now;
			if (ptemp->data.getwhenwait() < time_now) {//挑选出最先按键的人，然后进行改变电梯的方向
				time_now = ptemp->data.getwhenwait();
			}
			ptemp = ptemp->next;
		}
		ptemp = p_head->next;
		while (ptemp != NULL) {
			int up(floor), down(floor);
			if (ptemp->data.getwhenwait() == time_now) {
				int x = ptemp->data.getgofloor() - ptemp->data.getnowfloor();
				//此时会出现4种情况，并且只会有2种是电梯上行，2种是电梯下行
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
				if (down != floor && up != floor) {//当上下同时有人请求时，满足先上的原则
					setnowState(Up); near = upinfar; setDir(1);
				}
				else if (up != floor) {//只有上行的请求
					setnowState(Up); near = upinfar; setDir(1);
				}
				else if (down != floor) {//只有下行的请求
					setnowState(Down); near = downinfar; setDir(0);
				}
				if (floor == 1) { setnowState(Up); setDir(1); }
			}
			ptemp = ptemp->next;
		}
		if (near == floor)  Open();
	}
	if (State == Up) {
		if (getAll() != 0) {//电梯里有人
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
		if (getAll() != 0) {//电梯里有人
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

bool elevator::JudgeOpen() {//判断此楼层是否有人需要进出
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
		cout << "电梯开门中";
		return;
	}
	else {//开门完成后
		record = 0;
		cout << "开门完成";
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
			cout << "乘客正在下电梯";
			if (DiantiLi[floor] != 0) {
				cout << "在该层一共下去" << DiantiLi[floor] << "个人";
				setAll(-DiantiLi[floor]);
				DiantiLi[floor] = 0;
			}
			setnowState(Out);
			return;
		}
		if (getnowState() == Out) {
			record++;
			cout << "乘客正在下电梯";
			return;
		}
	}
	else {
		cout << "电梯里需要下的乘客都已下去";
		record = 0;
		setnowState(Opened);
	}
}

bool elevator::JudgeIn() {//如果电梯未满，则返回true，可以继续进人
	//目前需要完善，因为是先把人删除输入进数组，所以需要进行有个判断
	if (getAll() != 13) {
		if (!empty()) {//不为空则执行if语句
			PNODE ptemp = p_head->next; int upnum1 = 0, downnum1 = 0;
			while (ptemp != NULL) {
				if (ptemp->data.getnowfloor() == floor) {
					if ((ptemp->data.getnowfloor() < ptemp->data.getgofloor()) && (getDir() > 0)) {
						//乘客是往上走的
						return true;
					}
					if ((ptemp->data.getnowfloor() > ptemp->data.getgofloor()) && (getDir() == 0)) {
						//乘客下行
						return true;
					}
					if (near == ptemp->data.getnowfloor()) {
						//达到了最大请求楼层，如果是与电梯方向同向，则不改变方向，并且允许进入
						//如果不与电梯同向，则改变方向，如果两个情况都有，就优先满足同方向的
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
					if (ptemp->data.getnowfloor() == floor) {//首先人得在电梯楼层，这才能进行判定
						if ((ptemp->data.getnowfloor() < ptemp->data.getgofloor()) && (getDir() > 0)) {
							//乘客是往上走的
							cout << "第" << ptemp->data.getID() << "个乘客正在进入电梯";
							DiantiLi[ptemp->data.getgofloor()] += 1;
							setAll(1);
							Remove(ptemp->data.getID());
							setnowState(In);
							return;
						}
						if ((ptemp->data.getnowfloor() > ptemp->data.getgofloor()) && (getDir() == 0)) {
							//乘客下行
							cout << "第" << ptemp->data.getID() << "个乘客正在进入电梯";
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
				cout << "乘客正在进入电梯";
				return;
			}
		}
		else {
			cout << "乘客已经进入电梯";
			record = 0;
			setnowState(Opened);
		}
	}
	else {
		cout << "电梯内人数已经达到最大值";
		setnowState(Closing);
	}
}

void elevator::Close() {
	if (record < close) {
		record++;
		setnowState(Closing);
		cout << "电梯正在关门中";
	}
	else {
		record = 0;
		cout << "电梯已经关门";
		setnowState(Closed);
		if (near == floor) {//电梯已经到达最大请求楼层，可能会出现4种情况
			if (empty() == false || getAll() != 0) {//等待队列有人或电梯里也有人
				PNODE ptemp = p_head->next; int OutPeople = 0;
				while (ptemp != NULL) {
					if (ptemp->data.getnowfloor() == floor)OutPeople += 1;
					if (getAll() != 0 && OutPeople != 0) {//电梯里有人，外面有人       判断去的方向
						if (getDir() == 1 && (ptemp->data.getgofloor() > floor)) {//电梯上行，乘客上行，开门
							setnowState(Opening);
						}
						else if (getDir() == 0 && (ptemp->data.getgofloor() < floor)) {//电梯下行，乘客下行，开门
							setnowState(Opening);
						}
					}
					if (getAll() == 0 && OutPeople != 0) {//电梯没人，外面有人
						if (getDir() == 1) {//电梯上行
							if (ptemp->data.getgofloor() > floor)
								setnowState(Opening);
							else if (ptemp->data.getgofloor() < floor) {
								setDir(0); setnowState(Opening);
							}
						}
						if (getDir() == 0) {//电梯下行
							if (ptemp->data.getgofloor() < floor)
								setnowState(Opening);
							else if (ptemp->data.getgofloor() > floor) {
								setDir(1); setnowState(Opening);
							}
						}
					}
					if (getAll() != 0 && OutPeople == 0) {
						//电梯里有人，外面没人，此时应该分是否继续送乘客上行或者下行，首先遍历数组得到乘客要去几层
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
			else if (empty() == true && getAll() == 0) {//等待队列没人，电梯也没人
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
		cout << "电梯正在上楼";
		return;
	}
	else {
		floor++;
		record = 0;
		if (JudgeOpen() == false)
			MoveUp();
		else {
			cout << "电梯正在上楼";
			setnowState(Opening);
		}
	}

}

void elevator::MoveDown() {
	if (record < down) {
		record++;
		cout << "电梯正在下楼";
		return;
	}
	else {
		floor--;
		record = 0;
		if (JudgeOpen() == false)MoveDown();
		else {
			cout << "电梯正在下楼";
			setnowState(Opening);
		}
	}
}

void elevator::JudgeClose() {
	if (getnowState() == Opened) {
		if (record < test) {
			record++;
			cout << "正在关门检测";
			return;
		}
		else {
			cout << "关门检测结束";
			if (getnowState() == Opened) {
				record = 0;
				Close();
				return;
			}
			/*else {//疑似可以删除    
				record = 0;
				return;
			}*/
		}
	}
	else return;
}

void elevator::MoveDirction(const int near) {
	//near为乘客的请求最远的楼层
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
	//一进入系统则先判断该时刻是否有人放弃
	//waittime为现在的时间，用于和乘客等待的时间+wait来进行判断乘客是否放弃
	PNODE ptemp = p_head->next;
	while (ptemp != NULL) {
		if ((ptemp->data.getwhenwait() + peoplewait) <= waittime) {
			cout << "第" << ptemp->data.getID() << "名乘客已放弃等待  ";
			Remove(ptemp->data.getID());
		}
		ptemp = ptemp->next;
	}
	NoPassenger();
}

#endif // ELEVATOR_H
#pragma once

