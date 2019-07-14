#include"package.h"
int main()
{
	list head = NULL;//带头结点的链表的头结点。
	list(*function[10])(list head);//函数指针
	function[0] = quitedit;        //放弃编辑
	function[1] = open;            //打开文件  
	function[2] = print;           //显示文件
	function[3] = insert;          //插入行
	function[4] = dele;            //删除行
	function[5] = copy;            //拷贝行
	function[6] = modify;          //修改行
	function[7] = find;            //查找字符串
	function[8] = replace;         //替换字符串
	function[9] = save;            //存盘退出
	int commond;//输入命令
	
	while (true)
	{
		menu();//显示菜单
		scanf("%d", &commond);//输入命令
		if (commond >= 0 && commond <= 9) {
			if (commond != 1 && head == NULL) {//判断文件是否打开或创。
				printf("文件未打开，请先打开文件！\n");
				continue;
			}
			else if (commond == 9) {//存盘退出
				head = function[commond](head);
				break;
			}
			else if (commond == 0) {//放弃编辑退出
				function[commond](head);
				break;
			}
			head = function[commond](head);//执行命令
		}
		else {
			reporterror();//输入不属于命令范围的命令报错。
		}
	}

	return 0;
}
