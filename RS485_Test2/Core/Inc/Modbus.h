#ifndef __Modbus_H__
#define __Modbus_H__

#include "MyApplication.h"

//����ö������

//����ṹ������
typedef struct 
{
  uint16_t addr;

  void (*Protocol_Analysis)(UART_t*);  //Э�����

} Modbus_t;

extern Modbus_t Modbus;


#endif
