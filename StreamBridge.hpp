#ifndef ARDUINO_STREAMBRIDGE_H
#define ARDUINO_STREAMBRIDGE_H

#ifndef BRIDGE_BAUDRATE
#define BRIDGE_BAUDRATE 250000
#endif

#include <Arduino.h>
#include <HardwareSerial.h>
#include <Stream.h>

class StreamBridgeClass {
public:
	StreamBridgeClass(Stream &_stream);
	void begin();
	int read(void *data, size_t length);
	void write(void *data, size_t length);

private:
	void dropAll();
	bool checkStatus();

private:
	Stream &stream;
	bool started;
};

// This subclass uses a serial port Stream
class SerialStreamBridgeClass : public StreamBridgeClass {
public:
	SerialStreamBridgeClass(HardwareSerial &_serial) : StreamBridgeClass(_serial), serial(_serial) {
		// Empty
	}

	void begin(unsigned long baudrate = BRIDGE_BAUDRATE) {
		serial.begin(baudrate);
		StreamBridgeClass::begin();
	}

private:
	HardwareSerial &serial;
};

extern SerialStreamBridgeClass StreamBridge;

#endif
