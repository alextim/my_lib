#ifndef my_sensor_h
#define my_sensor_h

#include "my_config.h"
#include "my_msg.h"
#include <stddef.h>

#include <stdarg.h>


#include <Arduino.h>
#include <SPI.h>

#include <RF24.h>
#include <RF24_config.h>

class my_sensor : public RF24
{
  public:
	my_sensor(uint8_t _cepin=DEFAULT_CE_PIN, uint8_t _cspin=DEFAULT_CS_PIN);

	void begin(bool _isGateway = false);

	bool sendMsg(my_msg &message);
	bool readMsg(my_msg &message);
	
	bool isGateway;
};
#endif
