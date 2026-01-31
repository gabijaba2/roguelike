CC = clang
INCLUDE_DIRS = -I/usr/local/include/ -I./public
CFLAGS = -c -Wall -Wextra $(INCLUDE_DIRS) -g

LDFLAGS = -L/usr/local/lib -lSDL2 -lGL -lm -s
LDFLAGS_DBG = -L/usr/local/lib -lSDL2 -lGL -lm

SRCS = 	main.c r_glloader.c r_init.c r_charset.c r_draw.c error.c cl_events.c ui_emit.c

OBJS = $(SRCS:.c=.o)

TARGET = roguelike

default: $(TARGET)

debug: $(TARGET)_dbg

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(LDFLAGS) $(OBJS) ./lib/freebsd142/cglm-0.9.4/libcglm.a

$(TARGET)_dbg: $(OBJS)
	$(CC) -o $(TARGET)_dbg $(LDFLAGS_DBG) $(OBJS) ./lib/freebsd142/cglm-0.9.4/libcglm.a

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean :
	rm -f *.o $(TARGET) $(TARGET)_dbg
