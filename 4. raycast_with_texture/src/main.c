#include "raycaster.h"

int w = 640;
int h = 480;

/* map info */
int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void	draw_img(t_img *img, int x, int y, int color)
{
	char *ptr;

	ptr = img->addr + y*img->line_len + x*(img->bits_per_pixel/8);
	*(unsigned int*)ptr = color;
}

void	draw_vertical_line(t_img *img, t_img *tex, int start, int end, int curr_w, double texPos, int texX, double step)
{
	int	i;

	i = 0;
	while (i < start)
	{
		draw_img(img, curr_w, i, 0);
		i++;
	}
	while (i <= end)
	{
		int texY = (int)texPos;
		int color = *(unsigned int *)(tex->addr + texY * tex->line_len + texX * (tex->bits_per_pixel/8));
		draw_img(img, curr_w, i, color);
		i++;
		texPos += step;
	}
	while (i < h)
	{
		draw_img(img, curr_w, i, 0);
		i++;
	}
	return ;
}

void	draw_sight(t_state *state)
{
	for (int x = 0; x < w; x++)
	{
		double cameraX = -2*x/(double)w + 1;
		// double cameraX = 2*x / (double)w - 1;
		double rayDirX = state->dirX + state->planeX*cameraX;
		double rayDirY = state->dirY + state->planeY*cameraX;

		int mapX = (int)(state->posX);
		int mapY = (int)(state->posY);

		double sideDistX; 
		double sideDistY;

		double deltaDistX = fabs(1/rayDirX);
		double deltaDistY = fabs(1/rayDirY);
		double perpWallDist;

		int stepX;
		int stepY;

		int hit = 0;
		int side;

		//calculate step and initial sideDist
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (state->posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - state->posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (state->posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - state->posY) * deltaDistY;
		}

		//perform DDA
		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (worldMap[mapY][mapX] > 0) hit = 1;
		}
		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		if (side == 0) perpWallDist = (mapX - state->posX + (1 - stepX) / 2) / rayDirX;
		else           perpWallDist = (mapY - state->posY + (1 - stepY) / 2) / rayDirY;

		//Calculate height of line to draw on screen
		int lineHeight = (int)(2*h / perpWallDist);
		double step = (double)state->tex.texHeight / lineHeight;

		//calculate lowest and highest pixel to fill in current stripe
		double texPos;
		texPos = 0;
		int drawStart = -lineHeight / 2 + h / 2;
		if (drawStart < 0) {
			// 만약 시야에서 벽이 잘려서 보여야 한다면 texture에서도 해당 부분은 건너뛰고 다음 pixel부터 추출해야 한다.
			texPos = -drawStart * step;
			drawStart = 0;
		}
		int drawEnd = lineHeight / 2 + h / 2;
		if(drawEnd >= h)drawEnd = h - 1;

		double wallX;
		t_img	*curr_img;
		if (side == 0 && rayDirX >= 0)
		{
			wallX = state->posY + perpWallDist * rayDirY;
			curr_img = &(state->tex.img_w);
		}
		else if (side == 0)
		{
			wallX = state->posY - perpWallDist * rayDirY;
			curr_img = &(state->tex.img_e);
		}
		if (side == 1 && rayDirY >= 0)
		{
			wallX = state->posX + perpWallDist * rayDirX;
			curr_img = &(state->tex.img_n);
		}
		else if (side == 1)
		{
			wallX = state->posX - perpWallDist * rayDirX;
			curr_img = &(state->tex.img_s);
		}
		wallX -= (int)wallX;
		int texX = wallX * state->tex.texWidth;
		// 현재 window에 그리려고 하는 line에 tex를 할당할 것.
		// 이 때 tex에서 얼마만큼 stepping을 하며 pixel을 뽑아낼 지 결정
		draw_vertical_line(&(state->img), curr_img, drawStart, drawEnd, x, texPos, texX, step);
	}
}

int main(void)
{
	t_state	state;

	state.mlx_ptr = mlx_init();
	state.win_ptr = mlx_new_window(state.mlx_ptr, w, h, "raycaster");
	state.posX = 22;
	state.posY = 12;
	state.dirX = -1;
	state.dirY = 0;
	state.planeX = 0;
	state.planeY = 0.66;
	load(&state);
	// double time = 0;
	// double oldtime = 0;

	// first 3d img print
	state.img.img_ptr = mlx_new_image(state.mlx_ptr, w, h);
	state.img.addr = mlx_get_data_addr(state.img.img_ptr, &(state.img.bits_per_pixel), &(state.img.line_len), &(state.img.endian));
	draw_sight(&state);
	mlx_put_image_to_window(state.mlx_ptr, state.win_ptr, state.img.img_ptr, 0, 0);
	mlx_hook(state.win_ptr, key_press, 0, event_key, &state);
	// mlx_put_image_to_window(state.mlx_ptr, state.win_ptr, state.img.img_ptr, 0, 0);
	mlx_loop(state.mlx_ptr);
	return (0);
}