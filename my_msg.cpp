#include "my_msg.h"
#include <stdio.h>
#include <stdlib.h>

my_msg::my_msg() {
}

my_msg::my_msg(uint8_t _sensor, uint8_t _type) {
	sensor = _sensor;
	type = _type;
}

float my_msg::getFloat() const {
return fValue;
/*
	if (miGetPayloadType() == P_FLOAT32) {
		return fValue;
	} else if (miGetPayloadType() == P_STRING) {
		return atof(data);
	} else {
		return 0;
	}
	*/
}

my_msg& my_msg::setType(uint8_t _type) {
	type = _type;
	return *this;
}

my_msg& my_msg::setSensor(uint8_t _sensor) {
	sensor = _sensor;
	return *this;
}

my_msg& my_msg::set(float value, uint8_t decimals) {
//	miSetLength(5); // 32 bit float + persi
//	miSetPayloadType(P_FLOAT32);
	fValue=value;
	fPrecision = decimals;
	return *this;
}

void my_msg::print() {
	Serial.print("MSG ");
	Serial.print("Sensor=");
	Serial.print(sensor);
	Serial.print(", "); 
	Serial.print(my_msg::getSensorName(sensor));
	Serial.print(", ");
	switch(type) {
//		Serial.print("numTemperatureSensors = ");
//		Serial.println(numTemperatureSensors);
		case V_TEMP:
		    Serial.print("t=");
		    Serial.print(getFloat());
			break;
		case V_PRESSURE:
			Serial.print("P=");
			Serial.print(getFloat());
			break;
		case V_HUM:	
			Serial.print("H=");
			Serial.print(getFloat());
			break;
		default:
			Serial.print("UKNOWN type=");
			Serial.print(type);
			break;
	}
	Serial.print("\n");
}

char* my_msg::getString(char *buffer) const {
	if (buffer != NULL) {
		dtostrf(fValue,2,fPrecision,buffer);
		return buffer;
	} 
	return NULL;
}

String my_msg::getSensorName(uint8_t sensorId) {
	switch(sensorId) {
	   case S_T_OUTSIDE: return "t_Out";    
  	   case S_H_OUTSIDE: return "H_Out";    
	   case S_T_INDOOR: return "t_Ind";   
	   case S_P_INDOOR: return "P_Ind";    
	   case S_H_INDOOR: return "H_Ind";    
	   case S_T_BOILER_OUT: return "t_B_Out";
	   case S_T_BOILER_RET: return "t_B_Ret";    
	   case S_T_RADIATOR_INP: return "t_Rr_Inp"; 
	   case S_T_RADIATOR_RET: return "t_Rr_Ret";  
	   case S_T_FLOOR_INP: return "t_Fl_Inp";  
	   case S_T_FLOOR_RET: return "t_Fl_Ret";      	   
   }
   return "UNKNOWN";
}