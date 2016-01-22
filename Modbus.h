#ifndef __MODBUS__
#define __MODBUS__

enum ModbusFunctions{
	mbf_ReadCoils = 1,
	mbf_ReadInputs = 2,
	mbf_ReadHoldingRegisters = 3,
	mbf_ReadInputRegisters = 4,
	mbf_WriteSingleCoil = 5,
	mbf_WriteSingleRegister = 6,
	mbf_Diagnostics = 8,
	mbf_WriteMultipleCoils = 15,
	mbf_WriteMultipleRegisters = 16,
	mbf_ReadWriteMultipleRegisters = 23
};

unsigned short CRC16(unsigned char * puchMsg, unsigned short usDataLen);


#endif

