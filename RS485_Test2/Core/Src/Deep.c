#include "MyApplication.h"


static uint8_t Read_Deep(void);
static void Deep_Enable(void);                     
static void Deep_Disable(void);                     

Deep_t Deep ={
    Read_Deep,
    Deep_Enable,
    Deep_Disable
};

static void Deep_Enable(void)
{
  HAL_GPIO_WritePin(beep_GPIO_Port, beep_Pin, GPIO_PIN_SET);
} 
                  
static void Deep_Disable(void)
{
  HAL_GPIO_WritePin(beep_GPIO_Port, beep_Pin, GPIO_PIN_RESET);
}     

static uint8_t Read_Deep(void)
{
  uint8_t val=0;

  val = HAL_GPIO_ReadPin(beep_GPIO_Port, beep_Pin);
  return val;
}                     
