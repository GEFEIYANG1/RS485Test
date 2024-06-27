#include "MyApplication.h"


static uint8_t  ucSend_Buffer[UART3_Send_LENGTH] = {0x00};
static uint8_t  ucRec_Buffer [UART3_Rec_LENGTH]  = {0x00};

static void SendArray(uint8_t*,uint16_t);  //串口发送数组
static void SendString(uint8_t*);          //串口发送字符串

static void RS485_Set_SendMode(void); //RS-485接口设置为发送模式
static void RS485_Set_RecMode(void);  //RS-485接口设置为接收模式

UART_t UART3 = {
  ucSend_Buffer,
  ucRec_Buffer,
  SendArray,
  SendString,
  RS485_Set_SendMode,
  RS485_Set_RecMode
};


static void SendArray(uint8_t* p_Arr,uint16_t LEN) 
{
	UART3.RS485_Set_SendMode();	
	HAL_UART_Transmit_DMA(&huart3,p_Arr,LEN);
}


static void SendString(uint8_t* p_Str) 
{	
	
}


static void RS485_Set_SendMode()
{
	HAL_GPIO_WritePin(RS485_DE_nRE_GPIO_Port, RS485_DE_nRE_Pin ,GPIO_PIN_SET);
}


static void RS485_Set_RecMode()
{
	HAL_GPIO_WritePin(RS485_DE_nRE_GPIO_Port, RS485_DE_nRE_Pin ,GPIO_PIN_RESET);
}

