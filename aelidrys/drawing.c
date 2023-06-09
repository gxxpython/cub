/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelidrys <aelidrys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 10:29:23 by aelidrys          #+#    #+#             */
/*   Updated: 2023/07/13 13:38:32 by aelidrys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"


void	start_cub(t_info *cub, char **av)
{
	check_name_map(av[1]);
	cub->mlx = malloc(sizeof(t_mlx));
	cub->big_img = malloc(sizeof(t_img));
	cub->mini_img = malloc(sizeof(t_img));
	cub->img = NULL;
	cub->map0 = get_map(av[1]);
	check_first_element(cub->map0);
	cub->map = cub->map0+6;
	cheak_map(cub->map);
	check_cmp(cub->map);
	check_cmp_valid(cub->map);
	cub->mlx->ptr = mlx_init();
	cub->mlx->win = mlx_new_window(cub->mlx->ptr, 1200, 1000, "CUB");
	store_info(cub->map0, cub);
	cub->x = get_position(cub->map).x * 100 + 50;
	cub->y = get_position(cub->map).y * 100 + 50;
	cub->size = 100;
	cub->corner = 0;
	cub->mini_img->ptr = mlx_new_image(cub->mlx->ptr, 350,210);
	cub->mini_img->addr = mlx_get_data_addr(cub->mini_img->ptr, &cub->mini_img->bits_per_pixel,
		&cub->mini_img->line_length, &cub->mini_img->endian);
	cub->big_img->ptr = mlx_new_image(cub->mlx->ptr, 1200,1000);
	cub->big_img->addr = mlx_get_data_addr(cub->big_img->ptr, &cub->big_img->bits_per_pixel,
		&cub->big_img->line_length, &cub->big_img->endian);

}

int	get_color(t_img *img, int x, int y)
{
	char	*dst;
	int color = 0;

	if (x < 0 || x >= img->width || y < 0 || y >= img->heigth)
		return 0;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	color = *(int*)dst;
	return (color);
}

void	draw_walls(t_info *cub, double cor_rad, t_point p)
{
	int	a;
	int	i;
	int start;

	i = 0;
	a = (cub->size / (p.r * fabs(cos(((cub->r_corner - cub->corner) * M_PI) / 180)))) * 500;
	if (sin(cor_rad) > 0 && cub->d == 0)
		draw_north_walls(cub, p, a);
	if (sin(cor_rad) < 0 && cub->d == 0)
		draw_south_walls(cub, p, a);
	if (cos(cor_rad) < 0 && cub->d == 1)
		draw_east_walls(cub, p, a);
	if (cos(cor_rad) > 0 && cub->d == 1)
		draw_west_walls(cub, p, a);
	if (a >= 500)
		a = 500;
	start = (1000 - a * 2) / 2;
	while (i <= start)
	{
		my_mlx_pixel_put1(cub->big_img, cub->width, i, cub->c);
		my_mlx_pixel_put1(cub->big_img, cub->width, 500 + a + i++, cub->f);
	}
}

int	draw_rays(t_info *cub, double corner)
{
	t_point	p;
	double	cor_rad;

	corner = cub->corner + 30;
	cub->r_corner = cub->corner - 30;
	cub->width = 0;
	while (corner >= cub->r_corner)
	{
		cor_rad = (M_PI * cub->r_corner) / 180.0;
		p = draw_ray(cub, cor_rad);
		draw_walls(cub,cor_rad, p);
		cub->r_corner += 0.05;
		cub->width++;
	}
	return (0);
}

t_point	draw_ray(t_info *cub, double cor_rad)
{
	t_point	px;
	t_point	py;

	det_direction(cub, cor_rad);
	px = det_coord_x(cub, cor_rad, 0, cub->size);
	py = det_coord_y(cub, cor_rad, 0, cub->size);
	if (py.r > px.r)
		cub->d = 0;
	if (px.r > py.r)
	{
		cub->d = 1;
		px = py;
	}
	return (px);
	// rf = p1.r;
	// x = cub->x + 5 * cos(cor_rd);
	// y = cub->y - 5 * sin(cor_rd);
	// while (ri < rf)
	// {
	// 	mlx_pixel_put(cub->mlx->ptr, cub->mlx->win, x, y, color);
	// 	x += cos(cor_rd);
	// 	y -= sin(cor_rd);
	// 	ri = sqrt(pow(floor(cub->x - x),2) + pow(floor(cub->y - y),2));
	// }
	//2463422 blue
	//8403230 maron
	//14605267 gree
}

int	a_event(int key, t_info *cub)
{
	input_key(key, cub);
	draw_simple_map(cub);
	if ((int)cub->corner == 360)
		cub->corner = 0;
	if (key == 124)
	{
		cub->corner+=10;
		draw_simple_map(cub);
	}
	if (key == 123)
	{
		cub->corner-=10;
		draw_simple_map(cub);
	}
	return (0);
}


void	draw_simple_map(t_info *cub)
{
	int x = 0;
	int y = 0;

	y = 0;
	x = 0;
	// while (cub->map[y] && y < 6)
	// {
	// 	x = 0;
	// 	while (cub->map[y][x])
	// 	{
	// 		if (cub->map[y][x] == '1')
	// 			mlx_put_image_to_window(cub->mlx->ptr, cub->mlx->win,
	// 				cub->mlx->img_b, x * 100, y * 100);
	// 		if (cub->map[y][x] != '1')
	// 			mlx_put_image_to_window(cub->mlx->ptr, cub->mlx->win,
	// 				cub->mlx->img_n, x * 100, y * 100);
	// 		x++;
	// 	}
	// 	y++;
	// }
	draw_rays(cub, 0);
	// put_pix(cub,&cub->img[1],14753280);
	mlx_put_image_to_window(cub->mlx->ptr, cub->mlx->win, cub->big_img->ptr, 0, 0);
	draw_mini_map(cub);
	// void *img = mlx_new_image(cub->mlx->ptr, 300, 210);
	// mlx_put_image_to_window(cub->mlx->ptr, cub->mlx->win, img, 0, 0);
}
