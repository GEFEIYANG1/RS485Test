#ifndef __MyInit_H__
#define __MyInit_H__

//定义结构体类型
typedef struct
{
	void (*Peripheral_Set)(void);
} MyInit_t;

extern MyInit_t  MyInit;

#endif
