/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarrero <rmarrero@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 23:07:54 by rmarrero          #+#    #+#             */
/*   Updated: 2024/10/08 12:06:41 by rmarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static t_list	*list[4096];
	char			*line;

	if (BUFFER_SIZE < 0 || fd < 0)
		return (NULL);
	create_and_append(&list[fd], fd);
	line = malloc(get_len(list[fd]) + 1);
	if (!(list[fd]) || !(line))
		return (free(line), NULL);
	get_copy(list[fd], line);
	get_clear_remaining_data(&list[fd]);
	return (line);
}

void	get_clear_remaining_data(t_list **list)
{
	t_list	*last;
	t_list	*replace;
	char	*buffer;
	int		i;
	int		j;

	i = 0;
	j = 0;
	last = ft_lstlast(*list);
	if (!last)
		return ;
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return ;
	while (((char *)last->content)[i] && ((char *)last->content)[i] != '\n')
		++i;
	while (((char *)last->content)[i] && ((char *)last->content)[++i])
		buffer[j++] = ((char *)last->content)[i];
	buffer[j] = '\0';
	replace = ft_lstnew(buffer);
	if (!replace)
		return (free(buffer), (void)0);
	ft_lstclear(list, free);
	*list = replace;
}
