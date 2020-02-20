/*
DEMO说明：
{

	MENU project是为了简单快速的创建一份console树状菜单而编写的库
	仅包含menu.c和menu.h文件 请使用#include "menu.h"
	数据结构说明:
	{
		- one_option 选项类型
		- one_option[] 选项数组
		- menu 菜单类型
	}
	函数说明:
	{
		构造函数:
		{
			- mk_option(char* 选项文本, (int*)功能函数());用于构造一个one_option 对象
			- mk_menu(char* 菜单名称, char* 菜单说明,menu* NULL , one_option* 选项列表, int 选项个数, boolean 是否可以返回上层菜单);用于构造一个menu对象
			- link_menu2option(one_option* 选项对象, 菜单对象); 用于将一个menu对象链接为一个option对象的下级menu
		}
		执行函数:
		{
			- modify_system_speaker(char* 系统提示自称);用于在提示处作为提示标识
			- start(menu* 菜单对象);用于启动菜单 若菜单正常结束将以 0 为返回值
		}
	}
	规范说明:
	{
		若希望给一个 option对象指定一个功能函数,请以一下格式编写该函数,若不希望执行一个功能函数，请在构造该option对象时将其功能函数指定为NONE_OPTION_FUNC
		-声明为: int func_name(void);
		-定义为:
		{

			int func_name(void)
			{
				statements;
				return NORMAL;//若返回值为TRUE 则正常结束 进入下一级菜单
				//若返回值为BACK 则返回原菜单
			}
			
		}
	}
}
*/
#include "menu.h"
#include <string.h>
//删减改查
int login() //仅实现login函数 假设有账号:admin 密码:123456
{ 
	char id[50];
	char pw[50];
	printf("\n账号:");
	scanf_s("%s",id,50);
	printf("\n密码:");
	scanf_s("%s",pw,50);
	if(!strcmp(id,"admin") && !strcmp(pw,"123456"))
	{
		printf("\n登录成功");
		return NORMAL;
	}
	else
	{
		printf("\n登录失败");
		return BACK;
	}
	
}
int logout() { return NORMAL; }//登入登出	 [未实现]
int reg() { return NORMAL; }//注册			[未实现]
int query() { return NORMAL; }//查			[未实现]
int modify() { return NORMAL; }//改			[未实现]
int delete() { return NORMAL; }//删			[未实现]

int main(int argc, char const *argv[])
{
    modify_system_speaker("<图书管理系统>");//此处修改了系统提示的标识

    cOPTION gate_options[3] = {
        mk_option("登录",login),
        mk_option("注册",reg),
        mk_option("退出",NONE_OPTION_FUNC)//此处为不需执行功能函数的情况
        };//此处构造了一个选项列表
    cMENU gate_menu = mk_menu("欢迎使用图书管理系统","提供 登入 注册等操作",NULL,gate_options,3,FALSE);//此处构造了menu对象gate_menu

	cOPTION op_options[3] =
	{
		mk_option("查询",query),
		mk_option("更改某条记录",modify),
		mk_option("删去某条记录",delete)
	};//此处构造了一个选项列表
	cMENU op_menu = mk_menu("操作菜单", "提供 删减改 操作", NULL, op_options, 3, TRUE);//此处构造了menu对象op_menu
	link_menu2option(&gate_options[0], &op_menu);//此处将 op_menu指定为gate_menu的第一个选项的下级菜单
	start(&gate_menu);//此处指定了以gate_menu作为起始菜单
    return 0;
}
