/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarrero <rmarrero@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 23:07:54 by rmarrero          #+#    #+#             */
/*   Updated: 2024/10/08 12:06:41 by rmarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

t_list	*get_last_node(t_list *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

int	get_len(t_list *list)
{
	int	i;
	int	len;

	if (!list)
		return (0);
	len = 0;
	while (list)
	{
		i = 0;
		while (list->data_buffer[i])
		{
			if (list->data_buffer[i] == '\n')
				return (++len);
			++i;
			++len;
		}
		list = list->next;
	}
	return (len);
}

void	get_copy(t_list *list, char *line)
{
	int	i;
	int	j;

	if (!list)
		return ;
	j = 0;
	while (list)
	{
		i = 0;
		while (list->data_buffer[i])
		{
			if (list->data_buffer[i] == '\n')
			{
				line[j++] = '\n';
				line[j] = '\0';
				return ;
			}
			line[j++] = list->data_buffer[i++];
		}
		list = list->next;
	}
	line[j] = '\0';
}

int	find_new_line(t_list *list)
{
	int	i;

	if (!list)
		return (0);
	while (list)
	{
		i = 0;
		while (list->data_buffer[i] && i < BUFFER_SIZE)
		{
			if (list->data_buffer[i] == '\n')
				return (1);
			i++;
		}
		list = list->next;
	}
	return (0);
}

void	create_and_append(t_list **list, int fd)
{
	t_list	*new_node;
	t_list	*last_node;
	char	*buffer;
	int		bytes_read;

	while (!find_new_line(*list))
	{
		buffer = malloc(BUFFER_SIZE + 1);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (!(buffer) || bytes_read <= 0)
			return (free(buffer), (void)0);
		buffer[bytes_read] = '\0';
		new_node = malloc(sizeof(t_list));
		if (!(new_node))
			return ;
		new_node->data_buffer = buffer;
		new_node->next = NULL;
		if (!*list)
			*list = new_node;
		else
		{
			last_node = get_last_node(*list);
			last_node->next = new_node;
		}
	}
}