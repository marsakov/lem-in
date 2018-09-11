/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 20:05:41 by msakovyc          #+#    #+#             */
/*   Updated: 2018/08/09 20:05:43 by msakovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_hashmap	*elembyi(t_lemin *ptr, int i)
{
	t_hashmap	*tmp;

	tmp = ptr->rooms;
	while (tmp)
	{
		if (tmp->i == i)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

int			coord_exist(t_lemin *ptr, t_hashmap *current)
{
	int			i;
	t_hashmap	*tmp;

	i = 0;
	tmp = ptr->rooms;
	while (i++ < current->i && tmp)
	{
		if (tmp->x == current->x && tmp->y == current->y)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int			error(int e, char *line)
{
	ft_printf(RED "%s [", "ERROR" NC);
	if (e == 0)
		ft_printf("%s]\n", "MEM ALLOC ERROR");
	else if (e == 1)
		ft_printf("%s : '%s']\n", "INVALID ANTS", line);
	else if (e == 2)
		ft_printf("%s : '%s']\n", "INVALID ROOM", line);
	else if (e == 3)
		ft_printf("%s : '%s']\n", "INVALID LINK", line);
	else if (e == 4)
		ft_printf("%s]\n", "MISSING '##start' or '##end'");
	else if (e == 5)
		ft_printf("%s : '%s']\n", "ROOM HAS ALREADY EXIST", line);
	else if (e == 6)
		ft_printf("%s]\n", "NO LINKS");
	else if (e == 7)
		ft_printf("%s]\n", "NO WAYS");
	else if (e == 8)
		ft_printf("%s : '%s']\n", "REPEAT COORD", line);
	else if (e == 9)
		ft_printf("%s : '%s']\n", "INVALID LINK", line);
	else if (e == 10)
		ft_printf("%s : '%s']\n", "REPEAT '##start' or '##end'", line);
	exit(1);
	return (1);
}

void		read_map(t_lemin *ptr, char *line)
{
	while (GNL(0, &line) > 0 && ft_strcmp(line, "END"))
	{
		if (!ft_strcmp(line, "##start") || !ft_strcmp(line, "##end"))
		{
			if (!ft_strcmp(line, "##start"))
				ptr->start == -1 ? ptr->start = ptr->count_r : error(10, line);
			if (!ft_strcmp(line, "##end"))
				ptr->end == -1 ? ptr->end = ptr->count_r : error(10, line);
			ft_printf("%s\n", line);
			ft_strdel(&line);
			while (GNL(0, &line) > 0 && ft_strchr(line, '#') &&
				ft_printf("%s\n", line))
				ft_strdel(&line);
			write_elem(ptr, line);
			free(line);
		}
		else if (ft_strchr(line, '-') && line[0] != '#' && ++ptr->l)
			write_link(ptr, line, 0);
		else
		{
			line[0] == '#' ? ft_printf("%s\n", line) : write_elem(ptr, line);
			free(line);
		}
	}
}

int			main(void)
{
	t_lemin	*ptr;
	char	*line;

	(!(ptr = malloc(sizeof(t_lemin)))) ? error(0, NULL) : 0;
	ptr->l = 0;
	ptr->count_r = 0;
	ptr->start = -1;
	ptr->end = -1;
	ptr->all_path = 0;
	ptr->true_path = 0;
	ptr->solv = NULL;
	while (GNL(0, &line) > 0 && ft_printf("%s\n", line) &&
		!(ptr->ants = ft_atoi(line)))
	{
		!ft_strchr(line, '#') ? error(1, line) : 0;
		ft_strdel(&line);
	}
	if (!line || !is_valid(line, 0) || ft_strlen(line) > 9 || !ptr->ants)
		error(1, line);
	ft_strdel(&line);
	read_map(ptr, NULL);
	(ptr->l == 0) ? error(6, NULL) : 0;
	(!find_ways(ptr)) ? error(7, NULL) : 0;
	solution(ptr, 1);
	return (0);
}
