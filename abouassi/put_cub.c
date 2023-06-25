/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_cub.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 11:26:06 by abouassi          #+#    #+#             */
/*   Updated: 2023/06/24 16:56:01 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../cub3d.h"

int	a_event1(int key, t_info *cub)
{
	input_key(key, cub);
	// mlx_clear_window(cub->mlx->ptr, cub->mlx->win);
	draw_simple_map1(cub);
	if ((int)cub->corner == 360)
		cub->corner = 0;
	if (key == 124)
	{
		cub->corner+=10;
		// mlx_clear_window(cub->mlx->ptr, cub->mlx->win);
		draw_simple_map1(cub);
	}
	if (key == 123)
	{
		cub->corner-=10;
		// mlx_clear_window(cub->mlx->ptr, cub->mlx->win);
		draw_simple_map1(cub);
	}
	return (0);
}
void draw_myray(t_info *cub,double corner)
{
	int r;
	double cor_rd;
	double x;
	double y;
	cor_rd = ((M_PI * corner)/180.0000);
	x = cub->x ;
	y = cub->y ;
	r = 0;
	while (r <= 20 && !prm_moves(cub->map,(int)(x /100),(int)( y/100)))
	{
		my_mlx_pixel_put(cub->big_img,  x, y, 16777015);
		x = x + cos(cor_rd) ;
		y = y  - sin(cor_rd) ;
		r++;
	}
	
}
void draw_mini_ray(t_info  *cub)
{
	double cor_l;
	double cor_r;

	cor_l = cub->corner - 30;
	cor_r = cub->corner + 30;
	while (cor_l <= cor_r)
	{

		draw_myray(cub,cor_l);
		cor_l++;
	}
	
	
}
void	my_mlx_pixel_put(t_img*data, int x, int y, int color)
{
	char	*dst;
	if (x >= 1000 || y >= 500)
		return ;
	//printf("(%d,%d)\n",x,y);
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
void print_image_square( t_info *data,int x, int y)
{
    int i, j;
	// printf("x %d\n",x);
	// printf("y %d\n",y);
	i = y;
    while(i < y + 100 )
	{
		j = x;
		while(j < x +100)
		{
			my_mlx_pixel_put(data->big_img,j,i ,0x00FF96FF);
			j++;
		}
		i++;
	}
}

void	draw_simple_map1(t_info *cub)
{
	int x = 0;
	int y = 0;

	//cub->corner = 180;
	
	if (!cub->mlx->img_b)
		ft_error();
	while (y < 500)
	{
		x = 0;
		while (x < 1000)
		{
			my_mlx_pixel_put(cub->big_img,x ,y ,0x001637FF);
			x++;
		}
		y++;
	}
	
	y = 0;
	x = 0;
	while (cub->map[y])
	{
		x = 0;
		while (cub->map[y][x]){
			if (cub->map[y][x] == '1')
			{
				
				print_image_square(cub,x * 100  ,y * 100);
			}
			x++;
		}
		y++;
	}
	draw_mini_ray(cub);
	put_pix(cub,cub->big_img,14753280);
	//mlx_put_image_to_window(cub->mlx->ptr, cub->mlx->win, cub->img[0].img, 0,500);
	mlx_put_image_to_window(cub->mlx->ptr, cub->mlx->win, cub->big_img->ptr, 0,0);
	//raw_rays(cub, 0, 16777215);
	
}