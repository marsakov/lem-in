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

typedef struct			s_lemin
{
	int					ants;
	int					start;
	int					end;
	int					count_r;
	int					**links;
	struct s_hashmap	*rooms;
}						t_lemin;

#endif
