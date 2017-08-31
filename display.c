#include <string.h>
#include <logging.h>
#include "display.h"
#include "streamwrapper.h"

void display_initDisplay(display_t *display) {
	memset(display, '\0', sizeof(display_t));
}

void display_render(display_t *display) {
	streamwrapper_write(display, sizeof(display_t));
}

void display_updateColor(display_t *display, uint8_t x, uint8_t y, color_t *color) {
	uint8_t colorInt = 0xFF;
	
	if ( x >= DISPLAY_WIDTH || y >= DISPLAY_WIDTH ) {
		return;
	}
	
	if ( color->r ) {
		colorInt &= 0b00110000;
	}
	if ( color->g ) {
		colorInt &= 0b00001100;
	}
	if ( color->b ) {
		colorInt &= 0b00000011;
	}
	display->data[x][y] = colorInt;
}