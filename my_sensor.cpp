#include "my_sensor.h"


my_sensor::my_sensor(uint8_t _cepin, uint8_t _cspin) : RF24(_cepin, _cspin) {
}

void my_sensor::begin(bool _isGateway) {
  Serial.println("\nSetup RF24...");
  isGateway = _isGateway;
  RF24::begin();
  if (!RF24::isPVariant()) {
	Serial.println("RF24 check wires");
	while(1);
  }

  RF24::setDataRate(RF24_250KBPS);
  RF24::setPALevel(RF24_PA_MAX);
  RF24::setRetries(15,15);

  if (isGateway) {
	RF24::openWritingPipe(BASE_RADIO_ID2);
	RF24::openReadingPipe(1, BASE_RADIO_ID);
  }
  else {
	RF24::openWritingPipe(BASE_RADIO_ID);
    RF24::openReadingPipe(1,BASE_RADIO_ID2);
  }
  RF24::startListening(); 
  RF24::printDetails();
  Serial.println();
}

bool my_sensor::sendMsg(my_msg &message) {
  Serial.println("Message sending...");
  message.print();
  RF24::stopListening();
  bool ok = RF24::write(&message, sizeof(my_msg));
  if (ok) 
	Serial.println("TX ok");
  else
	Serial.println("TX ERROR");
    
	RF24::startListening();

    // Wait here until we get a response, or timeout (250ms)
    unsigned long started_waiting_at = millis();
    bool timeout = false;
    while ( ! RF24::available() && ! timeout )
      if (millis() - started_waiting_at > 200 )
        timeout = true;

    // Describe the results
    if ( timeout )
    {
      printf("Failed, response timed out.\n\r");
    }
    else
    {
      // Grab the response, compare, and send to debugging spew
      unsigned long got_time;
      RF24::read( &got_time, sizeof(unsigned long) );

      // Spew it
      printf("Got response %lu, round-trip delay: %lu\n\r",got_time,millis()-got_time);
    }
  return ok;
}

bool my_sensor::readMsg(my_msg &message) {
	uint8_t pipe;
	boolean available = RF24::available(&pipe);

	if (!available || pipe>6)
		return false;
		
    Serial.println("Radio available");
	bool ok = RF24::read(&message, sizeof(my_msg));
    if (ok) {
        Serial.println("RX ok");
		message.print();
    }
	else
	   Serial.println("RX ERROR");
    Serial.println("Radio done");
	return ok;  
}