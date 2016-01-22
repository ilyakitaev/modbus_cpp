#ifndef __MODBUS_MESSAGE__
#define __MODBUS_MESSAGE__

#include <vector>

class ModbusMessage{
public:

	unsigned char slave_addr, function_code;
	std::vector<unsigned char> frame;

	ModbusMessage(const unsigned char * data, unsigned int data_size): 
		slave_addr(data[0]), 
		function_code(data[1]),
		frame(data, data+data_size)
		{}

	ModbusMessage(unsigned char addr, unsigned char code): 
		slave_addr(addr), 
		function_code(code)
	{}

	static const int MinRequestFrameLength = 3;

};


#endif