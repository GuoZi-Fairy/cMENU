#if !defined(__WINDOWS__) && (defined(WIN32) || defined(WIN64) || defined(_MSC_VER) || defined(_WIN32))
#define __WINDOWS__
#endif
#ifndef STDLIB_H
    #define STDLIB_H
    #include <stdlib.h>
#endif

#ifndef STRING_H
    #define STRING_h
    #include <string.h>
#define STRING_H
#endif

#ifndef STDIO_H
    #define STDIO_H
    #include <stdio.h>
#endif

#ifndef STDARG_H
    #define STDARG_H
    #include <stdarg.h>
#endif

#define END_OPTION_TEXT "END_TOKEN"
#define END_OPTION_FUNC null_func
#define NONE_OPTION_FUNC null_func
#define END_MENU none_menu_token
#define NONE_MENU none_menu_token
#define MAX_MENU_OPTION_NUM 10
#define BACK 1 //��func�� ��return BACK �� ������һ��˵�
#define NORMAL 0 //��func�� ��return NORMAL �������һ��˵�
#define STDCAL(type) type __cdecl
typedef enum _boolean{
    FALSE,
    TRUE 
}boolean;
typedef struct _menu cMENU;
typedef struct _one_option
{
    char *text;//ѡ�������
    cMENU *parent_menu;//ָ���ѡ��ĸ��˵�
    cMENU *next_menu;//��ѡ�������ӵ���һ���˵�ָ��
    int (*function)(void);//ѡ���Ӧ��ִ�й��ܣ�����ִ������null_func���ú����޴�int�����,�ú�������Ϊint����,����ֵΪ0.
}cOPTION;

typedef struct _menu
{
    char *name;//�˵�������
    char *text;//�˵�������
    struct _menu *parent_menu; //�ò˵��ĸ����˵�,��Ϊ�����˵�����NULL
    cOPTION *options_list;//options_list[MAX_MENU_OPTION_NUM];
    int option_number;//ѡ�����
    boolean back_available;//�Ƿ�ɷ�����һ���˵�
}cMENU;
extern int null_func(void);
extern int next_func(void);
extern cMENU none_menu_token;
extern cOPTION end_option_token;
extern char __system_speaker[50];//ϵͳ��ʾ�Գƣ�Ĭ��<|ϵͳ��ʾ|>,��ʹ��system_speaker(char[50])�޸�
extern STDCAL(cOPTION) mk_option(char *text,int (*func)(void));
extern STDCAL(cMENU) mk_menu(char *name,char *text,cMENU *parent_menu,cOPTION *list,int num,boolean back_available);//list[11] = {option1,option2,option3,option4,...option10,END_OPTION}�ֶ���ʼ��
extern STDCAL(void) modify_system_speaker(char *speaker_name);
extern STDCAL(void) link_menu2option(cOPTION *option_obj,cMENU *menu_obj);
extern STDCAL(int) start(cMENU *menu);