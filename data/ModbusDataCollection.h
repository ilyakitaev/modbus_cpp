#ifndef _MODBUS_DATACOLLECTION_
#define _MODBUS_DATACOLLECTION_

#include <vector>
#include <string>
#include <windows.h>

template<class T>
class ModbusDataCollection{

private:
	bool allow_zero_item;
	std::vector<T> data;
	CRITICAL_SECTION cs_data;

public:	

	ModbusDataCollection();
	~ModbusDataCollection();

	void insert_item(unsigned int index, T item);
	void set_item(unsigned int index, T item);
	T get_item(unsigned int index);
	void clear_items() { data.clear() } ;
	unsigned int size() { return data.size(); }
	const T * get_data();
	void block_data(){ EnterCriticalSection(&cs_data); }
	void release_data(){ LeaveCriticalSection(&cs_data); }

};

template<class T> 
ModbusDataCollection<T>::ModbusDataCollection(): data(100) {
	InitializeCriticalSection(&cs_data);
}

template<class T> 
ModbusDataCollection<T>::~ModbusDataCollection(){
	DeleteCriticalSection(&cs_data);
}

template<class T> 
void ModbusDataCollection<T>::set_item(unsigned int index, T item){
	EnterCriticalSection(&cs_data);
	if (data.size() < index){
		data.resize(index+50);
	}
	data[index] = item;
	LeaveCriticalSection(&cs_data);
}

template<class T> 
T ModbusDataCollection<T>::get_item(unsigned int index){
	EnterCriticalSection(&cs_data);
	T ret_data = data[index];
	LeaveCriticalSection(&cs_data);
	return ret_data;
}

template<class T> 
void ModbusDataCollection<T>::insert_item(unsigned int index, T item){
	EnterCriticalSection(&cs_data);
	if (data.size() < index){
		data.resize(index+50);
	}
	data.insert( data.begin() + index, item );
	LeaveCriticalSection(&cs_data);
}

template<class T> 
const T* ModbusDataCollection<T>::get_data(){
	return (T*)&(*(data.begin()));
}

#endif