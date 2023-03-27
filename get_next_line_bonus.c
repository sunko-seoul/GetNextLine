/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 17:39:35 by sunko             #+#    #+#             */
/*   Updated: 2023/03/27 20:40:00 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_free(char *str)
{
	free(str);
	return (0);
}

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
	list->cur->save = (char *)malloc(sizeof(char) * 1);
	if (!list->cur->save)
		return ((int)remove_node(list, NULL));
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
		return (extract_line(list, rst, (int)(ft_strchr(rst, '\n') - rst)));
	else
	{
		free(list->cur->save);
		return (rst);
	}
}

char	*extract_line(t_list *list, char *rst, int pos)
{
	int		j;
	char	*tmp;
	char	*tmp_rst;

	j = -1;
	tmp = (char *)malloc(sizeof(char) * (ft_strlen(rst) - pos));
	if (!tmp)
		return (remove_node(list, rst));
	tmp_rst = (char *)malloc(sizeof(char) * (pos + 2));
	if (!tmp_rst)
		return (remove_node(list, rst) + ft_free(tmp));
	while (++pos < (int)ft_strlen(rst))
		tmp[++j] = rst[pos];
	tmp[++j] = 0;
	list->cur->save = tmp;
	pos = (int)(ft_strchr(rst, '\n') - rst);
	j = -1;
	while (++j <= (pos))
		tmp_rst[j] = rst[j];
	tmp_rst[j] = 0;
	free(rst);
	if (!(*tmp_rst))
		free(list->cur->save);
	return (tmp_rst);
}

char	*get_next_line(int fd)
{
	static t_list	list;
	char			*rst;

	rst = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!check_fd(&list, fd))
		return (NULL);
	rst = (char *)malloc(sizeof(char) * 1);
	if (!rst)
		return (remove_node(&list, list.cur->save));
	rst[0] = 0;
	if (list.cur->save != 0)
		rst = ft_strjoin(&list, rst, list.cur->save);
	if (!rst)
		return (NULL);
	free(list.cur->save);
	list.cur->save = 0;
	rst = read_line(&list, rst);
	if (!rst)
		return (NULL);
	else if (!(*rst))
		return (remove_node(&list, rst));
	return (rst);
}
