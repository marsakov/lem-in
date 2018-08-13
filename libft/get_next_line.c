/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 15:22:21 by msakovyc          #+#    #+#             */
/*   Updated: 2018/04/25 18:48:02 by msakovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static t_gnl	*ft_check(int fd, t_gnl *temp)
{
	while (temp)
	{
		if (temp->fd == fd)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

static void		ft_zapominalka(int fd, char *buf, t_gnl **lst, int counter)
{
	t_gnl	*elem;
	t_gnl	*temp;

	temp = ft_check(fd, *lst);
	if (temp && temp->fd == fd)
	{
		ft_strncpy(temp->content, buf, BUFF_SIZE);
		temp->i = counter;
	}
	else
	{
		elem = (t_gnl *)malloc(sizeof(t_gnl));
		ft_strncpy(elem->content, buf, BUFF_SIZE);
		elem->fd = fd;
		elem->i = counter;
		elem->next = *lst;
		*lst = elem;
	}
}

static int		ft_writer(char **line, t_gnl *temp, int i)
{
	int		tmp;
	char	*p;

	p = *line;
	tmp = temp->i;
	while (temp->i < BUFF_SIZE && temp->content[temp->i] != '\n' &&
		temp->content[temp->i] != 0)
	{
		temp->i++;
		i++;
	}
	*line = ft_strnjoin(*line, (temp->content + tmp), i);
	if (p)
		free(p);
	if (temp->i != BUFF_SIZE)
	{
		if (temp->content[temp->i] == 0 || (temp->content[temp->i + 1] == 0
			&& temp->content[temp->i] == '\n'))
			temp->i = BUFF_SIZE;
		else if (temp->content[temp->i] == '\n')
			temp->i++;
		return (1);
	}
	return (0);
}

int				ft_reader(int fd, int i, t_gnl **temp, t_gnl **lst)
{
	char			buf[BUFF_SIZE + 1];
	int				bytes;

	bytes = read(fd, buf, BUFF_SIZE);
	if (bytes == -1)
		return (-1);
	if (bytes == 0)
	{
		if (i)
			return (1);
		return (0);
	}
	buf[bytes] = 0;
	ft_zapominalka(fd, buf, lst, 0);
	if (!*temp)
		*temp = *lst;
	return (5);
}

int				get_next_line(const int fd, char **line)
{
	static t_gnl	*lst = NULL;
	t_gnl			*temp;
	int				rdr;
	int				wrtr;
	int				i;

	i = 0;
	temp = ft_check(fd, lst);
	if (line && *line)
		*line = 0;
	wrtr = 0;
	while (wrtr == 0)
	{
		if (!temp || temp->i == BUFF_SIZE)
		{
			rdr = ft_reader(fd, i, &temp, &lst);
			if (rdr == 1 || rdr == -1 || rdr == 0)
				return (rdr);
		}
		wrtr = ft_writer(line, temp, 0);
		i++;
	}
	return (1);
}
