#ifndef __System_H__
#define __System_H__

//定义结构体类型
typedef struct
{
	void (*Run)(void);
	void (*Error_handler)(void);
	void (*Assert_Failed)(void);
} System_t;

extern System_t  System;

#endif

