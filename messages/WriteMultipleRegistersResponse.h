#ifndef __WRITEMUL_REGISTERS_RESPONSE__
#define __WRITEMUL_REGISTERS_RESPONSE__

class WriteMultipleRegistersResponse: public ModbusMessage{
public:

	WriteMultipleRegistersResponse(unsigned char addr, 
		unsigned char code,
		unsigned char start_addr,
		unsigned char byteCount): ModbusMessage(addr, code){
			frame.assign(2 + 2 + 2, 0);
			frame[0] = addr;
			frame[1] = code;
			frame[2] = 0;
			frame[3] = start_addr;
			frame[4] = 0;
			frame[5] = byteCount;
			
	}

};



#endif