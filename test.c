#include "fdf.h"

/* typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
} */

void	put_color(t_data *screen, int color)
{
	int x;
	int	y;
	
	y = 0;
	while (y <= screen->row)
	{
		x = 0;
		while (x <= screen->line)
		{	
			mlx_pixel_put(screen->mlx, screen->win, x, y, color);
			x++;
		}
		y++;
	}
}

int	mouse_move(int x, int y, void *param)
{
	t_data	*screen;

	screen = (t_data *)param;
	//printf("Mouse move: x=%d, y=%d\n", x, y);
	if ((x <= screen->line && x >= 0) && (y <= screen->row && y >= 0))
		mlx_pixel_put(screen->mlx, screen->win, x, y, 0x000000);
	return 0;
}

int	mouse_click(int	button, int x, int y, void *param)
{
	t_data *screen;

	screen = (t_data *)param;
	if (button == 1)
	{
		if ((x >= 0 && x <= screen->line) && (y >= 0 && y <= screen->row))
			put_color(screen, 0x000000);
	}
	return (0);
}

void draw_circle(t_data *screen, int center_x, int center_y, int radius)
{
    int x = radius;
    int y = 0;
    int radius_error = 1 - x;

    while (x >= y)
    {
        mlx_pixel_put(screen->mlx, screen->win, center_x + x, center_y - y, 0xFFFFFF);
        mlx_pixel_put(screen->mlx, screen->win, center_x - x, center_y - y, 0xFFFFFF);
        mlx_pixel_put(screen->mlx, screen->win, center_x - x, center_y + y, 0xFFFFFF);
        mlx_pixel_put(screen->mlx, screen->win, center_x + x, center_y + y, 0xFFFFFF);
        mlx_pixel_put(screen->mlx, screen->win, center_x + y, center_y - x, 0xFFFFFF);
        mlx_pixel_put(screen->mlx, screen->win, center_x - y, center_y - x, 0xFFFFFF);
        mlx_pixel_put(screen->mlx, screen->win, center_x - y, center_y + x, 0xFFFFFF);
        mlx_pixel_put(screen->mlx, screen->win, center_x + y, center_y + x, 0xFFFFFF);

        y++;
        if (radius_error < 0)
            radius_error += 2 * y + 1;
        else
        {
            x--;
            radius_error += 2 * (y - x) + 1;
        }
    }
}

int	keyup(int keycode, t_data *data)
{
	
	t_circle	circle;

	circle.x = data->line / 2;
	circle.y = data->row / 2;
	circle.rad = 50;
	static int	x_cord = 750;
	static int	y_cord = 500;
	
	if (keycode == XK_Escape)
	{
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		exit(1);
	}
	if (keycode == XK_r)
		put_color(data, 0xFF0000);
	if (keycode == XK_b)
		put_color(data, 0x0000FF);
	if (keycode == XK_g)
		put_color(data, 0x00FF00);
	if (keycode == XK_w)
	{
		put_color(data, 0x000000);
		draw_circle(data, x_cord, y_cord, circle.rad);
		y_cord -= 5;
	}
	return (0);
}
int	main(void)
{
	t_data		screen;
	
	screen.line = 1500;
	screen.row = 1000;
	screen.mlx = mlx_init();
	screen.win = mlx_new_window(screen.mlx, screen.line, screen.row, "FdF");
	mlx_key_hook(screen.win, keyup, &screen);
	mlx_hook(screen.win, 6, 1L<<6, mouse_move, &screen);
	mlx_mouse_hook(screen.win, mouse_click, &screen);
	mlx_loop(screen.mlx);
}