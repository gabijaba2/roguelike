#include "engine.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

extern bool eng_should_quit;
extern u8 key_state[SDL_NUM_SCANCODES];
extern bool eng_window_focused;
extern bool eng_mouse_grabbed;
extern u8 mouse_state[6];

extern i32 mouse_pos_x;
extern i32 mouse_pos_y;


u32 window_width;
u32 window_height;

int main(int argc, char *argv[])
{
	u64 cur_time = 0;
	u64 prev_time = 0;
	window_width = 1000;
	window_height = 1000;

	render_init(window_width, window_height);
	cl_init_events(window_width, window_height);

	GLuint vertex_array_id;
	glGenVertexArrays(1, &vertex_array_id);
	glBindVertexArray(vertex_array_id);

	glViewport(0, 0, window_width, window_height);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	//glEnable(GL_CULL_FACE);
	//glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LESS);

	while(!eng_should_quit) 
	{
		SDL_Event event;

		/* Limit to 60 fps */
		prev_time = cur_time;
		cur_time = SDL_GetTicks64();

		if ((cur_time - prev_time) < 16666) 
		{
			while (SDL_PollEvent(&event)) 
			{
				cl_process_event(&event, (cur_time - prev_time));
			}
			//SDL_Delay((100000 - (cur_time - prev_time))/1000);
		}	        
		
		bool prev_focus_state = false;	

		if(key_state[SDL_SCANCODE_ESCAPE] && !prev_focus_state) 
		{
			if(eng_mouse_grabbed) 
			{
				eng_mouse_grabbed = false;
				SDL_SetRelativeMouseMode(SDL_FALSE);
				SDL_SetWindowGrab(g_window, SDL_FALSE);
			}	
		}
		prev_focus_state = key_state[SDL_SCANCODE_ESCAPE];		
		
		if(mouse_state[SDL_BUTTON_LEFT] && eng_window_focused && !eng_mouse_grabbed)
		{
				eng_mouse_grabbed = true;
				SDL_SetRelativeMouseMode(SDL_TRUE);
				SDL_SetWindowGrab(g_window, SDL_TRUE);
		}


		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(g_gl_shader_program);


		for(int i = 0; i < 100; i++) 
		{
			ui_emit_tile(i, i, 0, 0xF);
		}
		for(int i = 0; i < 100; i++) 
		{
			ui_emit_tile(i + 100, i, 1, 0xF);
		}
		for(int i = 0; i < 58; i++) 
		{
			ui_emit_tile(i + 200, i, 2, 0xF);
		}
		for(int i = 0; i < 16; i++) 
		{
			ui_emit_tile(176, i, 3, i);
		}
		for(int i = 16; i < 32; i++) 
		{
			ui_emit_tile(177, i, 3, i-16);
		}
		for(int i = 32; i < 48; i++) 
		{
			ui_emit_tile(178, i, 3, i-32);
		}
		for(int i = 48; i < 64; i++) 
		{
			ui_emit_tile(219, i, 3, i-48);
		}

		ui_emit_line(205, 50, 50, 20, DIRECTION_RIGHT);
		ui_emit_line(205, 50, 46, 20, DIRECTION_RIGHT);

		ui_emit_line(186, 49, 49, 3, DIRECTION_UP);
		ui_emit_line(186, 70, 49, 3, DIRECTION_UP);

		ui_emit_line(196, 53, 44, 14, DIRECTION_RIGHT);
		
		
		ui_emit_string("Guys are hot", 54, 48, DIRECTION_RIGHT);
		ui_emit_tile(200, 49,50, 0xF);
		ui_emit_tile(188, 70,50, 0xF);	

		ui_emit_tile(201, 49,46, 0xF);
		ui_emit_tile(187, 70,46, 0xF);

		ui_emit_tile(207, 52,46, 0xF);
		ui_emit_tile(207, 67,46, 0xF);

		ui_emit_tile(179, 52,45, 0xF);
		ui_emit_tile(179, 67,45, 0xF);

		ui_emit_tile(218, 52,44, 0xF);
		ui_emit_tile(191, 67,44, 0xF);

		//emit_char_dirty(179, 52,45);
		ui_emit_string("System message", 53,45,3);
	

		//void draw_box(int x, int y, int width, int height, int line_type)
		ui_emit_box(10,10, 5,5, 1, 0xF);
		ui_emit_box(30,30, 30,10, 1, 0xF);
		//mouse_pos_x
		char buffer[256];
		sprintf(buffer, "Mouse X pos: %i", mouse_pos_x);		
		ui_emit_string(buffer, 33, 33, 3);
		sprintf(buffer, "Mouse Y pos: %i", mouse_pos_y);		
		ui_emit_string(buffer, 33, 34, 3);
		sprintf(buffer, "Mouse button: %i", mouse_state[1]);		
		ui_emit_string(buffer, 33, 35, 3);

		ui_emit_window(100,20, 30, 7, LINESTYLE_DOUBLE, 0xF, "Title test");
		ui_emit_window(100,30, 30, 7, LINESTYLE_SINGLE, 0xF, "Title test");

		r_submit_tile_draw_calls(window_width, window_height, g_r_tile_draw_list, g_r_tile_draw_list_count);
		g_r_tile_draw_list_count = 0;

		SDL_GL_SwapWindow(g_window);

	}
	return 0;
}
