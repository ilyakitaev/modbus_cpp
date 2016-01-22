#ifndef __MODBUS_SLAVE_SERIAL__
#define __MODBUS_SLAVE_SERIAL__

#include "device/ModbusSlave.h"
#include "io/ModbusTransportRTU.h"

class ModbusSlaveSerial: public ModbusSlave{

private:
	
	ModbusSlaveSerial(ModbusTransport * t) {
		transport = t;
	}

public:

	static ModbusSlave * create_rtu(unsigned char slave_addr, const char * dev_name){
		if (dev_name == NULL){
			throw "ModbusSlave::create_rtu: dev_name is NULL.";
		}
		ModbusTransportRTU * tr = new ModbusTransportRTU(dev_name);
		ModbusSlaveSerial * sl = new ModbusSlaveSerial((ModbusTransport*)tr);

		return (ModbusSlave *)sl;

	}

	void listen();

	
};

#endif