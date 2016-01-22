#ifndef __DEVICE_SERIAL__
#define __DEVICE_SERIAL__

#include <windows.h>

class DeviceSerial{
private:
	HANDLE hCom;

	void check();

public:
	DeviceSerial(){ hCom = INVALID_HANDLE_VALUE; }
	
	void open(const char * dev_name, 
		DWORD baud_rate = 9600, 
		unsigned char parity = NOPARITY, 
		int byte_size = 8, 
		unsigned char stop_bits = ONESTOPBIT);

	void close(){
		if (hCom!=INVALID_HANDLE_VALUE){
			CloseHandle(hCom);
		}
	}

	void read(unsigned char * buffer, unsigned int size);
	void write(unsigned char * buffer, unsigned int size);

	bool is_initialized(){
		return (hCom == INVALID_HANDLE_VALUE)?false:true;
	}

	void reset();
};

#endif
