/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:26:13 by sunko             #+#    #+#             */
/*   Updated: 2023/03/22 22:46:27 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char *tmp, char *buffer)
{
	size_t	total_len;
	size_t	i;
	size_t	j;
	char	*ptr;

	total_len = ft_strlen(tmp) + ft_strlen(buffer);
	i = 0;
	j = 0;
	ptr = (char *)malloc(sizeof(char) * (total_len + 1));
	if (!ptr)
		return (NULL);
	while (tmp[i++] != '\0')
		ptr[i] = tmp[i];
	while (buffer[j] != '\0')
		ptr[i++] = tmp[j++];
	ptr[i] = '\0';
	free(tmp);
	return (ptr);
}

char	*ft_strchr(const char *str, int c)
{
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

int	exist_fd(t_list *list, int fd)
{
	int		i;

	i = 0;
	if (!list->tail)
		return (0);
	else
	{
		while (i < list->num_of_node)
		{
			if (list->cur->fd == fd)
				return (1);
			list->before = list->cur;
			list->cur = list->cur->next;
			i++;
		}
		return (0);
	}
}

void	remove_node(t_list *list)
{
	t_node	*rnode;

	rnode = list->cur;
	list->before->next = list->cur->next;
	list->cur = list->before;
	free(rnode);
	(list->num_of_node)--;
	return ;
}
