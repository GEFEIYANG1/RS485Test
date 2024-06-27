#include "MyApplication.h"




int _write(int fd, char *ptr, int len)
{
  HAL_UART_Transmit(&huart1, (uint8_t*)ptr, len, 0xFFFF);
  return len;
}

int _read (int fd, char *ptr, int len)
{
  *ptr = 0x00; // Flush the character buffer
  HAL_UART_Receive(&huart1, (uint8_t*) ptr, 1, 0xFFFF);
  return 1;
}
