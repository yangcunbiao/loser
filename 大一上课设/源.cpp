#include"package.h"
int main()
{
	list head = NULL;//��ͷ���������ͷ��㡣
	list(*function[10])(list head);//����ָ��
	function[0] = quitedit;        //�����༭
	function[1] = open;            //���ļ�  
	function[2] = print;           //��ʾ�ļ�
	function[3] = insert;          //������
	function[4] = dele;            //ɾ����
	function[5] = copy;            //������
	function[6] = modify;          //�޸���
	function[7] = find;            //�����ַ���
	function[8] = replace;         //�滻�ַ���
	function[9] = save;            //�����˳�
	int commond;//��������
	
	while (true)
	{
		menu();//��ʾ�˵�
		scanf("%d", &commond);//��������
		if (commond >= 0 && commond <= 9) {
			if (commond != 1 && head == NULL) {//�ж��ļ��Ƿ�򿪻򴴡�
				printf("�ļ�δ�򿪣����ȴ��ļ���\n");
				continue;
			}
			else if (commond == 9) {//�����˳�
				head = function[commond](head);
				break;
			}
			else if (commond == 0) {//�����༭�˳�
				function[commond](head);
				break;
			}
			head = function[commond](head);//ִ������
		}
		else {
			reporterror();//���벻�������Χ�������
		}
	}

	return 0;
}
