#ifndef __MODBUS_MESSAGE_FACTORY__
#define __MODBUS_MESSAGE_FACTORY__

#include "ModbusMessage.h"

class ModbusMessageFactory{

public:

	static ModbusMessage * create_modbus_request(unsigned char * data, unsigned int size);

};


#endif