#include "StreamBridge.hpp"

StreamBridgeClass::StreamBridgeClass(Stream &_stream) : stream(_stream), started(false) {
}

void StreamBridgeClass::begin() {
	if ( started )
		return;
	started = true;

	// Wait for U-boot to finish startup
	do {
		dropAll();
		delay(1000);
	} while ( stream.available() > 0 );

	while ( true ) {
		delay(1000);
		if (checkStatus()) {
			return;
		}

		stream.print((char) 3);
		delay(250);
		stream.print(F("\n"));
		delay(250);
		stream.print(F("\n"));
		delay(500);
		
		stream.print("/tmp/cstreammultiplexer server /dev/console\n");
		delay(500);
		
		if ( stream.available() > 0 ) {
			dropAll();
		}

		if ( !checkStatus() ) {
			delay(1000);
			continue;
		}
		return;
	}
}

boolean StreamBridgeClass::checkStatus() {
	char buffer[11];
	int readCount;

	stream.print("!Me:Status!");
	readCount = read(buffer, 11);
	
	stream.print(buffer);
	if ( readCount && ( !strncmp("!Me:Status!", buffer, 11) ) ) {
		return true;
	}
	return false;
}

int StreamBridgeClass::read(void *data, size_t length) {
	return stream.readBytes((char *) data, length);
}

void StreamBridgeClass::write(void *data, size_t length) {
	if ( stream.available() > 0 ) {
		dropAll();
	}
	stream.write((char *) data, length);
}

void StreamBridgeClass::dropAll() {
	while ( stream.available() > 0 ) {
		stream.read();
	}
}

// Bridge instance
#if defined(SERIAL_PORT_LINUXBRIDGE)
SerialStreamBridgeClass StreamBridge(SERIAL_PORT_LINUXBRIDGE);
#elif defined(SERIAL_PORT_HARDWARE)
SerialStreamBridgeClass StreamBridge(SERIAL_PORT_HARDWARE);
#elif defined(SERIAL_PORT_HARDWARE_OPEN)
SerialStreamBridgeClass StreamBridge(SERIAL_PORT_HARDWARE_OPEN);
#elif defined(__AVR_ATmega32U4__) // Legacy fallback
// Leonardo variants (where HardwareSerial is Serial1)
SerialStreamBridgeClass StreamBridge(Serial1);
#else
SerialStreamBridgeClass StreamBridge(Serial);
#endif

