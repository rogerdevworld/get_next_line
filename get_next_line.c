/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarrero <rmarrero@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 21:11:16 by rmarrero          #+#    #+#             */
/*   Updated: 2024/11/04 17:08:51 by rmarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_list	*list;
	char			*line;

	line = NULL;
	if (BUFFER_SIZE < 0 || fd < 0)
		return (NULL);
	create_and_append(&list, fd);
	if (!list)
		return (NULL);
	line = malloc(get_len(list) + 1);
	if (!line)
		return (free(line), NULL);
	if (!(list) || !(line))
		return (free(line), NULL);
	get_copy(list, line);
	get_clear_remaining_data(&list);
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
/*
#include <stdio.h>


int	main(void)
{
	char	*str;
	int fd = open("file.txt", O_RDONLY);
	while (str)
	{
		str = get_next_line(fd);
		printf("line: %s\n", str);
		free(str);
	}
}*/
//comand > 
//gcc -o get_next_line main.c get_next_line.c get_next_line_utils.c -I./includes
