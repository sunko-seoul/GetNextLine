/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:26:11 by sunko             #+#    #+#             */
/*   Updated: 2023/03/24 13:56:26 by sunko            ###   ########.fr       */
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
	return (1);
}

char	*read_line(t_list *list)
{
	char	*buffer;
	char	*rst;
	int		flag;
	int		size;

	flag = 1;
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (remove_node(list, list->cur->save));
	while (flag)
	{
		size = read(list->cur->fd, buffer, BUFFER_SIZE);
		if (size == 0)
			flag = 0;
		buffer[size] = 0;
		list->cur->save = ft_strjoin(list, list->cur->save, buffer);
		if (ft_strchr(list->cur->save, '\n'))
			break ;
	}
	free(buffer);
	if (!list->cur->save)
		return (NULL);
	rst = extract_line(list);
	return (rst);
}

char	*extract_line(t_list *list)
{
	char	*tmp;
	char	*rst;
	size_t	i;
	int		j;
	int		k;

	i = 0;
	j = -1;
	k = -1;
	while (list->cur->save[i] != '\n')
		i++;
	rst = (char *)malloc(sizeof(char) * (i + 2));
	tmp = (char *)malloc(sizeof(char) * (ft_strlen(list->cur->save) - i));
	if (!rst || !tmp)
		return (NULL);
	while (++j <= (int)i)
		rst[j] = list->cur->save[j];
	rst[j] = 0;
	tmp[ft_strlen(list->cur->save) - i - 1] = 0;
	while (list->cur->save[++i] != 0)
		tmp[++k] = list->cur->save[i];
	free(list->cur->save);
	list->cur->save = tmp;
	return (rst);
}

char	*get_next_line(int fd)
{
	static t_list	list;
	char			*rst;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) == -1)
		return (NULL);
	if (!exist_fd(&list, fd))
		if (!make_node(&list, fd))
			return (NULL);
	if (!list.cur->save)
		list.cur->save = (char *)malloc(sizeof(char) * 1);
	rst = read_line(&list);
	if (!rst || !(*rst))
		return (remove_node(&list, list.cur->save));
	return (rst);
}

#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

int main(void)
{
    int fd;
    char *line;

    fd = open("test.txt", O_RDONLY);
    if (fd < 0)
    {
        printf("Failed to open file\n");
        return (1);
    }
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s\n", line);
        free(line);
    }
    close(fd);
    return (0);
}
