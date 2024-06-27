#ifndef __Deep_H__
#define __Deep_H__

#include "MyApplication.h"

typedef enum
{
  Deep_Status_OFF = 0x00,
	Deep_Status_ON  = 0x01,
} Deep_Status_t;

typedef struct
{
  uint8_t (*Read_Deep)(void);                     
	void (*Deep_Enable)(void);                     
	void (*Deep_Disable)(void);                     
} Deep_t;

extern Deep_t Deep;


#endif

