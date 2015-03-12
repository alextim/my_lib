#ifndef my_config_h
#define my_config_h

#define BASE_RADIO_ID 	   ((uint64_t)0xE8E8F0F0E1LL) // This is also act as base value for sensor nodeId addresses. Change this (or channel) if you have more than one sensor network.
#define BASE_RADIO_ID2 	   ((uint64_t)0xE8E8F0F0E1LL) // This is also act as base value for sensor nodeId addresses. Change this (or channel) if you have more than one sensor network.

#define BAUD_RATE 115200


#define DEFAULT_CE_PIN 9
#define DEFAULT_CS_PIN 10


/***
 * Enable/Disable debug logging
 */
#define DEBUG

#endif
