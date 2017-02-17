#include <string.h>
#include "display.h"
//#include "../wrapper/bridge.h"

void display_initDisplay(display_t *display) {
	memset(display, '\0', sizeof(display_t));
	
}


void display_render(display_t *display) {
//	streambridge_write(display, sizeof(display_t));	
}
