#include "ModbusMessageFactory.h"
#include "ReadCoilsInputsRequest.h"
#include "ReadHoldingInputRegistersRequest.h"
#include "WriteMultipleRegistersRequest.h"
#include "WriteSingleRegistersRequest.h"
#include "Modbus.h"

ModbusMessage * ModbusMessageFactory::create_modbus_request(unsigned char * data, unsigned int size){

	if (size < ModbusMessage::MinRequestFrameLength)
		throw "ModbusMessageFactory::create_modbus_request: frame length is lesser than minimal length.";

	ModbusMessage * request;
	unsigned char functionCode = data[1];

	switch ((ModbusFunctions)functionCode)
	{
	case mbf_ReadCoils:
	case mbf_ReadInputs:
		request = (ModbusMessage*)new ReadCoilsInputsRequest(data, size);
		break;
	case mbf_ReadHoldingRegisters:
	case mbf_ReadInputRegisters:
		request = (ModbusMessage*)new ReadHoldingInputRegistersRequest(data, size);
		break;
	case mbf_WriteSingleCoil:
		//request = create_modbus_message<WriteSingleCoilRequestResponse>(frame);
		//break;
	case mbf_WriteSingleRegister:
		request = (ModbusMessage*)new WriteSingleRegistersRequest(data, size);
		break;
	case mbf_Diagnostics:
		//request = create_modbus_message<DiagnosticsRequestResponse>(frame);
		//break;
	case mbf_WriteMultipleCoils:
		//request = create_modbus_message<WriteMultipleCoilsRequest>(frame);
		//break;
	case mbf_WriteMultipleRegisters:
		request = (ModbusMessage*)new WriteMultipleRegistersRequest(data, size);
		break;
	case mbf_ReadWriteMultipleRegisters:
		//request = create_modbus_message<ReadWriteMultipleRegistersRequest>(frame);
		//break;
	default:
		throw "ModbusMessageFactory::create_modbus_request: unsupported function code";
	}

	return request;

}