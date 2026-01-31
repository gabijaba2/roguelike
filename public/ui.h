#ifndef _UI_H_
#define _UI_H_

typedef enum 
{
	DIRECTION_UP,
	DIRECTION_DOWN,
	DIRECTION_LEFT,
	DIRECTION_RIGHT
} direction_t;

typedef enum
{
	LINESTYLE_SINGLE,
	LINESTYLE_DOUBLE
} linestyle_t;

void ui_emit_line(u8 tile_index, u16 startX, u16 startY, u16 length, direction_t direction);
void ui_emit_string(char *str, u16 startX, u16 startY, direction_t direction);
void ui_emit_tile(u8 tile_index, u16 x, u16 y, u8 color);
void ui_emit_box(u16 x, u16 y, u16 width, u16 height, linestyle_t line_type, u8 color);
void ui_emit_window(u16 x, u16 y, u16 width, u16 height, linestyle_t line_type, u8 color, char *title);


#endif /* _UI_H_ */
