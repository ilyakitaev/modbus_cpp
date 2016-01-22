// nmodbus++.cpp : Defines the entry point for the console application.
//

#include "device/ModbusSlaveSerial.h"
#include "data/DataStore.h"

void registers_h(DataStore* data_store, int from, int count, void*){
	if(!data_store){
		printf("registers_h: data_store is NULL\n");
		return;
	}

	printf("Registers set: ");
	for (int i = 0; i<count; ++i){
		const unsigned short * data = &(*(data_store->HoldingRegisters.get_data() + from));
		printf("%d, ", data[i]);
	}
}

int main(int argc, char * argv[]){

	try{
	ModbusSlave * sl = ModbusSlaveSerial::create_rtu(1, argv[1]);

	sl->data_store.holding_registers_h = registers_h;
	sl->data_store.HoldingRegisters.set_item(0, 1); //brigada
	sl->data_store.HoldingRegisters.set_item(1, 2); //production
	sl->data_store.HoldingRegisters.set_item(2, 1); //active
	sl->data_store.HoldingRegisters.set_item(10, 99); //count % 1000
	sl->data_store.HoldingRegisters.set_item(11, 0); //((count / 1000) % 1000)
	sl->data_store.HoldingRegisters.set_item(12, 0); //((count / 1000000) % 1000)
	sl->data_store.HoldingRegisters.set_item(13, 1); //day
	sl->data_store.HoldingRegisters.set_item(14, 1); //mon
	sl->data_store.HoldingRegisters.set_item(15, 2009); //year
	sl->data_store.HoldingRegisters.set_item(16, 15); //hour
	sl->data_store.HoldingRegisters.set_item(17, 15); //min

	sl->listen();
	}catch(const char * e){
		printf("Exception: %s", e);
	}

	return 0;
}

