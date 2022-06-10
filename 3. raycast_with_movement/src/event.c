#include "raycaster.h"

int	event_key(int key, t_state *state)
{
	double deltaX;
	double deltaY;
	double curr_dirX;
	double curr_planeX;

	if (key == KEY_W)
	{
		deltaX = state->dirX / sqrtf(powf(state->dirX, 2) + powf(state->dirY, 2));
		deltaY = state->dirY / sqrtf(powf(state->dirX, 2) + powf(state->dirY, 2));
		state->posX += deltaX * del_move;
		state->posY += deltaY * del_move;
	}
	else if (key == KEY_A)
	{
		deltaX = state->dirY / sqrtf(powf(state->dirX, 2) + powf(state->dirY, 2));
		deltaY = -state->dirX / sqrtf(powf(state->dirX, 2) + powf(state->dirY, 2));
		state->posX += deltaX * del_move;
		state->posY += deltaY * del_move;
	}
	else if (key == KEY_S)
	{
		deltaX = state->dirX / sqrtf(powf(state->dirX, 2) + powf(state->dirY, 2));
		deltaY = state->dirY / sqrtf(powf(state->dirX, 2) + powf(state->dirY, 2));
		state->posX -= deltaX * del_move;
		state->posY -= deltaY * del_move;
	}
	else if (key == KEY_D)
	{
		deltaX = -state->dirY / sqrtf(powf(state->dirX, 2) + powf(state->dirY, 2));
		deltaY = state->dirX / sqrtf(powf(state->dirX, 2) + powf(state->dirY, 2));
		state->posX += deltaX * del_move;
		state->posY += deltaY * del_move;
	}
	else if (key == KEY_LA)
	{
		curr_dirX = state->dirX;
		state->dirX = state->dirX*cos(theta) + state->dirY*sin(theta);
		state->dirY = state->dirY*cos(theta) - curr_dirX*sin(theta);
		curr_planeX = state->planeX;
		state->planeX = state->planeX*cos(theta) + state->planeY*sin(theta);
		state->planeY = state->planeY*cos(theta) - curr_planeX*sin(theta);
	}
	else if (key == KEY_RA)
	{
		curr_dirX = state->dirX;
		state->dirX = state->dirX*cos(theta) - state->dirY*sin(theta);
		state->dirY = state->dirY*cos(theta) + curr_dirX*sin(theta);
		curr_planeX = state->planeX;
		state->planeX = state->planeX*cos(theta) - state->planeY*sin(theta);
		state->planeY = state->planeY*cos(theta) + curr_planeX*sin(theta);
	}
	mlx_clear_window(state->mlx_ptr, state->win_ptr);
	draw_sight(state);
	mlx_put_image_to_window(state->mlx_ptr, state->win_ptr, state->img.img_ptr, 0, 0);
	return (0);
}