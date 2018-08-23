/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solution.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 21:20:45 by msakovyc          #+#    #+#             */
/*   Updated: 2018/08/21 21:20:49 by msakovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

t_hashmap	*mem_room(t_lemin *ptr, int row, int index)
{
	t_hashmap	*tmp;
	t_hashmap	*way;

	tmp = elembyi(ptr, row);
	way = malloc(sizeof(t_hashmap));
	way->i = index;
	way->name = ft_strdup(tmp->name);
	way->x = tmp->x;
	way->y = tmp->y;
	return (way);
}

void		find_next(t_lemin *ptr, t_ways *solv, int numb, int row, int index)
{
	int 		i;
	t_hashmap	*way;

	i = 0;
	if (row == ptr->start)
	{
		way = mem_room(ptr, row, index);
		way->next = solv->way;
		solv->way = way;
		return ;
	}
	while (i < ptr->count_r)
	{
		if (ptr->links[row][i] == numb)
		{
			way = mem_room(ptr, row, index);
			way->next = solv->way;
			solv->way = way;
			find_next(ptr, solv, numb - 1, i, index + 1);
		}
		i++;
	}
}

void		mem_solv(t_lemin *ptr)
{
	int 		i;
	t_ways		*w;

	if (ptr->ways == 0)
		ptr->solv = NULL;
	i = 0;
	while (i < ptr->count_r)
	{
		if (ptr->links[ptr->end][i] != 0)
		{
			w = malloc(sizeof(t_ways));
			w->i = ptr->ways++;
			w->way = mem_room(ptr, ptr->end, 0);
			w->way->next = NULL;
			w->next = ptr->solv;
			ptr->solv = w;
			find_next(ptr, ptr->solv, ptr->links[ptr->end][i] - 1, i, 1);
		}
		i++;
	}
}

void	copy_arr(int **dst, int **src, int size)
{
	int i;
	int j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			dst[i][j] = src[i][j];
			j++;
		}
		i++;
	}
}

void	check_link(int k, t_lemin *ptr, int m)
{
	int i;

	if (k == ptr->end)
		return ;
	i = 0;
	while (i < ptr->count_r)
	{
		if (ptr->links[k][i] == 1)
		{
			ptr->links[k][i] = m;
			ptr->links[i][k] = m;
			check_link(i, ptr, m + 1);
		}
		i++;
	}
}

void	del_wrong_ways(t_lemin *ptr)
{
	t_ways *tmp;
	t_hashmap *start;

	tmp = ptr->solv;
	start = elembyi(ptr, ptr->start);
	while (ft_strcmp(ptr->solv->name, start->name))
		ptr->solv = ptr->solv->next;
	while (tmp->next)
	{
		if (ft_strcmp(tmp->next->way->name, start->name))
		{
			tmp->next = tmp->next->next;
		}
		else
			tmp = tmp->next;
	}
}

int		find_solutions(t_lemin *ptr)
{
	int	i;

	i = -1;
	ptr->ways = 0;
	ptr->copy_links = ft_memalloc(sizeof(int**));
	while (++i < ptr->count_r)
		ptr->copy_links[i] = ft_memalloc(sizeof(int*) * ptr->count_r);
	copy_arr(ptr->copy_links, ptr->links, ptr->count_r);
	i = 0;
	while (i < ptr->count_r)
	{
		if (ptr->links[ptr->start][i] == 1)
		{
			ptr->links[ptr->start][i] = 2;
			ptr->links[i][ptr->start] = 2;
			check_link(i, ptr, 3);
			mem_solv(ptr);
			copy_arr(ptr->links, ptr->copy_links, ptr->count_r);
		}
		i++;
	}
	// mem_solv(ptr);

	del_wrong_ways(ptr);
	/* ------------------------------------------------*/
	ft_printf("_________ mem solv ________\n");
	t_ways *tmp = ptr->solv;
	while (tmp)
	{
		t_hashmap *tmp_way = tmp->way;
		while (tmp_way)
		{
			ft_printf("-> %s ", tmp_way->name);
			tmp_way = tmp_way->next;
		}
		ft_printf("\n");
		tmp = tmp->next;
	}
	ft_printf("__________________________\n");
	/* ------------------------------------------------*/
	ft_printf("ways = %d\n", ptr->ways);
	return (ptr->ways);
}
