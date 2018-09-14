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

#ifndef LEMIN_H
# define LEMIN_H

# include <math.h>
# include "libft/includes/libft.h"

# define GNL(fd, ln) get_next_line(fd, &line)
# define ANT_STEP nxt_rm && !ptr->ant_step[rm->ant - 1]
# define NE_VALID line[0] != '#' || !ft_strcmp(line, "##start") || !ft_strcmp(line, "##end")

typedef struct			s_hashmap
{
	int					i;
	char				*name;
	int					x;
	int					y;
	int					ant;
	struct s_hashmap	*next;
}						t_hashmap;

typedef struct			s_ways
{
	int					i;
	int					len;
	int					*way;
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
	int					*ant_in_end;
	int					*ant_step;
	struct s_hashmap	*rooms;
	struct s_ways		*solv;
}						t_lemin;

/*
** ---------------- main.c ---------------- **
*/
t_hashmap				*elembyi(t_lemin *ptr, int i);
int						coord_exist(t_lemin *ptr, t_hashmap	*current);
int						error(int e, char *line);
void					read_map(t_lemin *ptr, char *line);

/*
** ------------- validation.c ------------- **
*/
int						is_valid(char *line, int bool);
int						ibyn(t_lemin *ptr, char *name);
void					create_elem(t_lemin *ptr, t_hashmap *tmp, char *line);
int						write_elem(t_lemin *ptr, char *line);
void					write_link(t_lemin *ptr, char *line, int i);

/*
** ------------- find_ways.c -------------- **
*/
void					find_next(t_lemin *ptr, int numb, int row, int **arr);
void					mem_solv(t_lemin *ptr, int **arr);
int						**copy_arr(int **src, int size);
void					check_link(int k, t_lemin *ptr, int m, int **arr);
int						find_ways(t_lemin *ptr, int ac, char **av);

/*
** ------------- ways_help.c -------------- **
*/
void					print_path(t_lemin *ptr);
void					sort_ways(t_lemin *ptr, int j);
int						cross_ways(t_ways *way1, t_ways *way2);
int						equal_ways(t_ways *way1, t_ways *way2);
void					del_double_ways(t_lemin *ptr, int i);

/*
** -------------- solution.c -------------- **
*/
void					solution(t_lemin *ptr, int ant);
void					print_step(t_lemin *ptr);
int						find_linked_room(t_lemin *ptr, int index);
void					next_step(t_lemin *ptr);

/*
** -------------- solv_help.c ------------- **
*/
int						ants_not_in_end(t_lemin *ptr);
int						ants_steps(t_lemin *ptr);
void					print_all_step(t_lemin *ptr);

#endif
