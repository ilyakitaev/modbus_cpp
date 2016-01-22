#ifndef __READCOILS_INPUT_RESPONSE__
#define __READCOILS_INPUT_RESPONSE__

class ReadCoilsInputsResponse: public ModbusMessage{
public:

	ReadCoilsInputsResponse(unsigned char addr, 
		unsigned char code,
		unsigned char byteCount): ModbusMessage(addr, code){
			frame.assign(2 + 1 + byteCount, 0);
			frame[0] = addr;
			frame[1] = code;
			frame[2] = byteCount;
	}

};



#endif