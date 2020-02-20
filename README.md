# cMENU

simply construct a menu

## Table of contents
table of Contents(out of data)
- [cMENU](#cmenu)
  - [Table of contents](#table-of-contents)
  - [Usage](#usage)
    - [Welcome to cMENU](#welcome-to-cmenu)
    - [Build](#build)
      - [Coping the source](#coping-the-source)
    - [Data Struct](#data-struct)
      - [cOPTION](#coption)
      - [cMENU](#cmenu-1)
    - [Working with cMENU and cOPTION](#working-with-cmenu-and-coption)
      - [cMENU construction build](#cmenu-construction-build)
      - [The option-function function standard](#the-option-function-function-standard)
      - [Start your cMENU progress](#start-your-cmenu-progress)
  - [License](#license)
  - [Enjoy cMENU](#enjoy-cmenu)
## Usage

### Welcome to cMENU

### Build
There are serval ways to incorporate cMENU into your projects

#### Coping the source
The entire library is only one C file and one Header file,you can just copy the `menu.h` and `menu.c` to your projects source and start using it.
You could include cMENU like this:
``` c
#include "menu.h"
```

cJSON is written in ANSI C (C89) in order to support as many platforms and compilers as possible.

### Data Struct
`cOPTION` represents a option data to declare a option
`cMENU` represents a menu data to declare a menu
#### cOPTION
```c
/* The cOPTION structrue: */
typedef struct _one_option cOPTION;
typedef struct _one_option
{
    char *text;
    cMENU *parent_menu;
    cMENU *next_menu;
    int (*function)(void);
}cOPTION;
```
An item of cOPTION could be structed by the function `mk_option(char*,(int*))`
A option list could be define like this:
```c
cOPTION option_list[N]={
    mk_option("option1",func1),
    mk_option("option2",func2),
    ...
    mk_option("optionN",funcN),
}
```
#### cMENU
```c
/* The cMENU structrue */
typedef struct _menu cMENU;
typedef struct _menu
{
    char *name;
    char *text;
    struct _menu *parent_menu;
    cOPTION *options_list;
    int option_number;
    boolean back_available;
}cMENU;
```
An item of cMENU could be structed by the function `mk_menu(char*,char*,cMENU*,cOPTION*,int,boolean)`(**Generally,you should make parameter cMENU* to NULL**)
A cMENU could be define like this:
```c
cMENU menu = mk_menu("menu_title","menu_introduction",NULL,option_list,N,TRUE);
```

### Working with cMENU and cOPTION

#### cMENU construction build
* **cMENU** struct cMENU by `mk_menu`
* **cOPTION** struct cOPTION by `mk_option`
* **cOPTION[]** struct like this:
```c
cOPTION option_list[N] = {
    mk_option,
    mk_option,...
}
```
* `modify_system_speaker` If you want to modify the system self-call,you should use `modify_system_speaker(char*)` to modify.Then you will see system self_call like this `<system_self-call>.....`
* `modify_menu_reminder` If you want to modify the menu remind style,you should use `modify_menu_reminder(char*)` to modify.Then you will see system self_call like this `menu-explain`
* `modify_whether_remind` If you want to modify the whether rechoose reminder style,you should use `modify_whether_remind(char*)` to modify.Then you will see system self_call like this `whether input again`
* `modify_back_choice` If you want to modify the back choice style,you should use `modify_back_choice(char*)` to modify.Then you will see system self_call like this `back to the parent menu`
* `link_menu2option` If you want to struct a multi-layered menu, you should use `link_menu2option` to link menu to option. After the link operation , if you choose the option you linked, after the execution of option-function, the system will skip to the linked-menu.

#### The option-function function standard
You could program a function to execute if you want to execute it after user choosed selected the option.If a option do not need a function to execute, you could build it like this:`mk_option("**",NONE_OPTION_FUNC)`(**NONE_OPTION_FUNC**).
**The function you program should observe the standard.**
```c
int func_name(void)
{
    statements;
    return NORMAL;//If return NORMAL,the progress will goto the next menu
    /*return BACK; //If return BACK, the progress will goto the parent menu
}
```

#### Start your cMENU progress
* `start` If you have accomplish your menu construction, you should start it by `start(cMENU*)`.You need to appoint the top menu as the only parameter.If the cMENU system normally terminate. `start` will return **0**.

## License

MIT License

>  Copyright (c) 2009-2017 Dave Gamble and cJSON contributors
>
>  Permission is hereby granted, free of charge, to any person obtaining a copy
>  of this software and associated documentation files (the "Software"), to deal
>  in the Software without restriction, including without limitation the rights
>  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
>  copies of the Software, and to permit persons to whom the Software is
>  furnished to do so, subject to the following conditions:
>
>  The above copyright notice and this permission notice shall be included in
>  all copies or substantial portions of the Software.
>
>  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
>  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
>  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
>  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
>  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
>  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
>  THE SOFTWARE.

## Enjoy cMENU
- GuoZi (original author)