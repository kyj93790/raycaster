#ifndef RAYCASTER_H
# define RAYCASTER_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <mlx.h>

#define mapWidth 24
#define mapHeight 24
#define screenWidth 640
#define screenHeight 480

# define red 0xFF0000
# define sub_red 0x7f0000
# define green 0x00FF00
# define sub_green 0x007f00
# define blue 0x0000FF
# define sub_blue 0x00007f
# define white 0xFFFFFF
# define gray 0x7f7f7f

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_len;
	int		endian;
}	t_img;


/* player info */

// position
float px, py;


/* functions */

// init.c //
void	init(void);

#endif