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