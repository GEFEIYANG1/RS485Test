#ifndef __MyInit_H__
#define __MyInit_H__

//����ṹ������
typedef struct
{
	void (*Peripheral_Set)(void);
} MyInit_t;

extern MyInit_t  MyInit;

#endif
