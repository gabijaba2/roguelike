#include "engine.h"

u8 key_state[SDL_NUM_SCANCODES] = {0};
bool eng_should_quit = false;
bool eng_window_focused = true;
bool eng_mouse_grabbed = true;
i32 mouse_pos_x = 0;
i32 mouse_pos_y = 0;
u8 mouse_state[6] = {0};

extern u32 window_height;
extern u32 window_width;

void cl_process_event(SDL_Event *e, u64 delta_time) 
{
	switch (e->type) {
	case SDL_KEYDOWN:
	case SDL_KEYUP:
		key_state[e->key.keysym.scancode] = e->key.state;
		
		/* TODO: call client code to handle key press */
		break;
		
	case SDL_MOUSEMOTION:
		mouse_pos_x = e->motion.x;
		mouse_pos_y = e->motion.y;

		//if(mouse_pos_x < 0) mouse_pos_x = 0;
		//if(mouse_pos_x > window_width) mouse_pos_x = window_width;

		//if(mouse_pos_y < 0) mouse_pos_y = 0;
		//if(mouse_pos_y > window_height) mouse_pos_y = window_height;		

		break;
	case SDL_MOUSEBUTTONDOWN:
	case SDL_MOUSEBUTTONUP:
		mouse_state[e->button.button] = e->button.state;
		/* TODO: call client code to handle mouse press */
		break;
		
	case SDL_WINDOWEVENT:
		switch(e->window.event) {
		case SDL_WINDOWEVENT_RESIZED:
			glViewport(0, 0, e->window.data1, e->window.data2);
            /* change mouse_pos_* ?? */
			window_width = e->window.data1;
			window_height = e->window.data2;

			//mouse_pos_x = window_width / 2;
			//mouse_pos_y = window_height / 2;
			break;

		case SDL_WINDOWEVENT_FOCUS_GAINED:
			eng_window_focused = true;

			//if( eng_mouse_grabbed )
			//{
			//	SDL_SetRelativeMouseMode(SDL_TRUE);
			//	SDL_SetWindowGrab(g_window, SDL_TRUE);

			//	mouse_pos_x = window_width / 2;
			//	mouse_pos_y = window_height / 2;
			//}
			break;
		case SDL_WINDOWEVENT_FOCUS_LOST:
			eng_window_focused = false;

			//SDL_SetRelativeMouseMode(SDL_FALSE);
			//SDL_SetWindowGrab(g_window, SDL_FALSE);

			memset(key_state, 0, sizeof(key_state));
			memset(mouse_state, 0, sizeof(mouse_state));
			break;
		}

		break;
	
	case SDL_QUIT:
		eng_should_quit = true;
		break;
	}
}

void cl_init_events(u32 window_width, u32 window_height) 
{
	//SDL_SetRelativeMouseMode(SDL_TRUE);

	//mouse_pos_x = window_width / 2;
	//mouse_pos_y = window_height / 2;


}

