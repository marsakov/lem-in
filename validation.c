/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 21:20:32 by msakovyc          #+#    #+#             */
/*   Updated: 2018/08/21 21:20:36 by msakovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int		is_valid(char *line, int bool)
{
	char *s;

	if (!bool)
	{
		while (*line)
			if (!ft_isdigit(*line++))
				return (0);
	}
	else
	{
		if (!(s = ft_strchr(line, ' ')) || !*(++s))
			return (0);
		while (*s && *s != ' ')
			if (!ft_isdigit(*s++))
				return (0);
		if (!*(++s))
			return (0);
		while (*s && *s != ' ')
			if (!ft_isdigit(*s++))
				return (0);
		if (*s)
			return (0);
	}
	return (1);
}

int		ibyn(t_lemin *ptr, char *name)
{
	t_hashmap	*tmp;
	int			c;

	c = 0;
	while (name[c] && name[c] != '-' && name[c] != ' ')
		c++;
	tmp = ptr->rooms;
	while (tmp)
	{
		if (name && !ft_strncmp(tmp->name, name, c))
			return (tmp->i);
		tmp = tmp->next;
	}
	return (-1);
}

void	create_elem(t_lemin *ptr, t_hashmap *tmp, char *line)
{
	int i;

	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	tmp->name = ft_memalloc(sizeof(char) * (i + 1));
	tmp->next = NULL;
	if (ibyn(ptr, line) != -1)
		error(5, line);
	tmp->name = ft_strncpy(tmp->name, line, i);
	tmp->x = ft_atoi(ft_strchr(line, ' ') + 1);
	tmp->y = ft_atoi(ft_strrchr(line, ' ') + 1);
}

void	write_elem(t_lemin *ptr, char *line)
{
	int			i;
	t_hashmap	*tmp;

	i = 0;
	if (!is_valid(line, 1))
		error(2, line);
	ft_printf("%s\n", line);
	tmp = ptr->rooms;
	while (i++ < ptr->count_r && tmp->next)
		tmp = tmp->next;
	if (!(i = 0) && !ptr->count_r)
	{
		!(tmp = malloc(sizeof(t_hashmap))) ? error(0, NULL) : 0;
		ptr->rooms = tmp;
	}
	else
	{
		!(tmp->next = malloc(sizeof(t_hashmap))) ? error(0, NULL) : 0;
		tmp = tmp->next;
	}
	create_elem(ptr, tmp, line);
	tmp->i = ptr->count_r;
	if (coord_exist(ptr, tmp))
		error(8, line);
	ptr->count_r++;
}

void	write_link(t_lemin *p, char *line, int i)
{
	if (p->start == -1 || p->end == -1)
		error(4, NULL);
	p->links = malloc(sizeof(int*) * p->count_r);
	while (i < p->count_r)
		p->links[i++] = (int*)ft_memalloc(sizeof(int) * p->count_r);
	if (ibyn(p, line) == -1 || ibyn(p, ft_strchr(line, '-') + 1) == -1)
		error(3, line);
	p->links[ibyn(p, line)][ibyn(p, ft_strchr(line, '-') + 1)] = 1;
	p->links[ibyn(p, ft_strchr(line, '-') + 1)][ibyn(p, line)] = 1;
	ft_printf("%s\n", line);
	ft_strdel(&line);
	while (GNL(0, &line) > 0)
	{
		if (ft_strchr(line, '-') && !ft_strchr(line, '#'))
		{
			if (ibyn(p, line) == -1 || ibyn(p, ft_strchr(line, '-') + 1) == -1)
				error(3, line);
			p->links[ibyn(p, line)][ibyn(p, ft_strchr(line, '-') + 1)] = 1;
			p->links[ibyn(p, ft_strchr(line, '-') + 1)][ibyn(p, line)] = 1;
		}
		ft_printf("%s\n", line);
		ft_strdel(&line);
	}
}
