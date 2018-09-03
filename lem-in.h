/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 20:05:59 by msakovyc          #+#    #+#             */
/*   Updated: 2018/08/09 20:06:01 by msakovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <math.h>
# include "libft/includes/libft.h"

# define GNL(fd, ln) get_next_line(fd, &line)

typedef struct			s_hashmap
{
	int					i;
	char				*name;
	int					x;
	int					y;
	struct s_hashmap	*next;
}						t_hashmap;

typedef struct			s_ways
{
	int					i;
	int					len;
	struct s_hashmap	*way;
	struct s_ways		*next;
}						t_ways;

typedef struct			s_lemin
{
	int					ants;
	int					start;
	int					end;
	int					count_r;
	int					l;
	int					ways;
	int					all_path;
	int					true_path;
	int					**links;
	int					*ant_in_room;
	int					*ant_in_end;
	int					*ant_step;
	struct s_hashmap	*rooms;
	struct s_ways		*solv;
}						t_lemin;

/* ---------------- main.c ---------------- */
t_hashmap				*elembyi(t_lemin *ptr, int i);
int						coord_exist(t_lemin *ptr, t_hashmap	*current);
int						error(int e, char *line);
void					read_map(t_lemin *ptr, char *line);

/* ------------- validation.c ------------- */
int						is_valid(char *line, int bool);
int						ibyn(t_lemin *ptr, char *name);
void					create_elem(t_lemin *ptr, t_hashmap *tmp, char *line);
int						write_elem(t_lemin *ptr, char *line);
void					write_link(t_lemin *ptr, char *line, int i);

/* ------------- find_ways.c -------------- */
void					find_next(t_lemin *ptr, t_ways *solv, int numb, int row, int **arr);
void					mem_solv(t_lemin *ptr, int **arr);
int						**copy_arr(int **src, int size);
void					check_link(int k, t_lemin *ptr, int m, int **arr);
int						find_ways(t_lemin *ptr);

/* ------------- ways_help.c -------------- */
int						free_way(t_ways *del);
int						cross_ways(t_ways *way1, t_ways *way2);
int						equal_ways(t_ways *way1, t_ways *way2);
void					del_double_ways(t_lemin *ptr, int i);
t_hashmap				*mem_room(t_lemin *ptr, int row);

/* -------------- solution.c -------------- */
void					solution(t_lemin *ptr);
void					sort_ways(t_lemin *ptr, int j);
t_hashmap				*find_room(t_lemin *ptr, int index);
void					next_step(t_lemin *ptr);
int						ants_not_in_end(t_lemin *ptr);

void	print_path(t_lemin *ptr);

#endif
