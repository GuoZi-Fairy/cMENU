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
#define BACK 1 //在func中 若return BACK 则 返回上一层菜单
#define NORMAL 0 //在func中 若return NORMAL 则进入下一层菜单
#define STDCAL(type) type __cdecl
typedef enum _boolean{
    FALSE,
    TRUE 
}boolean;
typedef struct _menu cMENU;
typedef struct _one_option
{
    char *text;//选项的描述
    cMENU *parent_menu;//指向该选项的父菜单
    cMENU *next_menu;//该选项所链接的下一级菜单指针
    int (*function)(void);//选项对应的执行功能，若无执行则传入null_func，该函数无传int入参数,该函数必须为int类型,返回值为0.
}cOPTION;

typedef struct _menu
{
    char *name;//菜单的名称
    char *text;//菜单的描述
    struct _menu *parent_menu; //该菜单的父级菜单,若为顶级菜单则传入NULL
    cOPTION *options_list;//options_list[MAX_MENU_OPTION_NUM];
    int option_number;//选项个数
    boolean back_available;//是否可返回上一级菜单
}cMENU;
extern int null_func(void);
extern int next_func(void);
extern cMENU none_menu_token;
extern cOPTION end_option_token;
extern char __system_speaker[50];//系统提示自称，默认<|系统提示|>,可使用system_speaker(char[50])修改
extern STDCAL(cOPTION) mk_option(char *text,int (*func)(void));
extern STDCAL(cMENU) mk_menu(char *name,char *text,cMENU *parent_menu,cOPTION *list,int num,boolean back_available);//list[11] = {option1,option2,option3,option4,...option10,END_OPTION}手动初始化
extern STDCAL(void) modify_system_speaker(char *speaker_name);
extern STDCAL(void) link_menu2option(cOPTION *option_obj,cMENU *menu_obj);
extern STDCAL(int) start(cMENU *menu);