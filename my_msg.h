#ifndef my_msg_h
#define my_msg_h

#include <Arduino.h>
#include <string.h>
#include <stdint.h>

#define MAX_ATTACHED_DS18B20 7
#define UNDEFINDED_VALUE -127

typedef enum {
	V_TEMP, 
	V_HUM, V_LIGHT, V_DIMMER, V_PRESSURE, V_FORECAST, V_RAIN,
	V_RAINRATE, V_WIND, V_GUST, V_DIRECTION, V_UV, V_WEIGHT, V_DISTANCE,
	V_IMPEDANCE, V_ARMED, V_TRIPPED, V_WATT, V_KWH, V_SCENE_ON, V_SCENE_OFF,
	V_HEATER, V_HEATER_SW, V_LIGHT_LEVEL, V_VAR1, V_VAR2, V_VAR3, V_VAR4, V_VAR5,
	V_UP, V_DOWN, V_STOP, V_IR_SEND, V_IR_RECEIVE, V_FLOW, V_VOLUME, V_LOCK_STATUS,
	V_DUST_LEVEL, V_VOLTAGE, V_CURRENT
} my_sensor_data;

typedef enum {
  S_T_OUTSIDE, S_H_OUTSIDE,
  S_T_INDOOR, S_P_INDOOR, S_H_INDOOR,
  S_T_BOILER_OUT, S_T_BOILER_RET,
  S_T_RADIATOR_INP, S_T_RADIATOR_RET, 
  S_T_FLOOR_INP, S_T_FLOOR_RET
}  my_sensor_id;

class my_msg {
public:
	my_msg();
	my_msg(uint8_t sensor, uint8_t type);
	
	void print();
	
	my_msg& setType(uint8_t type);
	my_msg& setSensor(uint8_t sensor);


   float getFloat() const;
   char* getString(char *buffer) const;
	
   my_msg& set(float value, uint8_t decimals);
   static String getSensorName(uint8_t sensorId);
	
	uint8_t type;            	 // 8 bit - Type varies depending on command
	uint8_t sensor;          	 // 8 bit - Id of sensor that this message concerns.
	union {
		uint8_t bValue;
		unsigned long ulValue;
		long lValue;
		unsigned int uiValue;
		int iValue;
		struct { // Float messages
			float fValue;
			uint8_t fPrecision;   // Number of decimals when serializing
		};
	}  __attribute__((packed));

} __attribute__((packed));

#endif
