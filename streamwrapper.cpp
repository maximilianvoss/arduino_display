#include "streamwrapper.h"
#include "StreamBridge.h"


void streamwrapper_begin() {
	StreamBridge.begin();
}

int streamwrapper_read(void *data, size_t length) {
	StreamBridge.read(data, length);
}

void streamwrapper_write(void *data, size_t length) {
	StreamBridge.write(data, length);
}