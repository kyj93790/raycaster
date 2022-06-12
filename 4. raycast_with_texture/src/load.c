#include "raycaster.h"

void load(t_state *state)
{
	state->tex.img_n.img_ptr = mlx_xpm_file_to_image(state->mlx_ptr, "static/north.xpm", &(state->tex.texWidth), &(state->tex.texHeight));
	state->tex.img_n.addr = mlx_get_data_addr(state->tex.img_n.img_ptr, &(state->tex.img_n.bits_per_pixel), &(state->tex.img_n.line_len), &(state->tex.img_n.endian));
	state->tex.img_s.img_ptr = mlx_xpm_file_to_image(state->mlx_ptr, "static/south.xpm", &(state->tex.texWidth), &(state->tex.texHeight));
	state->tex.img_s.addr = mlx_get_data_addr(state->tex.img_s.img_ptr, &(state->tex.img_s.bits_per_pixel), &(state->tex.img_s.line_len), &(state->tex.img_s.endian));
	state->tex.img_w.img_ptr = mlx_xpm_file_to_image(state->mlx_ptr, "static/west.xpm", &(state->tex.texWidth), &(state->tex.texHeight));
	state->tex.img_w.addr = mlx_get_data_addr(state->tex.img_w.img_ptr, &(state->tex.img_w.bits_per_pixel), &(state->tex.img_w.line_len), &(state->tex.img_w.endian));
	state->tex.img_e.img_ptr = mlx_xpm_file_to_image(state->mlx_ptr, "static/east.xpm", &(state->tex.texWidth), &(state->tex.texHeight));
	state->tex.img_e.addr = mlx_get_data_addr(state->tex.img_e.img_ptr, &(state->tex.img_e.bits_per_pixel), &(state->tex.img_e.line_len), &(state->tex.img_e.endian));
}