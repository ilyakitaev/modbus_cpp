#ifndef __READHOLDIN_REGISTERS_RESPONSE__
#define __READHOLDIN_REGISTERS_RESPONSE__

class ReadHoldingInputRegistersResponse: public ModbusMessage{
public:

	ReadHoldingInputRegistersResponse(unsigned char addr, 
		unsigned char code,
		unsigned char byteCount): ModbusMessage(addr, code){
			frame.assign(2 + 1 + byteCount, 0);
			frame[0] = addr;
			frame[1] = code;
			frame[2] = byteCount;
	}

};



#endif