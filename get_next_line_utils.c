/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:26:13 by sunko             #+#    #+#             */
/*   Updated: 2023/03/27 15:28:47 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(t_list *list, char *rst, char *buffer)
{
	int		i;
	int		j;
	char	*ptr;
	size_t	len;

	i = -1;
	j = -1;
	len = ft_strlen(rst) + ft_strlen(buffer);
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
	{
		free(buffer);
		return (remove_node(list, rst));
	}
	ptr[len] = 0;
	while (rst[++i] != '\0')
		ptr[i] = rst[i];
	while (buffer[++j] != '\0')
		ptr[i++] = buffer[j];
	free(rst);
	return (ptr);
}

char	*ft_strchr(const char *str, int c)
{
	if (!str)
		return (NULL);
	while (*str != (char)c)
	{
		if (*str == '\0')
			return (NULL);
		str++;
	}
	return ((char *)str);
}

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	check_fd(t_list *list, int fd)
{
	int		i;

	i = 0;
	while (list->tail && i < list->num_of_node)
	{
		if (list->cur->fd == fd)
			return (1);
		list->before = list->cur;
		list->cur = list->cur->next;
		i++;
	}
	if (!make_node(list, fd))
	{
		free(list->cur);
		return (0);
	}
	return (1);
}

char	*remove_node(t_list *list, char *str)
{
	t_list_node		*dnode;

	dnode = list->cur;
	list->before->next = list->cur->next;
	if (list->tail == list->cur)
		list->tail = list->before;
	free(dnode);
	free(str);
	(list->num_of_node)--;
	if (list->num_of_node == 0)
		list->tail = NULL;
	else
		list->cur = list->before->next;
	return (NULL);
}
