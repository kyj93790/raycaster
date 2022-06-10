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

void	draw_vertical_line(t_img *img, int start, int end, int curr_w, int color)
{
	int	i;

	i = start;
	while (i <= end)
	{
		draw_img(img, curr_w, i, color);
		i++;
	}
	return ;
}

void	draw_sight(t_img *img, double posX, double posY, double dirX, double dirY, double planeX, double planeY)
{
	for (int x = 0; x < w; x++)
	{
		double cameraX = -2*x/(double)w + 1;
		// double cameraX = 2*x / (double)w - 1;
		double rayDirX = dirX + planeX*cameraX;
		double rayDirY = dirY + planeY*cameraX;

		int mapX = (int)posX;
		int mapY = (int)posY;

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
			sideDistX = (posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
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
		if (side == 0) perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
		else           perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

		//Calculate height of line to draw on screen
		int lineHeight = (int)(2*h / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + h / 2;
		if(drawStart < 0)drawStart = 0;
		int drawEnd = lineHeight / 2 + h / 2;
		if(drawEnd >= h)drawEnd = h - 1;

		int curr_color = 0;
		if (worldMap[mapY][mapX] == 1)
		{
			curr_color = red;
			if (side == 1)
				curr_color = sub_red;
		}
		else if (worldMap[mapY][mapX] == 2)
		{
			curr_color = green;
			if (side == 1)
				curr_color = sub_green;
		}
		else if (worldMap[mapY][mapX] == 3)
		{
			curr_color = blue;
			if (side == 1)
				curr_color = sub_blue;
		}
		else if (worldMap[mapY][mapX] == 4)
		{
			curr_color = white;
			if (side == 1)
				curr_color = gray;
		}
		draw_vertical_line(img, drawStart, drawEnd, x, curr_color);
	}
}

int main(void)
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, w, h, "raycaster");

	double posX = 22, posY = 12;		// start position of player
	double dirX = -1, dirY = 0;			// initial direction (left)
	double planeX = 0, planeY = 0.66;	// camera plane

	// double time = 0;
	// double oldtime = 0;

	// first 3d img print
	img.img_ptr = mlx_new_image(mlx_ptr, w, h);
	img.addr = mlx_get_data_addr(img.img_ptr, &(img.bits_per_pixel), &(img.line_len), &(img.endian));
	draw_sight(&img, posX, posY, dirX, dirY, planeX, planeY);

	mlx_put_image_to_window(mlx_ptr, win_ptr, img.img_ptr, 0, 0);
	mlx_loop(mlx_ptr);
	return (0);
}