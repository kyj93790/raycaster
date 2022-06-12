#ifndef RAYCASTER_H
# define RAYCASTER_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <mlx.h>

# define mapWidth 24
# define mapHeight 24
# define screenWidth 640
# define screenHeight 480

# define red 0xFF0000
# define sub_red 0x7f0000
# define green 0x00FF00
# define sub_green 0x007f00
# define blue 0x0000FF
# define sub_blue 0x00007f
# define white 0xFFFFFF
# define gray 0x7f7f7f

# define key_press 2
# define buttonpress 4

# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_LA 123
# define KEY_RA 124
# define KEY_ESC 53

# define theta 2 * M_PI / 180
# define del_move 0.5

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_len;
	int		endian;
}	t_img;

typedef struct	s_texture
{
	int	texWidth;
	int texHeight;
	struct s_img	img_n;
	struct s_img	img_s;
	struct s_img	img_w;
	struct s_img	img_e;
}	t_texture;

typedef struct	s_state
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
	t_texture	tex;
} t_state;

/* functions */

// load.c
void load(t_state *state);

// main.c
void	draw_sight(t_state *state);

// event.c
int	event_key(int key, t_state *state);

#endif