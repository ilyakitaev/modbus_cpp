#ifndef __MODBUS_DATASTORE__
#define __MODBUS_DATASTORE__

#include "ModbusDataCollection.h"

enum data_handler_type{
	DATAH_COILDISCRETES,
	DATAH_INPUTDISCRETES,
	DATAH_HOLDINGREG,
	DATAH_INPUTREG
};


class DataStore{
private:
	

public:

	typedef void (*datah)(DataStore *, int, int, void*);

	DataStore(){
		coil_discretes_h = NULL;
		input_discretes_h = NULL;
		holding_registers_h = NULL;
		input_registers_h = NULL;
	}

	datah coil_discretes_h;
	datah input_discretes_h;
	datah holding_registers_h;
	datah input_registers_h;

	void * coil_discretes_param;
	void * input_discretes_param;
	void * holding_registers_param;
	void * input_registers_param;

	ModbusDataCollection<unsigned char> CoilDiscretes;
	ModbusDataCollection<unsigned char> InputDiscretes;
	ModbusDataCollection<unsigned short> HoldingRegisters;
	ModbusDataCollection<unsigned short> InputRegisters;
};

#endif