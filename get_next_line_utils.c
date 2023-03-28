/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:26:13 by sunko             #+#    #+#             */
/*   Updated: 2023/03/28 16:00:42 by sunko            ###   ########.fr       */
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
		return (ft_free(list, list->cur->save, rst));
	while (rst[++i] != '\0')
		ptr[i] = rst[i];
	while (buffer[++j] != '\0')
		ptr[i++] = buffer[j];
	ptr[i] = 0;
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

char	*ft_free(t_list *list, char *str1, char *str2)
{
	if (str1)
		free(str1);
	str1 = NULL;
	if (str2)
		free(str2);
	str2 = NULL;
	if (list)
	{
		free(list->cur);
		list->cur = NULL;
	}
	return (NULL);
}
