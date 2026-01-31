#include "engine.h"

void ui_emit_line(u8 tile_index, u16 startX, u16 startY, u16 length, direction_t direction) {

	assert(g_r_tile_draw_list_count + length <= g_r_tile_draw_list_size);
	assert(direction <= DIRECTION_RIGHT && direction >= DIRECTION_UP);

	for(int i = 0; i < length; i++) 
	{
		int list_index = g_r_tile_draw_list_count + i;
		switch(direction)
		{
			case DIRECTION_UP:
				g_r_tile_draw_list[list_index].coordinates[0] = startX;
				g_r_tile_draw_list[list_index].coordinates[1] = startY - i;
				break;
	
			case DIRECTION_DOWN:
				g_r_tile_draw_list[list_index].coordinates[0] = startX;
				g_r_tile_draw_list[list_index].coordinates[1] = startY + i;
				break;

			case DIRECTION_LEFT:
				g_r_tile_draw_list[list_index].coordinates[0] = startX - i;
				g_r_tile_draw_list[list_index].coordinates[1] = startY;
				break;

			case DIRECTION_RIGHT:
				g_r_tile_draw_list[list_index].coordinates[0] = startX + i;
				g_r_tile_draw_list[list_index].coordinates[1] = startY;
				break;
		}
		g_r_tile_draw_list[list_index].character_id = tile_index;
		g_r_tile_draw_list[list_index].color = 0x0F;
	}
	g_r_tile_draw_list_count += length;
}

void ui_emit_string(char *str, u16 startX, u16 startY, direction_t direction) {

	int length = strlen(str);

	assert(g_r_tile_draw_list_count + length <= g_r_tile_draw_list_size);
	assert(direction <= DIRECTION_RIGHT && direction >= DIRECTION_UP);

	for(int i = 0; i < length; i++) 
	{
		int list_index = g_r_tile_draw_list_count + i;
		switch(direction)
		{
			case DIRECTION_UP:
				g_r_tile_draw_list[list_index].coordinates[0] = startX;
				g_r_tile_draw_list[list_index].coordinates[1] = startY - i;
				break;
	
			case DIRECTION_DOWN:
				g_r_tile_draw_list[list_index].coordinates[0] = startX;
				g_r_tile_draw_list[list_index].coordinates[1] = startY + i;
				break;

			case DIRECTION_LEFT:
				g_r_tile_draw_list[list_index].coordinates[0] = startX - i;
				g_r_tile_draw_list[list_index].coordinates[1] = startY;
				break;

			case DIRECTION_RIGHT:
				g_r_tile_draw_list[list_index].coordinates[0] = startX + i;
				g_r_tile_draw_list[list_index].coordinates[1] = startY;
				break;
		}
		g_r_tile_draw_list[list_index].character_id = str[i];
		g_r_tile_draw_list[list_index].color = 0x0F;
	}
	g_r_tile_draw_list_count += length;
}

void ui_emit_tile(u8 tile_index, u16 x, u16 y, u8 color) 
{
	g_r_tile_draw_list[g_r_tile_draw_list_count].coordinates[0] = x;
	g_r_tile_draw_list[g_r_tile_draw_list_count].coordinates[1] = y;
	g_r_tile_draw_list[g_r_tile_draw_list_count].character_id = tile_index;
	g_r_tile_draw_list[g_r_tile_draw_list_count].color = color;

	g_r_tile_draw_list_count++;
}

void ui_emit_box(u16 x, u16 y, u16 width, u16 height, linestyle_t line_type, u8 color)
{
	if(width < 3 || height < 3)
		return;

	int single_line_style[] = 
	{
		179, // vertical
		196, // horizontal
		218, // top left corner
		191, // top right corner
		192, // bottom left corner
		217, // bottom right corner
	};	

	int double_line_style[] = 
	{
		186, // vertical
		205, // horizontal
		201, // top left corner
		187, // top right corner
		200, // bottom left corner
		188, // bottom right corner
	};	

	int *line_style;	

	if(line_type == LINESTYLE_SINGLE)
		line_style = single_line_style;
	else
		line_style = double_line_style;

	// box top
	ui_emit_tile(line_style[2], x, y, color);
	ui_emit_line(line_style[1], x+1, y, width-2, 3);
	ui_emit_tile(line_style[3], x + width - 1, y, color);

	// box sides
	ui_emit_line(line_style[0], x, y+1, height-2, 1);
	ui_emit_line(line_style[0], x + width - 1, y+1, height-2, 1);

	//box bottom
	ui_emit_tile(line_style[4], x, y + height - 1, color);
	ui_emit_line(line_style[1], x+1, y + height - 1, width-2, 3);
	ui_emit_tile(line_style[5], x + width - 1, y + height - 1, color);

}

void ui_emit_window(u16 x, u16 y, u16 width, u16 height, linestyle_t line_type, u8 color, char *title)
{
	if(width < 3 || height < 3)
		return;

	int single_line_style[] = 
	{
		179, // vertical
		196, // horizontal
		218, // top left corner
		191, // top right corner
		192, // bottom left corner
		217, // bottom right corner
	};	

	int double_line_style[] = 
	{
		186, // vertical
		205, // horizontal
		214, // top left corner
		183, // top right corner
		200, // bottom left corner
		188, // bottom right corner
	};	

	int *line_style;	

	if(line_type == LINESTYLE_SINGLE)
		line_style = single_line_style;
	else
		line_style = double_line_style;
	
	u32 title_length = strlen(title);
	if(title_length > width-5)
		width = title_length + 5;

	u32 left_padding = (width-3 - title_length) / 2;

	// box top
	ui_emit_tile(line_style[2], x, y, color);
	ui_emit_line(240, x+1, y, width-2, 3);
	ui_emit_tile(line_style[3], x + width - 1, y, color);
	ui_emit_tile('X', x + width - 2, y, color);

	// box sides
	ui_emit_line(line_style[0], x, y+1, height-2, 1);
	ui_emit_line(line_style[0], x + width - 1, y+1, height-2, 1);

	//box bottom
	ui_emit_tile(line_style[4], x, y + height - 1, color);
	ui_emit_line(line_style[1], x+1, y + height - 1, width-2, 3);
	ui_emit_tile(line_style[5], x + width - 1, y + height - 1, color);

	ui_emit_string(title, x + left_padding+1, y, DIRECTION_RIGHT);
}
