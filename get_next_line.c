/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:26:11 by sunko             #+#    #+#             */
/*   Updated: 2023/03/25 23:15:05 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	make_node(t_list *list, int fd)
{
	t_list_node	*new_node;

	new_node = (t_list_node *)malloc(sizeof(t_list_node));
	if (!new_node)
		return (0);
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
	list->cur->save[0] = 0;
	return (1);
}

char	*read_line(t_list *list, char *rst)
{
	char	buffer[BUFFER_SIZE + 1];
	int		size;

	buffer[BUFFER_SIZE] = 0;
	while (1)
	{
		size = read(list->cur->fd, buffer, BUFFER_SIZE);
		if (size == 0)
			break ;
		else if (size == -1)
			return (remove_node(list, rst));
		buffer[size] = 0;
		rst = ft_strjoin(list, rst, buffer);
		if (!rst)
			return (NULL);
		if (ft_strchr(rst, '\n'))
			break ;
	}
	if (ft_strchr(rst, '\n'))
		return (extract_line(list, rst));
	else
		return (rst);
}

char	*extract_line(t_list *list, char *rst)
{
	int		pos;
	size_t	i;
	size_t	len;
	int		j;

	i = 0;
	len = ft_strlen(rst);
	j = -1;
	pos = (int)(ft_strchr(rst, '\n') - rst);
	while (j < BUFFER_SIZE && ++pos < (int)len)
		list->cur->save[++j] = rst[pos];
	while (j < BUFFER_SIZE)
		list->cur->save[++j] = 0;
	pos = (int)(ft_strchr(rst, '\n') - rst);
	while (++pos < (int)len)
		rst[pos] = 0;
	return (rst);
}

char	*get_next_line(int fd)
{
	static t_list	list;
	char			*rst;
	int				i;

	rst = NULL;
	i = -1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!check_fd(&list, fd))
		return (NULL);
	rst = (char *)malloc(sizeof(char) * 1);
	rst[0] = 0;
	rst = ft_strjoin(&list, rst, list.cur->save);
	while (++i <= BUFFER_SIZE)
		list.cur->save[i] = 0;
	if (!rst)
		return (NULL);
	rst = read_line(&list, rst);
	if (!rst)
		return (NULL);
	else if (!(*rst))
		return (remove_node(&list, rst));
	return (rst);
}
