/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 15:30:17 by jthuy             #+#    #+#             */
/*   Updated: 2020/10/10 19:29:05 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdio.h>  //   <----- NEED DELL!!!!!!
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>

# include "const.h"
# include "struct.h"

/*
** bdrinkin.c
*/

size_t			ft_strlen(const char *s);
void			ft_putstr(char *s);
void			ft_putendl_fd(char const *s, int fd);
int				put_error_sys(char *error);
void			ft_bzero(void *s, size_t n);
void			*ft_memalloc(size_t size);
int				ft_strcmp(const char *s1, const char *s2);
void			clear_wad_dir(t_dir *dir);
bool			wad_loader(t_wad *doom, char *path);
void			read_head_data(const uint8_t *data, int offset, t_wad_head *head);
void			read_dir_data(const uint8_t *data, int offset, t_dir *dir);
uint32_t		find_offset_lump(t_dir *dir, char *lable, char *name_map);
uint32_t		find_size_lump(t_dir *dir, char *lable, char *name_map);
bool			wad_reader(t_wad *doom);
void			wad_get_vertex(t_wad *doom, t_vlist *vert, char *name_map);

/*
** main.c
*/
void	clear_screen(t_sdl *sdl);
char	check_event(SDL_Event event, t_player *player, t_sdl *sdl);
char	check_collision(t_sdl *sdl, t_player *player, char step_x, char step_y);
void	draw_win(t_sdl *sdl, t_player *player);
void	draw_normal(t_sdl *sdl, t_bsp *root, t_map *map);

/*
** init.c
*/
t_sdl		*init_sdl();
t_map		*init_map(int n);
t_player	*init_player(t_map *map);

/*
** vlist.c
*/
t_vlist	*set_vlist(t_map *map);
t_vlist	*set_vtail(t_map *map);
t_vlist	*create_vnode(int index, t_map *map);
t_vlist	*create_vempty();
void	add_vnode(t_vlist **head, int index, t_map *map);
void	del_vlist(t_vlist **head);

/*
** llist.c
*/
t_llist		*set_llist(t_vlist *vlist);
t_llist		*create_lnode(t_vlist *vertex_0, t_vlist *vertex_1);
void		sort_llist(t_llist *llist);

/*
** bsp_tree.c
*/

t_bsp	*set_tree(t_llist *llist);
t_bsp	*create_bspnode(double *vertex_0, double *vertex_1, t_llist *lcursor);
void	add_bspnode(t_bsp *bsp_tree, t_llist *lcursor, double *vertex_0, double *vertex_1);
double	*sep_lnode(t_bsp *bsp_tree, t_llist *lcursor);

/*
** draw_map.c
*/
void	draw_map(t_sdl *sdl, t_bsp *root, t_map *map, t_player	*player);
void	fill_backgraund(t_sdl *sdl, int mapwidth);
void	draw_sectors(t_sdl *sdl, t_bsp *root, t_map *map);
void	draw_wall(t_sdl *sdl, t_bsp *root, t_map *map);
void	draw_normal(t_sdl *sdl, t_bsp *root, t_map *map);
void	draw_player(t_sdl *sdl, t_player *player);
void	clear_player(t_sdl *sdl, t_player *player);

/*
** draw_line.c
*/
void	draw_line(t_sdl *sdl, int *vert_0, int *vert_1);
void	draw_xmore(t_sdl *sdl, int *vert_0, int *vert_1, char *d, int *len);
void	draw_ymore(t_sdl *sdl, int *vert_0, int *vert_1, char *d, int *len);

#endif
