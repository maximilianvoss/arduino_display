#include <logging.h>
#include "StreamBridge.h"

StreamBridgeClass::StreamBridgeClass(Stream &_stream) : stream(_stream), started(false) {
}

void StreamBridgeClass::begin() {
	DEBUG_MSG("StreamBridgeClass::begin: START");
	if ( started ) {
		DEBUG_MSG("StreamBridgeClass::begin: already started");
		DEBUG_MSG("StreamBridgeClass::begin: DONE");
		return;
	}
	started = true;

	// Wait for U-boot to finish startup
	do {
		DEBUG_MSG("StreamBridgeClass::begin: Wait for U-boot to finish start up");
		dropAll();
		delay(1000);
	} while ( stream.available() > 0 );
	DEBUG_MSG("StreamBridgeClass::begin: U-boot finished start up");

	while ( true ) {
		DEBUG_MSG("StreamBridgeClass::begin: Loop");
		delay(1000);
		if (checkStatus()) {
			DEBUG_MSG("StreamBridgeClass::begin: checkStatus = true");
			DEBUG_MSG("StreamBridgeClass::begin: DONE");
			return;
		}

		DEBUG_MSG("StreamBridgeClass::begin: Start Multiplexer");
		stream.print((char) 3);
		delay(250);
		stream.print(F("\n"));
		delay(250);
		stream.print(F("\n"));
		delay(500);
		
		stream.print(STREAMMULTIPLEXER);
		stream.print("\n");
		delay(500);
		
		if ( stream.available() > 0 ) {
			dropAll();
		}

		DEBUG_MSG("StreamBridgeClass::begin: Check Status");
		if ( !checkStatus() ) {
			DEBUG_MSG("StreamBridgeClass::begin: Status = not okay");
			delay(1000);
			continue;
		}
		DEBUG_MSG("StreamBridgeClass::begin: Status = okay");
		DEBUG_MSG("StreamBridgeClass::begin: DONE");
		return;
	}
}

boolean StreamBridgeClass::checkStatus() {
	DEBUG_MSG("StreamBridgeClass::checkStatus: START");
	char buffer[11];
	int readCount;

	DEBUG_MSG("StreamBridgeClass::checkStatus: write Message");
	stream.print("!Me:Status!");
	readCount = read(buffer, 11);
	
	stream.print(buffer);
	if ( readCount && ( !strncmp("!Me:Status!", buffer, 11) ) ) {
		DEBUG_MSG("StreamBridgeClass::checkStatus: status = okay");
		DEBUG_MSG("StreamBridgeClass::checkStatus: DONE");
		return true;
	}
	DEBUG_MSG("StreamBridgeClass::checkStatus:");
	DEBUG_MSG(buffer);
	DEBUG_MSG("StreamBridgeClass::checkStatus: status = not okay");
	DEBUG_MSG("StreamBridgeClass::checkStatus: DONE");
	return false;
}

int StreamBridgeClass::read(void *data, size_t length) {
	DEBUG_MSG("StreamBridgeClass::read: START");
	DEBUG_MSG("StreamBridgeClass::read: DONE");
	return stream.readBytes((char *) data, length);
}

void StreamBridgeClass::write(void *data, size_t length) {
	DEBUG_MSG("StreamBridgeClass::write: START");
	char boundaries = 0xFF;
	if ( stream.available() > 0 ) {
		dropAll();
	}
	DEBUG_MSG("StreamBridgeClass::write: ");
	DEBUG_MSG((char *) data);
	stream.write(&boundaries, 1);
	stream.write(&boundaries, 1);
	stream.write((char *) &length, sizeof(size_t));
	stream.write(&boundaries, 1);
	stream.write((char *) data, length);
	stream.write(&boundaries, 1);
	stream.write(&boundaries, 1);
	DEBUG_MSG("StreamBridgeClass::write: message done");
	DEBUG_MSG("StreamBridgeClass::write: DONE");
}

void StreamBridgeClass::dropAll() {
	DEBUG_MSG("StreamBridgeClass::dropAll: START");
	while ( stream.available() > 0 ) {
#ifdef DEBUG
		char buffer[1024];
		stream.readBytes(buffer, 1024);
		DEBUG_MSG("StreamBridgeClass::dropAll: ");
		DEBUG_MSG(buffer);
#else
		stream.read();
#endif
	}
	DEBUG_MSG("StreamBridgeClass::dropAll: DONE");
}

#if defined(SERIAL_PORT_LINUXBRIDGE)
SerialStreamBridgeClass StreamBridge(SERIAL_PORT_LINUXBRIDGE);
#elif defined(SERIAL_PORT_HARDWARE)
SerialStreamBridgeClass StreamBridge(SERIAL_PORT_HARDWARE);
#elif defined(SERIAL_PORT_HARDWARE_OPEN)
SerialStreamBridgeClass StreamBridge(SERIAL_PORT_HARDWARE_OPEN);
#elif defined(__AVR_ATmega32U4__) 
SerialStreamBridgeClass StreamBridge(Serial1);
#else
SerialStreamBridgeClass StreamBridge(Serial);
#endif
