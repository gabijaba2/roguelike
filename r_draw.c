#include "engine.h"

void r_submit_tile_draw_calls(u32 window_width, u32 window_height, tile_draw_request_t *tiles, u32 number_of_tiles) {

	if(number_of_tiles == 0)
		return;

	glBindBuffer(GL_ARRAY_BUFFER, g_r_tile_draw_list_buffer);

	/* Upload draw list */
	glBufferSubData(GL_ARRAY_BUFFER, 0, number_of_tiles * sizeof(tile_draw_request_t), tiles);
	
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, g_r_quad_buffer);
	glVertexAttribPointer(
		0,
		2,
		GL_FLOAT,
		GL_FALSE,
		2 * sizeof(float),
		NULL
	);
	
	glBindBuffer(GL_ARRAY_BUFFER, g_r_tile_draw_list_buffer);
	
	/* coordinate x */
	glEnableVertexAttribArray(1);
	glVertexAttribIPointer(
		1, 
		1, 
		GL_UNSIGNED_BYTE,
		sizeof(tile_draw_request_t), 
		(const void *)0	
	);
	glVertexAttribDivisor(1, 1);
	
	/* coordinate y */
	glEnableVertexAttribArray(2);
	glVertexAttribIPointer(
		2, 
		1, 
		GL_UNSIGNED_BYTE,
		sizeof(tile_draw_request_t), 
		(const void *)1	
	);
	glVertexAttribDivisor(2, 1);

	/* character id */
	glEnableVertexAttribArray(3);
	glVertexAttribIPointer(
		3, 
		1, 
		GL_UNSIGNED_BYTE,
		sizeof(tile_draw_request_t), 
		(const void *)2	
	);
	glVertexAttribDivisor(3, 1);

	/* color */
	glEnableVertexAttribArray(4);
	glVertexAttribIPointer(
		4, 
		1, 
		GL_UNSIGNED_BYTE,  
		sizeof(tile_draw_request_t), 
		(const void *)3	
	);
	glVertexAttribDivisor(4, 1);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, g_r_charset_atlas_tex);
	glUniform1i(glGetUniformLocation(g_gl_shader_program, "texSampler"), 0);	

	glUniform2f(glGetUniformLocation(g_gl_shader_program, "tileScreenSize"), 8.0f, 16.0f);
	//glUniform2f(glGetUniformLocation(g_gl_shader_program, "tileScreenSize"), window_width / 240.0f, window_height / 65.0f); // 240x65 (67)
	glUniform2f(glGetUniformLocation(g_gl_shader_program, "screenSize"), window_width, window_height);
	glUniform2f(glGetUniformLocation(g_gl_shader_program, "atlasSize"), 1.0f*8.0f, 257.0f*16.0f);
	glUniform2f(glGetUniformLocation(g_gl_shader_program, "tileAtlasSize"), 8.0f, 16.0f);

	glDrawArraysInstanced(GL_TRIANGLE_FAN, 0, 4, number_of_tiles);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
	glDisableVertexAttribArray(4);

}
