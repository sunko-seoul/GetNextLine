/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:26:16 by sunko             #+#    #+#             */
/*   Updated: 2023/03/25 23:13:05 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>

typedef struct s_node
{
	int				fd;
	char			save[BUFFER_SIZE + 1];
	struct s_node	*next;
}	t_list_node;

typedef struct s_list
{
	t_list_node	*cur;
	t_list_node	*before;
	t_list_node	*tail;
	int			num_of_node;
}	t_list;

size_t	ft_strlen(char *s);
char	*ft_strchr(const char *str, int c);
char	*ft_strjoin(t_list *list, char *tmp, char *buffer);
char	*get_next_line(int fd);
void	keep_save(t_list *list, char *rst);
char	*extract_line(t_list *list, char *str);
char	*include_enter(t_list *list);
int		make_node(t_list *list, int fd);
char	*remove_node(t_list *list, char *str);
int		check_fd(t_list *list, int fd);

#endif
