#ifndef _ENGINE_H_
#define _ENGINE_H_

#include "platform.h"
#include "types.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <cglm/call.h>
#include <cglm/cglm.h>
#include <SDL2/SDL.h>

#include "gldefs.h"
#include "render.h"
#include "ui.h"

void cmn_error(char *msg, ...);

void cl_process_event(SDL_Event *e, u64 delta_time);
void cl_init_events(u32 window_width, u32 window_height);

#endif /* _ENGINE_H_ */
