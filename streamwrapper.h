#ifndef ARDUINO_DISPLAY_STREAMWRAPPER_H
#define ARDUINO_DISPLAY_STREAMWRAPPER_H

#include <Arduino.h>

#ifdef __cplusplus
extern "C" {
#endif

void streamwrapper_write(void *data, size_t length);
int streamwrapper_read(void *data, size_t length);
void streamwrapper_begin();

#ifdef __cplusplus
}   
#endif

#endif
