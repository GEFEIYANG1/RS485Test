#ifndef __UART_H__
#define __UART_H__

#include "MyApplication.h"

//定义枚举类型

//定义结构体类型
typedef struct 
{
  uint8_t* pucSend_Buffer;     //发送缓存指针  
  uint8_t* pucRec_Buffer;     //接收缓存指针 

  void (*SendArray)(uint8_t*, uint16_t);    //串口发送数组
  void (*SendString)(uint8_t*);             //串口发送字符串

	void (*RS485_Set_SendMode)(void);  //RS-485接口设置为发送模式
	void (*RS485_Set_RecMode)(void);   //RS-485接口设置为接收模式
 
} UART_t;



#endif
