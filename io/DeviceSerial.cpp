#include "DeviceSerial.h"
#include <stdio.h>

void format_last_error(char * fname, char * buffer){	
	DWORD dw = GetLastError(); 
	FormatMessageA(
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		dw,
		0,
		(LPSTR)buffer,
		1024, NULL );
}

void DeviceSerial::open(const char * dev_name, DWORD baud_rate,  unsigned char parity,  int byte_size, unsigned char stop_bits){
	if (!dev_name){
		throw "DeviceSerial: device name is NULL.";
	 }

	hCom = CreateFileA(dev_name, 
	 GENERIC_WRITE | GENERIC_READ, 
	 0, 
	 NULL, 
	 OPEN_EXISTING, 
	 FILE_ATTRIBUTE_NORMAL, 
	 NULL);  

	if (hCom == INVALID_HANDLE_VALUE){

		char buf[1024];
		memset(buf, 0, 1024);

		format_last_error("DeviceSerial", buf);
		throw buf;
	}

	DCB dcb;
	GetCommState(hCom, &dcb);

	dcb.BaudRate = baud_rate;
	dcb.StopBits = stop_bits;
	dcb.ByteSize = byte_size;
	dcb.Parity = parity;

	SetCommState(hCom, &dcb);

	/*COMMTIMEOUTS CommTimeOuts; 
	CommTimeOuts.ReadIntervalTimeout= 10;
	CommTimeOuts.ReadTotalTimeoutMultiplier = 1;
	// значений этих тайм – аутов вполне хватает для уверенного приема
	// даже на скорости 110 бод
	CommTimeOuts.ReadTotalTimeoutConstant = 100;
	// используется в данном случае как время ожидания посылки
	CommTimeOuts.WriteTotalTimeoutMultiplier = 0;
	CommTimeOuts.WriteTotalTimeoutConstant = 0;
	SetCommTimeouts(handle, &CommTimeOuts); */

	reset();
}

void DeviceSerial::reset(){
	PurgeComm(hCom, PURGE_RXCLEAR);
	PurgeComm(hCom, PURGE_TXCLEAR);
}

void DeviceSerial::check(){
	if (hCom==INVALID_HANDLE_VALUE){
		throw "DeviceSerial: Device not initialized.";
	}
}

void DeviceSerial::read(unsigned char * buffer, unsigned int size){
	check();

	DWORD bytes_read = 0;

	while(size){
		ReadFile(hCom, buffer, size, &bytes_read, NULL);
		size -= bytes_read;
		buffer += bytes_read;
	}
	
}

void DeviceSerial::write(unsigned char * buffer, unsigned int size){
	check();

	DWORD bytes_written = 0;

	/*for (int i=0; i < size; ++i){
		printf("%X ", buffer[i]);
	}
	printf("\n");*/

	while(size){
		WriteFile(hCom, buffer, size, &bytes_written, NULL);
		size -= bytes_written;
		buffer += bytes_written;
	}

}