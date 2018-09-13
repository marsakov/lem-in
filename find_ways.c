/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_ways.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakovyc <msakovyc@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 13:42:48 by msakovyc          #+#    #+#             */
/*   Updated: 2018/08/25 13:42:51 by msakovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	find_next(t_lemin *ptr, int numb, int row, int **arr)
{
	int	i;

	i = -1;
	if (row == ptr->start)
	{
		ptr->solv->way[0] = row;
		return ;
	}
	while (++i < ptr->count_r)
		if (arr[row][i] == numb)
		{
			ptr->solv->way[ptr->solv->len - ++(ptr->solv->i)] = row;
			find_next(ptr, numb - 1, i, arr);
		}
}

void	mem_solv(t_lemin *ptr, int **arr)
{
	int		i;
	t_ways	*w;

	if (ptr->ways > 5000)
	{
		sort_ways(ptr, -1);
		del_double_ways(ptr, 0);
	}
	if (ptr->ways == 0)
		ptr->solv = NULL;
	i = -1;
	while (++i < ptr->count_r)
		if (arr[ptr->end][i] != 0 && arr[ptr->end][i] != 1)
		{
			!(w = malloc(sizeof(t_ways))) ? error(0, NULL) : 0;
			if (!(w->way = malloc(sizeof(int) * arr[ptr->end][i])))
				error(0, NULL);
			w->i = 0;
			w->len = arr[ptr->end][i];
			w->way[w->len - ++(w->i)] = ptr->end;
			w->next = ptr->solv;
			ptr->solv = w;
			find_next(ptr, arr[ptr->end][i] - 1, i, arr);
			ptr->ways++;
		}
}

int		**copy_arr(int **src, int size)
{
	int i;
	int j;
	int **arr;

	i = -1;
	!(arr = ft_memalloc(sizeof(int*) * size)) ? error(0, NULL) : 0;
	while (++i < size)
		!(arr[i] = ft_memalloc(sizeof(int) * size)) ? error(0, NULL) : 0;
	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size)
			arr[i][j] = src[i][j];
	}
	return (arr);
}

void	check_link(int k, t_lemin *ptr, int m, int **arr)
{
	int	i;
	int	j;
	int	**next_arr;

	if (ptr->ways && m > ptr->ants && m > ptr->solv->len)
		return ;
	if (k == ptr->end)
	{
		mem_solv(ptr, arr);
		return ;
	}
	i = -1;
	while (++i < ptr->count_r)
		if (arr[k][i] == 1)
		{
			next_arr = copy_arr(arr, ptr->count_r);
			next_arr[k][i] = m;
			next_arr[i][k] = m;
			check_link(i, ptr, m + 1, next_arr);
			j = -1;
			while (++j < ptr->count_r)
				free(next_arr[j]);
			free(next_arr);
		}
}

int		find_ways(t_lemin *ptr, int ac, char **av)
{
	int		i;
	t_ways	*w;

	ptr->ways = 0;
	if (ptr->links[ptr->end][ptr->start] == 1)
	{
		print_step(ptr, 0);
		exit(1);
	}
	i = -1;
	while (++i < ptr->count_r)
		ptr->links[i][ptr->start] = 0;
	check_link(ptr->start, ptr, 2, ptr->links);
	i = -1;
	w = ptr->solv;
	while (w && (w->i = i++) + 1)
		w = w->next;
	sort_ways(ptr, -1);
	if ((ac - 1) && (!ft_strcmp(av[1], "-a") || !ft_strcmp(av[1], "-at")
		|| !ft_strcmp(av[1], "-ta")))
		print_path(ptr);
	del_double_ways(ptr, 0);
	if ((ac - 1) && (!ft_strcmp(av[1], "-t") || !ft_strcmp(av[1], "-at")
		|| !ft_strcmp(av[1], "-ta")))
		print_path(ptr);
	return (ptr->ways);
}
