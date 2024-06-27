#include "MyApplication.h"


void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{

  if(huart->Instance == huart3.Instance)
	{
		UART3.RS485_Set_RecMode();
	}
}

void HAL_UART_IdleCallback(UART_HandleTypeDef *huart)
{  
  if(huart->Instance == huart3.Instance)
	{
    Modbus.Protocol_Analysis(&UART3);                                       // 接收数据解析
    HAL_UART_Receive_DMA(&huart3, UART3.pucRec_Buffer, UART3_Rec_LENGTH);   // 重新开启接收DMA
	}
}