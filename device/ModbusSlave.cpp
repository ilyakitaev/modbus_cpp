#include "ModbusSlave.h"
#include "Modbus.h"

void ModbusSlave::byte_to_bit(const unsigned char * bytes, unsigned char * bits, unsigned int bytes_count){
	if(!bytes){
		throw "ModbusSlave::byte_to_bit: bytes is NULL";
	}
	if(!bits){
		throw "ModbusSlave::byte_to_bit: bits is NULL";
	}

	unsigned char bits_count = 0;
	unsigned char b;
	while (bytes_count){
		b = (*bytes)?0x01:0x00;
		*bits |= b<<bits_count;			
		bytes_count--;
		bits_count++;
		if (bits_count == 8){
			bits_count = 0;
			bits++;
		}
	}
}

ModbusMessage * ModbusSlave::read_registers(ReadHoldingInputRegistersRequest * request){
	if (!request){
		throw "ModbusSlave::read_registers: request is NULL";
	}
	if (data_store.HoldingRegisters.size() < (request->start_address + request->num_points) ){
		throw "ModbusSlave::read_registers: Too many coils requested";
	}

	unsigned char num_bytes = request->num_points*2;

	ReadHoldingInputRegistersResponse * resp = new ReadHoldingInputRegistersResponse(request->slave_addr, 
		request->function_code, 
		num_bytes );

	data_store.HoldingRegisters.block_data();
	const unsigned short * from = data_store.HoldingRegisters.get_data() + request->start_address;
	unsigned short * to = (unsigned short *)&(*(resp->frame.begin()+3));

	for (int i =0; i < request->num_points; ++ i){
		to[i] = from[i]<<8 | from[i]>>8&0x00FF;
		//to[i] = from[i];
	}
	data_store.HoldingRegisters.release_data();

	return resp;
}

ModbusMessage * ModbusSlave::write_registers(WriteMultipleRegistersRequest* request){
	if (!request){
		throw "ModbusSlave::write_registers: request is NULL";
	}
	if (data_store.HoldingRegisters.size() < (request->start_address + request->num_points) ){
		throw "ModbusSlave::write_registers: Too many coils requested";
	}

	WriteMultipleRegistersResponse * resp = new WriteMultipleRegistersResponse(request->slave_addr, 
		request->function_code, request->start_address, request->num_points );

	unsigned short * from = (unsigned short *)&(*(request->frame.begin()+7));

	for (int i=0; i < request->num_points; ++i){
		unsigned short val = from[i]<<8 | from[i]>>8&0x00FF;
		data_store.HoldingRegisters.set_item(i+request->start_address, val);		
	}

	return resp;
}

ModbusMessage * ModbusSlave::write_register(WriteSingleRegistersRequest* request){
	if (!request){
		throw "ModbusSlave::write_registers: request is NULL";
	}
	
	WriteSingleRegistersResponse * resp = new WriteSingleRegistersResponse(request->slave_addr, 
		request->function_code, request->start_address, request->val );

	unsigned short * from = (unsigned short *)&(*(request->frame.begin()+4));

	unsigned short val = from[0]<<8 | from[0]>>8&0x00FF;
	data_store.HoldingRegisters.set_item(request->start_address, val);		

	return resp;
}

ModbusMessage * ModbusSlave::read_discretes(ReadCoilsInputsRequest * request){
	if (!request){
	   throw "ModbusSlave::read_discretes: request is NULL";
	}


	if (data_store.CoilDiscretes.size() < (request->start_address + request->num_points) ){
		throw "ModbusSlave::read_discretes: Too many coils requested";
	}

	unsigned char num_bytes = request->num_points/8 + (request->num_points%8 > 0)?1:0;

	ReadCoilsInputsResponse * resp = new ReadCoilsInputsResponse(request->slave_addr, 
	   request->function_code, 
	   num_bytes );

	data_store.CoilDiscretes.block_data();
	const unsigned char * from = data_store.CoilDiscretes.get_data() + request->start_address;
	unsigned char * to = &(*(resp->frame.begin()+3));
	
	byte_to_bit( from, to, request->num_points);
	data_store.CoilDiscretes.release_data();

	return resp;

}

ModbusMessage * ModbusSlave::apply_request(ModbusMessage  * request){
	ModbusMessage * response;
	switch ((ModbusFunctions)request->function_code)
	{
	case mbf_ReadCoils:
		response = read_discretes((ReadCoilsInputsRequest*)request);
		break;
	case mbf_ReadInputs:
		//response = ReadDiscretes((ReadCoilsInputsRequest) request, DataStore, DataStore.InputDiscretes);
		//break;
	case mbf_ReadHoldingRegisters:
		response = read_registers((ReadHoldingInputRegistersRequest*) request);
		break;
	//case mbf_ReadInputRegisters:
		//response = ReadRegisters((ReadHoldingInputRegistersRequest) request, DataStore, DataStore.InputRegisters);
		//break;
	//case mbf_Diagnostics:
		//response = request;
		//break;
	//case mbf_WriteSingleCoil:
		//response = WriteSingleCoil((WriteSingleCoilRequestResponse) request, DataStore, DataStore.CoilDiscretes);
		//break;
	case mbf_WriteSingleRegister:
		response = write_register((WriteSingleRegistersRequest*) request);
		break;
	//case mbf_WriteMultipleCoils:
		//response = WriteMultipleCoils((WriteMultipleCoilsRequest) request, DataStore, DataStore.CoilDiscretes);
		//break;
	case mbf_WriteMultipleRegisters:
		response = write_registers((WriteMultipleRegistersRequest*) request);
		break;
	//case mbf_ReadWriteMultipleRegisters:
		//ReadWriteMultipleRegistersRequest readWriteRequest = (ReadWriteMultipleRegistersRequest) request;
		//response = ReadRegisters(readWriteRequest.ReadRequest, DataStore, DataStore.HoldingRegisters);
		//WriteMultipleRegisters(readWriteRequest.WriteRequest, DataStore, DataStore.HoldingRegisters);
		//break;
	default:
		throw "ModbusSlave::apply_request: function not implemented";
	}			

	return response;
}