#include "raycaster.h"

int	event_key(int key, t_state *state)
{
	// left arrow와 right arrow만 들어온다고 가정
	double curr_dirX;
	double curr_planeX;
	mlx_clear_window(state->mlx_ptr, state->win_ptr);
	if (key == KEY_LA)
	{
		printf("left\n");
		curr_dirX = state->dirX;
		state->dirX = state->dirX*cos(theta) - state->dirY*sin(theta);
		state->dirY = state->dirY*cos(theta) + curr_dirX*sin(theta);
		curr_planeX = state->planeX;
		state->planeX = state->planeX*cos(theta) - state->planeY*sin(theta);
		state->planeY = state->planeY*cos(theta) + curr_planeX*sin(theta);
	}
	else if (key == KEY_RA)
	{
		printf("right\n");
		curr_dirX = state->dirX;
		state->dirX = state->dirX*cos(theta) + state->dirY*sin(theta);
		state->dirY = state->dirY*cos(theta) - curr_dirX*sin(theta);
		curr_planeX = state->planeX;
		state->planeX = state->planeX*cos(theta) + state->planeY*sin(theta);
		state->planeY = state->planeY*cos(theta) - curr_planeX*sin(theta);
	}
	mlx_clear_window(state->mlx_ptr, state->win_ptr);
	draw_sight(state);
	mlx_put_image_to_window(state->mlx_ptr, state->win_ptr, state->img.img_ptr, 0, 0);
	return (0);
}