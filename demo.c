/*
DEMO˵����
{

	MENU project��Ϊ�˼򵥿��ٵĴ���һ��console��״�˵�����д�Ŀ�
	������menu.c��menu.h�ļ� ��ʹ��#include "menu.h"
	���ݽṹ˵��:
	{
		- one_option ѡ������
		- one_option[] ѡ������
		- menu �˵�����
	}
	����˵��:
	{
		���캯��:
		{
			- mk_option(char* ѡ���ı�, (int*)���ܺ���());���ڹ���һ��one_option ����
			- mk_menu(char* �˵�����, char* �˵�˵��,menu* NULL , one_option* ѡ���б�, int ѡ�����, boolean �Ƿ���Է����ϲ�˵�);���ڹ���һ��menu����
			- link_menu2option(one_option* ѡ�����, �˵�����); ���ڽ�һ��menu��������Ϊһ��option������¼�menu
		}
		ִ�к���:
		{
			- modify_system_speaker(char* ϵͳ��ʾ�Գ�);��������ʾ����Ϊ��ʾ��ʶ
			- start(menu* �˵�����);���������˵� ���˵������������� 0 Ϊ����ֵ
		}
	}
	�淶˵��:
	{
		��ϣ����һ�� option����ָ��һ�����ܺ���,����һ�¸�ʽ��д�ú���,����ϣ��ִ��һ�����ܺ��������ڹ����option����ʱ���书�ܺ���ָ��ΪNONE_OPTION_FUNC
		-����Ϊ: int func_name(void);
		-����Ϊ:
		{

			int func_name(void)
			{
				statements;
				return NORMAL;//������ֵΪTRUE ���������� ������һ���˵�
				//������ֵΪBACK �򷵻�ԭ�˵�
			}
			
		}
	}
}
*/
#include "menu.h"
#include <string.h>
//ɾ���Ĳ�
int login() //��ʵ��login���� �������˺�:admin ����:123456
{ 
	char id[50];
	char pw[50];
	printf("\n�˺�:");
	scanf_s("%s",id,50);
	printf("\n����:");
	scanf_s("%s",pw,50);
	if(!strcmp(id,"admin") && !strcmp(pw,"123456"))
	{
		printf("\n��¼�ɹ�");
		return NORMAL;
	}
	else
	{
		printf("\n��¼ʧ��");
		return BACK;
	}
	
}
int logout() { return NORMAL; }//����ǳ�	 [δʵ��]
int reg() { return NORMAL; }//ע��			[δʵ��]
int query() { return NORMAL; }//��			[δʵ��]
int modify() { return NORMAL; }//��			[δʵ��]
int delete() { return NORMAL; }//ɾ			[δʵ��]

int main(int argc, char const *argv[])
{
    modify_system_speaker("<ͼ�����ϵͳ>");//�˴��޸���ϵͳ��ʾ�ı�ʶ

    cOPTION gate_options[3] = {
        mk_option("��¼",login),
        mk_option("ע��",reg),
        mk_option("�˳�",NONE_OPTION_FUNC)//�˴�Ϊ����ִ�й��ܺ��������
        };//�˴�������һ��ѡ���б�
    cMENU gate_menu = mk_menu("��ӭʹ��ͼ�����ϵͳ","�ṩ ���� ע��Ȳ���",NULL,gate_options,3,FALSE);//�˴�������menu����gate_menu

	cOPTION op_options[3] =
	{
		mk_option("��ѯ",query),
		mk_option("����ĳ����¼",modify),
		mk_option("ɾȥĳ����¼",delete)
	};//�˴�������һ��ѡ���б�
	cMENU op_menu = mk_menu("�����˵�", "�ṩ ɾ���� ����", NULL, op_options, 3, TRUE);//�˴�������menu����op_menu
	link_menu2option(&gate_options[0], &op_menu);//�˴��� op_menuָ��Ϊgate_menu�ĵ�һ��ѡ����¼��˵�
	start(&gate_menu);//�˴�ָ������gate_menu��Ϊ��ʼ�˵�
    return 0;
}
