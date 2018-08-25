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
	int					**links;
	int					*full_empty;
	struct s_hashmap	*rooms;
	struct s_ways		*solv;
}						t_lemin;

/* ------------- validation.c ------------- */
t_hashmap				*elembyi(t_lemin *ptr, int i);
int						coord_exist(t_lemin *ptr, t_hashmap	*current);
void					error(int e, char *line);
void					read_map(t_lemin *ptr);
int						is_valid(char *line, int bool);

/* ---------------- main.c ---------------- */
int						ibyn(t_lemin *ptr, char *name);
void					create_elem(t_lemin *ptr, t_hashmap *tmp, char *line);
void					write_elem(t_lemin *ptr, char *line);
void					write_link(t_lemin *ptr, char *line, int i);

/* ------------- find_ways.c -------------- */
void					find_next(t_lemin *ptr, t_ways *solv, int numb, int row, int **arr);
void					mem_solv(t_lemin *ptr, int **arr);
int						**copy_arr(int **src, int size);
void					check_link(int k, t_lemin *ptr, int m, int **arr);
int						find_ways(t_lemin *ptr);

/* ------------- ways_help.c -------------- */
void					free_way(t_ways *del);
int						equal_ways(t_ways *way1, t_ways *way2);
void					del_double_ways(t_lemin *ptr, int i);
t_hashmap				*mem_room(t_lemin *ptr, int row);

/* -------------- solution.c -------------- */
void					solution(t_lemin *ptr);

#endif
