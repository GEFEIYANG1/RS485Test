#ifndef __PUBLIC_H_
#define __PUBLIC_H_

/* Public define-------------------------------------------------------------*/
#define SoftWare_Version 	(float)1.0
#define	huart_debug		huart1

//定义枚举类型 -> TRUE/FALSE位
typedef enum 
{
  FALSE = 0U, 
  TRUE = !FALSE
} FlagStatus_t;

typedef enum 
{
  FAILED = 0U, 
  PASSED = !FAILED
} TestStatus_t;
//定义结构体类型


#endif

