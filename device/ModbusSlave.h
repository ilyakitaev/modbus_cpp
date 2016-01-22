#ifndef  __MODBUS_SLAVE__
#define  __MODBUS_SLAVE__

#include "data\DataStore.h"
#include "io\ModbusTransport.h"
#include "messages\ModbusMessage.h"
#include "messages\ReadCoilsInputsRequest.h"
#include "messages\ReadCoilsInputsResponse.h"
#include "messages\ReadHoldingInputRegistersRequest.h"
#include "messages\ReadHoldingInputRegistersResponse.h"
#include "messages\WriteMultipleRegistersRequest.h"
#include "messages\WriteMultipleRegistersResponse.h"
#include "messages\WriteSingleRegistersRequest.h"
#include "messages\WriteSingleRegistersResponse.h"
#include "data\ModbusDataCollection.h"


class ModbusSlave{

protected:
	ModbusTransport * transport;

public:
	ModbusSlave(){
		transport = NULL;
	}

	DataStore data_store;

	virtual void listen() = 0;

	void byte_to_bit(const unsigned char * bytes, unsigned char * bits, unsigned int bytes_count);

	ModbusMessage * read_discretes(ReadCoilsInputsRequest * request);

	ModbusMessage * read_registers(ReadHoldingInputRegistersRequest * request);

	ModbusMessage * write_registers(WriteMultipleRegistersRequest* request);
	ModbusMessage * write_register(WriteSingleRegistersRequest* request);

	ModbusMessage * apply_request(ModbusMessage * request);

	void reset() { if (transport) { transport->reset(); } }
};

typedef  ModbusSlave *  LPIModbusSlave;

#endif