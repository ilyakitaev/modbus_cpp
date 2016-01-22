#ifndef __MODBUS_TRANSPORT__
#define __MODBUS_TRANSPORT__

#include "messages/ModbusMessage.h"

class ModbusTransport{

public:
	virtual unsigned int read_request(unsigned char * buffer, unsigned int buffer_size) = 0;
	virtual void prepare_response(ModbusMessage * message) = 0;
	virtual void write(ModbusMessage * message) = 0;
	virtual void reset() = 0;
};

#endif