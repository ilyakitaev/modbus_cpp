#include "ModbusSlaveSerial.h"
#include "messages/ModbusMessageFactory.h"
#include <vector>

void ModbusSlaveSerial::listen(){

	const int data_buffer_size = 1024;
	std::vector<unsigned char> data_buffer(data_buffer_size);
	
	unsigned char * data_buff_addr = &(*data_buffer.begin());

	while(true){
		int count = transport->read_request( data_buff_addr, data_buffer_size);

		ModbusMessage * request = ModbusMessageFactory::create_modbus_request( data_buff_addr, count);

		ModbusMessage * response = apply_request(request);

		transport->write(response);

		if (data_store.holding_registers_h){
			if (request->function_code==mbf_WriteMultipleRegisters){
				data_store.holding_registers_h(&data_store, 
					((WriteMultipleRegistersRequest*)request)->start_address, 
					((WriteMultipleRegistersRequest*)request)->num_points, 
					data_store.holding_registers_param);
			}else if (request->function_code==mbf_WriteSingleRegister){
				data_store.holding_registers_h(&data_store, 
					((WriteMultipleRegistersRequest*)request)->start_address, 
					1, 
					data_store.holding_registers_param);
			}
			
		}


		delete request;
		delete response;
		Sleep(0);
	}
}