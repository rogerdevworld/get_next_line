/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarrero <rmarrero@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 21:11:16 by rmarrero          #+#    #+#             */
/*   Updated: 2024/10/12 17:13:36 by rmarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line_bonus.h"

void	get_clear_remaining_data(t_list **list);
void	create_and_append(t_list **list, int fd);
void	get_free_list(t_list **list, t_list *replace, char *buf);
int		find_new_line(t_list *list);

char	*get_next_line(int fd)
{
	static t_list	*list[4096];
	char			*line;

	line = NULL;
	if (BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	if (fd < 0 || fd > 4095 || read(fd, line, 0) < 0)
		return (NULL);
	create_and_append(list, fd);
	line = malloc(get_len(list[fd]) + 1);
	if (!(list[fd]) || !(line))
		return (free(line), NULL);
	get_copy(list[fd], line);
	get_clear_remaining_data(&list[fd]);
	return (line);
}

void	get_free_list(t_list **list, t_list *replace, char *buffer)
{
	t_list	*tmp;

	if (NULL == *list)
		return ;
	while (*list)
	{
		tmp = (*list)->next;
		free((*list)->data_buffer);
		free(*list);
		*list = tmp;
	}
	*list = NULL;
	if (replace->data_buffer[0])
		*list = replace;
	else
	{
		free(buffer);
		free(replace);
	}
}

void	get_clear_remaining_data(t_list **list)
{
	char	*buffer;
	t_list	*last;
	t_list	*replace;
	int		i;
	int		j;

	i = 0;
	j = 0;
	buffer = malloc(BUFFER_SIZE + 1);
	replace = malloc(sizeof(t_list));
	if (!(buffer) || !(replace))
		return ;
	last = get_last_node(*list);
	while (last->data_buffer[i] && last->data_buffer[i] != '\n')
		++i;
	while (last->data_buffer[i] && last->data_buffer[++i])
		buffer[j++] = last->data_buffer[i];
	buffer[j] = '\0';
	replace->data_buffer = buffer;
	replace->next = NULL;
	get_free_list(list, replace, buffer);
}
//comand > 
//gcc -o get_next_line main.c get_next_line.c get_next_line_utils.c -I./includes
