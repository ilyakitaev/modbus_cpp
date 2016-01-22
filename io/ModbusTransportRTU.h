#ifndef __MODBUS_TRANSPORTRTU__
#define __MODBUS_TRANSPORTRTU__

#include "ModbusTransportSerial.h"
#include "Modbus.h"
#include <vector>

class ModbusTransportRTU: ModbusTransportSerial{
public:

	ModbusTransportRTU(const char * dev_name):ModbusTransportSerial(dev_name){}

	static const int RequestFrameStartLength = 7;
	static const int ResponseFrameStartLength = 4;

	unsigned int read_request(unsigned char * buffer, unsigned int buffer_size);
	unsigned int request_bytes_to_read(unsigned char * buffer, unsigned int buffer_size);
	virtual void prepare_response(ModbusMessage * message){
		if (!message){
			throw "ModbusTransportRTU::prepare_response: message is NULL";
		}
		unsigned short crc = CRC16( &(*(message->frame.begin())), message->frame.size() );
		message->frame.push_back( *((unsigned char *)(&crc)) );
		message->frame.push_back( *((unsigned char *)(&crc) + 1) );
	}

};

#endif