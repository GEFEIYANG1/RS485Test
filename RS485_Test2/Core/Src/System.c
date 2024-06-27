#include "MyApplication.h"

/* Private define-------------------------------------------------------------*/

/* Private variables----------------------------------------------------------*/
static void Run(void); 
static void Error_handler(void);
static void Assert_Failed(void);
	
/* Public variables-----------------------------------------------------------*/
System_t System = 
{
	Run,
	Error_handler,
	Assert_Failed
};

/* Private function prototypes------------------------------------------------*/      

/*
	* @name   Run
	* @brief  ϵͳ����
	* @param  None
	* @retval None      
*/
static void Run()
{
}

/*
	* @name   Error_Handler
	* @brief  ϵͳ������
	* @param  None
	* @retval None      
*/
static void Error_handler()
{
	/* User can add his own implementation to report the HAL error return state */
}

/*
	* @name   Assert_Failed
	* @brief  ��������������
	* @param  None
	* @retval None      
*/
static void Assert_Failed()
{
	/* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
}
/********************************************************
  End Of File
********************************************************/
