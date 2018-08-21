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

void	find_next(t_lemin *ptr, t_ways *solv, int numb, int row, int index)
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

void	mem_solv(t_lemin *ptr)
{
	int 		i;
	int			m;
	t_ways		*w;

	m = 0;
	ptr->solv = NULL;
	i = 0;
	while (i < ptr->count_r)
	{
		if (ptr->links[ptr->end][i] != 0)
		{
			w = malloc(sizeof(t_ways));
			w->i = m++;
			w->way = mem_room(ptr, ptr->end, 0);
			w->way->next = NULL;
			w->next = ptr->solv;
			ptr->solv = w;
			find_next(ptr, ptr->solv, ptr->links[ptr->end][i] - 1, i, 1);
		}
		i++;
	}

	while (ptr->solv)
	{
		while (ptr->solv->way)
		{
			ft_printf("-> %s ", ptr->solv->way->name);
			ptr->solv->way = ptr->solv->way->next;
		}
		ft_printf("\n");
		ptr->solv = ptr->solv->next;
	}
}

void	check_link(int k, t_lemin *ptr, int m)
{
	if (k == ptr->end)
		return ;
	int i = 0;
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

int		find_solutions(t_lemin *ptr)
{
	int	i;

	i = 0;
	while (i < ptr->count_r)
	{
		if (ptr->links[ptr->start][i] == 1)
		{
			ptr->links[ptr->start][i] = 2;
			ptr->links[i][ptr->start] = 2;
			check_link(i, ptr, 3);
		}
		i++;
	}
	i = 0;
	ptr->ways = 0;
	while (i < ptr->count_r)
		if (ptr->links[ptr->end][i++] != 0)
			ptr->ways++;
	ft_printf("ways = %d\n", ptr->ways);
	mem_solv(ptr);
	return (ptr->ways);
}