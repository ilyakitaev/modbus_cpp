#ifndef __READHOLDIN_REGISTERS_REQUEST__
#define __READHOLDIN_REGISTERS_REQUEST__

#include "ModbusMessage.h"

class ReadHoldingInputRegistersRequest: public ModbusMessage{
public:

	unsigned short start_address, num_points;

	ReadHoldingInputRegistersRequest(const unsigned char * data, unsigned int data_size): ModbusMessage(data, data_size){
		start_address = data[2]<< 8 | data[3] ;
		num_points = data[4]<< 8 | data[5] ;
	}

};

#endif