/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 15:30:21 by jthuy             #+#    #+#             */
/*   Updated: 2020/09/30 17:33:13 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		main()
{
	t_sdl		*sdl;
	t_map		*map;
	t_player	*player;
	t_vlist		*vlist;
	t_vlist		*cursor;
	t_vlist		*head;
	t_bsp		*root;

	sdl = init_sdl();
	clear_screen(sdl);

	vlist = NULL;
	cursor = vlist;
	int		i = 0;
	while (i < 3)
	{
		map = init_map();
		if (!i)
			player = init_player(map);
		head = set_vlist(map);
		if (i)
		{
			while (cursor->next)
				cursor = cursor->next;
			cursor->next = create_vempty();
			cursor = cursor->next;
		}
		if (!i)
		{
			cursor = head;
			vlist = cursor;
		}
		else
		{
			cursor->next = head;
		}
		i += 1;
		
	}
	
	cursor = vlist;
	while (cursor)
	{
		printf ("%d\n", cursor->data);
		cursor = cursor->next;
	}
	
	
	// exit(0);
	
	
	root = set_tree(vlist);


	// printf("projection: %d %d\n", root->proj[X], root->proj[Y]);
	// printf("len: %f\n", root->len);
	// printf("pivot crd: %f %f\n", root->pivot[X], root->pivot[Y]);
	// printf("direction deg: %f\n", root->direct * 180 / M_PI);
	// printf("normal deg: %f\n", root->normal * 180 / M_PI);
	// exit(10);

	
	fill_backgraund(sdl, map->width * SCALER); // <--- USED SCALAR
	draw_contur(sdl, vlist, map);
	// draw_normal(sdl, root, map);
	
	draw_player(sdl, player);


	while (1)
	{
		if (check_event(sdl->event, player, sdl))
			draw_win(sdl, player);
		SDL_UpdateWindowSurface(sdl->window);
	}
	return (0);
}

void	draw_normal(t_sdl *sdl, t_bsp *root, t_map *map)
{
	map->scale_vert[0][X] = root->pivot[X] * SCALER;
	map->scale_vert[0][Y] = root->pivot[Y] * SCALER;
	map->scale_vert[1][X] = (cos(root->normal) + root->pivot[X]) * SCALER;
	map->scale_vert[1][Y] = (sin(root->normal) + root->pivot[Y]) * SCALER;
	draw_line(sdl, map->scale_vert[0], map->scale_vert[1]);
}

void	clear_screen(t_sdl *sdl)
{
	int		i = -1;
	while (++i < WIDTH * HEIGHT)
		PIXEL[i] = 0;
}

char	check_event(SDL_Event event, t_player *player, t_sdl *sdl)
{
	if (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT ||
			(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
			exit(0);
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_a)
			{
				if (check_collision(sdl, player, -1, 0))
					return (0);
				player->crd[X] -= 1;
				return (1);
			}
			if (event.key.keysym.sym == SDLK_d)
			{
				if (check_collision(sdl, player, 1, 0))
					return (0);
				player->crd[X] += 1;
				return (1);
			}
			if (event.key.keysym.sym == SDLK_w)
			{
				if (check_collision(sdl, player, 0, -1))
					return (0);
				player->crd[Y] -= 1;
				return (1);
			}
			if (event.key.keysym.sym == SDLK_s)
			{
				if (check_collision(sdl, player, 0, 1))
					return (0);
				player->crd[Y] += 1;
				return (1);
			}
		}
		return (0);
	}
	return (0);
}

char	check_collision(t_sdl *sdl, t_player *player, char step_x, char step_y)
{
	char	cursor;

	cursor = 1;
	if (step_x)
		while (cursor < 5)
		{
			if (PIXEL[player->crd[X] + cursor * step_x + WIDTH * player->crd[Y]] == SECTCOLOR)
				return (1);
			cursor += 1;
		}
	else
	{
		while (cursor < 5)
		{
			if (PIXEL[player->crd[X] + WIDTH * (player->crd[Y] + cursor * step_y)] == SECTCOLOR)
				return (1);
			cursor += 1;
		}
	}
	return (0);
}

void	draw_win(t_sdl *sdl, t_player *player)
{
	clear_player(sdl, player);
	draw_player(sdl, player);
}
