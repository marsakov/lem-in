/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ways_help.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakovyc <msakovyc@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 13:42:57 by msakovyc          #+#    #+#             */
/*   Updated: 2018/08/25 13:43:00 by msakovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int			free_way(t_ways *del)
{
	// ft_printf(RED "free_way : " NC);
	if (!del)
		return (0);
	while (del->way)
	{
		// ft_printf(YELLOW " |adr = %p| " NC, del->way->name);
		// ft_printf(YELLOW " del->way->name |i = %d| " NC, del->way->i);
		if (del->way->name)
			// free(del->way->name);
			ft_strdel(&(del->way->name));
		// ft_printf(YELLOW " del->way\n" NC);
		// if (del->way)
		// 	free(del->way);
		del->way = del->way->next;
	}
	if (del)
		free(del);
	// ft_printf(RED "END free_way\n" NC);
	return (1);
}

int			cross_ways(t_ways *way1, t_ways *way2)
{
	t_hashmap	*tmp1;
	t_hashmap	*tmp2;

	// ft_printf(LGREEN "cross_ways : " NC);
	tmp1 = way1->way->next;
	while (tmp1)
	{
		tmp2 = way2->way->next;
		while (tmp2 && tmp1->name && tmp2->name)
		{
			if (tmp1->next && tmp2->next && !ft_strcmp(tmp1->name, tmp2->name))
			{
				// ft_printf(LBLUE "OK\n" NC);
				return (1);
			}
			tmp2 = tmp2->next;
		}
		tmp1 = tmp1->next;
	}
	// ft_printf(LBLUE "OK\n" NC);
	return (0);
}

int			equal_ways(t_ways *way1, t_ways *way2)
{
	t_hashmap *tmp1;
	t_hashmap *tmp2;

	if (!way1 || !way2)
		return (0);
	// ft_printf(LCYAN "equal_ways : " NC);
	tmp1 = way1->way;
	tmp2 = way2->way;
	while (tmp1 && tmp2 && tmp1->name && tmp2->name)
	{
		if (ft_strcmp(tmp1->name, tmp2->name))
		{
			// ft_printf(LBLUE "OK\n" NC);
			return (0);
		}
		tmp1 = tmp1->next;
		tmp2 = tmp2->next;
	}
	// ft_printf(LBLUE "OK\n" NC);
	return (1);
}

void		del_double_ways(t_lemin *ptr, int i)
{
	t_ways	*tmp1;
	t_ways	*tmp2;
	t_ways	*leak;

	tmp1 = ptr->solv;
	while (tmp1)
	{
		tmp2 = ptr->solv;
		while (tmp2 && tmp2->next)
			if (tmp1->i != tmp2->next->i && (equal_ways(tmp1, tmp2->next) ||
						cross_ways(tmp1, tmp2->next)))
			{
				leak = tmp2->next;
				tmp2->next = tmp2->next->next;
				free_way(leak);
				ptr->ways--;
			}
			else
				tmp2 = tmp2->next;
		tmp1 = tmp1->next;
	}
	tmp1 = ptr->solv;
	while (tmp1)
	{
		tmp1->i = i++;
		tmp1 = tmp1->next;
	}
}

t_hashmap	*mem_room(t_lemin *ptr, int row)
{
	t_hashmap	*tmp;
	t_hashmap	*way;

	tmp = elembyi(ptr, row);
	if (!tmp)
		return (NULL);
	!(way = malloc(sizeof(t_hashmap))) ? error(1, NULL) : 0;
	way->i = tmp->i;
	way->name = ft_strdup(tmp->name);
	way->x = tmp->x;
	way->y = tmp->y;
    way->next = NULL;
	return (way);
}
