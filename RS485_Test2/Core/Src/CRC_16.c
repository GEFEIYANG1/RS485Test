#include "MyApplication.h"

static uint16_t CRC_Check(uint8_t*,uint8_t);  //CRC校验


CRC_16_t  CRC_16 = {0,0,0,CRC_Check};

/*******************************************************
说明：CRC添加到消息中时，低字节先加入，然后高字

CRC计算方法：
 1.预置1个16位的寄存器为十六进制FFFF(即全为1);称此寄存器为CRC寄存器;
 2.把第一个8位二进制数据(既通讯信息帧的第一个字节)与16位的CRC寄存器的低
 8位相异或，把结果放于CRC寄存器;
 3.把CRC寄存器的内容右移一位(朝低位)用0填补最高位，并检查右移后的移出位;
 4.如果移出位为0:重复第3步(再次右移一位);
 如果移出位为1:CRC寄存器与多项式A001(1010 0000 0000 0001)进行异或;
 5.重复步骤3和4，直到右移8次，这样整个8位数据全部进行了处理;
 6.重复步骤2到步骤5，进行通讯信息帧下一个字节的处理;
 7.将该通讯信息帧所有字节按上述步骤计算完成后，得到的16位CRC寄存器的高、低
 字节进行交换;
********************************************************/

uint16_t CRC_Check(uint8_t *CRC_Ptr,uint8_t LEN)
{
	uint16_t CRC_Value = 0;
	uint8_t  i         = 0;
	uint8_t  j         = 0;

	CRC_Value = 0xffff;
	for(i=0;i<LEN;i++)
	{
		CRC_Value ^= *(CRC_Ptr+i);
		for(j=0;j<8;j++)
		{
			if(CRC_Value & 0x00001)
				CRC_Value = (CRC_Value >> 1) ^ 0xA001;
			else
				CRC_Value = (CRC_Value >> 1);
		}
	}
	CRC_Value = ((CRC_Value >> 8) +  (CRC_Value << 8)); //交换高低字节

	return CRC_Value;
}