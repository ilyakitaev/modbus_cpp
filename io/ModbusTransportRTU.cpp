#include "ModbusTransportRTU.h"
#include "Modbus.h"

unsigned int ModbusTransportRTU::read_request(unsigned char * buffer, unsigned int buffer_size){
	if (!buffer){
		throw "ModbusTransportRTU::read_request: buffer is NULL";
	}

	if (!device.is_initialized()){
		throw "ModbusTransportRTU: com device is not initialized.";
	}

	//TODO check buffer length!!!!

	device.read( buffer, RequestFrameStartLength);
	int end_bytes = 0;
	try	{
		end_bytes = request_bytes_to_read( buffer, buffer_size);
	}catch (const char * e){
		printf("Exception: %s\n", e);
	}
	
	device.read( buffer + RequestFrameStartLength, end_bytes);

	/*for (int i=0; i < RequestFrameStartLength + end_bytes; ++i){
		printf("%X ", buffer[i]);
	}
	printf("\n");*/

	return RequestFrameStartLength + end_bytes;
}

unsigned int ModbusTransportRTU::request_bytes_to_read(unsigned char * buffer, unsigned int buffer_size){
	if (!buffer){
		throw "ModbusTransportRTU::request_bytes_to_read: buffer is NULL";
	}
	//TODO check buffer length!!!!
	unsigned char func_code = buffer[1];
	unsigned int num_bytes = 0, byteCount = 0;

	switch((ModbusFunctions)func_code){
		case mbf_ReadCoils:
		case mbf_ReadInputs:
		case mbf_ReadHoldingRegisters:
		case mbf_ReadInputRegisters:
		case mbf_WriteSingleCoil:
		case mbf_WriteSingleRegister:
		case mbf_Diagnostics:
			num_bytes = 1;
			break;
		case mbf_WriteMultipleCoils:
		case mbf_WriteMultipleRegisters:
			byteCount = buffer[6];
			num_bytes = byteCount + 2;
			break;
		default:			
			throw "ModbusTransportRTU::request_bytes_to_read: function code not implemented.";
	}
	return num_bytes;
}