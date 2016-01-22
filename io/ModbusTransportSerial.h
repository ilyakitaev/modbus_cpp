#ifndef __MODBUS_TRANSPORTSERIAL__
#define __MODBUS_TRANSPORTSERIAL__

#include <windows.h>
#include "ModbusTransport.h"
#include "DeviceSerial.h"

class ModbusTransportSerial: ModbusTransport{
protected:
	DeviceSerial device;
public:

	ModbusTransportSerial(const char * dev_name){
		device.open(dev_name);
	};

	virtual unsigned int read_request(unsigned char * buffer, unsigned int buffer_size) = 0;

	virtual void prepare_response(ModbusMessage * message) = 0;
	virtual void write(ModbusMessage * message){
		prepare_response(message);
		device.write( &(*(message->frame.begin())),  message->frame.size());
	}
	virtual void reset(){ device.reset(); }
};

#endif