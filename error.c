#include "engine.h"

void cmn_error(char *msg, ...)
{
	va_list argptr;
	char str[1024];

	va_start( argptr, msg );
	vsprintf( str, msg, argptr );
	va_end( argptr );

	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "roguelike fatal error", str, NULL);
	exit(1);
}
