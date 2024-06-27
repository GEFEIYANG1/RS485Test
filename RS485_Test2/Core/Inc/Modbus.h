#ifndef __Modbus_H__
#define __Modbus_H__

#include "MyApplication.h"

//定义枚举类型

//定义结构体类型
typedef struct 
{
  uint16_t addr;

  void (*Protocol_Analysis)(UART_t*);  //协议分析

} Modbus_t;

extern Modbus_t Modbus;


#endif
