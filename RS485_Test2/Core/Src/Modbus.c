#include "MyApplication.h"

#define UART_Order_Index 8
#define FunctionCode_Read_Register 0x03
#define FunctionCode_Write_Register 0x06

static void Protocol_Analysis(UART_t* UART); 
static void Modbus_Read_Register(UART_t* UART);   
static void Modbus_Wrtie_Register(UART_t* UART); 

Modbus_t Modbus = {

  1,

  Protocol_Analysis

};

static void Protocol_Analysis(UART_t* UART)
{
  UART_t* const COM_UART = UART;
  uint8_t i = 0, Index = 0;

#ifdef DWB_Dug
  uint8_t j =0;
#endif

  // 1、关闭接收
  HAL_UART_AbortReceive(&huart3);

  // 2、整理接收数据
  for(i=0; i<UART3_Rec_LENGTH; i++)
  {
	if(Index == 0)
	{
		if(*(COM_UART->pucRec_Buffer+i) != Modbus.addr)
		continue;
	}

    *(COM_UART->pucRec_Buffer + Index) = *(COM_UART->pucRec_Buffer + i);
    // 取7字节
    if(Index == UART_Order_Index) 
      break;        
     
    Index++;
  }

#ifdef DWB_Dug
	for(j=0; j<UART_Order_Index; j++)
	{
		printf("DWB ------ Protocol_Analysis, pucRec_Buffer[%d] = 0x%x \n\r", j, *(COM_UART->pucRec_Buffer+j));
	}
#endif

	// 4、校验码
	CRC_16.CRC_Value = CRC_16.CRC_Check(COM_UART->pucRec_Buffer, 6);
	CRC_16.CRC_H = (u_int8_t)(CRC_16.CRC_Value >> 8);
	CRC_16.CRC_L = (u_int8_t)CRC_16.CRC_Value;

#ifdef DWB_Dug
	printf("DWB ------ Protocol_Analysis, pucRec_Buffer[6] = 0x%x ,pucRec_Buffer[7] = 0x%x \n\r", *(COM_UART->pucRec_Buffer+6), *(COM_UART->pucRec_Buffer+7));
	printf("DWB ------ Protocol_Analysis, CRC_16.CRC_L = 0x%x ,CRC_16.CRC_H = 0x%x \n\r", CRC_16.CRC_L, CRC_16.CRC_H);
#endif

	if(((*(COM_UART->pucRec_Buffer+6) == CRC_16.CRC_L) && (*(COM_UART->pucRec_Buffer+7) == CRC_16.CRC_H))
																								||
	   ((*(COM_UART->pucRec_Buffer+6) == CRC_16.CRC_H) && (*(COM_UART->pucRec_Buffer+7) == CRC_16.CRC_L)))
	{
			//校验地址
			if((*(COM_UART->pucRec_Buffer+0)) == Modbus.addr)
			{
			// 5、数据处理
				if((*(COM_UART->pucRec_Buffer+1)) == FunctionCode_Read_Register)
				{
					Modbus_Read_Register(COM_UART);
				}
				else if((*(COM_UART->pucRec_Buffer+1)) == FunctionCode_Write_Register)
				{
					Modbus_Wrtie_Register(COM_UART);
				}	
			}
		}
	
	//清缓存
	for(i=0;i<UART3_Rec_LENGTH;i++)
	{
		*(COM_UART->pucRec_Buffer+i) = 0x00;
	}
}

static void Modbus_Read_Register(UART_t* UART)
{
  UART_t* const COM_UART = UART;
	
	//校验地址
	if((*(COM_UART->pucRec_Buffer+2) == 0x9C) && (*(COM_UART->pucRec_Buffer+3) == 0x41))
	{
		////回应数据
		//地址码
		*(COM_UART->pucSend_Buffer+0)  = Modbus.addr;
		//功能码
		*(COM_UART->pucSend_Buffer+1)  = FunctionCode_Read_Register;
		//数据长度(字节)
		*(COM_UART->pucSend_Buffer+2)  = 2;
		//发送数据
		// deep status
		*(COM_UART->pucSend_Buffer+3)  = 0;
		*(COM_UART->pucSend_Buffer+4) = Deep.Read_Deep();
		*(COM_UART->pucSend_Buffer+5)  = 0;
		*(COM_UART->pucSend_Buffer+6) = 0x66;
		
		//插入CRC
		CRC_16.CRC_Value = CRC_16.CRC_Check(COM_UART->pucSend_Buffer,7); //计算CRC值
		CRC_16.CRC_H     = (uint8_t)(CRC_16.CRC_Value >> 8);
		CRC_16.CRC_L     = (uint8_t)CRC_16.CRC_Value;
		
		*(COM_UART->pucSend_Buffer+7) = CRC_16.CRC_L;
		*(COM_UART->pucSend_Buffer+8) = CRC_16.CRC_H;

		//发送数据
		UART3.SendArray(COM_UART->pucSend_Buffer,9);
	}
}

static void Modbus_Wrtie_Register(UART_t* UART)
{
	UART_t* const COM_UART = UART;
	uint8_t i=0;
	
	//回应数据
	for(i=0;i<8;i++)
	{
		*(COM_UART->pucSend_Buffer+i) = *(COM_UART->pucRec_Buffer+i);
	}
	//发送数据
	UART3.SendArray(COM_UART->pucSend_Buffer,8);

	if((*(COM_UART->pucRec_Buffer+2) == 0x9C) && (*(COM_UART->pucRec_Buffer+3) == 0x42))
	{
		if(*(COM_UART->pucRec_Buffer+5) == Deep_Status_ON )
			Deep.Deep_Enable();
		else
			Deep.Deep_Disable();
	}
}

