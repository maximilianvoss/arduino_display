#ifndef ARDUINO_DISPLAY_DISPLAY_H
#define ARDUINO_DISPLAY_DISPLAY_H

#include <Arduino.h>

#define DISPLAY_HEIGHT 8
#define DISPLAY_WIDTH 8

#define LATCHPIN 3

#define COLUMN_CLOCKPIN 12
#define COLUMN_DATAPIN 11

#define ROW_CLOCKPIN 7
#define ROW_DATAPIN 6

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	uint8_t volatile data[DISPLAY_HEIGHT][DISPLAY_WIDTH];
} display_t;

typedef struct {
	bool r;
	bool g;
	bool b;
} color_t;

void display_initDisplay(display_t *display);
void display_render(display_t *display);
void display_updateColor(display_t *display, uint8_t x, uint8_t y, color_t *color);

#ifdef __cplusplus
}
#endif

#endif
