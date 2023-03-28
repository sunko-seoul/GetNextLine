/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:26:11 by sunko             #+#    #+#             */
/*   Updated: 2023/03/28 16:08:27 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	total;
	size_t	i;
	char	*ptr;

	total = count * size;
	i = 0;
	ptr = (char *)malloc(total);
	if (!ptr)
		return (NULL);
	while (i < total)
	{
		ptr[i] = 0;
		i++;
	}
	return (ptr);
}

int	make_node(t_list *list, int fd)
{
	t_list_node	*new_node;

	new_node = (t_list_node *)malloc(sizeof(t_list_node));
	if (!new_node)
		return (0);
	list->cur = new_node;
	list->cur->fd = fd;
	list->cur->save = (char *)ft_calloc(1, sizeof(char));
	if (!list->cur->save)
		return ((int)ft_free(list, NULL, NULL));
	return (1);
}

char	*read_line(t_list *list, char *rst)
{
	char	buffer[BUFFER_SIZE + 1];
	int		size;

	while (1)
	{
		size = read(list->cur->fd, buffer, BUFFER_SIZE);
		if (size == 0)
			break ;
		else if (size == -1)
			return (ft_free(list, rst, NULL));
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
		list->cur->save = ft_free(NULL, NULL, list->cur->save);
		return (rst);
	}
}

char	*extract_line(t_list *list, char *rst, int pos)
{
	int		j;
	char	*tmp_rst;
	size_t	len;
	char	*enter;

	j = -1;
	len = ft_strlen(rst);
	enter = ft_strchr(rst, '\n');
	list->cur->save = (char *)ft_calloc(len - pos, sizeof(char));
	if (!list->cur->save)
		return (ft_free(list, rst, NULL));
	tmp_rst = (char *)ft_calloc(pos + 2, sizeof(char));
	if (!tmp_rst)
		return (ft_free(list, rst, list->cur->save));
	while (++pos < (int)len)
		list->cur->save[++j] = rst[pos];
	pos = (int)(enter - rst);
	j = -1;
	while (++j <= (pos))
		tmp_rst[j] = rst[j];
	rst = ft_free(NULL, NULL, rst);
	if (!(*tmp_rst))
		list->cur->save = ft_free(NULL, NULL, list->cur->save);
	return (tmp_rst);
}

char	*get_next_line(int fd)
{
	static t_list	list;
	char			*rst;

	rst = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!list.cur)
		if (!make_node(&list, fd))
			return (NULL);
	rst = (char *)ft_calloc(1, sizeof(char));
	if (!rst)
		return (ft_free(&list, list.cur->save, NULL));
	if (list.cur->save != 0)
		rst = ft_strjoin(&list, rst, list.cur->save);
	if (!rst)
		return (NULL);
	list.cur->save = ft_free(NULL, NULL, list.cur->save);
	rst = read_line(&list, rst);
	if (!rst)
		return (NULL);
	else if (!(*rst))
		return (ft_free(&list, rst, NULL));
	return (rst);
}
