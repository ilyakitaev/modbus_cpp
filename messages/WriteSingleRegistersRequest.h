#ifndef __WRITESING_REGISTERS_REQUEST__
#define __WRITESING_REGISTERS_REQUEST__

#include "ModbusMessage.h"

class WriteSingleRegistersRequest: public ModbusMessage{
public:

	unsigned short start_address, val;

	WriteSingleRegistersRequest(const unsigned char * data, unsigned short size): ModbusMessage(data, size){
		start_address = data[2]<< 8 | data[3] ;
		val = data[4]<< 8 | data[5] ;
	}

};

#endif