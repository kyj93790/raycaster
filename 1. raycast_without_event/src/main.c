#include "raycaster.h"

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

int w = 640;
int h = 480;

int main(void)
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, w, h, "raycaster");

	double posX = 12, posY = 20;		// start position of player
	double dirX = 0, dirY = -1;			// initial direction (left)
	double planeX = 0.66, planeY = 0;	// camera plane
	// printf("curr map : %d\n", worldMap[(int)posX][(int)posY]);

	// double time = 0;
	// double oldtime = 0;

	// first 3d img print
	img.img_ptr = mlx_new_image(mlx_ptr, w, h);
	img.addr = mlx_get_data_addr(img.img_ptr, &(img.bits_per_pixel), &(img.line_len), &(img.endian));
	for (int x = 0; x < w; x++)
	{
		// double cameraX = -2*x/(double)w + 1;
		double cameraX = 2*x / (double)w - 1;
		double rayDirX = dirX + planeX*cameraX;
		double rayDirY = dirY + planeY*cameraX;
		// printf("rayDirX : %lf\n", rayDirX);
		// printf("rayDirY : %lf\n", rayDirY);

		// hmmmm..
		int mapX = (int)posX;
		int mapY = (int)posY;

		double sideDistX; 
		double sideDistY;

		double deltaDistX = fabs(1/rayDirX);
		double deltaDistY = fabs(1/rayDirY);
		// printf("deltaDistX : %lf\n", deltaDistX);
		// printf("deltaDistY : %lf\n", deltaDistY);
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
			// printf("[minus] sideDistX : %lf\n", sideDistX);
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
			// printf("[plus] sideDistX : %lf\n", sideDistX);
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (posY - mapY) * deltaDistY;
			// printf("[minus] sideDistY : %lf\n", sideDistY);
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
			// printf("[plus] sideDistY : %lf\n", sideDistY);
		}
		// printf("sideDistX : %lf\n", sideDistX);
		// printf("sideDistY : %lf\n", sideDistY);
		//perform DDA
		int hit_cnt = 1;
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
			//Check if ray has hit a wall
			// printf("mapX : %d\n", mapX);
			// printf("mapY : %d\n", mapY);
			// printf("curr checking map : %d\n", worldMap[mapY][mapX]);
			if (worldMap[mapY][mapX] > 0) hit = 1;
			hit_cnt++;
		}
		// printf("hit_cnt : %d\n", hit_cnt);
		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		if (side == 0) perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
		else           perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

		//Calculate height of line to draw on screen
		int lineHeight = (int)(2*h / perpWallDist);
		// printf("line height : %d\n", lineHeight);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + h / 2;
		if(drawStart < 0)drawStart = 0;
		int drawEnd = lineHeight / 2 + h / 2;
		if(drawEnd >= h)drawEnd = h - 1;

		int curr_color = 0;
		// printf("(mapY, mapX) : (%d), (%d)\n", mapY, mapX);
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
		// if (side == 1)
		// 	curr_color = curr_color / 2;
		// draw_vertical_line(&img, drawStart, drawEnd, x, curr_color);
		// if (x == 0)
		// {
			// printf("%x\n", curr_color);
		// printf("len : %d\n", drawEnd - drawStart);
		draw_vertical_line(&img, drawStart, drawEnd, x, curr_color);
		// 	mlx_put_image_to_window(mlx_ptr, win_ptr, img.img_ptr, 0, 0);
		// 	break ;
		// }
		// sleep(1);
	}

	// init();
	// img.img_ptr = mlx_new_image(mlx_ptr, 1024, 512);
	// img.addr = mlx_get_data_addr(img.img_ptr, &(img.bits_per_pixel), &(img.line_len), &(img.endian));

	mlx_put_image_to_window(mlx_ptr, win_ptr, img.img_ptr, 0, 0);
	//mlx_pixel_put(mlx_ptr, win_ptr, px, py, 0xFFFFFF);
	mlx_loop(mlx_ptr);
	return (0);
}