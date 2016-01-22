#ifndef __WRITESING_REGISTERS_RESPONSE__
#define __WRITESING_REGISTERS_RESPONSE__

class WriteSingleRegistersResponse: public ModbusMessage{
public:

	WriteSingleRegistersResponse(unsigned char addr, 
		unsigned char code,
		unsigned char start_addr,
		unsigned short val): ModbusMessage(addr, code){
			frame.assign(1 + 1 + 2 + 2, 0);
			frame[0] = addr;
			frame[1] = code;
			frame[2] = *((unsigned char *)&start_addr + 1);
			frame[3] = *((unsigned char *)&start_addr);
			frame[4] = *((unsigned char *)&val + 1);
			frame[5] = *((unsigned char *)&val);

	}

};



#endif