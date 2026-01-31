#ifndef _RENDER_H_
#define _RENDER_H_

typedef struct _tile_draw_request_t {
	u8 coordinates[2];
	u8 character_id;
	u8 color;
} tile_draw_request_t;

typedef struct _re_t {
	SDL_Window *window;
	SDL_GLContext gl_context;
	GLuint gl_shader_program;
	
	tile_draw_request_t *tile_draw_list;
	u32 tile_draw_list_size;
	GLuint tile_draw_list_buffer;

	GLuint quad_buffer;

	u8 *charset_atlas;
	GLuint charset_atlas_tex;
} re_t;

void render_load_glfuncs( void );
void render_init( u32 window_width, u32 window_height );
GLuint render_load_shaders( const char *vertex_source_filepath, const char *fragment_source_filepath );

void r_submit_tile_draw_calls( u32 window_width, u32 window_height, tile_draw_request_t *tiles, u32 number_of_tiles );

extern SDL_Window *g_window;
extern SDL_GLContext g_gl_context;
extern GLuint g_gl_shader_program;

extern tile_draw_request_t *g_r_tile_draw_list;
extern u32 g_r_tile_draw_list_count;
extern u32 g_r_tile_draw_list_size;
extern GLuint g_r_tile_draw_list_buffer;

extern GLuint g_r_quad_buffer;

extern u8 g_r_charset_atlas[];
extern GLuint g_r_charset_atlas_tex;



#endif // _RENDER_H_
