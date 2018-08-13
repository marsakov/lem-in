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

int		ibyname(t_lemin *ptr, char *name)
{
	t_hashmap	*tmp;
	int			c;

	c = 0;
	while (name[c] && name[c] != '-' && name[c] != ' ')
		c++;
	tmp = ptr->rooms;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, name, c))
			return (tmp->i);
		tmp = tmp->next;
	}
	return (-1);
}

void	error(int e, char *line)
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
		ft_printf("%s\n", "MISSING '##start' or '##end']");
	else if (e == 5)
		ft_printf("%s : '%s']\n", "ROOM HAS ALREADY EXIST", line);
	exit(1);
}

void	create_elem(t_lemin *ptr, t_hashmap *tmp, char *line)
{
	int i;

	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	tmp->name = ft_memalloc(sizeof(char) * (i + 1));
	if (ibyname(ptr, line) != -1)
		error(5, line);
	tmp->name = ft_strncpy(tmp->name, line, i);
	tmp->x = ft_atoi(ft_strchr(line, ' ') + 1);
	tmp->y = ft_atoi(ft_strrchr(line, ' ') + 1);
	tmp->next = NULL;
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
		if (!(tmp = malloc(sizeof(t_hashmap))))
			error(0, NULL);
		ptr->rooms = tmp;
	}
	else
	{
		if (!(tmp->next = malloc(sizeof(t_hashmap))))
			error(0, NULL);
		tmp = tmp->next;
	}
	create_elem(ptr, tmp, line);
	tmp->i = ptr->count_r;
	ptr->count_r++;
}

void	write_link(t_lemin *ptr, char *line)
{
	int i;

	i = 0;
	if (ptr->start == -1 || ptr->end == -1)
		error(4, NULL);
	ptr->links = malloc(sizeof(int*) * ptr->count_r);
	while (i < ptr->count_r)
		ptr->links[i++] = (int*)ft_memalloc(sizeof(int) * ptr->count_r);
	if (ibyname(ptr, line) == -1 || ibyname(ptr, ft_strchr(line, '-') + 1) == -1)
		error(3, line);
	ptr->links[ibyname(ptr, line)][ibyname(ptr, ft_strchr(line, '-') + 1)] = 1;
	ptr->links[ibyname(ptr, ft_strchr(line, '-') + 1)][ibyname(ptr, line)] = 1;
	ft_printf("%s\n", line);
	ft_strdel(&line);
	while (GNL(0, &line) > 0)
	{
		if (ft_strchr(line, '-') && !ft_strchr(line, '#'))
		{
			if (ibyname(ptr, line) == -1 || ibyname(ptr, ft_strchr(line, '-') + 1) == -1)
				error(3, line);
			ptr->links[ibyname(ptr, line)][ibyname(ptr, ft_strchr(line, '-') + 1)] = 1;
			ptr->links[ibyname(ptr, ft_strchr(line, '-') + 1)][ibyname(ptr, line)] = 1;
		}
		ft_printf("%s\n", line);
		ft_strdel(&line);
	}
}

void	read_map(t_lemin *ptr)
{
	char *line;

	while (GNL(0, &line) > 0)
	{
		if (!ft_strcmp(line, "##start") || !ft_strcmp(line, "##end"))
		{
			if (ft_strcmp(line, "##start"))
				ptr->start = ptr->count_r;
			else
				ptr->end = ptr->count_r;
			ft_printf("%s\n", line);
			ft_strdel(&line);
			while (GNL(0, &line) > 0 && ft_strchr(line, '#'))
			{
				ft_printf("%s\n", line);
				ft_strdel(&line);
			}
			write_elem(ptr, line);
		}
		else if (ft_strchr(line, '-') && !ft_strchr(line, '#'))
			write_link(ptr, line);
		else if (!ft_strchr(line, '#'))
			write_elem(ptr, line);
		else
			ft_printf("%s\n", line);
		if (line && *line && !(ft_strchr(line, '-') && !ft_strchr(line, '#')))
			ft_strdel(&line);
	}
	ft_printf("END WRITTNG\n");
}

int		main(void)
{
	t_lemin	*ptr;
	char	*line;

	if (!(ptr = malloc(sizeof(t_lemin))))
		return (0);
	ptr->count_r = 0;
	ptr->start = -1;
	ptr->end = -1;
	while (GNL(0, &line) > 0 && !(ptr->ants = ft_atoi(line)))
		ft_strdel(&line);
	if (!line || !is_valid(line, 0) || !ptr->ants)
		error(1, line);
	ft_strdel(&line);
	ft_printf("ants = %d\n", ptr->ants);
	read_map(ptr);
	for (int j = 0; j < ptr->count_r; j++)
	{
		for (int k = 0; k < ptr->count_r; k++)
			ft_printf("%d ", ptr->links[j][k]);
		ft_printf("\n");
	}
	// while (1);
	return (0);
}