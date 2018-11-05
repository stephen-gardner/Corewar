/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_gui.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 03:06:53 by asarandi          #+#    #+#             */
/*   Updated: 2018/11/04 20:57:30 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_gui.h"
#include <time.h>
#include <math.h>
#include "corewar.h"

int	hsl_to_rgb(float h, float s, float l)
{
	float	c;	//chroma
	float	h1;
	float	x;
	float	m;
	float	r = 0;
	float 	g = 0;
	float	b = 0;

	s = s / (float)100;
	l = l / (float)100;
	c = ((float)1 - fabsf(((float)2 * l) - (float)1)) * s;
	h1 = h / (float)60;
	x = c * ((float)1 - fabsf(fmodf(h1,(float)2) - (float)1));

	if ((0 <= h1) && (h1 <= 1)) {			//0, 1		c,x,0
		r = c; g = x; b = 0; }
	else if ((1 <= h1) && (h1 <= 2)) {		//1, 2		x,c,0
		r = x; g = c; b = 0;}
	else if ((2 <= h1) && (h1 <= 3)) {		//2, 3		0,c,x
		r = 0; g = c; b = x;}
	else if ((3 <= h1) && (h1 <= 4)) {		//3, 4		0,x,c
		r = 0; g = x; b = c;}
	else if ((4 <= h1) && (h1 <= 5)) {		//4, 5		x,0,c
		r = x; g = 0; b = c;}
	else if ((5 <= h1) && (h1 <= 6)) {		//4, 5		c,0,x
		r = c; g = 0; b = x;}

	m = l - (c / 2);
	r += m;
	g += m;
	b += m;

	int ri = (int)(roundf((float)255 * (float)r));
	int gi = (int)(roundf((float)255 * (float)g));
	int bi = (int)(roundf((float)255 * (float)b));

	int rgb = ((ri & 0xff) << 16) + ((gi & 0xff) << 8) + (bi & 0xff);
	return (rgb);
}

void	corewar_gui_make_pcolors(t_corewar_gui *g)
{
	int i;
	int j;
	float	hues[] = {0, 60, 120, 240};	//red, yellow, green, blue
//	float	hues[] = {120, 240, 0, 180};	//zaz's corewar colors
	float fstep = (float)LUM_RANGE / (float)MAX_LUM_STEPS;

	i = 0;

	j = 0;
	while (j < MAX_LUM_STEPS)
		g->p_colors[i][j++] = BLOCK_DEFAULT_COLOR;
	i = 1;
	while (i < MAX_PLAYERS + 1)
	{
		j = 0;
		while (j < MAX_LUM_STEPS)
		{
			float f3 = (float)LUM_START - (float)(j * fstep);
			int rgb = hsl_to_rgb((float)hues[i - 1], (float)100, (float)f3);
			g->p_colors[i][j] = rgb;
			j++;
		}
		i++;
	}
	return ;
}

void	corewar_gui_clean_up(t_corewar_gui *g)
{
	if (g == NULL)
		return ;
	if (g->mlx != NULL)
		free(g->mlx);
//	if (g->arena != NULL)
//		free(g->arena);
//	if (g->colors != NULL)
//		free(g->colors);
	free(g);
	return ;
}

void	corewar_gui_fatal_error(t_corewar_gui *g, char *msg)
{
	if (g != NULL)
		corewar_gui_clean_up(g);
	ft_printf(CONSOLE_TEXT_RED, "ERROR:", CONSOLE_TEXT_EOC, " %s\n", msg);
	exit(0);
}

int	corewar_gui_is_numeric_key(int keycode)
{
	if ((keycode == KEY_1) || (keycode == KEY_2) || (keycode == KEY_3))
		return (1);
	else if ((keycode == KEY_4) || (keycode == KEY_5) || (keycode == KEY_6))
		return (1);
	else if ((keycode == KEY_7) || (keycode == KEY_8) || (keycode == KEY_9))
		return (1);
	else if (keycode == KEY_0)
		return (1);
	return (0);
}

int	corewar_gui_set_cpf_to_numeric_key(int keycode, t_corewar_gui *g)
{
	int	keys[] = {KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_0};
	int values[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
	int	i;

	i = 0;
	while (i < (int)(sizeof(keys) / sizeof(int)))
	{
		if (keycode == keys[i])
		{
			g->cpf = values[i];
			return (1);
		}
		i++;
	}
	return (0);
}

int	corewar_gui_increment_cpf(int keycode, t_corewar_gui *g)
{
	if ((keycode == KEY_PLUS) && (g->cpf < CPF_MAX))
		g->cpf += 1;
	else if ((keycode == KEY_MINUS) && (g->cpf > 0))
		g->cpf -= 1;
	return (0);
}

int	corewar_gui_key_hook(int keycode, t_corewar_gui *g)
{
	if ((keycode == KEY_ESCAPE) || (keycode == KEY_Q))
	{
		if (g->img != NULL)
			(void)mlx_destroy_image(g->mlx, g->img);
		if (g->img_dist != NULL)
			(void)mlx_destroy_image(g->mlx, g->img_dist);
		if (g->win != NULL)
			(void)mlx_destroy_window(g->mlx, g->win);
		(void)corewar_gui_clean_up(g);
		exit(0);
	}
	else if (corewar_gui_is_numeric_key(keycode))
		(void)corewar_gui_set_cpf_to_numeric_key(keycode, g);
	else if (keycode == KEY_SPACE)
		g->state ^= 1;
	else if ((keycode != KEY_PLUS) && (keycode != KEY_MINUS))
		ft_printf("you pressed: %d, %s\n", keycode, GUI_CONTROLS_INFO);
	return (0);
}

int	corewar_gui_key_repeat(int keycode, t_corewar_gui *g)
{
    if ((keycode == KEY_PLUS) || (keycode == KEY_MINUS))
		(void)corewar_gui_increment_cpf(keycode, g);
    return (0);
}

int	corewar_gui_mouse_hook(int button, int x, int y, t_corewar_gui *g)
{
    (void)button;
    (void)x;
    (void)y;
    (void)g;
	return (0);
}

int	corewar_gui_init_colors(t_corewar_gui *g)
{
	(void)corewar_gui_make_pcolors(g);
	return (0);
}

int	corewar_gui_get_color(t_corewar_gui *g, int i, int j)
{
	int	owner;
	int	age;
	int	idx;

	idx = (i * GUI_BLOCK_NUM_COLS + j) % GUI_ARENA_SIZE;
	owner = g->core->owner[idx]; 	//g->owner[i * GUI_BLOCK_NUM_COLS + j];
	age = g->core->epoch[idx]; 	//g->age[i * GUI_BLOCK_NUM_COLS + j];
	return (g->p_colors[owner % (MAX_PLAYERS + 1)][age % MAX_LUM_STEPS]);
}

int	corewar_gui_put_block(t_corewar_gui *g, int i, int j)
{
	int	i1;
	int j1;
	int	rgb;
	int *ptr;

	rgb = corewar_gui_get_color(g, i, j);
	i = GUI_BLOCK_ARENA_X_POS + (i * GUI_BLOCK_ROW_HEIGHT);
	j = GUI_BLOCK_ARENA_Y_POS + (j * GUI_BLOCK_COL_WIDTH);
	i1 = i + GUI_BLOCK_HEIGHT;
	j1 = j + GUI_BLOCK_WIDTH;
	while (i < i1)
	{
		while (j < j1)
		{
			ptr = (int *)&g->img_data[(i * WIN_BLOCK_WIDTH * SZ_INT) + (j * SZ_INT)];
			*ptr = rgb;
			j++;
		}
		j -= GUI_BLOCK_WIDTH;
		i++;
	}
	return (0);
}

int	corewar_gui_info_panel(t_corewar_gui *g)
{
	char	fps[1000];
	char	*ptr;
	int		i;
	int		x;

	if (g->state == 1)
		ptr = STATE_RUNNING;
	else
		ptr = STATE_PAUSED;

	mlx_string_put(g->mlx, g->win, STATE_Y, STATE_X, INFO_TEXT_COLOR, ptr);
	ptr = (char *)&fps;
	sprintf(ptr, FPS_STR, g->fps);
	mlx_string_put(g->mlx, g->win, FPS_Y, FPS_X, INFO_TEXT_COLOR, ptr);
	sprintf(ptr, CPF_STR, g->cpf);
	mlx_string_put(g->mlx, g->win, CPF_Y, CPF_X, INFO_TEXT_COLOR, ptr);
	sprintf(ptr, CPS_STR, g->fps * g->cpf);
	mlx_string_put(g->mlx, g->win, CPS_Y, CPS_X, INFO_TEXT_COLOR, ptr);
	sprintf(ptr, PROC_NUM, g->nproc);
	mlx_string_put(g->mlx, g->win, PROC_NUM_Y, PROC_NUM_X, INFO_TEXT_COLOR, ptr);
	sprintf(ptr, CYCLE_NUM, g->core->cycle);
	mlx_string_put(g->mlx, g->win, CYCLE_NUM_Y, CYCLE_NUM_X, INFO_TEXT_COLOR, ptr);

	i = 0;
	x = PLAYER_X + (GUI_CHAR_HEIGHT * 2);
	while (i < g->core->nplayers)
	{
		sprintf(ptr, PLAYER_NUM, i, g->core->champions[i].id);
		mlx_string_put(g->mlx, g->win, PLAYER_Y, x, INFO_TEXT_COLOR, ptr);
        x+= GUI_CHAR_HEIGHT;
		mlx_string_put(g->mlx, g->win, PLAYER_Y, x,	g->p_colors[i + 1][0], g->core->champions[i].name);
        x+= GUI_CHAR_HEIGHT;
		x += GUI_CHAR_HEIGHT;
		i++;
	}

	if (g->core->processes == 0)
	{
		i = 0;
		x += GUI_CHAR_HEIGHT;
		while (i < MAX_PLAYERS)
		{
			if (g->core->victor == &g->core->champions[i])
			{
				mlx_string_put(g->mlx, g->win, PLAYER_Y, x, INFO_TEXT_COLOR, GUI_WINNER1);	x+= GUI_CHAR_HEIGHT;
				mlx_string_put(g->mlx, g->win, PLAYER_Y, x, g->p_colors[i + 1][0], g->core->victor->name);	x+= GUI_CHAR_HEIGHT;
				sprintf(ptr, GUI_COMMENT_QUOTES, g->core->victor->comment);
				mlx_string_put(g->mlx, g->win, PLAYER_Y, x, g->p_colors[i + 1][0], ptr);	x+= GUI_CHAR_HEIGHT;
				break ;		
			}
			i++;
		}
	}
	return (0);
}

int	corewar_gui_block_visuals(t_corewar_gui *g)
{
	int		i;
	int		j;
	int		k;

	(void)ft_memset(g->distrib, 0, (MAX_PLAYERS + 1) * sizeof(int));
	i = 0;
	while (i < GUI_BLOCK_NUM_ROWS)
	{
		j = 0;
		while (j < GUI_BLOCK_NUM_COLS)
		{
			corewar_gui_put_block(g, i, j);
			k = g->core->owner[i * GUI_BLOCK_NUM_COLS + j];
			g->distrib[k]++;
			j++;
		}
		i++;
	}
	return (0);
}

int	corewar_gui_calc_fps(t_corewar_gui *g)
{
	time_t	tloc;
	static	int	current;
	static	int previous;
	static	int	counter;

	counter++;
	current = time(&tloc);
	if (current == previous + 1)
	{
		g->fps = counter;
		counter = 0;
		previous = current;
	}
	else if (previous != current)
		previous = current;
	return (0);
}

int	corewar_gui_mark_pc(t_corewar_gui *g, int i, int j)
{
	int	i1;
	int j1;
	int	rgb;
	int	*ptr;
	int	tmp;

	rgb = GUI_PC_BOX_COLOR;
	i = GUI_BLOCK_ARENA_X_POS + (i * GUI_BLOCK_ROW_HEIGHT); i--;
	j = GUI_BLOCK_ARENA_Y_POS + (j * GUI_BLOCK_COL_WIDTH); j--;
	i1 = i + GUI_BLOCK_HEIGHT; i1+=2;
	j1 = j + GUI_BLOCK_WIDTH; j1+=2;
	while (i < i1)
	{
		tmp = j;
		while (j < j1)
		{
			ptr = (int *)&g->img_data[(i * WIN_BLOCK_WIDTH * SZ_INT) + (j * SZ_INT)];
			*ptr = rgb;
			j++;
		}
		j = tmp;
		i++;
	}
	return (0);

}

int	corewar_gui_show_pcs(t_corewar_gui *g)
{
	t_proc	*p;
	int		idx;

	p = g->core->processes;
	g->nproc = 0;
	ft_memset(g->pc_box, 0, MEM_SIZE);
	while (p)
	{
		g->nproc += 1;
		idx = (p->pc - g->core->arena) % MEM_SIZE;
		if (g->pc_box[idx] == 0)
		{
			g->pc_box[idx] = 1;
			(void)corewar_gui_mark_pc(g, idx / GUI_BLOCK_NUM_COLS, idx % GUI_BLOCK_NUM_COLS);
		}
		p = p->next;
	}
	return (0);
}

int	corewar_gui_create_images(t_corewar_gui *g)
{
	if (g->img != NULL)
		(void)mlx_destroy_image(g->mlx, g->img);
	if ((g->img = mlx_new_image(g->mlx, WIN_BLOCK_WIDTH, WIN_BLOCK_HEIGHT))== NULL)
		(void)corewar_gui_fatal_error(g, "mlx_new_image() failed");
	g->img_data = mlx_get_data_addr(g->img, &g->img_bpp, &g->img_sz, &g->img_endian);

	if (g->img_dist != NULL)
		(void)mlx_destroy_image(g->mlx, g->img_dist);
	if ((g->img_dist = mlx_new_image(g->mlx, DIST_WIDTH, DIST_HEIGHT)) == NULL)
		(void)corewar_gui_fatal_error(g, "mlx_new_image() failed");
	g->img_dist_data = mlx_get_data_addr(g->img_dist, &g->img_dist_bpp, &g->img_dist_sz, &g->img_dist_endian);
	return (0);
}

int	corewar_gui_get_distrib_color(t_corewar_gui *g, int j)
{
	float x = DIST_WIDTH;
	x = (float)MEM_SIZE / (float)DIST_WIDTH;
	float y = (float)j * (float)x;
	int	i = 1;
	int	left = 0;
	int right = 0;
	while (i < MAX_PLAYERS + 1)
	{
		right = g->distrib[i];
		right += left;
		if (((int)y >= left) && ((int)y <= right))
			return (g->p_colors[i][MAX_LUM_STEPS / LUM_TEXT_DIV]);
		left = right;
		i++;
	}
	right += g->distrib[0];
	if (((int)y >= left) && ((int)y <= right))
		return (g->p_colors[0][0]);
	return (0xffffff);
}

int	corewar_gui_fill_distrib(t_corewar_gui *g)
{
	int	i;
	int	j;
	int	*ptr;

	i = 0;
	while (i < DIST_HEIGHT)
	{
		j = 0;
		while (j < DIST_WIDTH)
		{
			ptr = (int *)&g->img_dist_data[(i * DIST_WIDTH * SZ_INT) + (j * SZ_INT)];
			if ((i == 0) || (i == DIST_HEIGHT - 1) || (j == 0) || (j == DIST_WIDTH - 1))
				*ptr = DIST_BORDER_COLOR;
			else
				*ptr = corewar_gui_get_distrib_color(g, j);
			j++;
		}
		i++;
	}
	return (0);
}

int	corewar_gui_loop_hook(t_corewar_gui *g)
{
	int	i;

	(void)corewar_gui_calc_fps(g);
	(void)corewar_gui_create_images(g);
	(void)corewar_gui_show_pcs(g);
	(void)corewar_gui_block_visuals(g);
	(void)corewar_gui_fill_distrib(g);
	(void)mlx_clear_window(g->mlx, g->win);
	(void)corewar_gui_info_panel(g);
	mlx_put_image_to_window(g->mlx, g->win, g->img, 0, 0);
	mlx_put_image_to_window(g->mlx, g->win, g->img_dist, DIST_Y_POS, DIST_X_POS);
	mlx_string_put(g->mlx, g->win, DIST_TEXT_Y_POS, DIST_TEXT_X_POS, INFO_TEXT_COLOR, DIST_TEXT);
	i = 0;
	if (g->state == 1)
	{
		while (i < g->cpf)
		{
			if (g->core->processes)
				execute_war(g->core);
			i++;
		}
	}
	return (0);
}

int	corewar_gui_expose_hook(t_corewar_gui *g)
{
    (void)g;
	return (0);
}

void	corewar_gui_init(t_core *core)
{
	t_corewar_gui	*g;
	g = ft_memalloc(sizeof(t_corewar_gui));
	g->core = core;
	if ((g->mlx = mlx_init()) == NULL)
		corewar_gui_fatal_error(g, "mlx_init() failed");
	mlx_do_key_autorepeaton(g->mlx);
	g->win = mlx_new_window(g->mlx, WIN_TOTAL_WIDTH, WIN_TOTAL_HEIGHT, WIN_BLOCK_TITLE);
	if (g->win == NULL)
		corewar_gui_fatal_error(g, "mlx_new_window() failed");
	g->cpf = 1;
	(void)corewar_gui_init_colors(g);
	(void)mlx_hook(g->win, KEYPRESS, KEYPRESSMASK, corewar_gui_key_repeat, g);
	(void)mlx_key_hook(g->win, corewar_gui_key_hook, g);
	(void)mlx_mouse_hook(g->win, corewar_gui_mouse_hook, g);
	(void)mlx_expose_hook(g->win, corewar_gui_expose_hook, g);
	(void)mlx_loop_hook(g->mlx, corewar_gui_loop_hook, g);
	(void)mlx_loop(g->mlx);
	(void)corewar_gui_clean_up(g);
}
