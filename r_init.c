#include "engine.h"

SDL_Window *g_window = NULL;
SDL_GLContext g_gl_context;

tile_draw_request_t *g_r_tile_draw_list;
u32 g_r_tile_draw_list_count = 0;
u32 g_r_tile_draw_list_size = 0;
GLuint g_r_tile_draw_list_buffer;
float quad_verts[8] = {
	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f
}; 
GLuint g_r_quad_buffer;

//void *g_r_charset_atlas;
GLuint g_r_charset_atlas_tex;

GLuint g_gl_shader_program;

GLuint render_load_shader( const char* source_filepath, GLenum shader_type ) 
{
	FILE *file = NULL;	
	GLuint shader_id;
	int file_size = 0;
	GLchar *source_code = NULL;

	shader_id = glCreateShader(shader_type);
		
	file = fopen(source_filepath, "r");
	if( !file )
		cmn_error("Unable to open shader source file");	

	fseek(file, 0L, SEEK_END);
	file_size = ftell(file);
	rewind(file);

	source_code = malloc(file_size + 1);
	if( !source_code )
		cmn_error("Unable to allocate memory for the shader source code");
	
	source_code[file_size] = 0;
	fread(source_code, 1, file_size, file);
	glShaderSource(shader_id, 1, (const GLchar **)&source_code, NULL);
	glCompileShader(shader_id);

	GLint result = GL_FALSE;
	int info_log_length = 0;

	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);
	glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &info_log_length);
	if( result != GL_TRUE ) 
	{
		if ( info_log_length ) 
		{
			char *shader_error_message = malloc(info_log_length+1);
			if( !shader_error_message )
				cmn_error("Unable to compile shader");

			glGetShaderInfoLog(shader_id, info_log_length, NULL, shader_error_message);
			cmn_error("Error during shader compilation (shader type: %u)\n%s", shader_type, shader_error_message);
		} else 
		{ 
			cmn_error("Unable to compile shader");
		}
	}

	free(source_code);
	fclose(file);

	return shader_id;

}

GLuint render_load_shaders( const char *vertex_source_filepath, const char *fragment_source_filepath )
{
	GLuint vertex_shader_id;
	GLuint fragment_shader_id;
	GLuint program_id;

	vertex_shader_id = render_load_shader(vertex_source_filepath, GL_VERTEX_SHADER);
	fragment_shader_id = render_load_shader(fragment_source_filepath, GL_FRAGMENT_SHADER);

	program_id = glCreateProgram();
	glAttachShader(program_id, vertex_shader_id);
	glAttachShader(program_id, fragment_shader_id);
	glLinkProgram(program_id);

	GLint result = GL_FALSE;
	int info_log_length = 0;

	glGetProgramiv(program_id, GL_LINK_STATUS, &result);
	glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &info_log_length);

	if ( info_log_length )
	{
		char *program_error_message = malloc(info_log_length+1);
		if( !program_error_message )
			cmn_error("Unable to link shader program");

		glGetProgramInfoLog(program_id, info_log_length, NULL, program_error_message);
		cmn_error("Error during shader linking\n%s", program_error_message); 
	}

	glDetachShader(program_id, vertex_shader_id);
	glDetachShader(program_id, fragment_shader_id);

	glDeleteShader(vertex_shader_id);
	glDeleteShader(fragment_shader_id);

	return program_id;
}

void render_tile_init(u32 initial_count)
{
	g_r_tile_draw_list = malloc(initial_count * sizeof(tile_draw_request_t));
	memset(g_r_tile_draw_list, 0, initial_count * sizeof(tile_draw_request_t));
	g_r_tile_draw_list_size = initial_count;

	glGenBuffers(1, &g_r_tile_draw_list_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, g_r_tile_draw_list_buffer);
	glBufferData(GL_ARRAY_BUFFER, initial_count * sizeof(tile_draw_request_t), g_r_tile_draw_list, GL_DYNAMIC_DRAW);
	
	glGenBuffers(1, &g_r_quad_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, g_r_quad_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quad_verts), quad_verts, GL_STATIC_DRAW);	

	glGenTextures(1, &g_r_charset_atlas_tex);
	glBindTexture(GL_TEXTURE_2D, g_r_charset_atlas_tex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, 8, 257*16, 0, GL_RED, GL_UNSIGNED_BYTE, g_r_charset_atlas);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//GLint swizzleMask[] = { GL_RED, GL_RED, GL_RED, GL_ONE };
	//glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_RGBA, swizzleMask);


	g_gl_shader_program = render_load_shaders("tile_vert.glsl", "tile_frag.glsl");

}

void render_init(u32 window_width, u32 window_height) 
{
	if( SDL_Init(SDL_INIT_VIDEO) ) 
		cmn_error("SDL init failure\n");

	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

	g_window = SDL_CreateWindow("roguelike", SDL_WINDOWPOS_CENTERED, 
				    SDL_WINDOWPOS_CENTERED, window_width, window_height, 
				    SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if( !g_window ) 
		cmn_error("Unable to create window\n");

	g_gl_context = SDL_GL_CreateContext( g_window );
	if( !g_gl_context ) 
		cmn_error("Unable to create GL context\n");

	render_load_glfuncs();

	if( SDL_GL_SetSwapInterval( 1 ) )
		fprintf(stderr, "Unable to turn on VSync!\n");

	render_tile_init(100000);

}
