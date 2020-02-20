/*
THIS FILE IS PART OF LibreBoot MENU PROJECT 
reboot.py - The core part of the reboot library  
THIS PROGRAM IS FREE SOFTWARE, BALABALA, IS LICENSED UNDER BALABALA
YOU SHOULD HAVE RECEIVED A COPY OF WTFPL LICENSE, IF NOT, BALABALA 
Copyright (c) 2020 XYG 
*/
#ifdef __cplusplus
extern "C"
{
#endif
#if !defined(_CRT_SECURE_NO_DEPRECATE) && defined(_MSC_VER)
#define _CRT_SECURE_NO_DEPRECATE
#endif

#ifdef __GNUC__
#pragma GCC visibility push(default)
#endif

#if defined(_MSC_VER)
#pragma warning (push)
/* disable warning about single line comments in system headers */
#pragma warning (disable : 4001)
#endif
#ifdef __GNUC__
#pragma GCC visibility pop
#endif

#if defined(_MSC_VER)
#pragma warning (pop)
#endif
#define STDCAL(type) type __cdecl
#include "menu.h"
/*****************************************************************************************************/
typedef struct _error
{
    char* type;
    char* msg;
    char* note;
}error;
error choice_error = {"[CHOICE ERROR]","[choice error]:Unexpected input","Insure the input within the limits of the indexes of choices"};
error function_error = {"[FUNCTION ERROR]","[function error]:Unexpected returned value","The function's return-value of your option should be NORMAL or BACK"};

/*****************************************************************************************************/
extern int null_func(void){return 0;}
extern int next_func(void){return 0;}//允许直接跳转至下一个菜单并显示
cOPTION end_option_token={END_OPTION_TEXT,&END_MENU,&END_MENU,END_OPTION_FUNC};
cOPTION none_options_list[MAX_MENU_OPTION_NUM];
cMENU NONE_MENU={"\0","\0",&NONE_MENU,none_options_list,MAX_MENU_OPTION_NUM};
char system_speaker[50] = "<|系统提示|>";
#define RAISE(error) printf("\n%s\n%s\nNote:%s",error.type,error.msg,error.note),system("pause")
static STDCAL(int) get_choice(char *text,cMENU* menu);
static STDCAL(int) execute_option();
static STDCAL(void) display();

extern STDCAL(cOPTION) mk_option(char *text,int (*func)(void))
{
    cOPTION option_obj = {text,NULL,&NONE_MENU,func};
    return option_obj; 
}

extern STDCAL(void) link_menu2option(cOPTION *option_obj,cMENU *menu_obj)
{
    option_obj->next_menu = menu_obj;
    menu_obj->parent_menu = option_obj->parent_menu;
}

static STDCAL(int) execute_option(cOPTION* option)
{
    if (option->function != NONE_OPTION_FUNC)
    {
		int (*func)(void) = option->function;
		int state = func();
		if (state == NORMAL) return NORMAL;
		else if(state == BACK) return BACK;
		else//error case
		{
			RAISE(function_error);
            return BACK;
		}
    }
    else return 0;
    return 0;
}

extern STDCAL(cMENU) mk_menu(char *name,char *text,cMENU *parent_menu,cOPTION list[MAX_MENU_OPTION_NUM],int num,boolean back_availabel)
{
    cMENU menu_obj = {name,text,parent_menu,list,num,back_availabel};
    for (int i = 0; i < num; i++)list[i].parent_menu = &menu_obj;
    return menu_obj;
}
static STDCAL(void) menu_flush()
{
    fflush(stdout);
    rewind(stdin);
}

static STDCAL(int) get_choice(char *text,cMENU* menu)
{
    int choice = 0;
    printf("%s%s",system_speaker,text);
    menu_flush();
    scanf_s("%d",&choice); 
    if(choice<=menu->option_number && choice>=0 && menu->back_available==TRUE)
        return choice;//允许返回上层菜单
    else if (choice<=menu->option_number && choice>0 && menu->back_available==FALSE)
        return choice;//不允许返回上层菜单
    else //error case
        {
            RAISE(choice_error);
			printf("是否重新输入[y/n]:");
            menu_flush();
			char y_or_n = getchar();
			switch (y_or_n)
			{
			case 'y':
			case 'Y':
				display(menu);
				get_choice("请输入选项:",menu);
				break;
			case 'n':
			case 'N':
				printf_s("暂时退出程序");
				system("exit");
				break;
			}
        }
    return choice;
}

extern STDCAL(void) modify_system_speaker(char *self_name)
{
    strcpy_s(__system_speaker,strlen(self_name)+1,self_name);
}

static STDCAL(void) display(cMENU* menu)
{
    system("cls");
    printf("\t\t|*%s*|\t\t\n",menu->name);
	printf("%s菜单说明:\n%s\t\n", system_speaker, menu->text);
	printf("===============================================\n");
    if(menu->back_available==1)printf("<option-0>返回上层菜单\n");
    cOPTION *p = NULL;
    for (int i = 0; i < menu->option_number; i++)
    {
        p = menu->options_list+i;
        printf("<option-%d>%s\n",i+1,p->text);
    }
	printf("===============================================\n");
}

extern STDCAL(int) start(cMENU *menu)
{
    if(menu == &NONE_MENU)return NORMAL;
	else
    {
        display(menu);
        int choice = get_choice("input a number to choice:",menu)-1;
        if (choice == -1)return BACK;//为返回上层菜单
		cOPTION* option_choice = menu->options_list + choice;
		if(execute_option(option_choice)==BACK)start(menu);
        system("pause");
        int value = start(option_choice->next_menu);
        if (value == NORMAL)return NORMAL;//0为结束值
        else if (value == BACK)start(menu);
        else
        {
            system("cls");
            printf("---------ERROR-----------");
            system("pause");
            return 3;
        }
    }
	return 0;
}