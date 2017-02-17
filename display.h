#ifndef ARDUINO_DISPLAY_H
#define ARDUINO_DISPLAY_H

#include <avr/io.h>

#define DISPLAY_X 8
#define DISPLAY_Y 8

#define LATCHPIN 3

#define COLUMN_CLOCKPIN 12
#define COLUMN_DATAPIN 11

#define ROW_CLOCKPIN 7
#define ROW_DATAPIN 6

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	uint8_t volatile data[DISPLAY_X][DISPLAY_Y];
} display_t;

void display_initDisplay(display_t *display);
void display_render(display_t *display);

#ifdef __cplusplus
}
#endif

#endif
