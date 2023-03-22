/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:26:11 by sunko             #+#    #+#             */
/*   Updated: 2023/03/22 22:46:45 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	make_node(t_list *list, int fd)
{
	t_node	*new_node;

	new_node = (t_node *)malloc(sizeof(t_node));
	if (!list->tail)
	{
		list->tail = new_node;
		new_node->next = new_node;
	}
	else
	{
		new_node->next = list->tail->next;
		list->tail->next = new_node;
	}
	list->cur = list->tail->next;
	list->before = list->tail;
	(list->num_of_node)++;
	list->cur->fd = fd;
	return (1);
}

char	*include_enter(t_list *list)
{
	int		size;
	char	*line;
	char	buffer[BUFFER_SIZE + 1];

	size = 1;
	buffer[BUFFER_SIZE] = 0;
	while (size > 0)
	{
		size = read(list->cur->fd, buffer, BUFFER_SIZE);
		if (size == -1 || size == 0)
		{
			remove_node(list);
			if (size == -1)
				return (NULL);
		}
		while (size < BUFFER_SIZE)
			buffer[size++] = 0;
		line = ft_strjoin(list->cur->save, buffer);
		if (ft_strchr(line, '\n'))
			break ;
	}
	return (line);
}

char	*extract_line(char *tmp)
{
	int		i;
	int		j;
	char	*rst;

	if (!tmp)
		return (NULL);
	i = 0;
	j = -1;
	while (ft_strchr(tmp, '\n') && tmp[i] != '\n')
		i++;
	if (tmp[i] == '\n')
	{
		rst = (char *)malloc(sizeof(char) * (i + 2));
		if (!rst)
			return (NULL);
		while (++j < i)
			rst[j] = tmp[j];
		rst[i + 1] = '\0';
	}
	if (!ft_strchr(tmp, '\n'))
	{
		while (tmp[i++] != '\0')
			rst[i] = tmp[i];
	}
	return (rst);
}

void	keep_save(t_list *list, char *rst)
{
	size_t	len;
	size_t	i;
	size_t	j;

	len = ft_strlen(rst);
	i = 0;
	j = 0;
	if (!ft_strchr(rst, '\n'))
		return ;
	while (ft_strchr(rst, '\n') && rst[i] != '\n')
		i++;
	list->cur->save = (char *)malloc(sizeof(char) * (len - i));
	while (i < len)
		list->cur->save[j++] = rst[i++];
	list->cur->save[i] = '\0';
}

char	*get_next_line(int fd)
{
	static t_list	list;
	char			*tmp;
	char			*rst;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!exist_fd(&list, fd))
	{
		if (!make_node(&list, fd))
			return (NULL);
	}
	if (!list.cur->save)
	{
		list.cur->save = (char *)malloc(1);
		if (list.cur->save)
			return (NULL);
		list.cur->save[0] = 0;
	}
	tmp = include_enter(&list);
	rst = extract_line(tmp);
	keep_save(&list, tmp);
	return (rst);
}
