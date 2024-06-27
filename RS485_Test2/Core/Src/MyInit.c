#include "MyApplication.h"


static void Peripheral_Set(void); 

MyInit_t MyInit = 
{
	Peripheral_Set
};




static void Peripheral_Set()
{
#ifdef STM32_F407_RS485_Modbus
#ifdef DWB_Dug
	printf("----DWB   RS485 Modbus test ----\r\n");
#endif

	__HAL_UART_ENABLE_IT(&huart3, UART_IT_IDLE);		// ????3????
	HAL_UART_Receive_DMA(&huart3, UART3.pucRec_Buffer, UART3_Rec_LENGTH);
#endif

}

